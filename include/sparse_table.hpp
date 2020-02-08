template < class Value, class Op >
class sparse_table {
        int n, ht;
        Op op;
        std::vector< std::vector< Value > > table;

    public:
        sparse_table()=default;
        sparse_table(std::vector< Value > const & a, Op const & op) :
            n(a.size()),
            ht(std::log2(n) + 1),
            op(op),
            table([this, &a, &op]{
                std::vector< std::vector< Value > > table(ht, a);
                auto block = 1;
                for (auto & v : table) {
                    auto forward = false;
                    auto l = 0, r = block;
                    for (; forward || r <= n; l += block, r += block, forward ^= 1) {
                        if (forward)
                            { std::partial_sum(v.begin() + l, v.begin() + std::min(r, n), v.begin() + l, op);}
                        else
                            { std::partial_sum(v.rbegin() + n - r, v.rbegin() + n - l, v.rbegin() + n - r, op); }
                    }
                    block *= 2;
                }
                return table;
            }())
            {}

        auto query(int l, int r) const {
            r--;
            if (l == r) return table.front().at(l);
            auto const & v = table.at(std::log2(l ^ r));
            return op(v.at(l), v.at(r));
        }
};
template < class Value, class Op >
auto make_sparse_table(std::vector< Value > const & a, Op const & op)
    { return sparse_table< Value, Op>(a, op); }
