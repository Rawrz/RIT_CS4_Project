/**Roseline Okpara, Andrew Clark
*
* $Id: Solver.h,v 1.3 2013/04/30 20:03:28 p334-01m Exp p334-01m $
*
* $Log: Solver.h,v $
* Revision 1.3  2013/04/30 20:03:28  p334-01m
* Reordered variables to get rid of some warnings.
*
* Revision 1.2  2013/04/30 04:32:45  p334-01m
* When pushing to stack: now pushing config.front() instead
* of puzzle.getGoal(). Works a lot better this way.
*
* Revision 1.1  2013/04/30 04:26:39  p334-01m
* Initial revision
*
* Revision 1.2  2013/04/16 22:38:42  p334-01m
* made new changes. Outputs correctly. Finished part 2
*
* Revision 1.1  2013/04/12 19:15:22  p334-01m
* Initial revision
*
*
**/
#ifndef _SOLVER_H
#define _SOLVER_H

#include <iostream>
#include <queue>
#include <map>
#include <stack>
#include <cstdlib>

//Template to accept any puzzle

using namespace std;

//Takes in the puzzle and the type of configurations
template <class P, class G>
class Solver{

private:
//Private members
queue<P> config;
map<P,P> memo;//Stores the child and parent
stack<P> path;
G puzzle;


public:
	//Constructor for the solver.
	Solver(G puz): config(), memo(),path(), puzzle(puz){}

	stack<P> solve(){
		//push initial configuration onto the queue
		config.push(puzzle.initState());
		//Also use map to keep track of parents and whatnot.
		memo.insert(pair<P,P>(puzzle.initState(),puzzle.initState())); //Store config in map as seen already.
		while(!config.empty() && !puzzle.isGoal(config.front())){
			P fConfig = config.front();//get children from config in front of queue
			config.pop();
			vector<P> kiddies = puzzle.getChildren(fConfig);
			//for each child, insert into the map with parent
			for(int i = 0; i < kiddies.size(); i++){ 
				//will only insert if child does not have a key value in map already (aka not seen)
				if(memo.insert(pair<P,P>(kiddies[i],fConfig)).second){
					config.push(kiddies[i]);
				}
			}
		}
		//If config was empty there was no solution
		if(!config.empty()){
			P temp = memo.at(config.front());
			//Create a stack for easy printing.
			path.push(config.front());//push the goal config
			while(temp != puzzle.initState()){
				path.push(temp);
				//Get it's parent and so on...till goal			
				temp = memo.at(temp);
			}
			//pushing in the games state
			path.push(puzzle.initState());
		}
		return path;
	}
};
#endif
