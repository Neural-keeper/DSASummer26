# Session 15
Tuesday July 7th, 2026 - Session 15 - Graphs

Attendance Form Link: [Session 15 - Peer Leading](https://forms.cloud.microsoft/r/HpWVEPra1r)

Github repo link: [DSA Summer 26](https://github.com/Neural-keeper/DSASummer26)

You might be wondering: Why a markdown file? It's because I wanted to separate all the code files, and explain the distribution here. Why? Because day 13 has almost 600 lines of code, and I personally find that overwhelming and hard to navigate.
Also, we have a lot to cover, so I probably won't be doing any live coding, but I'll show some live traces of the code and explain it line by line. Since we'll be going faster this session, please interrupt me or send a message if you have a doubt. 

---

# Step One
Graphs: We'll implement three types of graphs. We're using V - Vertices, and E - Edges. 

## Adjacency Matrix
Navigate to `adjmat.cpp` for the code.

A 2d matrix of all the vertices as source vertices along the rows, and destination vertices along the columns. Tracks edge weights at positions. This is great for dense graphs, where you have to look up whether an edge exists often. 

## Adjacency List
Navigate to `adjlist.cpp` for the code.

A list of vertices, each with their own list of adjacent vertices (can mention edge weights as well). Pretty much the default choice. It's perfect for standard traversals (DFS and BFS), and sparse graphs (this refers to when there's far fewer edges than the possible number of edges (V^2)). It's also great for anything that cares about a list of its neighbors a lot. 

## Edge List
Navigate to `edgelist.cpp` for the code.

Likely the simplest form of graph implementations. It's what its name suggests: a list of edges. This is particularly useful for Kruskal's where you only care about the edges themselves as objects, and don't care about the structural whole.

---

# Step Two
Minimum Spanning Tree algorithms.

## Prim's Algorithm
"local greedy"

Grows a single connected tree outward from an arbitrary seed node, expanding like a localized ink blot. At any given point in mid-execution, your chosen lines always form a single, valid, connected tree structure. 

It relies on an Adjacency List and a Priority Queue (Min-Heap). It constantly tracks all edges leaving your visited tree zone into the outside world, instantly grabbing the cheapest option available in O(logE) time. 

Complexity: O(ElogV) time and O(V + E).

## Kruskal's Algorithm
"puzzle"

Disregards your position entirely. It views the graph globally as a giant bucket of disconnected paths. It grabs the absolute cheapest edges on the entire map first, allowing independent "islands" of nodes to form across the graph, which eventually snap together into a complete tree at the very end.

It relies on an Edge List and a Disjoint Set Union (DSU / Union-Find) class. It sorts all global edges upfront by weight. The DSU acts as a fast component registry, allowing the loop to verify if adding an edge will connect separate islands or cause a closed loop (cycle) in near O(1) time.

Complexity: O(ElogE) time (dominated by the sorting step) and O(V + E) space.

---

# Step Three
Graph traversal: Depth First Search and Breadth First Search. It will be covered in class on Thursday. 

Navigate to `traversals.cpp` for the code.

## DFS
Essentially, the idea is to keep going along one path until you reach the end of it, backtrack, go deep into another track, and just keep doing this until you've explored everything. 

Relies on the Call Stack implicitly through recursion (Last-In, First-Out behavior). It marks nodes as visited the moment it enters the function call stack. (We can also represent it iteratively using a stack).

Complexity: O(V + E) time and O(V) space.

## BFS
Here, we go level by level. So we check every neighbor of the current node, then go down and cheack all of their neighbors, until the graph is traversed. 

Relies on an explicit iterative queue container (First-In, First-Out behavior). It marks nodes as visited the exact moment they are pushed onto the queue to prevent cycles.

Complexity: O(V + E) time and O(V) space.

