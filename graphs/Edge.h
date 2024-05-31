#ifndef EDGE_H
#define EDGE_H

class Edge {
public:
  Edge(int neighbor_ind = -1, int weight = -1) {
    this->weight = weight;
    this->neighbor_ind = neighbor_ind;
  }

  bool operator<(const Edge& other) const {
    return this->weight < other.weight;
  }
  bool operator>(const Edge& other) const {
    return this->weight > other.weight;
  }

  int weight;
  int neighbor_ind;
};


#endif