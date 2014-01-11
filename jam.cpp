/* Roseline Okpara, Andrew Clark
 * 
 * $Id: jam.cpp,v 1.7 2013/04/30 20:55:12 p334-01m Exp p334-01m $
 * 
 * $Log: jam.cpp,v $
 * Revision 1.7  2013/04/30 20:55:12  p334-01m
 * Now does valid board/car checking.
 *
 * Revision 1.6  2013/04/30 19:46:47  p334-01m
 * Added comments. Fixed funky printing. Weird indexing issues still persist.
 *
 * Revision 1.5  2013/04/30 14:58:26  p334-01m
 * Fixed no solution errors (Was not checking all children with else if's)
 * No longer segfaults with big problems.
 *
 * Revision 1.3  2013/04/30 04:09:41  p334-01m
 * No longer core dumps. Does not print out final path
 * for some reason.
 *
 * Revision 1.2  2013/04/29 19:45:25  p334-01m
 * Test board was print backwards and going out of bounds
 * Fixed the problem. Can now print a board.
 *
 * Revision 1.1  2013/04/29 19:43:38  p334-01m
 * Initial revision
 *
 *
 */

#include "Solver.h"
#include "jam.h"
#include <math.h>
#include <vector>
#include <stack>
#include <utility>
#include <iostream>
#include <ostream>
#include <fstream>

using namespace std; 

Jam::Jam(const int bWidth, const int bHeight, const int numCars,
   Board initBoard, ostream &out):
      bWidth_(bWidth),bHeight_(bHeight),numCars_(numCars),
      theBoard(initBoard), out_(out)   {
   if(!isLegalBoard(initBoard)){
      cerr<<"Invalid Board."<<endl;
      exit(0);
   }
   for(int i = 0; i < theBoard.size(); i++){
      int sX,eX;
      sX = theBoard[i][0].first;
      eX = theBoard[i][1].first;
      if(sX == eX){
         carOrient.push_back(VERT);
      }
      else{
         carOrient.push_back(HORIZ);
      }
   }
   out_ << endl;
}

vector<Board> Jam::getChildren(Board config){
      //cout<<bWidth_<< " " << numCars_<<endl;
   vector<Board> kiddies;
   MarkedBoard refBoard = markBoard(config);
   for(int i = 0; i < config.size(); i++){
      if(carOrient[i] == VERT){
         //check to see if can move car either way
         if(isCarMovable(config[i],refBoard,UP)){
            Board temp(config);
            temp[i][0].second--;
            temp[i][1].second--;
            kiddies.push_back(temp);
         }
         if(isCarMovable(config[i],refBoard,DOWN)){
            Board temp(config);
            temp[i][0].second++;
            temp[i][1].second++;
            kiddies.push_back(temp);
         }
      }
      else{ //its horizontal and can move up or down
         if(isCarMovable(config[i],refBoard,LEFT)){
            Board temp(config);
            temp[i][0].first--;
            temp[i][1].first--;
            kiddies.push_back(temp);
         }
         if(isCarMovable(config[i],refBoard,RIGHT)){
            Board temp(config);
            temp[i][0].first++;
            temp[i][1].first++;
            kiddies.push_back(temp);
         }
      }
   }
   return kiddies;
}

Board Jam::initState(){
   return theBoard;
}

bool Jam::isGoal(Board curConfig){
   //If last car's start x is at the end of boards width
   if((curConfig.back()[1].first == bWidth_ - 1) &&
      carOrient.back() == HORIZ){
      return true;
   }
   return false;
}

MarkedBoard Jam::markBoard(Board init){
   MarkedBoard marked(bHeight_,vector<int>(bWidth_,0));
   for(int i = 0; i < init.size(); i++){ //i+1 is car's corresponding number
      int len = 0; //length of current car
      if(carOrient[i] == HORIZ){
         //abs start x - end x
         len = init[i][0].first - init[i][1].first;
         if(len > 0){
            len = len + 1;
            for(int j = 0; j < len; j++){
               marked[init[i][0].second][init[i][0].first -j] = i + 1;
            }
         }
         else{
            len-=1;
            for(int j =0; j < abs(len); j++){
               marked[init[i][0].second][init[i][0].first + j] = i + 1;
            }
         }
      }
      else{
         // abs of start y - endy
         len = init[i][0].second - init[i][1].second;
         if(len > 0){
            len = len + 1;
            for(int j = 0; j < len; j++){
               marked[init[i][0].second - j ][init[i][0].first] = i + 1;
            }
         }
         else{
            len-=1;
            for(int j =0; j < abs(len); j++){
               marked[init[i][0].second + j][init[i][0].first] = i + 1;
            }
         }
      }
   }
   return marked;         
}

