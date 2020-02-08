class fully_indexable_dictionary {
        using value_t = uint32_t;
        using count_t = unsigned;
        static constexpr size_t sz = 8 * sizeof(uint32_t);
        bool built;
        size_t full_length, n;
        std::vector<value_t> row_data;
        std::vector<count_t> rank_table;

    public:
        fully_indexable_dictionary(size_t full_length) :
            built(false),
            full_length(full_length),
            n((full_length + sz - 1) / sz),
            row_data(n), rank_table(n) {
                debug(sz, n);
            }

        // Set the i-th bit.
        void set(size_t i) {
            assert(!built);
            row_data.at(i / sz) |= (1u << i);
        }

        // Initialize the rank-table.
        void build() {
            assert(!built);
            rank_table = [&]{
                std::vector<count_t> pop_counts(n), rank_table(n);
                std::transform(row_data.begin(), row_data.end(), pop_counts.begin(),
                    [](auto x){return __builtin_popcountl(x);});
                std::partial_sum(pop_counts.begin(), pop_counts.end(), rank_table.begin());
                rank_table.insert(rank_table.begin(), 0u);
                return rank_table; 
            }();
            built = true;
            debug(row_data, rank_table);
        }

        // Access the i-th bit.
        auto access(size_t i) const -> bool {
            return row_data.at(i / sz) >> (i % sz) & 1u;
        }
        // An alias of access
        auto at(size_t i) const -> bool {return access(i);}
        
        // Count the 1.
        auto rank(size_t i) const -> count_t {
            return rank_table.at(i / sz)
                + __builtin_popcountl(row_data.at(i / sz) & ((1 << (i % sz)) - 1));
        }

        // Find the k-th 1. (That is the maximal i such that rank(i) <= k.)
        // When not found, returns the full-size of the sequence.
        auto select(size_t k) const -> size_t {
            size_t left = 0, right = full_length + 1, mid;
            while (right - left > 1) {
                mid = (left + right) / 2;
                (rank(mid) <= k ? left : right) = mid;
            }
            return left;
        }
};