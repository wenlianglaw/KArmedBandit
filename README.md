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
Using normal distribution with sigma: 3.5
sigma 3.5
Test: 0
Pulling 1000 Times
 ----------------------------------------------------------------
|Rank |           Agent Name          | Total Score|Average Score|
 ----------------------------------------------------------------
|  1  |   WL's sample average agent   | 8592.378465|   8.592378  |
 ----------------------------------------------------------------
|  2  |       Wl's greedy agent       | 8327.543142|   8.327543  |
 ----------------------------------------------------------------
|  3  | Wl's greedy agent with errors | 7933.258749|   7.933259  |
 ----------------------------------------------------------------
Test: 1
Pulling 1000 Times
 ----------------------------------------------------------------
|Rank |           Agent Name          | Total Score|Average Score|
 ----------------------------------------------------------------
|  1  |   WL's sample average agent   | 9851.771634|   9.851772  |
 ----------------------------------------------------------------
|  2  |       Wl's greedy agent       | 9403.048222|   9.403048  |
 ----------------------------------------------------------------
|  3  | Wl's greedy agent with errors | 8491.471485|   8.491471  |
 ----------------------------------------------------------------
Test: 2
Pulling 1000 Times
 ----------------------------------------------------------------
|Rank |           Agent Name          | Total Score|Average Score|
 ----------------------------------------------------------------
|  1  |   WL's sample average agent   | 8115.678435|   8.115678  |
 ----------------------------------------------------------------
|  2  |       Wl's greedy agent       | 7557.027302|   7.557027  |
 ----------------------------------------------------------------
|  3  | Wl's greedy agent with errors | 6953.465828|   6.953466  |
 ----------------------------------------------------------------
Test: 3
Pulling 1000 Times
 ----------------------------------------------------------------
|Rank |           Agent Name          | Total Score|Average Score|
 ----------------------------------------------------------------
|  1  |   WL's sample average agent   | 9054.045176|   9.054045  |
 ----------------------------------------------------------------
|  2  |       Wl's greedy agent       | 7869.400590|   7.869401  |
 ----------------------------------------------------------------
|  3  | Wl's greedy agent with errors | 7658.553889|   7.658554  |
 ----------------------------------------------------------------
Test: 4
Pulling 1000 Times
 ----------------------------------------------------------------
|Rank |           Agent Name          | Total Score|Average Score|
 ----------------------------------------------------------------
|  1  |   WL's sample average agent   | 7962.415837|   7.962416  |
 ----------------------------------------------------------------
|  2  |       Wl's greedy agent       | 7156.451314|   7.156451  |
 ----------------------------------------------------------------
|  3  | Wl's greedy agent with errors | 6242.826272|   6.242826  |
 ----------------------------------------------------------------
```


![alt text](https://github.com/wenlianglaw/KArmBandit/blob/master/Images/Sigma_3.5.png "benchmark_fig_sigma_3.5")
