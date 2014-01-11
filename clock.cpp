/**Roseline Okpara, Andrew Clark
* 
* $Id: clock.cpp,v 1.2 2013/04/16 22:38:42 p334-01m Exp $
*
* $Log: clock.cpp,v $
* Revision 1.2  2013/04/16 22:38:42  p334-01m
* made new changes. Outputs correctly. Finished part 2
*
* Revision 1.1  2013/04/12 19:14:24  p334-01m
* Initial revision
*
*
*/

#include "clock.h"
#include "Solver.h"
#include <vector>
#include <stack>

using namespace std;

Clock::Clock(const int clkHours, int initTime, const int goalTime):
clkHours_(clkHours), initTime_(initTime),  theGoal(goalTime){

}

vector<int> Clock::getChildren(int curTime){
    vector<int> kiddies;
    //Clean way of incrementing time
    kiddies.push_back(max( (curTime + 1) % (clkHours_ + 1),1));
    //Push back when decrementing time
    if(curTime - 1 == 0) { //Can't be zero
        kiddies.push_back(clkHours_);
    }
    else{
        kiddies.push_back(curTime - 1);
    }
    return kiddies;
}

int Clock::initState(){
    return this->initTime_;
}

bool Clock::isGoal(int config){
    return (this->theGoal == config);
}

int Clock::getGoal(){
    return this->theGoal;
}

void Clock::printPath(stack<int> path){

    int size = path.size();
    //Print the stack. If empty, then no path was found 
    //and there is no solution
    if (size != 0){
        for (int i = 0; i < size; i++){
            cout << "Step " << i << ": " << "The clock was set to ";
            cout << path.top() << ":00" << endl;
            path.pop();
        }
    }
    else{
        cout << "No solution found." << endl;
    }
}

int main(int argc, char *argv[]){
    
    if (argc == 4){
        int hoursOnClock = atoi(argv[1]);
        int initTime = atoi(argv[2]);
        int goalTime = atoi(argv[3]);
        
        if (hoursOnClock > 0 && initTime > 0 && goalTime > 0){ 
            if(initTime <= hoursOnClock && goalTime <= hoursOnClock){
            
                Clock puz(hoursOnClock, initTime, goalTime);
                Solver<int, Clock> solver(puz);
                stack<int> path = solver.solve();
                puz.printPath(path);
        
            }
            else{
                cerr << "Error, initial time and goal time must be less ";
                cerr << "than or equal to the hours on the clock" << endl;
            }
        }
        else{
            cerr << "Invalid inputs. All inputs must be greater ";
            cerr <<    "than 0. " << endl;
        }
    }
    else{
        cerr << "Usage: ./clock hours start goal" << endl;
    }
    
    return(0);

}
    
