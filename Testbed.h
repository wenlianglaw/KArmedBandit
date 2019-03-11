/* Test and measure different agent's performance. */

#pragma once
#include <functional>
#include <random>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <array>

#include "./Machines/MachineInterface.h"
#include "./Agents/AgentInterface.h"

template <typename T> class AgentInterface;
template <typename T = std::normal_distribution<>>
class Testbed {
    private:
        // All agents
        std::unordered_set<AgentInterface<T>*> all_agents;
        // User - Total score Mapping
        std::unordered_map<AgentInterface<T>*, double> user_score;
        // User - Steps Mapping
        std::unordered_map<AgentInterface<T>*, int> user_steps;
        // Test machine, with probability
        MachineInterface *machine;
        // Test time out for each user, in seconds.
        int timeout;
        // Pulling time
        int pulling_times;
    public:
        Testbed(MachineInterface *m): machine(m){
            Init();
        }

        /***
         * Initialize
         */
        void Init(){
            timeout = 60;
            machine->Init();
            user_score.clear();
            user_steps.clear();
        }

        /***
         * Initialize an agent.
         */
        void InitAgent(AgentInterface<T>* agent){
            agent->Init(this);
            user_score[agent] = user_steps[agent] = 0;
        }

        /***
         * Get arm count of the testing k-armed-machine
         */
        inline int GetArmsCount() const{
            return machine->GetArmsCount();
        }

        /***
         * Register your agent.
         */
        void RegisterAgent( AgentInterface<T> *agent){
            if( all_agents.find( agent ) != all_agents.end() )
                throw(std::runtime_error("Same agent exists"));
            
            agent->Init(this);
            all_agents.insert(agent);
        }

        /***
         * Pull kth Arm and get a reward.
         *
         * Args:
         *  agent: From which agent.
         *  k: Pull kth arm.
         *
         * Return: kth arm's reward.
         */
        double PullArm( AgentInterface<T> *agent, int k ){
            double reward = machine->GetReward(k);
            user_steps[agent]++;
            user_score[agent] += reward;
            agent->LogReward(reward);
            return reward;
        }

        /***
         * Get Users Stats
         *
         * Args:
         *  username: user name to query.
         * Return:
         *  pair<double, int> --- < Average Reward, total test steps >
         */
        std::pair<double, int> GetUserStats( std::string username ){
            return {1.0, 1};
        }

        /***
         * Run all agents, pulling arms for pull_times times.
         *
         * Args:
         *  pull_times: For each agent, pulling pull_times times arms.
         */
        void RunAllAgents( int pull_times ){
            Init();
            pulling_times = pull_times;
            for ( auto agent : all_agents){
                InitAgent( agent );
                for( int i=0; i<pull_times; i++){
                    agent->PullArm();
                }
            }
        }

        /***
         * ------------------------------
         *| Name |  1st  |  2nd  |  3rd  |
         * ------------------------------
         *| ...  |  ...  |  ...  |  ...  |
         * ------------------------------
         *
         */
        void RunTournment( int tournament_times, int pull_times ){
            using namespace std;
            cout<<"Running tournment "<< tournament_times <<" times"<<endl;
            vector<string> row { "Name", "1st","2nd","3rd"};
            constexpr int diff_ranks = 3;
            vector<vector<string>> buffer;
            buffer.emplace_back(row);

            // Run tournments
            // Name the agents a number and we will use their assigned numbers later.
            unordered_map<AgentInterface<T>*, int> agent_no;
            int agent_cnt=0;
            for( auto agent : all_agents )
                agent_no[agent] = agent_cnt++;

            // Rank prep.  We are displaying diff_ranks different ranks.
            vector<array<int,diff_ranks>> rank(agent_cnt, array<int,diff_ranks>{0,0,0});
            
            // Run tournament.
            // for sorting
            std::vector<AgentInterface<T>*> sorted_agent;
            std::transform( all_agents.begin(), all_agents.end(), std::back_inserter(sorted_agent),
                    []( const auto& a ){ return a;});

            for( int i = 0; i < tournament_times; i++ ){
                RunAllAgents(pull_times);

                // Update rank.
                sort( sorted_agent.begin(), sorted_agent.end(), [&, this]( auto *agent1, auto *agent2){
                        return (this->user_score)[agent1] > (this->user_score)[agent2];
                        });
                for( int j=0; j < diff_ranks; j++)
                    rank[agent_no[sorted_agent[j]]][j]++;
            }

            // Sort and Display final rank table.
            sort( sorted_agent.begin(), sorted_agent.end(), [&]( auto *agent1, auto *agent2){
                    int no1(agent_no[agent1]), no2(agent_no[agent2]);
                    for(int j=0;j<diff_ranks;j++)
                        if(rank[no1][j]>rank[no2][j]) return true;
                        else if(rank[no1][j] < rank[no2][j]) return false;
                    return true;
                    });

            for ( auto agent : sorted_agent ){
                row.clear();
                row.emplace_back(agent->GetName());
                for( int j=0; j < diff_ranks; j++)
                    row.emplace_back(to_string(rank[agent_no[agent]][j]));
                buffer.emplace_back( row );
            }
            
            PrettyPrint( buffer );
        }


