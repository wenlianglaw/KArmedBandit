/* Implements Sample-Average agent. */
#include <string>
#include <fstream>
#include <vector>

#include "AgentInterface.h"

template <typename T>
class AgentSampleAverage : public AgentInterface<T>{
    public:
    private:
        // Some history data.
        std::vector<double> rewardHistory;
        // Total average.
        double averageReward = 0.0f;
        double totalRewards = 0.0f;
        // Current step.
        int totalStep = 0;
    public:
        AgentSampleAverage(std::string &&name):AgentInterface<T>(std::forward<std::string&&>(name)){
        }
        /***
         * The algorithm 
         *
         **/
        int PullArm() override {
            int selection = 0;

            double reward = AgentInterface<T>::testbed->PullArm( this, selection);
            this->LogReward(reward);

            return selection;
        }

        void Init(Testbed<T> *t) override {
            AgentInterface<T>::Init(t);

            averageReward = totalRewards = totalStep = 0;
            rewardHistory.clear();
            // 2000 is a big-enough for our tests.
            rewardHistory.reserve(2000);
        }
};
