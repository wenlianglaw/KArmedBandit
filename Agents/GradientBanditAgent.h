/* Gradient Bandit Agent */
#pragma once
#include "AgentInterface.h"


template <typename T>
class GradientBanditAgent : public AgentInterface<T>{
    public:

    public:
        GradientBanditAgent( const std::string &name ): AgentInterface<T>(name){
        }
};
