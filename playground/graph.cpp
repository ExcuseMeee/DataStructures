#include <iostream>
#include <vector>

template<typename T>
class Vertex {
public:
  Vertex(const T& val) : data(val), visited(false) {}

  T data;
  bool visited;
};

class Edge {
public:
  Edge(int src, int dest, int w) : srcIndex(src), destIndex(dest), weight(w) {}

  int srcIndex;
  int destIndex;
  int weight;
};

template<typename T>
class Graph {
public:
  Graph() {}

  void insertVertex(const Vertex<T>& ver) {
    if (getVertexIndex(ver) == -1) {
      vertices.push_back(ver);
      adjLists.push_back(std::vector<Edge>());
    }
  }

  void addEdge(const Vertex<T>& src, const Vertex<T>& dest, int cost) {
    int srcInd = getVertexIndex(src);
    int destInd = getVertexIndex(dest);

    if (srcInd == -1 || destInd == -1) return;

    adjLists[srcInd].push_back(Edge(srcInd, destInd, cost));

    if (srcInd != destInd) adjLists[destInd].push_back(Edge(destInd, srcInd, cost));
  }

  void print() const {
    puts("[print]");
    for (int rowInd = 0; rowInd < adjLists.size(); rowInd++) {
      std::cout << vertices[rowInd].data << ": ";
      for (const Edge& e : adjLists[rowInd]) {
        std::cout << "("
          << vertices[e.destIndex].data << ", " << e.weight
          << ") ";
      }
      std::cout << "\n";
    }
  }

private:
  std::vector<Vertex<T>> vertices;
  std::vector<std::vector<Edge>> adjLists;

  int getVertexIndex(const Vertex<T>& ver) {
    for (int i = 0; i < vertices.size(); i++) {
      if (vertices.at(i).data == ver.data) return i;
    }
    return -1;
  }

};


int main() {

  Vertex<std::string> A("A");
  Vertex<std::string> B("B");
  Vertex<std::string> C("C");
  Vertex<std::string> D("D");

  Graph<std::string> g;

  g.insertVertex(A);
  g.insertVertex(B);
  g.insertVertex(C);
  g.insertVertex(D);

  g.addEdge(A, D, 5);
  g.addEdge(A, C, 7);
  g.addEdge(C, B, 10);

  g.print();


  return 0;
}