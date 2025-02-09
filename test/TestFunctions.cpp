#include <TestFunctions.h>
#include <iostream>
#include <ctime>
#include <random>

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

bool check_impulse_mov_avg()
{
    const int WINDOW_SIZE = 1 << (rand() % 7);
    std::vector<float> impulse(WINDOW_SIZE);
    impulse[WINDOW_SIZE - 1] = 1;
    std::vector<float> impulse_h;
    status ret = moving_average(impulse,impulse_h,WINDOW_SIZE);

    if(ret != completed)
    {
        return false;
    }

    float ret_data = 0;
    // Для ограничения фильтра по степеням 2 должно быть равенство по float.
    for(auto i: impulse_h)
    {
        if(i != static_cast<float>(1)/WINDOW_SIZE)
        {
            break;
        }
        ret_data+= i;
    }

    if(ret_data != 1)
    {
        return false;
    }
    std::cout << "Impulse test with window size " << WINDOW_SIZE << " passed" << "\n";
    return true;
}


void speed_test()
{
    std::vector<float> noise;

    {
        std::random_device rd{};
        int rand_seed = static_cast<int>(rand());
        std::mt19937 gen{rand_seed};
        const float mean = 0;
        const float deviation = 10;
        std::normal_distribution<float> d{mean,deviation};
        auto random_value = [&d, &gen]{ return d(gen); };

        const int samples = 1e5;
        noise.reserve(samples);
        while(noise.size() < samples)
        {
            noise.push_back(random_value());
        }
    }

    int window_size = 2;
    while(window_size <= 256)
    {
        std::vector<float> out_signal(noise.size());
        clock_t start = clock();
        status ret_status = moving_average(noise,out_signal,window_size);
        clock_t stop = clock();

        if(ret_status != completed)
        {
            std::cout << "Test fail:" << ret_status << std::endl;
            return;
        }

        double seconds = (double)(stop - start) / CLOCKS_PER_SEC;

        std::cout <<window_size << " " << noise.size()/seconds <<" samp/sec" << std::endl;
        window_size<<=1;
    }

    return;
}
