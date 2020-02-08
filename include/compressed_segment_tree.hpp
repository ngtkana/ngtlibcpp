template<typename T, typename U>
class compressed_segment_tree {
    const std::vector<T> a;
    const size_t sz, Sz;
    std::vector<U> seg;
    const std::function<U(U, U)> o;
    const U id;
    auto find (T k) const {
        auto it = std::lower_bound(a.begin(), a.end(), k);
        assert(it != a.end() && *it == k);
        return it - a.begin() + sz;
    }
    public:
        compressed_segment_tree (
                const std::vector<T> a,
                const std::function<U(U, U)> o,
                const U id
            ) :
            a(a),
            sz([&](){
                    size_t ret = 1;
                    for (; ret < a.size(); ret <<= 1) {}
                    return ret;
                }()),
            Sz(sz << 1),
            seg(Sz, id),
            o(o),
            id(id)
            {
            }
        void update (T x, const U& y) {
            auto k = find(x);
            seg[k] = y;
            while(k >>= 1) {
                seg[k] = o(seg[2 * k], seg[2 * k + 1]);
            }
        }
        void add (T x, const U& y) {
            update(x, at(x) + y);
        }
        U query (T l, T r) {
            l = std::lower_bound(a.begin(), a.end(), l) - a.begin();
            r = std::lower_bound(a.begin(), a.end(), r) - a.begin();
            U L = id, R = id;
            for(l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
                if(l & 1) L = o(L, seg[l++]);
                if(r & 1) R = o(seg[--r], R);
            }
            return o(L, R);
        }
        U at (T x) const {
            return seg[find(x)];
        }
        void print () const {
            int n = a.size();
            std::cout << std::setw(4) << "----"; for (int i = 0; i < n; i++) std::cout << std::setw(4) << "----" ; std::cout << std::endl;
            std::cout << std::setw(4) << ""; for (auto const& e : a) std::cout << std::setw(4) << e; std::cout << std::endl;
            std::cout << std::setw(4) << "----"; for (int i = 0; i < n; i++) std::cout << std::setw(4) << "----" ; std::cout << std::endl;
            std::cout << std::setw(4) << "val"; for (auto const& e : a) std::cout << std::setw(4) << at(e); std::cout << std::endl;
            std::cout << std::setw(4) << "----"; for (int i = 0; i < n; i++) std::cout << std::setw(4) << "----" ; std::cout << std::endl;
        }
};