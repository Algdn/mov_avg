#include "TestFunctions.h"
#include <iostream>

#define FAIL_IF(exp) if(exp) return 1
int main()
{
    test_init();
    int test_correct_tries = 50;
    while(test_correct_tries--)
    {
        FAIL_IF(!check_periodic_mov_avg());
        FAIL_IF(!check_impulse_mov_avg());
    }

    std::cout << "all tests passed\n";
    speed_test();
    return 0;
}
