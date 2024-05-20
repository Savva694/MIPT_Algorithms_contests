#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

class Graph {
 private:
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

  std::vector<Node> vertices_;
  std::vector<std::vector<Edge>> edges_;
  std::vector<size_t> bridges_;
  size_t my_time_ = 0;

  void Dfs(size_t vertex) {
    ++my_time_;
    vertices_[vertex].color = 1;
    vertices_[vertex].time_in = my_time_;
    for (Edge neighbour : edges_[vertex]) {
      if (vertices_[neighbour.vertex_2].color == 0) {
        vertices_[neighbour.vertex_2].parent = vertex;
        Dfs(neighbour.vertex_2);
        ++my_time_;
      }
    }
    vertices_[vertex].color = 2;
    vertices_[vertex].time_out = my_time_;
  }

  void RetCountingAndBridgesFinding(size_t vertex) {
    vertices_[vertex].color = 1;
    vertices_[vertex].highest_reachable_vertex = vertices_[vertex].time_in;
    for (size_t index = 0; index < edges_[vertex].size(); ++index) {
      Edge neighbour = edges_[vertex][index];
      if (vertices_[vertex].time_in >= vertices_[neighbour.vertex_2].time_in &&
          vertices_[vertex].time_out <=
              vertices_[neighbour.vertex_2].time_out &&
          vertices_[vertex].parent != neighbour.vertex_2) {
        vertices_[vertex].highest_reachable_vertex =
            std::min(vertices_[vertex].highest_reachable_vertex,
                     vertices_[neighbour.vertex_2].time_in);
      }
      if (vertices_[neighbour.vertex_2].color == 0) {
        vertices_[neighbour.vertex_2].color = 1;
        RetCountingAndBridgesFinding(neighbour.vertex_2);
        if (vertices_[vertex].parent != neighbour.vertex_2) {
          vertices_[vertex].highest_reachable_vertex =
              std::min(vertices_[vertex].highest_reachable_vertex,
                       vertices_[neighbour.vertex_2].highest_reachable_vertex);
        }
        if (vertices_[vertex].time_in <
            vertices_[neighbour.vertex_2].highest_reachable_vertex) {
          size_t vertex_count = 0;
          for (Edge edge : edges_[vertex]) {
            if (edge.vertex_2 == neighbour.vertex_2) {
              ++vertex_count;
            }
          }
          if (vertex_count == 1) {
            bridges_.push_back(edges_[vertex][index].edge_id);
          }
        }
      }
    }
    vertices_[vertex].color = 2;
  }

 public:
  Graph(size_t vertex_count,
        const std::vector<std::pair<size_t, size_t>>& edges) {
    vertices_.resize(vertex_count);
    for (size_t i = 0; i < vertex_count; ++i) {
      vertices_[i] = Node(i);
    }
    edges_.resize(vertex_count);
    for (size_t i = 0; i < edges.size(); ++i) {
      edges_[edges[i].first].emplace_back(edges[i].first, edges[i].second, i);
      edges_[edges[i].second].emplace_back(edges[i].second, edges[i].first, i);
    }
  }

  std::vector<size_t> GetBridges() {
    size_t vertex_count = vertices_.size();
    for (size_t i = 0; i < vertex_count; ++i) {
      if (vertices_[i].color == 0) {
        Dfs(i);
      }
    }

    for (size_t i = 0; i < vertex_count; ++i) {
      vertices_[i].color = 0;
    }

    for (size_t i = 0; i < vertex_count; ++i) {
      if (vertices_[i].color == 0) {
        RetCountingAndBridgesFinding(i);
      }
    }

    sort(bridges_.begin(), bridges_.end());
    return bridges_;
  }
};

int main() {
  size_t vertex_count;
  size_t edge_count;
  std::cin >> vertex_count;
  std::cin >> edge_count;
  std::vector<std::pair<size_t, size_t>> edges;

  size_t vertex_1;
  size_t vertex_2;
  for (size_t i = 0; i < edge_count; ++i) {
    std::cin >> vertex_1;
    std::cin >> vertex_2;
    edges.emplace_back(vertex_1 - 1, vertex_2 - 1);
  }

  Graph graph(vertex_count, edges);
  std::vector<size_t> bridges = graph.GetBridges();

  std::cout << bridges.size() << "\n";
  for (size_t bridge : bridges) {
    std::cout << bridge + 1 << "\n";
  }
}