bool Jam::isLegalBoard(Board board){
   //Can't have more than 25 cars
   if(numCars_ > 25){
      return false;
   }
   for(int i = 0; i < board.size(); i++){
      Car car = board[i];
      //Check is is a valid car
      //Check if x and y values are not negative
      if(car[0].first < 0 || car[1].first < 0 ||
      		 car[0].second < 0 || car[1].second < 0){
         return false;
      }
      //Check if x and y values are greater than the size of the board
      if(car[0].first > bWidth_ - 1 || car[1].first > bWidth_ - 1 || 
      		car[0].second > bHeight_ - 1 || car[1].second > bHeight_ - 1){
         return false;
      }
      //Check for diagnols
      if(car[0].first != car[1].first && car[0].second != car[1].second){
         return false;
      }
      //Check for 1x1 square inputs
      if(car[0] == car[1]){
         return false;
      }
   }
   //We are okay!
   return true;
}

bool Jam::isCarMovable(Car car, MarkedBoard mBoard, int orient){
   //Check if move is out of bounds || check if space is occupied already
   if(orient == UP){
      if((car[0].second - 1 < 0) || 
      		(mBoard[car[0].second - 1][car[0].first] !=0)){
         return false;
      }
      return true;
   }
   else if(orient == DOWN){
      if((car[1].second + 1 > bHeight_ - 1) || 
      		(mBoard[car[1].second + 1][car[0].first] != 0)){
         return false;
      }
      return true;
   }
   else if(orient == LEFT){
      if((car[0].first - 1 < 0) || 
      		(mBoard[car[0].second][car[0].first - 1] != 0)){
         return false;
      }
      return true;
       
   }
   else if(orient == RIGHT){
      if((car[1].first + 1 > bWidth_ - 1) || 
      		(mBoard[car[0].second][car[1].first + 1] !=0)){
         return false;
      }
      return true;
      
   }
   return false;
}

void Jam::printPath(stack<Board> path){
   int size = path.size();
   char c = 'A'; //can increment char
   if(size != 0){
      for(int i = 0; i < size; i++){
         out_ <<"Step " << i << endl;
         out_ <<endl;
         Board temp = path.top();
         MarkedBoard blk = markBoard(temp);
         //loop through board
         for(int row = 0; row < blk.size(); row++){
            for(int col = 0; col < blk[row].size(); col++){
               if(blk[row][col] == 0){ //Nothing here
                  out_ << "* ";
               }
               else{
                  //Increment char by number in cell
                  out_ << (char)(c + blk[row][col] - 1) << " ";
               }
            }
            out_ <<endl;
         }
         path.pop();
         out_<<endl;
      }
   }
   else {
      out_ << "no solution exists" <<endl;
   }
}

int main(int argc, char* argv[]){
   ostream *oo(0);
   if(argc != 3){
      cerr << "Usage:./jam inputFile outputFile" <<endl;
      return -1;
   }
   
   istream *isp(0);
   ifstream ifs;
   ofstream ofs;

   if(argv[1][0] == '-' && argv[1][1] == '\0' ){
      isp = &cin;
   }
   else{
      ifs.open(argv[1] );
      isp = &ifs;
   }
   istream &is = *isp;

   if(argv[2][0] == '-' && argv[2][1] == '\0') {
      oo = &cout;
   }
   else{
      ofs.open(argv[2]);
      oo = &ofs;
   }
   ostream &os = *oo;
   //cout << "stream: " << *oo <<endl;
   int numRows, numCols, numCars;
   is >> numRows >> numCols >> numCars;
   Board init(numCars,Car (2,make_pair(-1,-1)));
   for(int i = 0; i < numCars; i++){
      for(int c = 0; c < 2; c++){
         int x,y;
         is >> x >> y;
         init[i][c] = make_pair(x,y);
      }
   }
   Jam puzzle(numRows,numCols,numCars,init,os);
   Solver<Board,Jam> solver(puzzle);
   stack<Board> path = solver.solve();
   puzzle.printPath(path);

}


   
