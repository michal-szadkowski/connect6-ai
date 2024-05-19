#ifndef CONNECT6_AI_NETWORK_H
#define CONNECT6_AI_NETWORK_H

#include <torch/nn.h>

struct NNetImpl : torch::nn::Module
{
    NNetImpl()
    {
        register_module("layer1", layer1);
        register_module("layer2", layer2);
        register_module("layer3", layer3);
        register_module("layer5", layer5);

        register_module("fc", fc);
        register_module("fc2", fc2);
    }
    torch::Tensor forward(torch::Tensor x)
    {
        x = layer1->forward(x);
        x = layer2->forward(x);
        x = layer3->forward(x);
        x = layer5->forward(x);
        x = x.view({-1, 1600});
        x = fc->forward(x);
        x = torch::nn::Tanh()->forward(x);
        x = fc2->forward(x);
        x = torch::nn::Tanh()->forward(x);
        return x.view({-1, 19, 19});
    }

    torch::nn::Sequential layer1{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(2, 64, 6).padding(3)),
        torch::nn::LeakyReLU(),
    };
    torch::nn::Sequential layer2{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(64, 64, 3).padding(1)),
        torch::nn::LeakyReLU(),
    };
    torch::nn::Sequential layer3{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(64, 64, 3).padding(1)),
        torch::nn::LeakyReLU(),
    };
    torch::nn::Sequential layer5{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(64, 4, 1)),
        torch::nn::LeakyReLU(),
    };


    torch::nn::Linear fc{1600, 722};
    torch::nn::Linear fc2{722, 19 * 19};
};

TORCH_MODULE(NNet);

#endif // CONNECT6_AI_NETWORK_H
