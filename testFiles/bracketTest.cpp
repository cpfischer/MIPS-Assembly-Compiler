#include <iostream>

class Test
{
public:
    Test()
    {
        for (int i = 0; i < 32; ++i)
        {
            testArray[i] = 42;
        }
    }

    int & operator[](int i)
    {
        std::cout << "testArray: " << testArray[i] << '\n';
        return testArray[i];
    }

    int operator[](int i) const
    {
        return testArray[i];
    }
    
    
private:
    int testArray[32];
};

int main()
{
    Test h;
    std::cout << h[0];
    h[0] = 3;
    std::cout << " Change: " << h[0];
    return 0;
}
