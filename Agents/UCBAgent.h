#pragma once
#include "AgentInterface.h"
#include <set>

template <typename T>
class UCBAgent : public AgentInterface<T>{
    private:
        using Key_t = std::pair<double, int>;
        std::set<Key_t, std::greater<Key_t>> estimation;
        std::unordered_map<int, int> choose_cnt;
        int current_steps = 0;
    public:
        UCBAgent(  std::string &&name ): AgentInterface<T>(std::forward<std::string&&>(name)){
        }

        virtual void Init(Testbed<T> *t) override{
            AgentInterface<T>::Init(t);
            choose_cnt.clear();
            current_steps = 0;
        }

        int PullArm() override {
            current_steps ++;
            auto selection = 0;
            // <arm, choosen times>


           return selection;
        }
};
