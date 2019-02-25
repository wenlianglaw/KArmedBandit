# KArmBandit
### **\<<Reinforcement Learning\>> Chapter 3**
I'm reading \<<Reinforcement leraning\>> right now.  This program is made for learning porpuse.  

## Install and run
### MacOS
```make```

Run
```./karms --plot --sigma 2.5```
-\--plot option plots the average rewards of each agent.
-\--sigma sets the sigma of the normal distribution.

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
        std::random_device rd;
        std::mt19937 gen;
    public:
        RandomAgent(std::string &&name): AgentInterface<T>(std::forward<std::string&&>(name)) {
            gen = std::mt19937(rd());
        }

        int PullArm() override {
            // Do some logic and return selection.  Let's return a random selection.
            int selection = gen() % (AgentInterface<T>::testbed->GetArmsCount());

            // Operate testbed and pull arm.
            double reward = AgentInterface<T>::testbed->PullArm( this, selection );

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

The Agent makes decision on which arm to pull.  You may consider to implement your own algorithm for this process.

## Benchmarks (To be update) 

```

```


