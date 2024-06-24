#ifndef SQEXBLOCK_H
#define SQEXBLOCK_H
#include <torch/nn/module.h>
#include <torch/nn/modules/activation.h>
#include <torch/nn/modules/linear.h>

struct SqExImpl : torch::nn::Module
{
    torch::nn::Linear fc1;
    torch::nn::ReLU reLu;

    torch::nn::Linear fc2;
    torch::nn::Sigmoid sigmoid;

    SqExImpl(int inputCh, int exciteCh): fc1(torch::nn::Linear(torch::nn::LinearOptions{inputCh, exciteCh}.bias(false))),
                                         fc2(torch::nn::Linear(torch::nn::LinearOptions{exciteCh, inputCh}.bias(false)))

    {
        reLu = torch::nn::ReLU();
        sigmoid = torch::nn::Sigmoid();
        register_module("SEFC1", fc1);
        register_module("SEFC2", fc2);
    }

    torch::Tensor forward(torch::Tensor x)
    {
        int batchSize = x.size(0);
        int chNum = x.size(1);

        auto y = x.view({batchSize, chNum, -1}).mean(2);

        y = fc1->forward(y);
        y = reLu->forward(y);
        y = fc2->forward(y);
        y = sigmoid->forward(y);

        y = y.view({batchSize, chNum, 1, 1});

        x = mul(x, y);
        return x;
    }
};

TORCH_MODULE(SqEx);

#endif //SQEXBLOCK_H
