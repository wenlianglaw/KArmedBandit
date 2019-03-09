# KArmBandit
### **\<<Reinforcement Learning\>> Chapter 3**
I'm reading \<<Reinforcement leraning\>> right now.  This program is made for learning porpuse.  

## Install and run
### MacOS
**Make**  
```make```

Make sure you have ```Logs``` directory in the same folder.  If not, execute   
```mkdir Logs```  

**Run**   
```./karms --help```  

--plot option plots the average rewards of each agent.   
--sigma sets the sigma of the normal distribution.   

You may also run python script separatly to plot the sattstic.
```python plot_stats.py```

### Other platform
N/A.  Well welcome to conrtibute your own make file or solution file!  :)



## How to make your own agent?
Implement an Agent derived from AgentInterface and implement the **int PullArm()** function, that's it!  You have made an agent now.

I have created a simple agent RandomAgent, let's see how it looks:
```
/* Implements a random agent. */
#include <random>
#include "AgentInterface.h"

template<typename T>
class RandomAgent: public AgentInterface<T>{
    private:
    public:
        RandomAgent(std::string &&name): AgentInterface<T>(std::forward<std::string&&>(name)) {
        }

        int PullArm() override {
            // Do some logic and return selection.  Let's return a random selection.
            int selection = this->gen() % (AgentInterface<T>::testbed->GetArmsCount());

            // Operate testbed and pull arm.
            double reward = AgentInterface<T>::testbed->PullArm( this, selection );
            // To log reward for later plotting.
            this->LogReward(reward);

            return selection;
        }
};
```
You can access Testbed class from an Agent.   You may take a look into Testbed.h to see what functions you could access.  There are just few public function in that class.

## Structure of the program
We have
- AgentInterface
- Testbed
- MachineInterface

Testbed provides a testbed to test and run all the agents you have made.  It has a K Armed Mahine inside itself.  Bascially it will use the agents to pull the machine repeatedly and record how it performs.

The machine is a K Armed Machine.  It defines how many arms in there, and what's the yiedl function of each arm.  
The true value q∗(a) of each of the ten actions was selected according to a normal distribution with mean zero and unit variance, and then the actual rewards were selected according to a mean q∗(a) unit variance normal distribution

The Agent makes decision on which arm to pull.  You may consider to implement your own algorithm for this process.

## Benchmarks

```
./karms --tournament_times 1000
--help to display help infomation.
--plot to plot the statistic after running tests.
--sigma X to set normal distribution's sigma.  This parameter only works when mahcine uses Normal distribution
--pulltimes X to set test pulling times.
--tournament_times to set how many tournament will be runned.
sigma 1
Same agent exists
Running tournment 1000 times
 ------------------------------------------------------------------------------------
|                          Name                          |    1st    |    2nd    |3rd|
 ------------------------------------------------------------------------------------
|                      My UCB agent                      |    382    |    280    |198|
 ------------------------------------------------------------------------------------
|               WL's sample average agent                |    379    |    299    |214|
 ------------------------------------------------------------------------------------
|         WL's sample average agent with epslion         |    231    |    347    |308|
 ------------------------------------------------------------------------------------
|           WL's sample average with step size           |     5     |     41    |159|
 ------------------------------------------------------------------------------------
|                   WL's greedy agent                    |     3     |     27    | 91|
 ------------------------------------------------------------------------------------
|             WL's greedy agent with epslion             |     0     |     6     | 30|
 ------------------------------------------------------------------------------------
|                   WL's random agent                    |     0     |     0     | 0 |
 ------------------------------------------------------------------------------------
Thank you!


```

![alt text](https://github.com/wenlianglaw/KArmBandit/blob/master/Images/Sigma_1.0_1.png "benchmark_fig_sigma_1.0")

You could see in the early stage ghe agent with epslion performs well, however in the latter stage they are lower than the non-epslion agents, because the estimate rewards are stable after exploring sufficient times.
