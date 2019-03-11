/* Gradient Bandit Agent */
#pragma once
#include <random>
#include <cmath>

#include "AgentInterface.h"

/* Pr{ A_t=a } = e^(H_t(a)) / sum{b=1_k}(e^(H_t(b))) = Prob_t(a)
 * H_(t+1)(A_t) = H_t(A_t) + alpha * (R_t - avg(R) )(a-Prob_t(A_t))
 * H_(t+1)(a) = H_t(a) + alpha * (avg(R) - R_t )(a-Prob_t(a))  for all a != A_t
 *
 * If reward is higher than the average reward, the probablity of taking this action is increased
 * in the future.  The Non taken actions move in the opposite way.
 *
 * where alpha > 0 is a step-size parameter.
 *
 * Init:  H(a) = 0 for all actions
 */
template <typename T>
class GradientBanditAgent : public AgentInterface<T>{
    private:
        std::vector<double> H;
        double sumOfEToH = 0.0f;
        int total_steps = 0;
        double total_reward = 0.0f;
        double alpha = 0.2f;

    public:
        GradientBanditAgent( std::string &&name, double _alpha ): AgentInterface<T>(std::forward<std::string>(name)){
            alpha = _alpha;
        }

        void Init( Testbed<T> *t) override {
            AgentInterface<T>::Init(t);

            H.clear();
            H = std::vector<double>(this->testbed->GetArmsCount(), 0.0f);

            sumOfEToH = std::accumulate( H.begin(), H.end(), 0.0f, [&](double a, double b){
                    return a + exp(b);});
            total_reward  = 0.0f;
            total_steps = 0;
        }

        int PullArm() override {
            int select = 0;
            total_steps++;
            // Pr(i) = e^H(i) / sumOfEToH
            double rand = std::uniform_real_distribution<double>(0,1)(this->gen);

            double sumOfPr = 0.0f;

            // When sumOfPr < rand <= sumOfPr + Pr(i), select i
            bool selected = false;
            for(int i=0; i < this->testbed->GetArmsCount() and not selected; i++){
                double prI = std::exp(H[i]) / sumOfEToH;
                if( sumOfPr < rand and rand <= sumOfPr + prI){
                    select = i;
                    selected = true;
                }
                sumOfPr += prI;
            }

            double reward = this->testbed->PullArm(this, select);
            UpdateH(reward, select);

            return select;
        }

    private:
        void UpdateH( double reward, int select ){
            double avg_reward = total_reward / total_steps;

            double newSumOfEToH = 0;
            for(int i=0; i < H.size(); i++){
                double prI = std::exp(H[i]) / sumOfEToH;
                if( i == select ){
                    H[i] += alpha * ( reward - avg_reward ) * ( 1 - prI );
                } else{
                    H[i] -= alpha * ( reward - avg_reward ) * prI;
                }
                newSumOfEToH += exp(H[i]);
            }

            sumOfEToH = newSumOfEToH;
            total_reward += reward;
        }
};
