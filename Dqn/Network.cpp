#include "Network.h"
NNetImpl::NNetImpl()
{
    register_module("layer1", layer1);
    register_module("layer2", layer2);
    register_module("layer3", layer3);
    register_module("fc", fc);
    register_module("fc2", fc2);
}
torch::Tensor NNetImpl::forward(torch::Tensor x)
{
    x = layer1->forward(x);
    x = layer2->forward(x);
    x = layer3->forward(x);
    x = x.view({-1, 1600});
    x = fc->forward(x);
    x = torch::nn::Tanh()->forward(x);
    x = fc2->forward(x);
    x = torch::nn::Tanh()->forward(x);
    return x.view({-1, 19, 19});
}
