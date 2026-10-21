#include <cstddef>
#include <cstdint>
#include <iostream>
#include <new>

// Single-threaded, first-fit free-list allocator over a fixed-size arena.
class Allocator
{
public:
    explicit Allocator(size_t arenaSize)
        : m_arenaSize(arenaSize)
    {
        m_arena = static_cast<std::byte*>(::operator new(arenaSize));
        auto* head = reinterpret_cast<Block*>(m_arena);
        head->size = arenaSize - sizeof(Block);
        head->free = true;
        head->next = nullptr;
        m_freeList = head;
    }

    ~Allocator()
    {
        ::operator delete(m_arena);
    }

    Allocator(const Allocator&) = delete;
    Allocator& operator=(const Allocator&) = delete;

    void* Allocate(size_t size)
    {
        size = AlignUp(size, alignof(std::max_align_t));

        Block* prev = nullptr;
        for(Block* block = m_freeList; block != nullptr; block = block->next)
        {
            if(block->free && block->size >= size)
            {
                SplitBlock(block, size);
                block->free = false;
                return reinterpret_cast<std::byte*>(block) + sizeof(Block);
            }
            prev = block;
        }
        (void)prev;
        return nullptr; // arena exhausted
    }

    void Free(void* ptr)
    {
        if(ptr == nullptr)
        {
            return;
        }
        auto* block = reinterpret_cast<Block*>(static_cast<std::byte*>(ptr) - sizeof(Block));
        block->free = true;
        CoalesceWithNext(block);
        CoalesceWithPrevious(block);
    }

private:
    struct Block
    {
        size_t size;
        bool free;
        Block* next; // singly-linked list ordered by address
    };

    static size_t AlignUp(size_t size, size_t alignment)
    {
        return (size + alignment - 1) & ~(alignment - 1);
    }

    // Carves a used-size chunk off the front of block, leaving the remainder free.
    void SplitBlock(Block* block, size_t size)
    {
        const size_t remaining = block->size - size;
        if(remaining <= sizeof(Block))
        {
            return; // remainder too small to host another block, keep as-is
        }

        auto* newBlock = reinterpret_cast<Block*>(
            reinterpret_cast<std::byte*>(block) + sizeof(Block) + size);
        newBlock->size = remaining - sizeof(Block);
        newBlock->free = true;
        newBlock->next = block->next;

        block->size = size;
        block->next = newBlock;
    }

    void CoalesceWithNext(Block* block)
    {
        while(block->next != nullptr && block->next->free)
        {
            Block* next = block->next;
            block->size += sizeof(Block) + next->size;
            block->next = next->next;
        }
    }

    void CoalesceWithPrevious(Block* block)
    {
        for(Block* prev = m_freeList; prev != nullptr; prev = prev->next)
        {
            if(prev->next == block && prev->free)
            {
                prev->size += sizeof(Block) + block->size;
                prev->next = block->next;
                return;
            }
        }
    }

    std::byte* m_arena = nullptr;
    size_t m_arenaSize = 0;
    Block* m_freeList = nullptr;
};

int main()
{
    Allocator allocator(1024);

    void* a = allocator.Allocate(64);
    void* b = allocator.Allocate(128);
    void* c = allocator.Allocate(32);

    std::cout << "a=" << a << " b=" << b << " c=" << c << std::endl;

    allocator.Free(b);
    void* d = allocator.Allocate(64); // should reuse coalesced space from b

    std::cout << "d=" << d << std::endl;

    allocator.Free(a);
    allocator.Free(c);
    allocator.Free(d);

    return 0;
}
