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
    protected:
        // <estimation, arm>
        using Key_t = std::pair<double, int>;
        std::set<Key_t, std::greater<Key_t>> estimation;

        double epslion = 0.1f;
    public:
        GreedyAgent(std::string &&name, double _ep = 0.0f): AgentInterface<T>(std::forward<std::string&&>(name)) {
            epslion = _ep;
        }

        void Init(Testbed<T> *t){
            AgentInterface<T>::Init(t);

            int n = t->GetArmsCount();
            for(int i=0;i<n;i++) estimation.insert({INT_MAX, i});
        }

        virtual int PullArm() override{
            // With probility epslion, selection a random node.
            if( std::uniform_real_distribution<>(0.0f, 1.0f)(this->gen) < epslion ){
                // Randomly select an arm
                int arm = this->gen() % (AgentInterface<T>::testbed->GetArmsCount());
                auto key = std::find_if(this->estimation.begin(), this->estimation.end(),
                        [&](auto key){ return key.second == arm; });
                auto selection = *key;
                this->estimation.erase(key);

                // Apply this selection
                double reward = AgentInterface<T>::testbed->PullArm( this, selection.second );
                this->LogReward(reward);

                // Update new estimation for this selection
                selection.first = reward;
                this->estimation.insert(selection);

                return selection.second;
            }
            else{
                auto selection = *estimation.begin();

                double reward = AgentInterface<T>::testbed->PullArm( this, selection.second );
                this->LogReward(reward);

                // Update new estimation
                estimation.erase( estimation.begin() );
                selection.first = reward;
                estimation.insert(selection);

                return selection.second;
            }
        }
    private:
};
