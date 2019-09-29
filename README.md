# Lem-in
42 project lemin
Graph projects


<img src="https://github.com/mini0621/lemin/blob/master/media/lemin.gif" width="80%">

## Description
Lemin is a graph/path project.  
The program get a map of an ant nest and the number of ants from the standard input.  
Then it will find the instruction to move all the ants from start node to the end node.  
All the rooms can hold exactly one ant, and no two ants can stay or cross the room at the same time.  
The ants will move one room to another by exactly one step.  


## Solution
Max flow algorithm, edmonds karp algorithm.  

## requirements
gcc   
  
####  visualizer
pkgconfig, sdl2, sdl2_image, sdl2_ttf  

## Usage
#### to run
```
make
./lemin < example.map
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
##### example map
```
# sending 10 ants from start to end
10
##start
start 8 8
##end
end 2 8
dead0 10 8
dead1 10 6
island 11 11
mid0   6 6
mid1   4 2
mid2   5 6
a 6 4
b 6 2
c 4 4
d 2 2
e 2 4
start-dead0
start-mid0
mid0-dead0
start-mid1
mid1-mid2
mid2-end
start-a
a-b
b-c
c-d
d-end
```
  
## visualizer
```
./lemin < example.map | ./visu
```
  
##### control
→ : next step
← : previous step
space : play
  
## Author

[Misaki Nishimoto](https://github.com/mini0621)  
[Sunca7](https://github.com/sunca7)
