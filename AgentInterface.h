/* Provid an AngentInterface. */
#pragma once
#include <fstream>
#include <string>

#include "MachineInterface.h"

template< typename D>
class AgentInterface{
    public:
        MachineInterface *machine;
    public:
        AgentInterface(MachineInterface *m):machine(m){}
        // Based on its strategy, select an arm to pull.
        virtual int PullArm() = 0;
        
        // Init state.
        virtual void Init() = 0;

        // Write step-avg_reward data to file.
        void WriteData(std::string filename) {
            std::ofstream out(filename, std::ofstream::out | std::ofstream::app);
            // TODO write dataw
            out.close();
        }
};
