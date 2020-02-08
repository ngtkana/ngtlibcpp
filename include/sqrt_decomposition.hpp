class sqrt_decomposition {
    public:
        int n, block_size, block_number;

        sqrt_decomposition(int n, int block_size) :
            n(n),
            block_size(block_size),
            block_number((n + block_size - 1) / block_size)
            {}

        auto get_block_size()     const { return block_size;     }
        auto get_block_number() const { return block_number; }

        template < class Append, class Stamp >
        void query(int l, int r, Append const & append, Stamp const & stamp) {
            while (l % block_size && l < r) {
                append(l, l / block_size);
                l++;
            }
            while (r % block_size && l < r) {
                r--;
                append(r, r / block_size);
            }
            for (auto j = l / block_size; j < r / block_size; j++) {
                stamp(j);
            }
        }
};
