#ifndef CONNECT6_AI_NETWORK_H
#define CONNECT6_AI_NETWORK_H

#include <torch/nn.h>

#include "../Game/Board.h"


struct NNetImpl : torch::nn::Module
{
    NNetImpl()
    {
        register_module("layer1", l1);
        register_module("layer2", l2);
        register_module("layer3", l3);
        register_module("layer4", l4);
        // register_module("layer5", l5);
        // register_module("layer6", l6);
        // register_module("layer7", l7);
        // register_module("layer8", l8);

        // register_module("layer5", l5);

        // register_module("layer3", l3);

        register_module("onebyone", onebyone);

        register_module("fc1", fc1);
        register_module("fc2", fc2);
        register_module("fc3", fc3);
        register_module("output", output);
    }

    torch::Tensor forward(torch::Tensor x)
    {
        int batch = x.size(0);
        x = l1->forward(x);
        x = l2->forward(x);

        x = l3->forward(x);
        x = l4->forward(x);
        // x = l5->forward(x);
        // x = l6->forward(x);
        // x = l7->forward(x);
        // x = l8->forward(x);

        x = onebyone->forward(x);

        x = x.view({batch, BOARD_SIZE * BOARD_SIZE * 8});

        x = fc1->forward(x);
        x = torch::nn::Tanh()->forward(x);

        x = fc2->forward(x);
        x = torch::nn::Tanh()->forward(x);

        x = fc3->forward(x);
        x = torch::nn::Tanh()->forward(x);

        x = output->forward(x);
        x = torch::nn::Tanh()->forward(x);
        return x.view({batch, BOARD_SIZE, BOARD_SIZE});
    }

    torch::nn::Sequential l1{torch::nn::Conv2d(torch::nn::Conv2dOptions(3, 32, 3).padding(1)), torch::nn::LeakyReLU()};
    torch::nn::Sequential l2{torch::nn::Conv2d(torch::nn::Conv2dOptions(32, 32, 3).padding(1)), torch::nn::LeakyReLU()};
    torch::nn::Sequential l3{torch::nn::Conv2d(torch::nn::Conv2dOptions(32, 32, 3).padding(1)), torch::nn::ReLU()};
    torch::nn::Sequential l4{torch::nn::Conv2d(torch::nn::Conv2dOptions(32, 32, 3).padding(1)), torch::nn::ReLU()};
    // torch::nn::Sequential l5{torch::nn::Conv2d(torch::nn::Conv2dOptions(32, 32, 3).padding(1)), torch::nn::ReLU()};
    // torch::nn::Sequential l6{torch::nn::Conv2d(torch::nn::Conv2dOptions(32, 32, 3).padding(1)), torch::nn::ReLU()};
    // torch::nn::Sequential l7{torch::nn::Conv2d(torch::nn::Conv2dOptions(32, 32, 3).padding(1)), torch::nn::ReLU()};
    // torch::nn::Sequential l8{torch::nn::Conv2d(torch::nn::Conv2dOptions(32, 32, 3).padding(1)), torch::nn::ReLU()};

    torch::nn::Sequential onebyone{torch::nn::Conv2d(torch::nn::Conv2dOptions(32, 8, 1)), torch::nn::ReLU(),};

    torch::nn::Linear fc1{BOARD_SIZE * BOARD_SIZE * 8, BOARD_SIZE * BOARD_SIZE * 8};
    torch::nn::Linear fc2{BOARD_SIZE * BOARD_SIZE * 8, BOARD_SIZE * BOARD_SIZE * 8};
    torch::nn::Linear fc3{BOARD_SIZE * BOARD_SIZE * 8, BOARD_SIZE * BOARD_SIZE * 8};
    torch::nn::Linear output{BOARD_SIZE * BOARD_SIZE * 8, BOARD_SIZE * BOARD_SIZE};
};

TORCH_MODULE(NNet);

#endif // CONNECT6_AI_NETWORK_H
