/************************************************************************
* CREATED TIME: 2016-9-4 18:03:09
* LAST MODIFIED TIME: 2016-9-4 18:03:09
* DESCRIPTION: 随机数生成器
* BY: 357688981@qq.com
************************************************************************/

#include <iostream>
#include <random>
#include <cstdlib>

class RandomHelper {
public:
    template<typename T>
    static inline T random_real(T min, T max) {
        std::uniform_real_distribution<T> dist(min, max);
        auto& mt = RandomHelper::getEngine();
        return dist(mt);
    }

    template<typename T>
    static inline T random_int(T min, T max) {
        std::uniform_int_distribution<T> dist(min, max);
        auto& mt = RandomHelper::getEngine();
        return dist(mt);
    }
private:
    static std::mt19937& getEngine();
};


std::mt19937& RandomHelper::getEngine() {
    static std::random_device seed_gen;
    static std::mt19937 engine(seed_gen());
    return engine;
}
/**
 * Returns a random value between `min` and `max`.
 */
template<typename T>
inline T random(T min, T max) {
    return RandomHelper::random_int<T>(min, max);
}

template<>
inline float random(float min, float max) {
    return RandomHelper::random_real(min, max);
}

template<>
inline long double random(long double min, long double max) {
    return RandomHelper::random_real(min, max);
}

template<>
inline double random(double min, double max) {
    return RandomHelper::random_real(min, max);
}

int main() {
    for (int i=0; i< 100; ++i) {
        std::cout << random(1, 9) << "\t";
    }
    std::cout << std::endl;

    for (int i=0; i< 100; ++i) {
        std::cout << random(1.0, 9.0) << "\t";
    }
    std::cout << std::endl;

    return 0;
}