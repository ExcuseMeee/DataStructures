#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include "Graph.h"
#include "Edge.h"
#include "MinHeap.h"
#include "MinHeap.cpp"

template<typename T>
void Graph<T>::insert_vertex(const Vertex<T>& ver) {
  if (get_vertex_index(ver) == -1) {
    this->vertices.push_back(ver);
    this->adjacency_list.push_back(std::vector<Edge>());
  }
}

template<typename T>
void Graph<T>::add_edge(const Vertex<T>& ver1, const Vertex<T>& ver2, int weight) {
  // connect ver1 to ver2
  int i1 = get_vertex_index(ver1);
  int i2 = get_vertex_index(ver2);

  if (i1 == -1 || i2 == -1) throw std::string("[add_edge] invalid vertex");


  adjacency_list[i1].push_back(Edge(i2, weight)); // i1 is connected to i2

  if (i1 != i2) adjacency_list[i2].push_back(Edge(i1, weight)); // i2 is connected to i1

}

template<typename T>
int Graph<T>::get_vertex_index(const Vertex<T>& ver) {
  for (int i = 0; i < vertices.size(); i++) {
    if (vertices.at(i).getData() == ver.getData()) return i;
  }

  return -1;
}

template<typename T>
void Graph<T>::print() const {
  for (int i = 0; i < vertices.size(); i++) {
    std::cout << vertices[i].getData() << ": "; // print current vertex

    // print its adjacency list
    for (Edge e : adjacency_list[i]) {
      std::cout << "("
        << vertices[e.neighbor_ind].getData() << ", " << e.weight
        << ")"
        << " ";
    }

    std::cout << std::endl;

  }
}

template<typename T>
void Graph<T>::DFS(Vertex<T>& ver) {
  clean_visited();
  DFS_helper(ver);

}

template<typename T>
void Graph<T>::DFS_helper(Vertex<T>& ver) {
  int index = get_vertex_index(ver);

  if (index == -1) throw std::string("[DFS_helper] invalid vertex");

  vertices[index].setVisited(true);
  std::cout << vertices[index].getData() << " ";

  for (Edge& e : adjacency_list[index]) {
    Vertex<T> neighbor = vertices[e.neighbor_ind];

    if (neighbor.getVisited() == false) {
      DFS_helper(neighbor);
    }
  }

}

template<typename T>
void Graph<T>::BFS(Vertex<T>& ver) {
  int i = get_vertex_index(ver);
  if (i == -1) throw std::string("[BFS] invalid vertex");

  clean_visited();

  // create a queue
  std::queue<int> q; // queue of indicies
  q.push(i); // add index of current vertex to queue
  vertices[i].setVisited(true);

  while (!q.empty()) {
    int ind = q.front();
    std::cout << vertices[ind].getData() << " ";
    for (Edge& e : adjacency_list[ind]) { // explore the neighbors
      if (vertices[e.neighbor_ind].getVisited() == false) {
        q.push(e.neighbor_ind);
        vertices[e.neighbor_ind].setVisited(true);
      }
    }
    q.pop(); // pop current vertex, because we checked all its neighbors
  }

  std::cout << std::endl;
  clean_visited();
}

template<typename T>
void Graph<T>::clean_visited() {
  for (Vertex<T>& v : vertices) {
    v.setVisited(false);
  }
}

template<typename T>
int Graph<T>::shortestPath(const Vertex<T>& src, const Vertex<T>& dest) {
  int i_src = get_vertex_index(src);
  int i_dest = get_vertex_index(dest);

  if (i_src == -1 || i_dest == -1) throw std::string("[shortestPath] invalid vertices");

  clean_visited();
  std::vector<int> distances(vertices.size()); // distances from src vertex to all other vertices

  // initialize distances
  for (int i = 0; i < distances.size(); i++)
    distances[i] = (i == i_src ? 0 : INT_MAX); // distance from src to itself is 0

  std::queue<int> q;
  q.push(i_src);

  while (!q.empty()) {
    int i = q.front();

    // go through neighbors
    for (Edge e : adjacency_list[i]) {
      int adj_ind = e.neighbor_ind;

      if (vertices[adj_ind].getVisited() == false) {
        q.push(adj_ind);
        int dist_to_neighbor = distances[i] + e.weight; // cumulative distance from src to vertices[adj_ind]
        if (dist_to_neighbor < distances[adj_ind]) {
          distances[adj_ind] = dist_to_neighbor;
        }
      }
    }

    vertices[i].setVisited(true);
    q.pop();
  }

  clean_visited();

  return distances[i_dest];

}

