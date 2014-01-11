/** Roseline Okpara, Andrew Clark
*
* $Id: hanoi.cpp,v 1.2 2013/04/16 22:38:42 p334-01m Exp $
*
* $Log: hanoi.cpp,v $
* Revision 1.2  2013/04/16 22:38:42  p334-01m
* made new changes. Outputs correctly. Finished part 2
*
* Revision 1.1  2013/04/12 20:16:35  p334-01m
* Initial revision
*
*
*
*
**/

#include "hanoi.h"
#include "Solver.h"
#include <vector>
#include <stack>
#include <iostream>

using namespace std;
  
Hanoi::Hanoi(const int numPegs, const int numDisks):
numPegs_(numPegs), numDisks_(numDisks), theGoal_(), initState_(){
    
    // Create the pegs
    for(int i = 0; i < numPegs; i++){
        stack<int> temp1;
        //stack<int> temp2;
        theGoal_.push_back(temp1);
        initState_.push_back(temp1);
    }
    
    // Place the disks in order on the left most peg for the initial state. 
    //Place the disks in order on the right most peg for the goal state. 
    for(int i = numDisks; i > 0; i--){   
        theGoal_[numPegs-1].push(i);
        initState_[0].push(i);
    }
}
  
vector<vector<stack<int> > > Hanoi::getChildren(vector<stack<int> > config){
    vector<vector<stack<int> > > kiddies;
    for(int i = 0; i < config.size(); i++){
    	//If it's not an empty stack, get top and compare
        if(!config[i].empty()){
            int top = config[i].top();
	    //Go through stacks again and compare
            for(int j = 0; j < config.size(); j++){
                if(!config[j].empty()){
                    int num = config[j].top();
		    //Move on if top is larger that current stakcs top
                    if(num < top) {
                        continue;
                    }
                    else{
		    	//Copy vector, pop top and add push it to cur stack
                        vector<stack<int> > temp = config;
                        temp[i].pop();
                        temp[j].push(top);
                        kiddies.push_back(temp);
                    }
                }
                else{
                    vector<stack<int> > temp = config;
                    temp[i].pop();
                    temp[j].push(top);
                    kiddies.push_back(temp);
                }
            }
        }
        else{
            //move along
            continue;
        }
    }
    return kiddies;
}

vector<stack<int> > Hanoi::initState(){
    return initState_;
}

bool Hanoi::isGoal(vector<stack<int> > config){
    return (this->getGoal() == config);
}

vector<stack<int> > Hanoi::getGoal(){
    return theGoal_;
}

void Hanoi::printPath(stack<vector<stack<int> > > path){
    int size = path.size();
    //Keep track of amount of configs to pop off stack
    if(size != 0){
        for(int i = 0; i < size; i++){
            cout<<"Step " << i <<endl;
            cout << endl;
	    //We count number of disks to make printing more readable
            for(int d = numDisks_; d > 0; d--){
	    	//Go through number of pegs and print contents
                for(int p = 0; p <numPegs_; p++){
		    //Only print if on the same level
                    if(path.top()[p].size() == d){
                        cout<<path.top()[p].top()<< " ";
                        path.top()[p].pop();
                    }
                    else{
                        cout<< "  ";
                    }
                }
                cout << " "  << endl;
            }
                for(int j = 0; j < numPegs_; j++)
                {
                    cout << "- ";
                
                }
                cout << "\n\n";
                path.pop();
        }
    }
    else{
        cout << "No solution found." << endl;
    }
}

int main(int argc, const char* argv[]){
    
    if(argc == 3){
        
        const int nPegs = atoi(argv[1]); //number of pegs
        const int nDisks = atoi(argv[2]); //number of disks

        if(nPegs > 0 && nDisks > 0){
    
            Hanoi puz(nPegs,nDisks);
            Solver<vector<stack<int> >,Hanoi> solver(puz);
            stack<vector<stack<int> > > path = solver.solve();
            puz.printPath(path);

        } 
        else{

            cerr << "Invalid inputs. All inputs must be greater ";
            cerr <<    "than 0. " << endl;
        }
    } 
    else{
        
        cerr << "Usage: ./hanoi pegs disks" << endl;
    }

    return(0);
}




