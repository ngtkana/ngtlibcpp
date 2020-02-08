class mo_algorithm {
        int n, q, block;
        std::vector< std::tuple< int, int, int > > queries;

    public:
        mo_algorithm(int n, int q, int block) :
            n(n),
            q(q),
            block(block),
            queries(q)
            {}

        void set(int i, int l, int r)
            { queries.at(i) = std::make_tuple(i, l, r); }

        void build() {
            std::sort(queries.begin(), queries.end(), [this](auto const& a, auto const& b){
                int la, ra, lb, rb;
                std::tie(std::ignore, la, ra) = a;
                std::tie(std::ignore, lb, rb) = b;
                auto qa = la / block, qb = lb / block;
                return qa != qb
                    ? qa < qb
                    : qa % 2 == 1
                    ? ra < rb
                    : ra > rb;
            });
        }

        template < class Append, class Remove, class Write >
        void run(Append const & append, Remove const & remove, Write const & write) {
            auto i = 0, j = 0;
            for(auto const tuple : queries) {
                int id, l, r; std::tie(id, l, r) = tuple;
                while (l < i) append(--i);
                while (j < r) append(j++);
                while (i < l) remove(i++);
                while (r < j) remove(--j);
                write(id);
            }
        }
};
