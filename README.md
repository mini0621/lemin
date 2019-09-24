# lemin
42 project lemin
Graph projects


## description
Lemin is a graph/path project.
The program get a map of an ant nest and the number of ants from the standard input.
Then it will find the instruction to move all the ants from start node to the end node.
All the rooms can hold exactly one ant, and no two ants can stay or cross the room at the same time.
The ants will move one room to another by exactly one step.


## solution
Max flow algorithm, edmonds karp algorithm.

## requirements
gcc
### for visualizer
pkgconfig, sdl

## Usage
#### to run
```
./lemin < mapfile
```

#### map file
```
a map file is defined as 
# sharps are comments
nbr_of_ants   # number of ants
roomname x y   # room name and the coordinates
# double sharps are used to command the next room is either start node or end node
## start
startroom 1 1
## end
endroom 2 2
a-b  # connection between rooms
```

## example

## visualizer


## Author

[Misaki Nishimoto](https://github.com/mini0621)
[Sunca7](https://github.com/sunca7)
