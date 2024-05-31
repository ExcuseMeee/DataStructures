#ifndef GRAPH_H
#define GRAPH_H
#include "Vertex.h"
#include "Edge.h"
#include <vector>

/*
two ways to represent graphs:

adjacency list: each vertex is listed, then for each node a list of adjacent vertecies
adjacency matrix: V x V matrix (V=num vertexes) intersection of row and col represents adjacency, if 1 adjacent if 0 no
*/
template<typename T>
class Graph {
public:

  Graph() {};

  void insert_vertex(const Vertex<T>& ver);
  void add_edge(const Vertex<T>& ver1, const Vertex<T>& ver2, int weight = -1); // connect ver1 and ver2

  void print() const;

  void DFS(Vertex<T>& ver); // depth first search: explore a branch as deep as possible before exploring another branch
  void BFS(Vertex<T>& ver);

  int shortestPath(const Vertex<T>& src, const Vertex<T>& dest);
  int dijkstra_shortestPath(const Vertex<T>& src, const Vertex<T>& dest);

  bool isConnected();


private:

  std::vector<Vertex<T>> vertices;
  std::vector<std::vector<Edge>> adjacency_list; // adjacency_list[i] represents the adjacency list of vertex at vertices[i]

  int get_vertex_index(const Vertex<T>& ver);

  void clean_visited();
  void DFS_helper(Vertex<T>& ver);

};


#endif