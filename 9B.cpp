#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

class Graph {
 private:
  using Pair = std::pair<size_t, size_t>;

  struct Edge {
    size_t vertex;
    size_t weight;
  };

  size_t vertices_count_;
  std::vector<std::vector<Edge>> edges_;

 public:
  Graph(size_t vertices_count,
        const std::vector<std::pair<std::pair<size_t, size_t>, size_t>>&
            other_edges)
      : vertices_count_(vertices_count) {
    edges_.resize(vertices_count);
    for (const auto& edge : other_edges) {
      edges_[edge.first.first].emplace_back(edge.first.second, edge.second);
      edges_[edge.first.second].emplace_back(edge.first.first, edge.second);
    }
  }

  size_t Prim() const {
    size_t sum_distance = 0;
    std::vector<size_t> edge_distances(vertices_count_,
                                       std::numeric_limits<size_t>::max());
    edge_distances[0] = 0;
    struct Compare {
      bool operator()(const Pair& first, const Pair& second) const {
        return first.second > second.second;
      }
    };
    std::priority_queue<Pair, std::vector<Pair>, Compare> distances;
    for (const auto& edge : edges_[0]) {
      distances.emplace(edge.vertex, edge.weight);
      edge_distances[edge.vertex] = edge.weight;
    }
    while (!distances.empty()) {
      Pair pair_vertex_distance = distances.top();
      size_t vertex = pair_vertex_distance.first;
      size_t distance = pair_vertex_distance.second;
      distances.pop();
      if (edge_distances[vertex] < distance) {
        continue;
      }
      sum_distance += distance;
      edge_distances[vertex] = 0;
      for (Edge neighbour_edge : edges_[vertex]) {
        if (edge_distances[neighbour_edge.vertex] > neighbour_edge.weight) {
          edge_distances[neighbour_edge.vertex] = neighbour_edge.weight;
          distances.emplace(neighbour_edge.vertex, neighbour_edge.weight);
        }
      }
    }
    return sum_distance;
  }
};

int main() {
  size_t vertices_count;
  size_t edges_count;
  std::cin >> vertices_count >> edges_count;
  std::vector<std::pair<std::pair<size_t, size_t>, size_t>> edges(edges_count);
  for (size_t i = 0; i < edges_count; ++i) {
    std::cin >> edges[i].first.first >> edges[i].first.second >>
        edges[i].second;
    --edges[i].first.first;
    --edges[i].first.second;
  }
  Graph graph(vertices_count, edges);
  std::cout << graph.Prim();
  return 0;
}
