class heavy_light_decomposition {
    int n;
    std::vector< std::vector< int > > graph;
    std::vector < int > prt, sz, vid, ord, head;

  public:
    heavy_light_decomposition()=default;
    heavy_light_decomposition(int n) :
      n     (n),
      graph (n),
      prt   (n),
      sz    (n, 1),
      vid   (n),
      ord   (n),
      head  (n)
      {}

    // Accessers.
    auto id(int x) const {return vid.at(x);}

    void build (int root = 0) {
      auto const dfs = [&](auto&& f , auto crr) -> void {
        for (auto& nxt : graph.at(crr)) {
          if (nxt == prt.at(crr)) continue;
          prt.at(nxt) = crr;
          f(f, nxt);
          sz.at(crr) += sz.at(nxt);
          auto& h = graph.at(crr).front();
          if (sz.at(h) < sz.at(nxt))
            { std::swap(h, nxt); }
        }
      };
      dfs(dfs, root);

      auto vm = 0;
      auto const efs = [&](auto&& f, auto crr) -> void {
        ord.at(vid.at(crr) = vm++) = crr;
        for (auto nxt : graph.at(crr)) {
          if (nxt == prt.at(crr)) continue;
          head.at(nxt) = nxt == graph.at(crr).front() ? head.at(crr) : nxt;
          f(f, nxt);
        }
      };
      efs(efs, root);
    }

    void insert (int x, int y) {
      graph.at(x).push_back(y);
      graph.at(y).push_back(x);
    }

    template < class RangeOp >
    void for_each (
      int x,
      int y,
      RangeOp const& op,   // range-operation f([vid(x), vid(y)[)
      bool skip            // skip the top vertex
    )
    {
      while (true) {
        if (id(x) > id(y)) std::swap(x, y);
        if (head.at(x) == head.at(y)) {
          op(id(x) + skip, id(y) + 1);
          return;
        }
        op(id(head.at(y)), id(y) + 1);
        y = prt.at(head.at(y));
      }
    }
};
