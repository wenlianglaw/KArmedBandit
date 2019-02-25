/* Implements Sample-Average agent.
 *
 * With eplison probability, it randomly choose an arm to pull.
 * If defined alpha, alpha must be a constant in (0,1), it will use alpha as step size.
 * Q(n+1) = Q(n) + alpha * ( R(n) - Q(n) )
 * Q(n+1) = Q(n) + 1/N * ( R(n) - Q(n) )
 */

#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <vector>
#include <functional>
#include <cmath>

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
        double epslion;
        double alpha;

    public:
        /***
         * Constructor
         *
         * With eplison probability, it randomly choose an arm to pull.
         * If defined alpha, alpha must be a constant in (0,1), it will use alpha as step size.
         * Q(n+1) = Q(n) + alpha * ( R(n) - Q(n) )
         * Q(n+1) = Q(n) + 1/N * ( R(n) - Q(n) )
         *
         * Args:
         *  _ep: eplison, double.
         *  _a: alpha, double
         */
        AgentSampleAverage(std::string &&name, double _ep = 0.0f, double _a = NAN):AgentInterface<T>(std::forward<std::string&&>(name)){
            epslion = _ep;
            alpha = _a;
        }
        /***
         * The algorithm 
         *
         **/
        int PullArm() override {
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

                estimation.erase( estimation.begin() );
                steps[selection.second]++;
                double reward = AgentInterface<T>::testbed->PullArm( this, selection.second );
                this->LogReward(reward);

                // Update new estimation
                // Use self defined nan or not
                if( std::isnan( alpha ) )
                    selection.first += 1.0 / steps[selection.second] * ( reward - selection.first );
                else
                    selection.first += 1.0 / alpha * ( reward - selection.first );
                estimation.insert(selection);

                return selection.second;
            }
        }

        void Init(Testbed<T> *t) override {
            AgentInterface<T>::Init(t);
            int n = t->GetArmsCount();
            for(int i=0;i<n;i++) estimation.insert({INT_MAX, i});
            steps.clear();
        }
};