template<typename T>
int Graph<T>::dijkstra_shortestPath(const Vertex<T>& src, const Vertex<T>& dest) {
  int i_src = get_vertex_index(src);
  int i_dest = get_vertex_index(dest);

  if (i_src == -1 || i_dest == -1) throw std::string("[shortestPath] invalid vertices");

  clean_visited();
  std::vector<int> distances(vertices.size()); // will ultimately store shortest distances from src vertex to all other vertices

  std::vector<int> sources(vertices.size()); // holds index of where current index came from. sources = [3,0,1,3]... the source of vertex at index 0 (call it v0) is sources[3] (call it v3), meaning that we reached v0 FROM v3 

  // initialize distances
  for (int i = 0; i < distances.size(); i++) distances[i] = (i == i_src ? 0 : INT_MAX); // distance from src to itself is 0

  // init sources
  for (int i = 0; i < sources.size(); i++) sources[i] = i;

  MinHeap<Edge> heap;
  int vertices_visited = 0;
  int cur_ver = i_src;

  while (vertices_visited < vertices.size()) {
    int i = cur_ver;

    // go through neighbors
    for (Edge e : adjacency_list[i]) {
      int adj_ind = e.neighbor_ind;

      if (vertices[adj_ind].getVisited() == false) {
        // distance from src to this node's neighbor is: distance to this node (distances[i]) + weight of edge from this node to neighbor (e.weight)
        int dist_to_neighbor = distances[i] + e.weight;
        heap.insert(e);
        if (dist_to_neighbor < distances[adj_ind]) {
          distances[adj_ind] = dist_to_neighbor;
          sources[adj_ind] = i;
        }
      }
    }

    Edge smallest_edge = heap.deleteMin();
    cur_ver = smallest_edge.neighbor_ind;
    if (vertices[i].getVisited() == false) vertices_visited++; // prevent incrementing if vertex is already visited (this probably can happen)

    vertices[i].setVisited(true);
  }

  clean_visited();

  // PRINT VERTEX PATH
  std::stack<int> st; // use stack to reverse path taken from sources (path taken from sources goes from dest to src. we want to print src to dest)
  int i_cur = i_dest;
  st.push(i_cur);
  while (true) {
    if (i_cur == i_src) break;
    st.push(sources[i_cur]);
    i_cur = sources[i_cur];
  }

  while (!st.empty()) {
    int vertex_ind = st.top();
    st.pop();
    std::cout << vertices[vertex_ind].getData() << " ";
  }


  return distances[i_dest];

}


template<typename T>
bool Graph<T>::isConnected() {
  // last resort? use disktra
  // BFS starting from any node.
  if (this->vertices.empty()) throw std::string("[isConnected] empty graph");

  clean_visited();

  std::queue<int> toVisit;
  toVisit.push(0);
  vertices[0].setVisited(true);

  while (!toVisit.empty()) {
    int index = toVisit.front();
    // std::cout << vertices[index].getData() << " ";

    for (auto e : this->adjacency_list[index]) {
      // Vertex<T> ver = vertices[e.neighbor_ind];
      if (vertices[e.neighbor_ind].getVisited() == false) {
        toVisit.push(e.neighbor_ind);
        vertices[e.neighbor_ind].setVisited(true);
      }
    }
    toVisit.pop();
  }


  for (Vertex<T> ver : vertices) {
    if (ver.getVisited() == false) return false;
  }

  return true;

}
