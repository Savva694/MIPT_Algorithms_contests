#include <iostream>
#include <queue>
#include <vector>

class Graph {
 private:
  struct Edge {
    size_t vertex;
    size_t weight;

    Edge() : vertex(0), weight(0) {}

    Edge(size_t vertex, size_t weight) : vertex(vertex), weight(weight) {}

    Edge(const Edge& other) : vertex(other.vertex), weight(other.weight) {}

    Edge& operator=(const Edge& other) {
      vertex = other.vertex;
      weight = other.weight;
      return *this;
    }
  };

  size_t vertices_count_;
  std::vector<std::vector<Edge>> edges_;

 public:
  Graph(size_t vertices_count,
        std::vector<std::pair<std::pair<size_t, size_t>, size_t>>& edges)
      : vertices_count_(vertices_count) {
    edges_.resize(vertices_count_);
    for (std::pair<std::pair<size_t, size_t>, size_t> edge : edges) {
      edges_[edge.first.first].emplace_back(edge.first.second, edge.second);
      edges_[edge.first.second].emplace_back(edge.first.first, edge.second);
    }
  }

  std::vector<size_t> FindDistances(size_t start) const {
    const size_t cSup = 2'009'000'999;
    std::vector<size_t> distances(vertices_count_, cSup);
    std::vector<size_t> now_best_distances(vertices_count_, cSup);
    using Pair = std::pair<size_t, size_t>;
    struct Compare {
      bool operator()(const Pair& first, const Pair& second) const {
        return first.second > second.second;
      }
    };
    std::priority_queue<Pair, std::vector<Pair>, Compare> bad_distances;
    for (size_t i = 0; i < vertices_count_; ++i) {
      if (i != start) {
        bad_distances.emplace(i, cSup);
      } else {
        bad_distances.emplace(i, 0);
      }
    }

    while (!bad_distances.empty()) {
      Pair pair_vertex_distance = bad_distances.top();
      size_t vertex = pair_vertex_distance.first;
      size_t distance = pair_vertex_distance.second;
      if (distances[vertex] < distance) {
        bad_distances.pop();
        continue;
      }
      distances[vertex] = distance;
      for (Edge neighbour_edge : edges_[vertex]) {
        if (distances[neighbour_edge.vertex] == cSup &&
            now_best_distances[neighbour_edge.vertex] >
                distance + neighbour_edge.weight) {
          now_best_distances[neighbour_edge.vertex] =
              distance + neighbour_edge.weight;
          bad_distances.emplace(neighbour_edge.vertex,
                                distance + neighbour_edge.weight);
        }
      }
      bad_distances.pop();
    }
    return distances;
  }
};

int main() {
  int graph_count;
  std::cin >> graph_count;
  while (graph_count-- > 0) {
    size_t vertices_count;
    size_t edges_count;
    std::cin >> vertices_count;
    std::cin >> edges_count;

    std::vector<std::pair<std::pair<size_t, size_t>, size_t>> edges;

    size_t vertex_1;
    size_t vertex_2;
    size_t weight;
    for (size_t j = 0; j < edges_count; ++j) {
      std::cin >> vertex_1;
      std::cin >> vertex_2;
      std::cin >> weight;
      edges.emplace_back(std::make_pair(vertex_1, vertex_2), weight);
    }

    size_t start_vertex;
    std::cin >> start_vertex;

    Graph graph(vertices_count, edges);
    std::vector<size_t> distances = graph.FindDistances(start_vertex);

    for (size_t distance : distances) {
      std::cout << distance << " ";
    }
  }
}
