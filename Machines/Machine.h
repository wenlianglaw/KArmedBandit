/* Implements a basic Game interface. */
#pragma once
#include "MachineInterface.h"
#include <assert.h>
#include <vector>

/* Only support uniform_real_distribution and normal_distribution */
template <typename Distribution>
class KArmMachine: public MachineInterface{
    private:
        std::random_device rd;
        std::mt19937 gen;
        Distribution dist;
        double sigma;

        static constexpr bool isUniformDistribution = std::is_same<Distribution,
                         std::uniform_real_distribution<>>();
    public:
        std::vector<Distribution> arms;
        KArmMachine(int k, double _sigma = 1.0f){
            gen = std::mt19937(rd());
            ResetArms(k);
            sigma = _sigma;
        }


        void Init() override{
            ResetArms(GetArmsCount());
        }

        void ResetArms(int k) override {
            arms.clear();
            arms.reserve(k);
            if(isUniformDistribution){
                // This number is a random choose.  We focus on algorithm.
                const int range = 200;
                for(int i=0;i<k;i++){
                    int min, max;
                    do{
                        min  = gen()%range, max = gen()%range;
                    }while(min == max);
                    if(min > max) std::swap(min,max);
                    min -= range/2, max-=range/2;

                    arms.push_back(Distribution(min,max));
                }
            }
            else{
                for(int i=0;i<k;i++){
                    double mean = std::uniform_real_distribution<>(0, 1)(gen);
                    arms.push_back(Distribution(mean, sigma));
                }
            }
        }

        double GetReward(int arm) override {
            return arms[arm](gen);
        }

        int GetArmsCount() override {
            return arms.size();
        }
};
