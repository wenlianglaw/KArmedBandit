#pragma once
#include "AgentInterface.h"
#include <set>
#include <cmath>


template <typename T>
class UCBAgent : public AgentInterface<T>{
    private:
        // <estimation value, selection>
        using Key_t = std::pair<double, int>;
        // estimation updates the arm's value interately, estimation[i] indicates the ith arm's value. 
        std::vector<double> estimation;
        // UCB value calculated according to the UCB function.
        std::set<Key_t, std::greater<Key_t>> ucb;
        std::unordered_map<int, int> choose_cnt;
        int total_steps = 0;
        // this is a experience value
        double c = 2.0f;

    public:
        UCBAgent(  std::string &&name, double _c = 2.0f ): AgentInterface<T>(std::forward<std::string&&>(name)),
        c(_c){
        }

        virtual void Init(Testbed<T> *t) override{
            AgentInterface<T>::Init(t);
            choose_cnt.clear();
            total_steps = 0;
            int k = this->testbed->GetArmsCount();
            estimation = std::vector<double>(k, 0.0f);
            ucb.clear();
            for(int i=0; i<k; i++)
                ucb.insert({0.0f, i});
        }

        int PullArm() override {
            total_steps ++;

            // Select the arm with the highest UCB value.
            auto selection = ucb.begin()->second;

            // Pull arm.
            double reward = AgentInterface<T>::testbed->PullArm( this, selection);

            // Update estimation
            UpdateEstimations(selection, reward);

           return selection;
        }


    private:
        void UpdateEstimations(int selection, double reward){
            // update new estimation value
            choose_cnt[selection]++;
            estimation[selection] += 1.0 / choose_cnt[selection] * ( reward - estimation[selection]);

            // update ucb
            ucb.clear();
            for( size_t i=0; i < estimation.size(); i++){
                double ucb_value;
                if( choose_cnt[i] == 0 )
                    ucb_value = INT32_MAX;
                else
                    ucb_value = estimation[i] + c*std::sqrt( std::log(total_steps) / choose_cnt[i]);
                ucb.insert( {ucb_value,i} );
            }
        }

};
