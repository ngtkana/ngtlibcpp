template <typename Cost>
struct edge_with
{
  using index_type = int;
  using cost_type  = Cost;

  index_type from, to;
  cost_type  cost;

  edge_with(index_type from, index_type to, cost_type cost) :
    from(from), to(to), cost(cost)
    {}
};

template <typename Label>
auto std::to_string (const edge_with<Label>& e) -> std::string
{
  return "edge_with{"s
    + "from: "  + std::to_string(e.from) + ", "
    + "to: "    + std::to_string(e.to)   + ", "
    + "label: " + std::to_string(e.label)
    + "}";
}

template <typename Edge>
class graph
{
  public:
    using size_type           = int;
    using index_type          = int;
    using edge_type           = Edge;
    using adjacency_list_type = std::vector<std::vector<edge_type>>;
    using edge_list_type      = std::vector<edge_type>;

  private:
    size_type                   n;
    adjacency_list_type         adjacency_list;
    edge_list_type              edge_list;

  public:
    graph()=default;
    graph(const graph&)=default;
    graph(graph&&)=default;
    graph& operator=(const graph&)=default;
    graph& operator=(graph&&)=default;

    graph(size_type n) :
      n(n),
      adjacency_list(n),
      edge_list()
      {}

    // Element access
    const auto& at       (index_type i) const {return adjacency_list.at(i);}

    // Container access
    auto edges           ()             const {return edge_list;}

    // Capacity
    auto size            ()             const {return n;}

    template <typename... Labels>
    void insert_directed_edge(index_type from, index_type to, Labels... labels)
    {
      adjacency_list.at(from).emplace_back(from, to, labels...);
      edge_list.emplace_back(from, to, labels...);
    }

    template <typename... Labels>
    void insert_undirected_edge(index_type from, index_type to, Labels... labels)
    {
      insert_directed_edge(from, to, labels...);
      insert_directed_edge(to, from, labels...);
    }
};

template <typename Label>
using graph_with = graph<edge_with<Label>>;
