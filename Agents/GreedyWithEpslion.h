/* Greedy agent with error epslion 
 *
 * With a probability epslion, it chooses random arm to pull.  Otherwise it chooses the greedy move.
 */
#pragma once
#include <random>
#include <algorithm>

#include "GreedyAgent.h"

template <typename T>
class GreedyWithEpslionAgent: public GreedyAgent<T>{
    private:
        double epslion = 0.1f;
        std::random_device rd;
        std::mt19937 gen;
    public:
        GreedyWithEpslionAgent(std::string &&name): GreedyAgent<T>(std::forward<std::string&&>(name)) { 
            gen = std::mt19937(rd());
        }

        GreedyWithEpslionAgent( std::string &&name, double _ep):
            GreedyWithEpslionAgent<T>(std::forward<std::string&&>(name)){
                epslion = _ep;
                gen = std::mt19937(rd());
            }

        virtual int PullArm() override{
            // With probility epslion, selection a random node.
            if( std::uniform_real_distribution<>(0.0f, 1.0f)(gen) < epslion ){
                // update a random arm's estimation
                int arm = gen() % (AgentInterface<T>::testbed->GetArmsCount());
                auto key = std::find_if(this->estimation.begin(), this->estimation.end(),
                        [&](auto key){ return key.second == arm; });
                auto selection = *key;
                this->estimation.erase(key);

                // Apply this selection
                double reward = AgentInterface<T>::testbed->PullArm( this, selection.second );
                this->LogReward(reward);

                // Update new estimation for this selection
                selection.first += 1.0 / this->steps[selection.second] * ( reward - selection.first );
                this->estimation.insert(selection);
                
                return selection.second;
            }
            else{
                return GreedyAgent<T>::PullArm();
            }
        }
};
