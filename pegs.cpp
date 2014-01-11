/** Roseline Okpara
*
* $Id: pegs.cpp,v 1.2 2013/05/08 03:20:37 rco5918 Exp rco5918 $
*
* $Log: pegs.cpp,v $
* Revision 1.2  2013/05/08 03:20:37  rco5918
* Finished.
*
* Revision 1.1  2013/05/08 02:26:03  rco5918
* Initial revision
*
*
**/

#include "pegs.h"
#include "Solver.h"
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

Pegs::Pegs(const int numPegs): _numPegs(numPegs*2+1){
   vector<int> init(_numPegs,0);
   vector<int> goal(_numPegs,0);
   for(int i = 0; i < numPegs; i++){
      init[i] = 1;
      init[_numPegs - 1 - i] = 2;
      goal[i] = 2;
      goal[_numPegs - 1 - i] = 1;
   }
   _theGoal = goal;
   _initState = init;
}

vector<vector<int> > Pegs::getChildren(vector<int> config){
   vector<vector<int> > kiddies;
   for(int i = 0; i < _numPegs; i++){
      //Check if no hole
      if(config[i] != 0){
         //Check going forwarda
         if((i+1) < _numPegs){
            //Check if there is a peg in front
            if(config[i+1] == 0){
               vector<int> temp = config;
               int num = config[i];
               temp[i] = 0;
               temp[i+1] = num;
               kiddies.push_back(temp);
            }
            //Check if we can jump over peg in front
            else if((i + 2) < _numPegs){
               if(config[i+2] == 0){
                  vector<int> temp = config;
                  int num = config[i];
                  temp[i] = 0;
                  temp[i+2] = num;
                  kiddies.push_back(temp);
               }
            }
         }
         //Going backwards
         if((i-1) > -1){
            if(config[i-1] == 0){
               vector<int> temp = config;
               int num = config[i];
               temp[i] = 0;
               temp[i-1] = num;
               kiddies.push_back(temp);
            }
            //Check if we can jump over peg behind us
            else if((i-2) > -1){
               if(config[i-2] == 0){
                  vector<int> temp = config;
                  int num = config[i];
                  temp[i] = 0;
                  temp[i-2] = num;
                  kiddies.push_back(temp);
               }
            }

         }
      }
   }

   return kiddies;
}

vector<int> Pegs::initState(){
   return _initState;
}

vector<int> Pegs::getGoal(){
   return _theGoal;
}

bool Pegs::isGoal(vector<int> config){
   return config == _theGoal;
}

void Pegs::printPath(stack<vector<int> > path){
   int size = path.size();
   if(size != 0){
      for(int i = 0; i < size; i++){
         cout<<"Step " << i << ":  ";
         for(int p = 0; p < _numPegs; p++){
            vector<int> config = path.top();
            if(config[p] == 0){
               cout<<". ";
            }
            else if(config[p] == 1){
               cout<<"R ";
            }
            else{
               cout<<"B ";
            }
         }
         path.pop();
         cout<<"\n\n";
      }
   }
   else{
      cout<< "No Solution Found."<<endl;
   }

}

int main(int argc, const char* argv[]){
   
   if(argc == 2){
      int num = atoi(argv[1]);
      if( num > 0){
         Pegs puz = Pegs(num);
         Solver<vector<int>, Pegs> solver(puz);
         stack<vector<int> > path = solver.solve();
         puz.printPath(path);
      }
      else{
         cerr<<"Input must be greater than 0 and an integer."<<endl;
      }
   }
   else{
      cout<<"Usage: ./pegs numPegs"<<endl;
   }

   return(0);
}