        /***
         * Write Logs for each agent to its own log file.
         * File name would be {agent_name}.
         */
        void LogAgentsData(){
            for( auto agent : all_agents )
                agent->LogDataToFile();
        }

        /***
         * After running tests, sort users by their performance and print to screen.
         *  ------------------------------------------------------
         * | Rank |  Agent Name  |  Total Score  |  Average Score |
         *  ------------------------------------------------------
         * |  1   |   ....       |    ......     |      ......    |
         *  ------------------------------------------------------
         */
        void SortAndPrintAgentRank(){
            using namespace std;
            // Sort
            std::vector<AgentInterface<T>*> sorted_agent;
            std::transform( all_agents.begin(), all_agents.end(), std::back_inserter(sorted_agent),
                    []( const auto& a ){ return a;});
            std::sort( sorted_agent.begin(), sorted_agent.end(), [&, this]( auto *agent1, auto *agent2){
                    return (this->user_score)[agent1] > (this->user_score)[agent2];
                    });

            // Data to be printed
            vector<vector<string>> buffer;
            vector<string> row;

            // Prepare header's data.
            row = {"Rank", "Agent Name", "Total Score", "Average Score"};
            buffer.emplace_back(row);
            
            // Prepare each row's data.
            int rank = 1;
            for(auto agent : sorted_agent ){
                row = { to_string(rank), agent->GetName(), to_string(user_score[agent]),
                    to_string(user_score[agent]/ user_steps[agent])};
                rank++;
                buffer.emplace_back(row);
            }
            cout<<"Pulling "<< pulling_times<<" Times"<<endl;
            PrettyPrint(buffer);
        }

    private:
        /***
         * Pretty print string.
         * Each column's width is adjusted by the string's length.  They are adjusted 
         * to make the maximum height minmum.
         */
        void PrettyPrint( const std::vector<std::vector<std::string>> &strs){
            // This number is randomly selected. It specifies a row's width
            int row_width = 80;
            auto best_layout = BestLayout( strs, row_width); 
            PrettyPrintHelper( strs, std::forward<std::vector<int>&&>(best_layout));
            std::cout<<" "<<std::string( row_width + strs[0].size() /* How many '|'s */, '-')<<std::endl;

        }

        void PrettyPrintHelper( const std::vector<std::vector<std::string>> &strs, std::vector<int> &&col_width ){
            for( auto str : strs ){
                PrettyPrintRow( str, std::forward<std::vector<int>&&>(col_width) );
            }
        }

