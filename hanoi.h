/** Roseline Okpara, Andrew Clark
*
* $Id: hanoi.h,v 1.3 2013/04/16 22:38:42 p334-01m Exp $
*
* $Log: hanoi.h,v $
* Revision 1.3  2013/04/16 22:38:42  p334-01m
* made new changes. Outputs correctly. Finished part 2
*
* Revision 1.2  2013/04/12 20:25:23  p334-01m
* Finished function Skeleton
*
* Revision 1.1  2013/04/12 20:16:35  p334-01m
* Initial revision
*
*
**/

#ifndef _HANOI_H
#define _HANOI_H

#include "Solver.h"

using namespace std;

class Hanoi {

public:

  /// Name:    (constructor)
  ///  Arguments: numPegs,  numDisks
  /// Description: Has two integer parameter: numPegs and numDisks. 
  ///	Instantiates two empty stacks for storage
  Hanoi(const int numPegs, const int numDisks);

  /// Name:    (getChildren)
  ///  Arguments: numPegs,  numDisks
  /// Description: Generates children of the give configuration
  vector<vector<stack<int> > > getChildren(vector<stack<int> > config);
  
  /// Name:    (initState)
  ///  Arguments: numPegs,  numDisks
  /// Description: Returns inital state
  vector<stack<int> > initState();

  /// Name:   (isGoal)
  ///  Arguments: config
  /// Description: returns if given configuration is goal config
  bool isGoal(vector<stack<int> > config);
  
  /// Name:    (getGoal)
  ///  Arguments: 
  /// Description: Returns the goal
  vector<stack<int> > getGoal();

  /// Name:   (printPath)
  ///  Arguments: path
  /// Description: Returns a human readable path to standard output.
  void printPath(stack<vector<stack<int> > > path);

private: //private members

  const int numPegs_;
  const int numDisks_;
  /// a vector of pegs with a stack of disks on each peg
  vector<stack<int> > theGoal_;
  vector<stack<int> > initState_; 

};

#endif
