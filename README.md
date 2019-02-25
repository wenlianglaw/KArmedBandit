# KArmBandit
### **\<<Reinforcement Learning\>> Chapter 3**
I'm reading \<<Reinforcement leraning\>> right now.  This program is made for learning porpuse.  

## Install and run
### MacOS
**Make**  
```make```

Run   
```./karms --plot --sigma 2.5```  

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
The true value q∗(a) of each of the ten actions was selected according to a normal distribution with mean zero and unit variance, and then the actual rewards were selected according to a mean q∗(a) unit variance normal distribution

The Agent makes decision on which arm to pull.  You may consider to implement your own algorithm for this process.

## Benchmarks (To be update) 

```
Using normal distribution with sigma: 1
sigma 1
Test: 0
Pulling 2000 Times
 ------------------------------------------------------------------------------------
|Rank |                  Agent Name                 |  Total Score  |  Average Score |
 ------------------------------------------------------------------------------------
|  1  |    WL's sample average agent with epslion   |  1541.485711  |    0.770743    |
 ------------------------------------------------------------------------------------
|  2  |              WL's greedy agent              |  1473.694417  |    0.736847    |
 ------------------------------------------------------------------------------------
|  3  |        WL's greedy agent with errors        |  1355.399004  |    0.677700    |
 ------------------------------------------------------------------------------------
|  4  |          WL's sample average agent          |  1336.776988  |    0.668388    |
 ------------------------------------------------------------------------------------
|  5  |              WL's random agent              |  1115.702940  |    0.557851    |
 ------------------------------------------------------------------------------------
Test: 1
Pulling 2000 Times
 ------------------------------------------------------------------------------------
|Rank |                  Agent Name                 |  Total Score  |  Average Score |
 ------------------------------------------------------------------------------------
|  1  |          WL's sample average agent          |  1534.492329  |    0.767246    |
 ------------------------------------------------------------------------------------
|  2  |              WL's greedy agent              |  1469.193770  |    0.734597    |
 ------------------------------------------------------------------------------------
|  3  |    WL's sample average agent with epslion   |  1389.232837  |    0.694616    |
 ------------------------------------------------------------------------------------
|  4  |        WL's greedy agent with errors        |  1191.656146  |    0.595828    |
 ------------------------------------------------------------------------------------
|  5  |              WL's random agent              |   649.747763  |    0.324874    |
 ------------------------------------------------------------------------------------
Test: 2
Pulling 2000 Times
 ------------------------------------------------------------------------------------
|Rank |                  Agent Name                 |  Total Score  |  Average Score |
 ------------------------------------------------------------------------------------
|  1  |          WL's sample average agent          |  1830.835518  |    0.915418    |
 ------------------------------------------------------------------------------------
|  2  |              WL's greedy agent              |  1145.849345  |    0.572925    |
 ------------------------------------------------------------------------------------
|  3  |    WL's sample average agent with epslion   |  1090.721249  |    0.545361    |
 ------------------------------------------------------------------------------------
|  4  |        WL's greedy agent with errors        |   905.293143  |    0.452647    |
 ------------------------------------------------------------------------------------
|  5  |              WL's random agent              |   714.772822  |    0.357386    |
 ------------------------------------------------------------------------------------
Test: 3
Pulling 2000 Times
 ------------------------------------------------------------------------------------
|Rank |                  Agent Name                 |  Total Score  |  Average Score |
 ------------------------------------------------------------------------------------
|  1  |          WL's sample average agent          |  1961.690738  |    0.980845    |
 ------------------------------------------------------------------------------------
|  2  |    WL's sample average agent with epslion   |  1747.437132  |    0.873719    |
 ------------------------------------------------------------------------------------
|  3  |              WL's greedy agent              |  1616.293984  |    0.808147    |
 ------------------------------------------------------------------------------------
|  4  |        WL's greedy agent with errors        |  1304.111207  |    0.652056    |
 ------------------------------------------------------------------------------------
|  5  |              WL's random agent              |  1090.141227  |    0.545071    |
 ------------------------------------------------------------------------------------
Test: 4
Pulling 2000 Times
 ------------------------------------------------------------------------------------
|Rank |                  Agent Name                 |  Total Score  |  Average Score |
 ------------------------------------------------------------------------------------
|  1  |          WL's sample average agent          |  1844.110368  |    0.922055    |
 ------------------------------------------------------------------------------------
|  2  |              WL's greedy agent              |  1505.967833  |    0.752984    |
 ------------------------------------------------------------------------------------
|  3  |    WL's sample average agent with epslion   |  1465.149732  |    0.732575    |
 ------------------------------------------------------------------------------------
|  4  |        WL's greedy agent with errors        |  1252.210399  |    0.626105    |
 ------------------------------------------------------------------------------------
|  5  |              WL's random agent              |   988.840844  |    0.494420    |
 ------------------------------------------------------------------------------------

```

![alt text](https://github.com/wenlianglaw/KArmBandit/blob/master/Images/Sigma_1.0_1.png "benchmark_fig_sigma_1.0")

You could see in the early stage ghe agent with epslion performs well, however in the latter stage they are lower than the non-epslion agents, because the estimate rewards are stable after exploring sufficient times.
