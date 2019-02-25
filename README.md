# KArmBandit
### **\<<Reinforcement Learning\>> Chapter 3**
I'm reading \<<Reinforcement leraning\>> right now.  This program is made for learning porpuse.  

## Install and run
### MacOS
```make```

Use
```python plot_stats.py```
To plot the statistics.

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
With probability normal_distribution(mean = rand(0,50), sigma  3,5), greedy error set to 0.1, sample average always chooses the first arm, we have:
```
Pulling 2000 Times
 ----------------------------------------------------------------
|Rank |          Agent Name          | Total Score |Average Score|
 ----------------------------------------------------------------
|  1  |       Wl's greedy agent      | 91535.270116|  45.767635  |
 ----------------------------------------------------------------
|  2  | Wl's greedy agent with errors| 87200.817205|  43.600409  |
 ----------------------------------------------------------------
|  3  |   WL's sample average agent  | 73458.530909|  36.729265  |
 ----------------------------------------------------------------
|  4  |       WL's random agent      | 51615.799309|  25.807900  |
 ----------------------------------------------------------------
Test: 1
Pulling 2000 Times
 ----------------------------------------------------------------
|Rank |          Agent Name          | Total Score |Average Score|
 ----------------------------------------------------------------
|  1  |       Wl's greedy agent      | 92977.221577|  46.488611  |
 ----------------------------------------------------------------
|  2  | Wl's greedy agent with errors| 69056.155691|  34.528078  |
 ----------------------------------------------------------------
|  3  |       WL's random agent      | 37243.618161|  18.621809  |
 ----------------------------------------------------------------
|  4  |   WL's sample average agent  | 12977.684715|   6.488842  |
 ----------------------------------------------------------------
Test: 2
Pulling 2000 Times
 ----------------------------------------------------------------
|Rank |          Agent Name          | Total Score |Average Score|
 ----------------------------------------------------------------
|  1  |       Wl's greedy agent      | 89360.761641|  44.680381  |
 ----------------------------------------------------------------
|  2  | Wl's greedy agent with errors| 84941.764293|  42.470882  |
 ----------------------------------------------------------------
|  3  |   WL's sample average agent  | 53693.832216|  26.846916  |
 ----------------------------------------------------------------
|  4  |       WL's random agent      | 52730.113159|  26.365057  |
 ----------------------------------------------------------------
Test: 3
Pulling 2000 Times
 ----------------------------------------------------------------
|Rank |          Agent Name          | Total Score |Average Score|
 ----------------------------------------------------------------
|  1  |       Wl's greedy agent      | 91633.440329|  45.816720  |
 ----------------------------------------------------------------
|  2  | Wl's greedy agent with errors| 88709.463600|  44.354732  |
 ----------------------------------------------------------------
|  3  |   WL's sample average agent  | 78134.997069|  39.067499  |
 ----------------------------------------------------------------
|  4  |       WL's random agent      | 59088.426010|  29.544213  |
 ----------------------------------------------------------------
Test: 4
Pulling 2000 Times
 ----------------------------------------------------------------
|Rank |          Agent Name          | Total Score |Average Score|
 ----------------------------------------------------------------
|  1  |   WL's sample average agent  | 81041.915629|  40.520958  |
 ----------------------------------------------------------------
|  2  |       Wl's greedy agent      | 80947.731332|  40.473866  |
 ----------------------------------------------------------------
|  3  | Wl's greedy agent with errors| 76652.085223|  38.326043  |
 ----------------------------------------------------------------
|  4  |       WL's random agent      | 41491.962390|  20.745981  |
 ----------------------------------------------------------------
```


