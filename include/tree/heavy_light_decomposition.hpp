class heavy_light_decomposition
{
  public:
    using size_type  = int;
    using index_type = int;
    using id_type    = int;
    using graph_type = std::vector<std::vector<index_type>>;
    using tablele_type = std::vector<int>;

  private:
    size_type  n;
    graph_type graph;
    tablele_type prt, sz, depth, vid, ord, head;

    // Helper
    void first_dfs(index_type x)
    {
      for (auto& y : graph.at(x))
      {
        if (y == prt.at(x)) continue;
        prt.at(y)   = x;
        depth.at(y) = depth.at(x) + 1;

        first_dfs(y);

        sz.at(x) += sz.at(y);
        auto& h = graph.at(x).front();
        if (sz.at(h) < sz.at(y))
        {
          std::swap(h, y);
        }
      }
    }

    // Helper
    void second_dfs(index_type x, id_type& counter)
    {
      ord.at(vid.at(x) = counter++) = x;
      for (auto y : graph.at(x))
      {
        if (y == prt.at(x)) continue;
        head.at(y) = y == graph.at(x).front()
          ? head.at(x)
          : y;
         second_dfs(y, counter);
      }
    }

  public:
    heavy_light_decomposition()=default;
    heavy_light_decomposition(const heavy_light_decomposition&)=default;
    heavy_light_decomposition(heavy_light_decomposition&&)=default;
    heavy_light_decomposition& operator=(const heavy_light_decomposition&)=default;
    heavy_light_decomposition& operator=(heavy_light_decomposition&&)=default;

    heavy_light_decomposition(int n) :
      n     (n),
      graph (n),
      prt   (n),
      sz    (n, 1),
      depth (n, 0),
      vid   (n),
      ord   (n),
      head  (n)
      {}

    // Accessers.
    auto id(index_type x) const {return vid.at(x);}

    void build (index_type root = 0)
    {
      id_type counter = 0;
      first_dfs(root);
      second_dfs(root, counter);
    }

    void insert (index_type x, index_type y)
    {
      graph.at(x).push_back(y);
      graph.at(y).push_back(x);
    }

    template <typename RangeOp>
    void for_each
    (
      index_type     x,
      index_type     y,
      RangeOp const& op,   // range-operation f([vid(x), vid(y)[)
      bool           skip  // skip the top vertex
    )
    {
      while (true)
      {
        if (id(x) > id(y)) std::swap(x, y);
        if (head.at(x) == head.at(y))
        {
          op(id(x) + skip, id(y) + 1);
          break;
        }
        op(id(head.at(y)), id(y) + 1);
        y = prt.at(head.at(y));
      }
    }
};
