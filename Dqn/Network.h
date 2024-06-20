#ifndef CONNECT6_AI_NETWORK_H
#define CONNECT6_AI_NETWORK_H

#include <torch/nn.h>

#include "../Game/Board.h"
#include "FusedMBConv.h"


struct NNetImpl : torch::nn::Module
{
    NNetImpl()
    {
        register_module("layer1", l1);
        register_module("layer2", l2);
        // register_module("layer3", l3);
        // register_module("layer4", l4);
        // register_module("layer5", l5);
        // register_module("layer6", l6);

        // register_module("layer3", l3);
        // register_module("layer4", l4);
        register_module("onebyone", onebyone);

        register_module("fc", fc);
        register_module("fc2", fc2);
    }
    torch::Tensor forward(torch::Tensor x)
    {
        int batch = x.size(0);
        x = l1->forward(x);
        x = l2->forward(x);
        x = onebyone->forward(x);

        x = x.view({batch, BOARD_SIZE * BOARD_SIZE * 4});

        // x = l3->forward(x);
        // x = torch::nn::Tanh()->forward(x);
        // x = l4->forward(x);
        // x = torch::nn::Tanh()->forward(x);
        // x = l5->forward(x);
        // x = torch::nn::Tanh()->forward(x);
        // x = l6->forward(x);
        // x = torch::nn::Tanh()->forward(x);

        x = fc->forward(x);
        x = torch::nn::Tanh()->forward(x);
        x = fc2->forward(x);
        x = torch::nn::Tanh()->forward(x);
        return x.view({batch, BOARD_SIZE, BOARD_SIZE});
    }

    torch::nn::Sequential l1{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(2, 64, 3).padding(1)),
        torch::nn::Sigmoid(),
    };
    torch::nn::Sequential l2{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(64, 32, 3).padding(1)),
        torch::nn::Sigmoid(),
    };


    torch::nn::Sequential onebyone{
        torch::nn::Conv2d(torch::nn::Conv2dOptions(32, 4, 1)),
        torch::nn::Sigmoid(),
    };

    torch::nn::Linear fc{BOARD_SIZE * BOARD_SIZE * 4, BOARD_SIZE *BOARD_SIZE * 4};
    torch::nn::Linear fc2{BOARD_SIZE * BOARD_SIZE * 4, BOARD_SIZE *BOARD_SIZE};
};

TORCH_MODULE(NNet);

#endif // CONNECT6_AI_NETWORK_H
