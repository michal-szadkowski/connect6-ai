#ifndef CONNECT6_AI_NETWORK_H
#define CONNECT6_AI_NETWORK_H

#include <torch/nn.h>

/**
 * Definition of libtorch based network
 */
struct NNetImpl : torch::nn::Module
{
    /**
     * Registers submodules of network
     */
    NNetImpl();

    /**
     * Propagates input tensor
     * @param x 4D tensor where 1st dim is sample, 2nd dim is channel, last 2 dim are board
     * @return 3D policy evaluation where 1st dim is sample
     */
    torch::Tensor forward(torch::Tensor x);

    torch::nn::Sequential layer1{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(2, 64, 6).stride(1).padding(3)),
        torch::nn::LeakyReLU(),
        torch::nn::BatchNorm2d(64),
    };
    torch::nn::Sequential layer2{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(64, 64, 3).stride(1).padding(1)),
        torch::nn::LeakyReLU(),
    };

    torch::nn::Sequential layer3{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(64, 4, 3).stride(1).padding(1)), torch::nn::LeakyReLU()
        // torch::nn::MaxPool2d(torch::nn::MaxPool2dOptions(2).stride(2))
    };


    torch::nn::Linear fc{1600, 800};
    torch::nn::Linear fc2{800, 19 * 19};
};

TORCH_MODULE(NNet);

#endif // CONNECT6_AI_NETWORK_H
