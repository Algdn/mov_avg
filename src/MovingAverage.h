#ifndef MOVINGAVERAGE_H
#define MOVINGAVERAGE_H

#include <vector>
#include <numeric>

typedef enum {
    completed,
    in_data_empty,
    window_size_invalid,
} status;


template <typename T>
status moving_average(const std::vector<T>&in_data, std::vector<T>&out_data, const int window_size)
{
    return completed;
}
#endif // MOVINGAVERAGE_H
