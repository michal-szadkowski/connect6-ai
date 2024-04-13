#ifndef CONNECT6_AI_NETWORK_H
#define CONNECT6_AI_NETWORK_H

#include <torch/nn.h>

struct NNetImpl : torch::nn::Module {
    NNetImpl() {
        register_module("layer1", layer1);
        register_module("layer2", layer2);
        register_module("layer3", layer3);
        register_module("fc", fc);
        register_module("fc2", fc2);
    }

    torch::Tensor forward(torch::Tensor x) {
        x = layer1->forward(x);
        x = layer2->forward(x);
        x = layer3->forward(x);
        x = x.view({-1, 400});
        x = fc->forward(x);
        x = torch::nn::Tanh()->forward(x);
        x = fc2->forward(x);
        x = torch::nn::Tanh()->forward(x);
        return x.view({-1, 19, 19});
    }

    torch::nn::Sequential layer1{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(2, 64, 6).stride(1).padding(3)),
        torch::nn::LeakyReLU(),
        torch::nn::BatchNorm2d(64),

        //            torch::nn::MaxPool2d(torch::nn::MaxPool2dOptions(3).stride(3))

    };
    torch::nn::Sequential layer2{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(64, 64, 3).stride(1).padding(1)),
        torch::nn::LeakyReLU(),

        // torch::nn::MaxPool2d(torch::nn::MaxPool2dOptions(2).stride(2))
    };

    torch::nn::Sequential layer3{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(64, 1, 1).stride(1)),
        torch::nn::LeakyReLU(),
        //            torch::nn::MaxPool2d(torch::nn::MaxPool2dOptions(2).stride(2))
    };


    torch::nn::Linear fc{400, 600};
    torch::nn::Linear fc2{600, 19 * 19};
};

TORCH_MODULE(NNet);

#endif //CONNECT6_AI_NETWORK_H
