
#include "logger/logger.hpp"
#include <torch/torch.h>
#include <chrono>


int main() {
    Logger lg(logging::CONSOLE);
    if (!torch::cuda::is_available()) {
        lg.critical("CUDA unavailable");
        return 1;
    }

    int N = 4096;

    auto a = torch::rand({N, N}, torch::device(torch::kCUDA));
    auto b = torch::rand({N, N}, torch::device(torch::kCUDA));

    auto start = std::chrono::high_resolution_clock::now();

    auto c = torch::matmul(a, b);

    torch::cuda::synchronize();

    auto end = std::chrono::high_resolution_clock::now();

    lg.info(std::string("Elapsed: ") + std::to_string(std::chrono::duration<double>(end - start).count()) + std::string("s"));

    return 0;
}

