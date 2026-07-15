
#include "model/perceptron.hpp"



Perceptron::Perceptron(std::vector<int64_t> sizes)
{
    device_ = torch::cuda::is_available() ? torch::kCUDA : torch::kCPU;

    layers_ = torch::nn::Sequential();
    for (size_t i = 0; i < sizes.size() - 1; ++i) {
        layers_->push_back(torch::nn::Linear(sizes[i], sizes[i + 1]));
        if (i < sizes.size() - 2) layers_->push_back(torch::nn::ReLU());
    }
    register_module("layers", layers_);
    to(device_);
}


torch::Tensor Perceptron::forward(torch::Tensor x)
{
    return layers_->forward(x.to(device_));
}


void Perceptron::fit(torch::Tensor inputs, torch::Tensor targets, int epochs, int batch, double lr)
{
    inputs = inputs.to(device_);
    targets = targets.to(device_);

    auto opt = torch::optim::Adam(parameters(), lr);
    auto loss_fn = torch::nn::CrossEntropyLoss();
    train();

    for (int e = 0; e < epochs; ++e) {
        float loss_sum = 0;
        int n = 0;
        auto idx = torch::randperm(inputs.size(0), device_);

        for (int i = 0; i < inputs.size(0); i += batch) {
            int end = std::min(i + batch, (int)inputs.size(0));
            auto x = inputs.index_select(0, idx.slice(0, i, end));
            auto y = targets.index_select(0, idx.slice(0, i, end));

            opt.zero_grad();
            auto loss = loss_fn(forward(x), y);
            loss.backward();
            opt.step();

            loss_sum += loss.item<float>();
            n++;
        }
        printf("Epoch %d/%d | Loss: %.4f\n", e + 1, epochs, loss_sum / n);
    }
}


torch::Tensor Perceptron::predict(torch::Tensor x)
{
    eval();
    torch::NoGradGuard g;
    return forward(x).argmax(1).cpu();
}

