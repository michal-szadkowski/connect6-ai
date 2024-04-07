#ifndef CONNECT6_AI_NETWORK_H
#define CONNECT6_AI_NETWORK_H

#include <torch/nn.h>

struct NNetImpl : torch::nn::Module {
    NNetImpl()
            : fc(1280, 800), fc2(800, 19 * 19) {
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
        x = x.view({-1, 1280});
        x = fc->forward(x);
        x = torch::nn::Tanh()->forward(x);
        x = fc2->forward(x);
        x = torch::nn::Tanh()->forward(x);
        return x.view({19, 19});
    }

    torch::nn::Sequential layer1{
            torch::nn::Conv2d(torch::nn::Conv2dOptions(1, 30, 6).stride(1).padding(3)),
            torch::nn::LeakyReLU(),
//            torch::nn::MaxPool2d(torch::nn::MaxPool2dOptions(2).stride(2))
    };
    torch::nn::Sequential layer2{
            torch::nn::Conv2d(torch::nn::Conv2dOptions(30, 30, 3).stride(1)),
            torch::nn::LeakyReLU(),
//            torch::nn::MaxPool2d(torch::nn::MaxPool2dOptions(2).stride(2))
    };

    torch::nn::Sequential layer3{
            torch::nn::Conv2d(torch::nn::Conv2dOptions(30, 20, 3).stride(1)),
            torch::nn::LeakyReLU(),
            torch::nn::MaxPool2d(torch::nn::MaxPool2dOptions(2).stride(2))
    };


    torch::nn::Linear fc;
    torch::nn::Linear fc2;
};

TORCH_MODULE(NNet);

#endif //CONNECT6_AI_NETWORK_H
