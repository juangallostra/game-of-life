# game-of-life
C implementation of Conway's game of life for the subject of Embedded and Real time systems. The application runs on a terminal.
To test it open a terminal and type:
1. ```$ git clone https://github.com/juangallostra/game-of-life.git```
2. Navigate to the folder where the repository has been cloned
3. ```$ make```
4. ```$ .\game-of-life```

If everything went ok you should see a message in the terminal asking to choose a pattern from 1 to 3. Actually the supported patterns are:
* [R-pentomino](http://www.conwaylife.com/wiki/R-pentomino)
* [Diehard](http://www.conwaylife.com/wiki/Diehard)
* [Acorn](http://www.conwaylife.com/w/index.php?title=Acorn)

If you want to know more about Conway's game of life I suggest visiting the [wiki](http://www.conwaylife.com/wiki/Main_Page) page, reading the [wikipedia](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) entry and [Standford's](http://web.stanford.edu/~cdebs/GameOfLife/)
univeristy introduction.

## Requirements
* ```ncurses```

## About
The repository contains two main branches that have diverged too much to be merged again and hence can be considered as two different implementations.
* The branch ```master``` contains a straightforward approach where a matrix is used to store the current state of the system. At each iteration the full matrix is traversed and the system is evolved to its next state. 
* The branch ```state-storage-in-bits``` contains a more sofisticated approach that tries to be more memory efficient than the straightforward approach. This is the current state-of-the-art implementation in the repository. The readme on that branch contains more information about how it works.

Up to now there is no support for letting the user specify the initial condition of the system but on future releases this will be one of the first things to be implemented.
