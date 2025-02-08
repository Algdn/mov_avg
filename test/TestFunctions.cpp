#include <TestFunctions.h>
#include <iostream>
#include <ctime>

template <typename T> void vec_print(const std::vector<T>& vec){for(const auto& item:vec){std::cout<<item << " ";} std::cout<<std::endl;}

void test_init()
{
    srand(time(nullptr));
}

bool check_periodic_mov_avg()
{
    std::vector<int> signal;
    int window_size = 0;
    if(!create_chainsaw_signal(signal,window_size) | !window_size)
    {
        return false;
    }

    std::vector<int> signal_filtered;
    signal_filtered.reserve(signal.size());

    status ret_status = moving_average(signal, signal_filtered, window_size);
    if(ret_status != completed)
    {
        return false;
    }

    signal_filtered.resize(signal_filtered.size() - window_size + 1);

    for(int sample: signal_filtered) {
        if(sample)
        {
            return false;
        }
    }

    std::cout << "Test with window size " << window_size << " passed" << "\n";
    return true;
}

bool create_chainsaw_signal(std::vector<int>& chainsaw, int& window)
{
    const int WINDOW_SIZE = (rand()%256)+2;
    std::vector<int> signal_pattern;
    signal_pattern.reserve(WINDOW_SIZE);

    for(int i = -WINDOW_SIZE/2; i !=0; i++)
    {
        signal_pattern.push_back(i);
    }

    if(WINDOW_SIZE % 2)
    {
       signal_pattern.push_back(0);
    }

    for(int i = 1; i <= WINDOW_SIZE/2; i++)
    {
        signal_pattern.push_back(i);
    }

    if(signal_pattern.size() != WINDOW_SIZE)
    {
        return false;
    }

    if(std::accumulate(signal_pattern.begin(), signal_pattern.begin() + WINDOW_SIZE,0))
    {
        return false;
    }

    int REPEATS = 10;
    chainsaw.clear();
    chainsaw.reserve(WINDOW_SIZE);

    while (REPEATS--) {
        chainsaw.insert(chainsaw.begin(),signal_pattern.begin(),signal_pattern.end());
    }

    window = WINDOW_SIZE;
    return true;
}
