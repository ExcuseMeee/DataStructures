#ifndef VERTEX_H
#define VERTEX_H

template<typename T>
class Vertex {
public:
  Vertex(const T& d = T()) : data(d), visited(false) {};

  const T& getData() const {
    return data;
  }
  const bool getVisited() const {
    return visited;
  }
  void setVisited(const bool v) {
    visited = v;
  }

private:
  T data;
  bool visited;

};


#endif