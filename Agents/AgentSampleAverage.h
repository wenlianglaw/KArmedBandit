/* Implements Sample-Average agent. */
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <vector>
#include <functional>


#include "AgentInterface.h"

template <typename T>
class AgentSampleAverage : public AgentInterface<T>{
    public:
    private:
      // <estimation, arm>
      using Key_t = std::pair<double, int>;
      std::set<Key_t, std::greater<Key_t>> estimation;
      // <arm, choosen times>
      std::unordered_map<int, int> steps;
     public:
        AgentSampleAverage(std::string &&name):AgentInterface<T>(std::forward<std::string&&>(name)){
        }
        /***
         * The algorithm 
         *
         **/
        int PullArm() override {
            auto selection = *estimation.begin();
            
            estimation.erase( estimation.begin() );
            steps[selection.second]++;
            double reward = AgentInterface<T>::testbed->PullArm( this, selection.second );
            this->LogReward(reward);

            // Update new estimation
            selection.first += 1.0 / steps[selection.second] * ( reward - selection.first );
            estimation.insert(selection);

            return selection.second;
        }

        void Init(Testbed<T> *t) override {
            AgentInterface<T>::Init(t);
            int n = t->GetArmsCount();
            for(int i=0;i<n;i++) estimation.insert({INT_MAX, i});
            steps.clear();

        }
};
