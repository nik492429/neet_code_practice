#include <iostream>
#include <string>
#include <unordered_set>

int max_substring_length(std::string str)
{
    int left = 0;
    int right = 0;
    int max_substring_length = 0;

    std::unordered_set<char> hash_set;
    for(auto e : str)
    {
        if(hash_set.find(e) == hash_set.end())
        {
            hash_set.insert(e);
            right = right+1;
        }
        else
        {
            hash_set.erase(e);
            auto len = right-left;
            if(len>max_substring_length)
            {
                max_substring_length = len;
            }

            left = left+1;
            hash_set.insert(e);
            right = right+1;
        }
    }
    return max_substring_length;
}

int main()
{
    int len = max_substring_length(std::string("abcaefgha"));
    std::cout << "len = " << len << std::endl;
    return 0;
}


