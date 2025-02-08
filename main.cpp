#include "TestFunctions.h"
#include <iostream>

#define FAIL_IF(exp) if(exp) return 1
int main()
{
    test_init();
    FAIL_IF(!check_periodic_mov_avg());
    std::cout << "all tests passed";
    return 0;
}
