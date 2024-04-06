#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Node {
  size_t vertex;
  int color;
  size_t time_in;
  size_t time_out;
  size_t highest_reachable_vertex;

  Node()
      : vertex(-1),
        color(-1),
        time_in(-1),
        time_out(-1),
        highest_reachable_vertex(-1) {}

  Node(size_t vertex)
      : vertex(vertex),
        color(0),
        time_in(-1),
        time_out(-1),
        highest_reachable_vertex(-1) {}

  Node(const Node& other)
      : vertex(other.vertex),
        color(other.color),
        time_in(other.time_in),
        time_out(other.time_out),
        highest_reachable_vertex(other.highest_reachable_vertex) {}

  Node& operator=(const Node& other) {
    vertex = other.vertex;
    color = other.color;
    time_in = other.time_in;
    time_out = other.time_out;
    highest_reachable_vertex = other.highest_reachable_vertex;
    return *this;
  }
};

namespace DfsVariables {
size_t my_time = 0;
size_t strong_connectivity_component_count = 0;
std::vector<Node> vertices;
std::vector<std::set<size_t>> edges;
std::vector<std::set<size_t>> reverse_edges;
}  // namespace DfsVariables

void Dfs(size_t vertex, const std::vector<std::set<size_t>>& local_edges) {
  ++DfsVariables::my_time;
  DfsVariables::vertices[vertex].color = 1;
  DfsVariables::vertices[vertex].time_in = DfsVariables::my_time;
  DfsVariables::vertices[vertex].highest_reachable_vertex =
      DfsVariables::strong_connectivity_component_count;
  for (int neighbour : local_edges[vertex]) {
    if (DfsVariables::vertices[neighbour].color == 0) {
      DfsVariables::vertices[neighbour].color = 1;
      Dfs(neighbour, local_edges);
      ++DfsVariables::my_time;
    }
  }
  DfsVariables::vertices[vertex].color = 2;
  DfsVariables::vertices[vertex].time_out = DfsVariables::my_time;
}

bool CompareTout(Node first, Node second) {
  return first.time_out > second.time_out;
}

void FindStrongConnectivityComponents() {
  size_t vertex_count = DfsVariables::vertices.size();
  for (size_t i = 0; i < vertex_count; ++i) {
    if (DfsVariables::vertices[i].color == 0) {
      Dfs(i, DfsVariables::edges);
    }
  }

  std::vector<Node> vertexes_copy = DfsVariables::vertices;
  sort(vertexes_copy.begin(), vertexes_copy.end(), CompareTout);
  for (size_t i = 0; i < vertex_count; ++i) {
    DfsVariables::vertices[i].color = 0;
  }

  for (size_t i = 0; i < vertex_count; ++i) {
    if (DfsVariables::vertices[vertexes_copy[i].vertex].color == 0) {
      ++DfsVariables::strong_connectivity_component_count;
      Dfs(vertexes_copy[i].vertex, DfsVariables::reverse_edges);
    }
  }
}

int main() {
  size_t vertex_count;
  size_t edge_count;
  std::cin >> vertex_count;
  std::cin >> edge_count;
  DfsVariables::vertices.resize(vertex_count);
  DfsVariables::edges.resize(vertex_count);
  DfsVariables::reverse_edges.resize(vertex_count);
  for (size_t i = 0; i < vertex_count; ++i) {
    DfsVariables::vertices[i] = Node(i);
  }

  size_t vertex_1;
  size_t vertex_2;
  for (size_t i = 0; i < edge_count; ++i) {
    std::cin >> vertex_1;
    std::cin >> vertex_2;
    DfsVariables::edges[vertex_1 - 1].insert(vertex_2 - 1);
    DfsVariables::reverse_edges[vertex_2 - 1].insert(vertex_1 - 1);
  }

  FindStrongConnectivityComponents();

  std::cout << DfsVariables::strong_connectivity_component_count << "\n";
  for (size_t i = 0; i < vertex_count; ++i) {
    std::cout << DfsVariables::vertices[i].highest_reachable_vertex << " ";
  }
}
