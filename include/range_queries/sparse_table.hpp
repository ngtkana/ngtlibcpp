template < class Value, class Op >
class sparse_table {
    int n;
    Op op;
    std::vector< int > floor_log;
    int ht;
    std::vector< std::vector< Value > > table;

  public:
    sparse_table()=default;
    sparse_table(std::vector< Value > const & a, Op const & op) :
      n(a.size()),
      op(op),
      floor_log([this]{
        std::vector< int > ret(2 * n, -1);
        for (auto i = 1; i < 2 * n; i++)
          { ret.at(i) = ret.at(i / 2) + 1; }
        return ret;
      }()),
      ht(floor_log.at(n) + 1),
      table([this, &a, &op]{
        std::vector< std::vector< Value > > table(ht, a);
        auto block = 1;
        for (auto & v : table) {
          for (auto j = 0; j < n; j++) {
            auto const l = j * block, r = l + block;
            if (j % 2 == 0) {
              if (n <= r) break;
              for (auto k = r - 2; l <= k; k--)
                { v.at(k) = op(v.at(k), v.at(k + 1)); }
            } else {
              for (auto k = l + 1; k < std::min(r, n); k++)
                { v.at(k) = op(v.at(k), v.at(k - 1)); }
            }
          }
          block *= 2;
        }
        return table;
      }())
      {}

    auto query(int l, int r) const {
      r--;
      if (l == r) return table.front().at(l);
      auto const & v = table.at(floor_log.at(l ^ r));
      return op(v.at(l), v.at(r));
    }
};
template < class Value, class Op >
auto make_sparse_table(std::vector< Value > const & a, Op const & op)
  { return sparse_table< Value, Op>(a, op); }
