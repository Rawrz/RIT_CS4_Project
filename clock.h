/**Roseline Okpara, Andrew Clark
*
* $Id: clock.h,v 1.2 2013/04/16 22:38:42 p334-01m Exp $
*
* $Log: clock.h,v $
* Revision 1.2  2013/04/16 22:38:42  p334-01m
* made new changes. Outputs correctly. Finished part 2
*
* Revision 1.1  2013/04/12 19:14:24  p334-01m
* Initial revision
*
**/

#ifndef CLOCK_H
#define CLOCK_H

#include "Solver.h"

using namespace std;

class Clock {

public: 
    
  /// Name:    (constructor)
  /// Arguments: hours, inTime, goalTime
  /// Description: constructor for the class
  Clock(const int clkHours, int inTime, const int goalTime);
    
  /// Name:    (getChildren)
  /// Arguments: curState
  /// Description: Generates the configurations
  vector<int> getChildren(int curState);
    
  /// Name:    (initState)
  /// Arguments: none
  /// Description: Returns the initial time
  int initState();
    
  /// Name:    (isGoal)
  /// Arguments: none
  /// Description: If current time is goal time, returns true;
  ///               else returns false
  bool isGoal(int config);
    
  /// Name:    (getGoal)
  /// Arguments: none
  /// Description: Returns the goal time 
  int getGoal();
    
  /// Name:    (printPath)
  /// Arguments: path
  /// Description: Prints the path to standard output in human
  ///            readable form
  void printPath(stack<int> path);

private: ///private members
    
  const int clkHours_; //number of hours on the clock
  int initTime_; //initial time on our clock
  const int theGoal; // goal time       
};

#endif
