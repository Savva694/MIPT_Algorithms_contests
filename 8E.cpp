#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

class Graph {
 private:
  struct Edge {
    size_t vertex;
    long long weight;

    Edge() : vertex(0), weight(0) {}

    Edge(size_t vertex, long long weight) : vertex(vertex), weight(weight) {}

    Edge(const Edge& other) : vertex(other.vertex), weight(other.weight) {}

    Edge& operator=(const Edge& other) {
      vertex = other.vertex;
      weight = other.weight;
      return *this;
    }
  };

  size_t vertices_count_;
  std::vector<std::vector<Edge>> edges_;
  std::vector<std::vector<Edge>> reversed_edges_;

  void UpdateShortestPath(std::vector<long long>& prev,
                          std::vector<long long>& next,
                          std::vector<Edge>& parents,
                          std::set<size_t>& unused) const {
    for (size_t vertex = 0; vertex < vertices_count_; ++vertex) {
      if (unused.find(vertex) == unused.end()) {
        continue;
      }
      next[vertex] = prev[vertex];
      for (Edge neighbour : reversed_edges_[vertex]) {
        if (unused.find(vertex) == unused.end()) {
          continue;
        }
        if (next[vertex] > prev[neighbour.vertex] + neighbour.weight) {
          next[vertex] = prev[neighbour.vertex] + neighbour.weight;
          parents[vertex] = neighbour;
        }
      }
    }
    prev = next;
  }

 public:
  Graph(size_t vertices_count,
        std::vector<std::pair<std::pair<size_t, size_t>, long long>>& edges)
      : vertices_count_(vertices_count) {
    edges_.resize(vertices_count_);
    reversed_edges_.resize(vertices_count_);
    for (std::pair<std::pair<size_t, size_t>, long long> edge : edges) {
      edges_[edge.first.first].emplace_back(edge.first.second, edge.second);
      reversed_edges_[edge.first.second].emplace_back(edge.first.first,
                                                      edge.second);
    }
  }

  std::vector<size_t> FindNegativeCycle() const {
    std::set<size_t> unused;
    for (size_t vertex = 0; vertex < vertices_count_; ++vertex) {
      unused.insert(vertex);
    }
    while (!unused.empty()) {
      const long long cSup = LLONG_MAX / 2;
      std::vector<long long> prev(vertices_count_, cSup);
      prev[*unused.begin()] = 0;
      std::vector<long long> next(vertices_count_);
      std::vector<Edge> parents(vertices_count_);
      for (size_t i = 0; i < vertices_count_ - 1; ++i) {
        UpdateShortestPath(prev, next, parents, unused);
      }
      std::vector<long long> distances = prev;
      UpdateShortestPath(prev, next, parents, unused);
      for (size_t vertex = 0; vertex < vertices_count_; ++vertex) {
        if (prev[vertex] < cSup / 2 && unused.find(vertex) != unused.end()) {
          unused.erase(vertex);
        }
      }
      size_t vertex_now = vertices_count_;
      for (size_t vertex = 0; vertex < vertices_count_; ++vertex) {
        if (distances[vertex] != prev[vertex]) {
          vertex_now = vertex;
          break;
        }
      }
      if (vertex_now == vertices_count_) {
        continue;
      }
      std::set<size_t> unordered_path;
      std::vector<size_t> ordered_path;
      std::vector<size_t> path_weight(vertices_count_);
      unordered_path.insert(vertex_now);
      ordered_path.push_back(vertex_now);
      path_weight[vertex_now] = 0;
      while (true) {
        size_t last_vertex = vertex_now;
        vertex_now = parents[vertex_now].vertex;
        if (unordered_path.find(vertex_now) != unordered_path.end() &&
            path_weight[vertex_now] >
                path_weight[last_vertex] + parents[vertex_now].weight) {
          std::vector<size_t> negative_cycle;
          negative_cycle.push_back(vertex_now);
          std::reverse(ordered_path.begin(), ordered_path.end());
          for (size_t negative_vertex : ordered_path) {
            negative_cycle.push_back(negative_vertex);
            if (negative_vertex == vertex_now) {
              break;
            }
          }
          return negative_cycle;
        }
        unordered_path.insert(vertex_now);
        ordered_path.push_back(vertex_now);
        path_weight[vertex_now] =
            path_weight[last_vertex] + parents[vertex_now].weight;
      }
    }
    return {};
  }
};

int main() {
  size_t vertices_count;
  std::cin >> vertices_count;

  std::vector<std::pair<std::pair<size_t, size_t>, long long>> edges;

  const long long cVoidEdge = 100'000;
  long long weight;
  for (size_t vertex_1 = 0; vertex_1 < vertices_count; ++vertex_1) {
    for (size_t vertex_2 = 0; vertex_2 < vertices_count; ++vertex_2) {
      std::cin >> weight;
      if (weight != cVoidEdge) {
        edges.emplace_back(std::make_pair(vertex_1, vertex_2), weight);
      }
    }
  }

  Graph graph(vertices_count, edges);
  std::vector<size_t> negative_cycle = graph.FindNegativeCycle();

  if (negative_cycle.empty()) {
    std::cout << "NO";
  } else {
    std::cout << "YES\n";
    std::cout << negative_cycle.size() << "\n";
    for (size_t vertex : negative_cycle) {
      std::cout << vertex + 1 << " ";
    }
  }
}
