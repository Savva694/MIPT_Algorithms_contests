#include <algorithm>
#include <iostream>
#include <set>
#include <stack>
#include <vector>

size_t my_time = 0;

struct Node {
  size_t vert;
  int color;
  size_t tin;
  size_t tout;
  size_t ret;
  size_t parent;

  Node() : vert(0), color(0), tin(0), tout(0), ret(0), parent(0) {}

  Node(size_t vert)
      : vert(vert), color(0), tin(0), tout(0), ret(0), parent(0) {}

  Node(const Node& other)
      : vert(other.vert),
        color(other.color),
        tin(other.tin),
        tout(other.tout),
        ret(other.ret),
        parent(other.parent) {}

  Node& operator=(const Node& other) {
    vert = other.vert;
    color = other.color;
    tin = other.tin;
    tout = other.tout;
    ret = other.ret;
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

std::vector<Node> vertices;
std::vector<std::vector<Edge>> edges;
std::vector<size_t> bridges;

void Dfs(size_t vertex) {
  ++my_time;
  vertices[vertex].color = 1;
  vertices[vertex].tin = my_time;
  for (Edge neighbour : edges[vertex]) {
    if (vertices[neighbour.vertex_2].color == 0) {
      vertices[neighbour.vertex_2].parent = vertex;
      ++my_time;
      Dfs(neighbour.vertex_2);
      ++my_time;
    }
  }
  vertices[vertex].color = 2;
  vertices[vertex].tout = my_time;
}

void RetCounting(size_t vertex) {
  vertices[vertex].color = 1;
  vertices[vertex].ret = vertices[vertex].tin;
  for (size_t index = 0; index < edges[vertex].size(); ++index) {
    Edge neighbour = edges[vertex][index];
    if (vertices[vertex].tin >= vertices[neighbour.vertex_2].tin &&
        vertices[vertex].tout <= vertices[neighbour.vertex_2].tout &&
        vertices[vertex].parent != neighbour.vertex_2) {
      vertices[vertex].ret =
          std::min(vertices[vertex].ret, vertices[neighbour.vertex_2].tin);
    }
    if (vertices[neighbour.vertex_2].color == 0) {
      vertices[neighbour.vertex_2].color = 1;
      RetCounting(neighbour.vertex_2);
      if (vertices[vertex].parent != neighbour.vertex_2) {
        vertices[vertex].ret =
            std::min(vertices[vertex].ret, vertices[neighbour.vertex_2].ret);
      }
      if (vertices[vertex].tin < vertices[neighbour.vertex_2].ret) {
        size_t vertex_count = 0;
        for (Edge edge : edges[vertex]) {
          if (edge.vertex_2 == neighbour.vertex_2) {
            ++vertex_count;
          }
        }
        if (vertex_count == 1) {
          bridges.push_back(edges[vertex][index].edge_id);
        }
      }
    }
  }
  vertices[vertex].color = 2;
}

int main() {
  size_t vertex_count;
  size_t edge_count;
  std::cin >> vertex_count;
  std::cin >> edge_count;
  vertices.resize(vertex_count);
  edges.resize(vertex_count);

  for (size_t i = 0; i < vertex_count; ++i) {
    vertices[i] = Node(i);
  }

  size_t vertex_1;
  size_t vertex_2;
  for (size_t i = 0; i < edge_count; ++i) {
    std::cin >> vertex_1;
    std::cin >> vertex_2;
    edges[vertex_1 - 1].push_back(Edge(vertex_1 - 1, vertex_2 - 1, i));
    edges[vertex_2 - 1].push_back(Edge(vertex_2 - 1, vertex_1 - 1, i));
  }

  for (size_t i = 0; i < vertex_count; ++i) {
    if (vertices[i].color == 0) {
      Dfs(i);
    }
  }

  for (size_t i = 0; i < vertex_count; ++i) {
    vertices[i].color = 0;
  }

  for (size_t i = 0; i < vertex_count; ++i) {
    if (vertices[i].color == 0) {
      RetCounting(i);
    }
  }

  sort(bridges.begin(), bridges.end());
  std::cout << bridges.size() << "\n";
  for (size_t bridge : bridges) {
    std::cout << bridge + 1 << "\n";
  }
}
