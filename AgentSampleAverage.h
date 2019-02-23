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
        std::vector<double> averageReward;
        // Total average.
        double totalAverage = 0.0f;
        double totalRewards = 0.0f;
        // Current step.
        int totalStep = 0;
    public:
        AgentSampleAverage(std::string &&name):AgentInterface<T>(std::forward<std::string&&>(name)){
        }
        /* The algorithm */
        // TODO
        int PullArm() override {
            int selection = 0;
            AgentInterface<T>::testbed->PullArm(this, selection);
            return 0;
        }

        void Init(Testbed<T> *t) override {
            AgentInterface<T>::Init(t);

            totalAverage = totalRewards = totalStep = 0;
            averageReward.clear();
            // 2000 is a big-enough for our tests.
            averageReward.reserve(2000);
        }
};
