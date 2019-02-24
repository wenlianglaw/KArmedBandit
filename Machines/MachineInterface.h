/* Provides the basic k-armed-machine interface.
 *
 * 2019-02-22
 * MTV
 */
#pragma once
#include <random>

class MachineInterface{
    public:
        /***
         * Reset arms, with random probability distribution.
         */
        virtual void ResetArms(int k) = 0;
        /***
         * Reset arms, with random probability distribution.
         */
        virtual void ResetArms() { ResetArms(GetArmsCount());}
        // Get a reward from an arm
        virtual double GetReward(int arm) = 0;
        // Get arm count
        virtual int GetArmsCount() = 0;
    private:
};

