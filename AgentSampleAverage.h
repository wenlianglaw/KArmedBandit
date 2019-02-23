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

        double PullArm(int k) override {
            double ret =  AgentInterface<D>::machine->GetReward(k);
            totalRewards += ret;
            totalAverage = totalRewards / totalStep;
            averageReward.push_back(totalAverage);
            return ret;
        }

        /* The algorithm */
        // TODO
        double PullArm() override {
            return 0.0f;
        }

        void WriteData(std::string filename) override {
            std::ofstream out(filename, std::ofstream::out | std::ofstream::app);

            out.close();
        }

        void Init() override {
            totalAverage = totalRewards = totalStep = 0;
            averageReward.clear();
            // 2000 is a big-enough for our tests.
            averageReward.reserve(2000);
        }
};
