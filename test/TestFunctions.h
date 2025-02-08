#ifndef TESTFUNCTIONS_H
#define TESTFUNCTIONS_H

#include "MovingAverage.h"

void test_init();
// Тест валидности работы функции скользящего среднего

bool check_periodic_mov_avg();

// Вспомогательные тестовые функции
bool create_chainsaw_signal(std::vector<int>& chainsaw, int& window);

#endif // TESTFUNCTIONS_H
