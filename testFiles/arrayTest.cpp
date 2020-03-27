#include <iostream>
#include <vector>

int main()
{
    int array[32] = {0};
    for (int i = 0; i < 32; ++i)
    {
        array[i] = i;
    }

    int count = 0;
    // int * i = &array[0];
    // for (i = array; i < &array[32]; i += 1)
    // {
    //     std::cout << *i << "\n";
    //     ++count;
    // }
    std::vector<int> vect;
    for (int i = 0; i < 32; ++i)
    {
        vect.push_back(i);
    }
    vect.shrink_to_fit();

    int * a = &vect[0];
    for (int i = 0; i < 32; i += 1)
    {
        std::cout << *(a + i) << "\n";
        ++count;
    }
    
    return 0;
}
