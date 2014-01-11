RIT_CS4_Project
===============

A Generic Puzzle Solver

Objective
=========

The project has two main objectives:

 1. Create a Generalized Solver : The solver will perform a breadth-first search of a given problem space such that we will always reach out goal configuration with the shortest path. In this implementation, we use create a template such that any puzzle implementing the solver must provide the following:
    * An initial configuration
    * A function that can generate all the children (possible next configurations)
    * A function that determines whether or not a configuration is a goal configuration
 2. Implement various puzzles : Puzzles implement the required functionally stated above as well as provide an input

(The project spec can be found here:
[CS4 Projects page](http://www.cs.rit.edu/~cs4/Projects/ConfigPuzzles_123/writeup.html)).

Puzzles
=======

Clock
-----

usage: clock hours start end

./clock 15 3 6
 * Step 0: The clock was set to 3:00
 * Step 1: The clock was set to 4:00
 * Step 2: The clock was set to 5:00
 * Step 3: The clock was set to 6:00

./clock 10 6 5
 * Step 0: The clock was set to 6:00
 * Step 1: The clock was set to 5:00

./clock 100 98 101
Error, initial time and goal time must be less than or equal to the hours on 
the clock.

Hanoi
-----

usage: hanoi pegs pieces

    ./hanoi 1 1
    Step 0
    1
    -

    Step 1
    1
    -

    ./hanoi 2 3
    No solution found.

    ./hanoi 3 2
    Step 0
    1
    2
    - - -
    
    Step 1
    
    2 1
    - - -
    
    Step 2
    
     1 2
    - - -
    
    Step 3
       1
       2
    - - -


Parking Lot Jam
---------------
There are two arguments:

The name of the input file to read for the initial configuration data. If this name is "-" then the initial configuration data is read from the standard input.

The name of the output file where the solution is to be written. If this name is "-" then the solution is written to the standard output.

usage: inFile|- outFile|-

    ./jam jam1.in -
  
    Step 0
    
    * B B
    * * A
    C C A
    
    Step 1
    
    B B *
    * * A
    C C A
    
    Step 2
    
    B B A
    * * A
    C C *
    
    Step 3
    
    B B A
    * * A
    * C C
    
    ./jam - -
    6 6
    2
    5 5 5 0
    0 0 2 0
    
    no solution exists

Pegs
----

usage: pegs numPegs

    ./pegs 2
  	Step 0:  R R . B B
  
  	Step 1:  R . R B B
  
  	Step 2:  R B R . B
  
  	Step 3:  R B R B .
  
  	Step 4:  R B . B R
  
  	Step 5:  . B R B R
  
  	Step 6:  B . R B R
  
  	Step 7:  B B R . R
  
  	Step 8:  B B . R R
  
  	./pegs 1
  	Step 0:  R . B
  
  	Step 1:  . R B
  
  	Step 2:  B R .
  
  	Step 3:  B . R
