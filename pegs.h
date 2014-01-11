/** Roseline Okpara
*
* $Id: pegs.h,v 1.2 2013/05/08 03:20:37 rco5918 Exp rco5918 $
*
* $Log: pegs.h,v $
* Revision 1.2  2013/05/08 03:20:37  rco5918
* Finished.
*
* Revision 1.1  2013/05/08 02:26:03  rco5918
* Initial revision
*
*
**/

#ifndef _PEGS_H
#define _PEGS_H

#include "Solver.h"

using namespace std;

class Pegs {

public:
   /// Name: (constructor)
   /// Arguments: numPegs
   /// Description: Instantiates the pegs
   Pegs(const int numPegs);

   /// Name: (getChildren)
   /// Arguments: config
   /// Description: Generates children of given config
   vector<vector<int> > getChildren(vector<int> config);
   
   /// Name: (initState)
   /// Arguments:
   /// Description: returns init state
   vector<int> initState();
   
   /// Name: (isGoal)
   /// Arguments: config
   /// Description: returns if at goal config
   bool isGoal(vector<int> config);
   
   /// Name: (getGoal)
   /// Arguments:
   /// Description: returns goal config
   vector<int> getGoal();
   
   /// Name: (printPath)
   /// ArgumentS: path
   /// Description: Human readable output of path
   void printPath(stack<vector<int> > path);

private:

   ///Total num of place holders
   const int _numPegs;

   vector<int> _theGoal;
   vector<int> _initState;

};

#endif
