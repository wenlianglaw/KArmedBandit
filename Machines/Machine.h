/* Implements a basic Game interface. */
#pragma once
#include "MachineInterface.h"
#include <assert.h>
#include <vector>
#include <functional>

#include <iostream>
/* Only support uniform_real_distribution and normal_distribution */
template <typename Distribution>
class KArmMachine: public MachineInterface{
    private:
        std::random_device rd;
        std::mt19937 gen;
        
        std::function<Distribution (void)> dist_init_func;

    public:
        std::vector<Distribution> arms;
        KArmMachine(int k, std::function<Distribution (void)> _func ){
            gen = std::mt19937(rd());
            dist_init_func = _func;
            ResetArms(k);
        }

        void Init() override{
            ResetArms(GetArmsCount());
        }

        void ResetArms(int k ) override {
            arms.clear();
            arms.reserve(k);
            for(int i=0; i<k; i++)
                arms.push_back(dist_init_func());
        }

        double GetReward(int arm) override {
            return arms[arm](gen);
        }

        int GetArmsCount() override {
            return arms.size();
        }
};
