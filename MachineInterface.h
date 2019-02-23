/* Provides the basic k-armed-machine interface.
 *
 * wenliang liu
 * 2019-02-22
 * MTV
 */
#pragma once
#include <random>

template <typename Distribution>
class MachineInterface{
    public:
        // Reset arms, with random probability distribution.
        virtual void ResetArms(int k) = 0;
        // Reset arms, with random probability distribution.
        virtual void ResetArmsWithProb(std::vector<Distribution> dist) = 0;
        // Get a reward from an arm
        virtual double GetReward(int arm) = 0;
    private:
};

