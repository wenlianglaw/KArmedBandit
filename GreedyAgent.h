/* A greedy agent.
 * 
 * Always the choose the highest estimation selection.
 */ 
#pragma once
#include <set>
#include <unordered_map>
#include <vector>
#include <functional>

#include "AgentInterface.h"

template <typename T>
class GreedyAgent : public AgentInterface<T>{
    private:
        // <estimation, arm>
        using Key_t = std::pair<double, int>;
        std::set<Key_t, std::greater<Key_t>> estimation;
        // <arm, choosen times>
        std::unordered_map<int, int> steps;
    public:
        GreedyAgent(std::string &&name): AgentInterface<T>(std::forward<std::string&&>(name)) {
        }

        void Init(Testbed<T> *t){
            AgentInterface<T>::Init(t);

            int n = t->GetArmsCount();
            for(int i=0;i<n;i++) estimation.insert({INT_MAX, i});
            steps.clear();
        }

        int PullArm() override{
            auto selection = *estimation.begin();
            
            estimation.erase( estimation.begin() );
            steps[selection.second]++;
            double reward = AgentInterface<T>::testbed->PullArm( this, selection.second );

            // Update new estimation
            selection.first += 1.0 / steps[selection.second] * ( reward - selection.first );
            estimation.insert(selection);

            return selection.second;
        }
    private:
};
