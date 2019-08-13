template <typename Cost>
class bellman_ford : public graph_with<Cost>
{
    using base_type  = graph_with<Cost>;
    using index_type = typename base_type::index_type;
    using size_type  = typename base_type::size_type;
    using edge_type  = typename base_type::edge_type;

    using cost_type  = Cost;

  private:
    size_type              n;
    std::vector<cost_type> dist;
    const cost_type inf = std::numeric_limits<cost_type>::max();

    // Helper
    void relax(const edge_type& e, bool fever=false)
    {
      if (dist.at(e.from) == inf) return;
      auto& target  = dist.at(e.to);
      auto  renewer = dist.at(e.from) + e.cost;
      if (renewer < target)
      {
        target = (fever ? -inf : renewer);
      }
    }

    // Helper
    void relax_all(bool fever=false)
    {
      for (auto e : base_type::edges())
      {
        relax(e, fever);
      }
    }

  public:
    bellman_ford()=default;
    bellman_ford(const bellman_ford&)=default;
    bellman_ford(bellman_ford&&)=default;
    bellman_ford& operator=(const bellman_ford&)=default;
    bellman_ford& operator=(bellman_ford&&)=default;

    bellman_ford(size_type n) :
      base_type(n),
      n(n)
      {
        dist.resize(n, inf);
      }

    auto build (index_type start, index_type goal)
    -> std::pair<cost_type, bool>
    {
      dist.at(start) = 0;
      for (int i = 0; i < n; i++) relax_all();
      for (int i = 0; i < n; i++) relax_all(true);
      auto ret = dist.at(goal);
      return {ret, ret == -inf};
    }
};
