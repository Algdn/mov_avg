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
    const int data_size = in_data.size();

    if(!data_size)
    {
        return in_data_empty;
    }

    if((window_size >= data_size) | (window_size < 1))
    {
        return window_size_invalid;
    }

    if(window_size == 1)
    {
        out_data = in_data;
        return completed;
    }

    if(out_data.size() < data_size)
    {
        out_data.resize(data_size);
    }

    // first step
    int step_offest = 0;
    int current_window_size = window_size;

    while(step_offest < data_size)
    {
        if(!step_offest)// first step
        {
            out_data[step_offest] = std::accumulate(in_data.begin(), in_data.begin() + window_size,0);
            step_offest++;
            continue;
        }

        out_data[step_offest] = out_data[step_offest - 1] - in_data[step_offest - 1];

        if((step_offest + window_size - 1) < data_size)
        {
            out_data[step_offest] += in_data[step_offest + window_size - 1];
        }

        step_offest++;
    }

    return completed;
}
#endif // MOVINGAVERAGE_H