        /***
         * Pretty print a row.
         *  ------------------------------------------------------
         * | Rank |  Agent Name  |  Total Score  |  Average Score |
         *  ------------------------------------------------------
         *
         * Args:
         *  strs:  The strs to be output.
         *  col_width:  Each string's width.
         *  center:  If enable, the word in the column will be centered.
         */
        void PrettyPrintRow( const std::vector<std::string> &strs, std::vector<int> &&col_width , bool center = true){
            using namespace std;
            // How many columns
            int n = strs.size();
            vector<int> i(n, 0),// indexs for each word
                len(n, 0);           // Length of each word
            for(int i=0;i<n;i++) len[i] = strs[i].size();

            // Row length
            int row_length = accumulate(col_width.begin(), col_width.end(), n);
            // Each string start index
            vector<int> section_end_index(n,col_width[0]+1);
            for(int i=1;i<n;i++) section_end_index[i] = section_end_index[i-1] + col_width[i] + 1;
            int curCursor = 0;
            int whichStr = 0;

            // While there are strings to output
            int toPrintCnt = n;
            string sepRow(row_length, '-');
            sepRow = ' ' + sepRow;
            cout<<sepRow<<endl;
            cout<<'|';
            while( toPrintCnt ){
                // cout<<curCursor;
                bool sectionEnd = false;
                for(int i=0;i<n-1 && not sectionEnd;i++) sectionEnd |= curCursor == section_end_index[i];
                sectionEnd |= curCursor == section_end_index.back();
                if(sectionEnd) cout<<'|';
                else{
                    if(curCursor >= section_end_index[whichStr]){
                        whichStr ++;
                    }
                    // center output in cells
                    if(center /* center enabled */
                            /* start of the column: If current cursor is the start of the first col or rest. */
                            and (curCursor == 0 or  (whichStr >= 1 and curCursor == section_end_index[whichStr-1] + 1))
                            /* left char's len < col len */
                            and col_width[whichStr] > strs[whichStr].size() - i[whichStr]){ 
                        int free_space = col_width[whichStr] - ( strs[whichStr].size() - i[whichStr] );
                        for(int i=0; i < free_space -  free_space  / 2; i++){
                            curCursor++;
                            cout<<' ';
                        }
                    }
                    if(i[whichStr] == len[whichStr]) cout<<' ';
                    else{
                        cout<<strs[whichStr][i[whichStr]];
                        i[whichStr]++;
                        // This string has been consumed.
                        if(i[whichStr] == len[whichStr]) toPrintCnt--;
                    }
                }
                // This row ends
                if(curCursor == row_length){
                    if( toPrintCnt ){
                        cout<<endl<<'|';
                        curCursor = 0;
                        whichStr = 0;
                    }
                }else{
                    curCursor++;
                }
            }
            // complete the unfinished row
            while( curCursor <= row_length ){
                bool sectionEnd = false;
                for(int i=0;i<n && not sectionEnd;i++) sectionEnd |= curCursor == section_end_index[i];
                sectionEnd |= curCursor == section_end_index.back();
                cout<< (sectionEnd?'|':' ');
                curCursor++;
            }
            cout<<endl;
        }

        /***
         * Calculate the best layout from the strs.
         *
         * This is a linear planning problem which finds a best width such that to make the highest column shortest.
         * We could try each height, we could verify if this height is available in O(1) time.  The minimum height is 1, 
         * the maximum possible height is max(strs.length).  Using binary search to find a minimum height in this range.
         *
         * Finding a best solution for all strings, we can just consider the longest string in each column, making it a
         * single row problem.
         *
         * Why do I need to implement this algorithm?  ----- Because of LOVE (BORING).
         *
         * Args:
         *  strs:  strs[i] is the ith row's data.
         *  rowWidth:  The row's width.  Fixed.
         *
         * Return:
         *  vector<int>:  each column's wdith
         */
        std::vector<int> BestLayout( std::vector<std::vector<std::string>> strs, int rowWidth){
            int m = strs.size();
            int n = strs[0].size();
            // Init as 1 for each col.
            std::vector<int> ret(n, 1);
            std::vector<int> len(n,-1);
            for(int i=0;i<n;i++) {
                for(int j=0;j<m;j++){
                    len[i] = std::max(len[i], (int)strs[j][i].size());
                }
            }
                
            std::vector<int> order(n,0);
            for(int i=0;i<n;i++) order[i] = i;

            // sort by length
            for (int i=0; i<n; i++){
                for(int j=i+1; j<n; j++)
                    if(len[order[i]] <len[order[j]]) std::swap(order[i], order[j]);
            }

            int lo = 1, hi = len[order[0]], mid = (lo+hi)/2;
            while( lo <= hi ){
                // mid is the height we are testing with 
                mid = (lo+hi) / 2;
                for(int i=0; i < n; i++)
                    ret[i] = (int)std::ceil(len[i]*1.0/mid); 
                // if this height is available, try to shrink the range
                int required_width_to_support_this_height = std::accumulate(ret.begin(), ret.end(), 0); 
                if( required_width_to_support_this_height <= rowWidth )
                    hi = mid - 1;
                else
                    lo = mid + 1;

                // We have some free spaces.  We need to assign it to the columns.
                // Actually we could assign it to any column.  These are free spaces.
                // I don't want to over-design here, just assign 1/2, 1/4, and 1/4 to the longest, 2nd longest
                // and 3rd longest oclumn.
                int freeSpaces = rowWidth - required_width_to_support_this_height;
                ret[order[0]] += freeSpaces - freeSpaces / 2;
                ret[order[1]] += freeSpaces/4;
                ret[order[2]] += freeSpaces/2 - freeSpaces/4;
            }
            return ret;
        }

};
