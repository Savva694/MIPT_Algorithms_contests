#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

class Graph {
 private:
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

  std::vector<Node> vertices_;
  std::vector<std::set<size_t>> edges_;
  std::vector<std::set<size_t>> reverse_edges_;
  size_t my_time_ = 0;
  size_t strong_connectivity_component_count_ = 0;

  void Dfs(size_t vertex, const std::vector<std::set<size_t>>& local_edges) {
    ++my_time_;
    vertices_[vertex].color = 1;
    vertices_[vertex].time_in = my_time_;
    vertices_[vertex].highest_reachable_vertex =
        strong_connectivity_component_count_;
    for (int neighbour : local_edges[vertex]) {
      if (vertices_[neighbour].color == 0) {
        vertices_[neighbour].color = 1;
        Dfs(neighbour, local_edges);
        ++my_time_;
      }
    }
    vertices_[vertex].color = 2;
    vertices_[vertex].time_out = my_time_;
  }

 public:
  Graph(size_t vertex_count, std::vector<std::set<size_t>> edges)
      : edges_(edges) {
    vertices_.resize(vertex_count);
    for (size_t i = 0; i < vertex_count; ++i) {
      vertices_[i] = Node(i);
    }
    reverse_edges_.resize(vertex_count);
    for (size_t vertex = 0; vertex < vertex_count; ++vertex) {
      for (size_t neigbour_vertex : edges_[vertex]) {
        reverse_edges_[neigbour_vertex].insert(vertex);
      }
    }
  }

  std::vector<size_t> GetStrongConnectivityComponents() {
    size_t vertex_count = vertices_.size();
    for (size_t i = 0; i < vertex_count; ++i) {
      if (vertices_[i].color == 0) {
        Dfs(i, edges_);
      }
    }

    std::vector<Node> vertexes_copy = vertices_;
    sort(vertexes_copy.begin(), vertexes_copy.end(),
         [](const Node& first, const Node& second) {
           return first.time_out > second.time_out;
         });
    for (size_t i = 0; i < vertex_count; ++i) {
      vertices_[i].color = 0;
    }

    for (size_t i = 0; i < vertex_count; ++i) {
      if (vertices_[vertexes_copy[i].vertex].color == 0) {
        ++strong_connectivity_component_count_;
        Dfs(vertexes_copy[i].vertex, reverse_edges_);
      }
    }

    std::vector<size_t> strong_connectivity_components(vertex_count);
    for (size_t i = 0; i < vertex_count; ++i) {
      strong_connectivity_components[i] = vertices_[i].highest_reachable_vertex;
    }
    return strong_connectivity_components;
  }

  size_t GetStrongConnectivityComponentsCount() const {
    return strong_connectivity_component_count_;
  }
};

int main() {
  size_t vertex_count;
  size_t edge_count;
  std::cin >> vertex_count;
  std::cin >> edge_count;
  std::vector<std::set<size_t>> edges(vertex_count);

  size_t vertex_1;
  size_t vertex_2;
  for (size_t i = 0; i < edge_count; ++i) {
    std::cin >> vertex_1;
    std::cin >> vertex_2;
    edges[vertex_1 - 1].insert(vertex_2 - 1);
  }

  Graph graph(vertex_count, edges);
  std::vector<size_t> strong_connectivity_components =
      graph.GetStrongConnectivityComponents();

  std::cout << graph.GetStrongConnectivityComponentsCount() << "\n";
  for (size_t i = 0; i < vertex_count; ++i) {
    std::cout << strong_connectivity_components[i] << " ";
  }
}
