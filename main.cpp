#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

struct Node {
  size_t vertex;
  int color;
  size_t time_in;
  size_t time_out;
  size_t highest_reachable_vertex;
  size_t parent;

  Node()
      : vertex(0),
        color(0),
        time_in(0),
        time_out(0),
        highest_reachable_vertex(0),
        parent(0) {}

  Node(size_t vertex)
      : vertex(vertex),
        color(0),
        time_in(0),
        time_out(0),
        highest_reachable_vertex(0),
        parent(0) {}

  Node(const Node& other)
      : vertex(other.vertex),
        color(other.color),
        time_in(other.time_in),
        time_out(other.time_out),
        highest_reachable_vertex(other.highest_reachable_vertex),
        parent(other.parent) {}

  Node& operator=(const Node& other) {
    vertex = other.vertex;
    color = other.color;
    time_in = other.time_in;
    time_out = other.time_out;
    highest_reachable_vertex = other.highest_reachable_vertex;
    parent = other.parent;
    return *this;
  }
};

struct Edge {
  size_t vertex_1;
  size_t vertex_2;
  size_t edge_id;

  Edge() : vertex_1(0), vertex_2(0), edge_id(0) {}

  Edge(size_t vertex_1, size_t vertex_2, size_t edge_id)
      : vertex_1(vertex_1), vertex_2(vertex_2), edge_id(edge_id) {}

  Edge(const Edge& other)
      : vertex_1(other.vertex_1),
        vertex_2(other.vertex_2),
        edge_id(other.edge_id) {}
};

namespace DfsVariables {
size_t my_time = 0;
std::vector<Node> vertices;
std::vector<std::vector<Edge>> edges;
std::vector<size_t> bridges;
}  // namespace DfsVariables

void Dfs(size_t vertex) {
  ++DfsVariables::my_time;
  DfsVariables::vertices[vertex].color = 1;
  DfsVariables::vertices[vertex].time_in = DfsVariables::my_time;
  for (Edge neighbour : DfsVariables::edges[vertex]) {
    if (DfsVariables::vertices[neighbour.vertex_2].color == 0) {
      DfsVariables::vertices[neighbour.vertex_2].parent = vertex;
      Dfs(neighbour.vertex_2);
      ++DfsVariables::my_time;
    }
  }
  DfsVariables::vertices[vertex].color = 2;
  DfsVariables::vertices[vertex].time_out = DfsVariables::my_time;
}

void RetCounting(size_t vertex) {
  DfsVariables::vertices[vertex].color = 1;
  DfsVariables::vertices[vertex].highest_reachable_vertex =
      DfsVariables::vertices[vertex].time_in;
  for (size_t index = 0; index < DfsVariables::edges[vertex].size(); ++index) {
    Edge neighbour = DfsVariables::edges[vertex][index];
    if (DfsVariables::vertices[vertex].time_in >=
            DfsVariables::vertices[neighbour.vertex_2].time_in &&
        DfsVariables::vertices[vertex].time_out <=
            DfsVariables::vertices[neighbour.vertex_2].time_out &&
        DfsVariables::vertices[vertex].parent != neighbour.vertex_2) {
      DfsVariables::vertices[vertex].highest_reachable_vertex =
          std::min(DfsVariables::vertices[vertex].highest_reachable_vertex,
                   DfsVariables::vertices[neighbour.vertex_2].time_in);
    }
    if (DfsVariables::vertices[neighbour.vertex_2].color == 0) {
      DfsVariables::vertices[neighbour.vertex_2].color = 1;
      RetCounting(neighbour.vertex_2);
      if (DfsVariables::vertices[vertex].parent != neighbour.vertex_2) {
        DfsVariables::vertices[vertex].highest_reachable_vertex =
            std::min(DfsVariables::vertices[vertex].highest_reachable_vertex,
                     DfsVariables::vertices[neighbour.vertex_2]
                         .highest_reachable_vertex);
      }
      if (DfsVariables::vertices[vertex].time_in <
          DfsVariables::vertices[neighbour.vertex_2].highest_reachable_vertex) {
        size_t vertex_count = 0;
        for (Edge edge : DfsVariables::edges[vertex]) {
          if (edge.vertex_2 == neighbour.vertex_2) {
            ++vertex_count;
          }
        }
        if (vertex_count == 1) {
          DfsVariables::bridges.push_back(
              DfsVariables::edges[vertex][index].edge_id);
        }
      }
    }
  }
  DfsVariables::vertices[vertex].color = 2;
}

void FindBridges() {
  size_t vertex_count = DfsVariables::vertices.size();
  for (size_t i = 0; i < vertex_count; ++i) {
    if (DfsVariables::vertices[i].color == 0) {
      Dfs(i);
    }
  }

  for (size_t i = 0; i < vertex_count; ++i) {
    DfsVariables::vertices[i].color = 0;
  }

  for (size_t i = 0; i < vertex_count; ++i) {
    if (DfsVariables::vertices[i].color == 0) {
      RetCounting(i);
    }
  }

  sort(DfsVariables::bridges.begin(), DfsVariables::bridges.end());
}

int main() {
  size_t vertex_count;
  size_t edge_count;
  std::cin >> vertex_count;
  std::cin >> edge_count;
  DfsVariables::vertices.resize(vertex_count);
  DfsVariables::edges.resize(vertex_count);

  for (size_t i = 0; i < vertex_count; ++i) {
    DfsVariables::vertices[i] = Node(i);
  }

  size_t vertex_1;
  size_t vertex_2;
  for (size_t i = 0; i < edge_count; ++i) {
    std::cin >> vertex_1;
    std::cin >> vertex_2;
    DfsVariables::edges[vertex_1 - 1].emplace_back(vertex_1 - 1, vertex_2 - 1,
                                                   i);
    DfsVariables::edges[vertex_2 - 1].emplace_back(vertex_2 - 1, vertex_1 - 1,
                                                   i);
  }

  FindBridges();

  std::cout << DfsVariables::bridges.size() << "\n";
  for (size_t bridge : DfsVariables::bridges) {
    std::cout << bridge + 1 << "\n";
  }
}
