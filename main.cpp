#include <algorithm>
#include <iostream>
#include <set>
#include <stack>
#include <vector>

size_t my_time = 0;
size_t kss_count = 0;

struct Node {
  size_t vert;
  int color;
  size_t tin;
  size_t tout;
  size_t ret;

  Node() : vert(-1), color(-1), tin(-1), tout(-1), ret(-1) {}

  Node(size_t vert) : vert(vert), color(0), tin(-1), tout(-1), ret(-1) {}

  Node(const Node& other)
      : vert(other.vert),
        color(other.color),
        tin(other.tin),
        tout(other.tout),
        ret(other.ret) {}

  Node& operator=(const Node& other) {
    vert = other.vert;
    color = other.color;
    tin = other.tin;
    tout = other.tout;
    ret = other.ret;
    return *this;
  }
};

std::vector<Node> vertices;
std::vector<std::set<size_t>> edges;
std::vector<std::set<size_t>> reverse_edges;

void Dfs(size_t vertex, const std::vector<std::set<size_t>>& local_edges) {
  ++my_time;
  vertices[vertex].color = 1;
  vertices[vertex].tin = my_time;
  vertices[vertex].ret = kss_count;
  for (int neighbour : local_edges[vertex]) {
    if (vertices[neighbour].color == 0) {
      vertices[neighbour].color = 1;
      ++my_time;
      Dfs(neighbour, local_edges);
      ++my_time;
    }
  }
  vertices[vertex].color = 2;
  vertices[vertex].tout = my_time;
}

bool CompareTout(Node first, Node second) { return first.tout > second.tout; }

bool CompareVert(Node first, Node second) { return first.vert < second.vert; }

int main() {
  size_t vertex_count;
  size_t edge_count;
  std::cin >> vertex_count;
  std::cin >> edge_count;
  vertices.resize(vertex_count);
  edges.resize(vertex_count);
  reverse_edges.resize(vertex_count);
  for (size_t i = 0; i < vertex_count; ++i) {
    vertices[i] = Node(i);
  }

  size_t vertex_1;
  size_t vertex_2;
  for (size_t i = 0; i < edge_count; ++i) {
    std::cin >> vertex_1;
    std::cin >> vertex_2;
    edges[vertex_1 - 1].insert(vertex_2 - 1);
    reverse_edges[vertex_2 - 1].insert(vertex_1 - 1);
  }

  for (size_t i = 0; i < vertex_count; ++i) {
    if (vertices[i].color == 0) {
      Dfs(i, edges);
    }
  }

  std::vector<Node> vertexes_copy = vertices;
  sort(vertexes_copy.begin(), vertexes_copy.end(), CompareTout);
  for (size_t i = 0; i < vertex_count; ++i) {
    vertices[i].color = 0;
  }

  for (size_t i = 0; i < vertex_count; ++i) {
    if (vertices[vertexes_copy[i].vert].color == 0) {
      ++kss_count;
      Dfs(vertexes_copy[i].vert, reverse_edges);
    }
  }

  std::cout << kss_count << "\n";
  for (size_t i = 0; i < vertex_count; ++i) {
    std::cout << vertices[i].ret << " ";
  }
}
