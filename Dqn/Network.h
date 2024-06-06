#ifndef CONNECT6_AI_NETWORK_H
#define CONNECT6_AI_NETWORK_H

#include <torch/nn.h>

#include "FusedMBConv.h"


struct NNetImpl : torch::nn::Module
{
    NNetImpl()
    {
        register_module("layer1", layer1);
        register_module("layer2", l2);
        register_module("layer3", l3);
        register_module("layer4", l4);
        register_module("onebyone", onebyone);

        register_module("fc", fc);
        register_module("fc2", fc2);
    }
    torch::Tensor forward(torch::Tensor x)
    {
        int batch = x.size(0);
        x = layer1->forward(x);
        x = l2->forward(x);
        x = l3->forward(x);
        x = l4->forward(x);
        x = onebyone->forward(x);
        x = x.view({batch, 361 * 2});
        x = fc->forward(x);
        x = torch::nn::Tanh()->forward(x);
        x = fc2->forward(x);
        x = torch::nn::Tanh()->forward(x);
        return x.view({batch, 19, 19});
    }

    torch::nn::Sequential layer1{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(2, 64, 6).padding(3)),
        torch::nn::Sigmoid(),
    };
    torch::nn::Sequential l2{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(64, 64, 2)),
        torch::nn::Sigmoid(),
    };
    torch::nn::Sequential l3{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(64, 64, 3).padding(1)),
        torch::nn::Sigmoid(),
    };
    torch::nn::Sequential l4{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(64, 64, 3).padding(1)),
        torch::nn::Sigmoid(),
    };
    // FusedMBConv l2{64, 1, 3};
    // FusedMBConv l3{64, 4, 3};
    // FusedMBConv l4{64, 4, 3};
    torch::nn::Sequential onebyone{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(64, 2, 1)),
        torch::nn::Sigmoid(),
    };

    //
    torch::nn::Linear fc{361 * 2, 361 * 2};
    torch::nn::Linear fc2{361 * 2, 19 * 19};
};

TORCH_MODULE(NNet);

#endif // CONNECT6_AI_NETWORK_H
