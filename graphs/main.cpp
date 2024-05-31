#include <iostream>
#include <string>
#include <stack>
#include "Vertex.h"
#include "Graph.h"
#include "Graph.cpp"


int main() {
  Vertex<std::string> v("SFO");
  Vertex<std::string> v2("LAX");
  Vertex<std::string> v3("DFW");
  Vertex<std::string> v4("ORD");
  Vertex<std::string> v5("JFK");
  Vertex<std::string> v6("BOS");
  Vertex<std::string> v7("MIA");

  Graph<std::string> airports;

  airports.insert_vertex(v);
  airports.insert_vertex(v2);
  airports.insert_vertex(v3);
  airports.insert_vertex(v4);
  airports.insert_vertex(v5);
  airports.insert_vertex(v6);
  airports.insert_vertex(v7);

  airports.add_edge(v, v2, 337);
  airports.add_edge(v, v3, 1464);
  airports.add_edge(v, v4, 1846);
  airports.add_edge(v, v6, 2704);
  airports.add_edge(v3, v4, 802);
  airports.add_edge(v6, v4, 867);
  airports.add_edge(v5, v6, 187);
  airports.add_edge(v5, v7, 1090);
  airports.add_edge(v6, v7, 1258);
  airports.add_edge(v2, v7, 2342);
  airports.add_edge(v2, v3, 1235);
  airports.add_edge(v7, v3, 1121);
  airports.add_edge(v4, v5, 740);


  Vertex<std::string> A("A");
  Vertex<std::string> B("B");
  Vertex<std::string> C("C");
  Vertex<std::string> D("D");
  Vertex<std::string> E("E");




  try
  {
    std::cout << airports.dijkstra_shortestPath(v5, v);
    puts("");
    std::cout << airports.dijkstra_shortestPath(v5, v2);
    puts("");
    std::cout << airports.dijkstra_shortestPath(v5, v4);
    puts("");
    std::cout << airports.dijkstra_shortestPath(v5, v3);
    puts("");

  }
  catch (const std::string& s)
  {
    std::cout << s << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }


  return 0;
}