
#include "model/perceptron.hpp"



int main()
{
    Perceptron model({784, 384, 384, 384, 10});

    auto x = torch::randn({5000, 784});
    auto y = torch::randint(0, 10, {5000});

    model.fit(x, y);

    auto pred = model.predict(torch::randn({5, 784}));
    std::cout << pred << std::endl;

    return 0;
}

