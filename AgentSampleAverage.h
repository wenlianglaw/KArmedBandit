/* Implements Sample-Average agent. */
#include "AgentInterface.h"
#include <string>
#include <fstream>
#include <vector>

template <typename D>
class AgentSampleAverage : public AgentInterface<D>{
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
        AgentSampleAverage(MachineInterface *m): AgentInterface<D>(m){
            Init();
        }

        /* The algorithm */
        // TODO
        int PullArm() override {
            return 0.0f;
        }

        void Init() override {
            totalAverage = totalRewards = totalStep = 0;
            averageReward.clear();
            // 2000 is a big-enough for our tests.
            averageReward.reserve(2000);
        }
};
