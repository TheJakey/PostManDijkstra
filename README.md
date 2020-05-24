# PostManDijkstra

Implementation of Dijkstra algorithm for (I believe) custom problem. 

Idea is to send a letter to each city (node), while postman (edge) has time-schedule of when he lefts the town. Transfer cost is 0 (postman goes from city A to B and back in given times). Starting city (node) is always 1. 
Goal is to find quickest way to contact each node.

## Input 1
1         - number of maps

3 2       - number of cities and number of postmen

3 2 1     - City A and City B where postman 1 operates and number of departure times

20        - his departure time(s)

2 1 1     - another postman

20



## Output 1
20        - Time that's needed to contact all nodes

## Input 2
1

3 2

1 2 2

50 51

2 3 3

29 30 31

## Output 2
129
