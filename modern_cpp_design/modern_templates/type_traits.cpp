// Question	Trait 
// Is it an integer?	      std::is_integral
// Is it a pointer?	          std::is_pointer
// Is it a class?	          std::is_class
// Is it an enum?	          std::is_enum
// Can it be copied?	      std::is_copy_constructible
// Can it be moved?	          std::is_move_constructible
// Is it trivially copyable?  std::is_trivially_copyable
// Are two types the same?	  std::is_same
// Does it inherit from another type?	std::is_base_of
// Transform a type?	remove_const, decay, remove_pointer


// Implement IsPointer

#include <iostream>
using namespace std;

template <typename T>
struct IsPointer {
    static constexpr bool value = false;
};

template <typename T>
struct IsPointer<T*> {
    static constexpr bool value = true;
};


//Implement RemovePointer

template <typename T>
struct RemovePointer {
    using type = T;
};

template <typename T>
struct RemovePointer<T*> {
    using type = T;
};
// Helper alias template for RemovePointer
template <typename T>
using RemovePointer_t = typename RemovePointer<T>::type;

int main() {
    cout << IsPointer<int>::value << endl;    // Output: 0
    cout << IsPointer<int*>::value << endl;   // Output: 1
    return 0;
}


