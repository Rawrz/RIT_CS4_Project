/**Roseline Okpara, Andrew Clark
*
* $Id: jam.h,v 1.1 2013/04/25
*
* $Log: jam.h,v $
* Revision 1.2  2013/04/30 04:09:41  p334-01m
* Fixed a some type problems.
*
* Revision 1.1  2013/04/29 19:43:38  p334-01m
* Initial revision
*
* Revision 1.1  2013/04/25
* Initial revision
*
**/

#ifndef JAM_H
#define JAM_H

#include "Solver.h"

using namespace std;

typedef vector<pair<int,int> > Car; ///Defines a car
typedef vector<vector<pair<int,int> > > Board; ///Defines a list of cars
typedef vector<vector<int> > MarkedBoard;///2D Vector for representing the board

class Jam {

    public: 
    
  /// Name:    (constructor)
  /// Arguments: bWidth, bHeight, numCars, carCoordinates
  /// Description:  
  Jam(const int bWidth, const int bHeight, const int numCars, 
  	Board initBoard, ostream &out);
    
  /// Name:    (getChildren)
  /// Arguments: curState
  /// Description: Generates the configurations
  vector <Board> getChildren(Board config);

  /// Name:    (isGoal)
  /// Arguments: curConfig
  /// Description: 
  ///               
  bool isGoal(Board curConfig);
 
  /// Name:    (isLegalBoard)
  /// Arguments: path
  /// Description:
  bool isLegalBoard(Board board);
    
  Board initState();
  /// Name:
  /// Arguments:
  /// Description:
  MarkedBoard markBoard(Board init);

  /// Name:    (isCarMoveable)
  /// Arguments: path
  /// Description:
  bool isCarMovable(Car car, MarkedBoard mBoard, int orient);

  /// Name:    (printPath)
  /// Arguments: path
  /// Description:
  void printPath(stack<Board> path);
   
  private: ///private members
    
  const int bWidth_; ///the board width
  const int bHeight_; /// the board height
  const int numCars_; /// the number of cars on the board

  Board theBoard; /// the board
  ostream &out_;
  vector<int> carOrient;
    
  enum CarOrientation { HORIZ = 1, VERT = 2 }; ///Orientations
  enum CarDirection { UP = 3, DOWN = 4, LEFT = 5, RIGHT = 6 }; ///Directions

          
};

#endif
