#include <cstdlib>

class SimUtil
{
public:
    static constexpr double cG = 0.00000667;
    static float DrawRandom (float min, float max) {
        return (min + ((max - min) * (std::rand() % 1001) / 1000.0f));
    }
};
