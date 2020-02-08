class trie_node {
        int                                 d;     // Root -> 0, One letter -> 1
        std::vector< int >    ids;
        std::vector< int >    nexts;

    public:
        trie_node(int n, int d): d(d), ids(), nexts(n, -1) {}

        auto get_ids()     const { return ids;     }
        auto get_nexts() const { return nexts; }
        auto depth()         const { return d;         }

        decltype(auto) emplace_back(int x) { return ids.emplace_back(x); }
        decltype(auto) at                    (int i) { return nexts.at(i);     }
};

std::ostream& operator<< (std::ostream& os, trie_node const& v) {
    auto const & a = v.get_ids();
    auto const & b = v.get_nexts();
    os << "({";
    for (auto it = a.begin(); it != a.end(); it++)
        { os << (it == a.begin() ? "" : " " ) << *it; }
    os << "},{";
    for (auto it = b.begin(); it != b.end(); it++)
        { os << (it == b.begin() ? "" : " " ) << *it; }
    return os << "})";
}

template < typename Fn >
class trie {
    int                                 n;             // The number of the kinds of chars
    int                                 cnt;         // The number of the strings
    std::vector< trie_node > storage; // The seq of nodes
    Fn                                    encoder; // char -> int

public:
    trie()=default;
    trie(int n, const Fn& encoder):
        n(n),
        cnt(0),
        storage(1, trie_node(n, 0)),
        encoder(encoder)
        {}

    auto get() const { return storage; }

    // Automatically issue a string id.
    void insert(const std::string& s) {
        std::vector< int > seq(s.length());
        std::transform(s.begin(), s.end(), seq.begin(), encoder);
        auto pos = 0, d = 0;
        for (auto x : seq) {
            d++;
            auto& now            = storage.at(pos);
            auto& next_pos = now.at(x);
            if (next_pos == -1) {
                next_pos = storage.size();
                storage.emplace_back(n, d);
            }
            pos = next_pos;
        }
        storage.at(pos).emplace_back(cnt++);
    }

    // Return the string ids.
    auto find(const std::string& s) {
        std::vector<int> seq(s.length());
        std::transform(s.begin(), s.end(), seq.begin(), encoder);
        auto vid = 0;
        for (auto x : seq) {
            vid = storage.at(vid).at(x);
            if (vid == -1) return std::vector< int >{};
        }
        return storage.at(vid).get_ids();
    }

    auto count(const std::string& s)
        { return find(s).size(); }

    // Return the pairs of length & id
    auto find_prefices(const std::string& s) {
        int    n     = s.length();
        auto ret = std::vector< std::pair< int, int > >{};
        auto vid = 0;
        for (int i = 0; i < n; i++) {
            vid = storage.at(vid).at(encoder(s.at(i)));
            if (vid == -1) return ret;
            for (auto id : storage.at(vid).get_ids())
                { ret.emplace_back(i + 1, id); }
        }
        return ret;
    }
};

template < typename Fn >
auto make_trie(int n, const Fn& encoder)
    { return trie< Fn >(n, encoder); }
