#ifndef FUSEDMBCONV_H
#define FUSEDMBCONV_H
#include <torch/torch.h>


struct FusedMBConvImpl : torch::nn::Module
{
    explicit FusedMBConvImpl(int ch, int expansion, int kernel)
    {
        int expanded = ch * expansion;

        inner = torch::nn::Sequential{
            torch::nn::Conv2d(torch::nn::Conv2dOptions(ch, expanded, kernel).padding(kernel / 2)),
            torch::nn::BatchNorm2d(expanded),
            torch::nn::ReLU(),
            torch::nn::Conv2d(torch::nn::Conv2dOptions(expanded, ch, 1)),
            torch::nn::BatchNorm2d(expanded),
        };

        register_module("fmbInner", inner);
    }

    torch::Tensor forward(torch::Tensor x)
    {
        auto res = x;
        x = inner->forward(x);
        x += res;
        x = torch::nn::ReLU6()->forward(x);
        return x;
    }
    torch::nn::Sequential inner;
};
TORCH_MODULE(FusedMBConv);

#endif // FUSEDMBCONV_H
