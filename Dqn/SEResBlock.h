#ifndef SERESBLOCK_H
#define SERESBLOCK_H
#include <torch/nn/module.h>
#include <torch/nn/pimpl.h>
#include <torch/nn/modules/conv.h>

#include "SqExBlock.h"


struct SEResBlockImpl : torch::nn::Module
{
    torch::nn::Conv2d conv1;
    torch::nn::Conv2d conv2;
    SqEx sqex;
    torch::nn::ReLU reLu;

    SEResBlockImpl(int filters, int seChannels): conv1(torch::nn::Conv2d(torch::nn::Conv2dOptions{filters, filters, 3}.padding(1))),
                                                 conv2(torch::nn::Conv2d(torch::nn::Conv2dOptions{filters, filters, 3}.padding(1))),
                                                 sqex(SqEx(filters, seChannels))

    {
        register_module("SqResBlockConv1", conv1);
        register_module("SqResBlockConv2", conv2);
        register_module("SqResBlockSE", sqex);
    }

    torch::Tensor forward(torch::Tensor x)
    {
        auto y = conv1->forward(x);
        y = conv2->forward(y);
        y = sqex->forward(y);
        y = x + y;
        y = reLu->forward(y);
        return y;
    }
};

TORCH_MODULE(SEResBlock);

#endif //SERESBLOCK_H
