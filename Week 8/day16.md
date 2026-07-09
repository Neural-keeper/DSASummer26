# Session 16

Thursday July 9th, 2026 - Session 16 - Graphs (Part II)

Attendance Form Link: [Session 16 - Peer Leading](https://forms.cloud.microsoft/r/HKPGVtz8zL)

Github repo link: [DSA Summer 26](https://github.com/Neural-keeper/DSASummer26)

---

### Plan
The plan is to start with Dijkstra's Algorithm and then go back to Prim's and Kruskal's, since they weren't given enough time (in my opinion) last session. Hopefully, we'll have enough time to see bfs and dfs in practice as well. 

---

# Dijkstra's Algorithm
Navigate to `dijkstra.cpp` for the code for this algorithm. 

This is an algorithm that finds the shortest path from a starting node to every other node in the graph. It finds use in things like Google Maps or entity pathfinding in video games. The guy who made it thought it up when on a date, and removed all the complexities because he didn't have a pen and paper (the lesson here is, try to find the simplest scenario first in all problems). 

To do this, it keeps the distances to other nodes in a min-priority-queue (a min heap), which is a queue that keeps the minimum value at the front. We'll use the STL Priority Queue included when we call `#include <queue>` to do this. 

It starts with the given starting node set to have distance 0 and added to the priority queue. Inside a while loop that runs as long as there are entries in the priority queue, it removes the first element and stores it as visited. It checks this node's neighbors and adds the distance + node entry to the priority queue, and notes these distances to these nodes in another distances array. It keeps doing this until everything has been visited or there's nothing left in the priority queue. 

Something to note here is the concept of `relaxation`, which refers to fixing the distances stored in the distances array if a new shorter path is found. We'll illustrate this on the tablet. 

---

# Practice
Navigate to `day16.cpp` to see the answer we got.

## Number of Islands
You're given an m x n 2D grid of '1's (land) and '0's (lava). You must return the number of islands. An island is surrounded by lava and is formed by connecting adjacent lands horizontally or vertically.
(This 2d grid being a graph is actually really nice, because you know each node has 2, 3 or 4 neighbors)


