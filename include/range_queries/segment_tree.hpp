template <class Seg, class SegPtr>
struct segment_tree_entry;

template <class Seg, class SegPtr, class Pointer, class Reference>
struct segment_tree_iterator;

template <typename Value, typename BinaryOp>
class segment_tree {
public:
  using value_type = Value;
  using this_type = segment_tree<Value, BinaryOp>;
  using entry_type = segment_tree_entry<this_type, this_type*>;
  using const_entry_type = segment_tree_entry<this_type, this_type const*>;
  using iterator = segment_tree_iterator<this_type, this_type*, value_type*, value_type&>;
  using const_iterator = segment_tree_iterator<this_type, this_type const*, value_type const*, value_type const&>;

friend class segment_tree_entry<this_type, this_type*>;
friend class segment_tree_entry<this_type, this_type const*>;

private:
  int                  sz, n, N;
  BinaryOp             op;
  Value                id;
  std::vector< Value > table;

  auto& op_assign(Value& x, Value y) const
    { return x = op(x, y); }
  void merge(int u)
    { table.at(u) = op(table.at(2 * u), table.at(2 * u + 1)); }

public:
  segment_tree(int sz, BinaryOp op, Value id):
    sz(sz), n(std::pow(2, int(std::log2(2*sz-1)))), N(n * 2), op(op), id(id), table (N, id) {}

  iterator begin()
    { return iterator(this, 0); }

  iterator end()
    { return iterator(this, sz); }

  const_iterator begin() const
    { return const_iterator(this, 0); }

  const_iterator end() const
    { return const_iterator(this, sz); }

  auto at(std::size_t i)
    { return entry_type(this, i); }

  auto at(std::size_t i) const
    { return table.at(n + i); }

  auto& lazy_at(std::size_t i)
    { return table.at(n + i); }

  auto& lazy_at(std::size_t i) const
    { return table.at(n + i); }

  auto collect() const {
    auto ret = std::vector<Value>(sz);
    for (auto i = 0; i < sz; i++)
      { ret.at(i) = at(i); }
    return ret;
  }

  auto query(int l, int r) const {
    auto const dfs = [&](auto&& f, int l, int r, int k, int L, int R) -> Value {
      return l <= L && R <= r ? table.at(k)
        : R <= l || r <= L ? id
        : op(f(f, l, r, 2*k, L, (L+R)/2), f(f, l, r, 2*k+1, (L+R)/2, R));
    };
    return dfs(dfs, l, r, 1, 0, n);
  }

  void build()
    { for (auto i = n - 1; i > 0; i--) merge(i); }
};

template <class Seg, class SegPtr>
class segment_tree_entry {
  using value_type = typename Seg::value_type;
  SegPtr seg;
  std::size_t i;

  auto& get()
    { return seg->table.at(seg->n + i); }

  void build_oneline(int i)
    { for (i += seg->n, i /= 2; i > 0; i /= 2) seg->merge(i); }

public:
  segment_tree_entry(SegPtr seg, std::size_t i) : seg(seg), i(i) {}

  operator value_type() {
    return seg->table.at(seg->n + i);
  }
  void operator=(value_type x) {
    seg->table.at(seg->n + i) = x;
    build_oneline(i);
  }
  void operator+=(value_type x) {
    seg->table.at(seg->n + i) += x;
    build_oneline(i);
  }
  void operator-=(value_type x) {
    seg->table.at(seg->n + i) += x;
    build_oneline(i);
  }
  void operator*=(value_type x) {
    seg->table.at(seg->n + i) += x;
    build_oneline(i);
  }
  void operator/=(value_type x) {
    seg->table.at(seg->n + i) += x;
    build_oneline(i);
  }
};

template <class Seg, class SegPtr, class Pointer, class Reference>
class segment_tree_iterator {
  using this_type = segment_tree_iterator<Seg, SegPtr, Pointer, Reference>;
  using value_type = typename Seg::value_type;
  using pointer = Pointer;
  using reference = Reference;

  template <class Seg_, class SegPtr_, class Pointer_, class Reference_>
  friend bool operator!=(segment_tree_iterator<Seg_, SegPtr_, Pointer_, Reference_>, segment_tree_iterator<Seg_, SegPtr_, Pointer_, Reference_>);

  SegPtr seg;
  std::size_t i;

public:
  segment_tree_iterator(SegPtr seg, std::size_t i) : seg(seg), i(i) {}

  this_type& operator++(){ i++; return *this; }
  this_type  operator++(int){ auto old = *this; ++i; return old; }
  pointer operator->(){ return &seg->at(i); }
  value_type operator*(){ return seg->at(i); }
};

template <class Seg, class SegPtr, class Pointer, class Reference>
bool operator!=(segment_tree_iterator<Seg, SegPtr, Pointer, Reference> a, segment_tree_iterator<Seg, SegPtr, Pointer, Reference> b) {
  return a.i != b.i;
}

template<typename Value, typename BinaryOp>
auto make_segment_tree(int sz, BinaryOp const& op, Value id)
  { return segment_tree<Value, BinaryOp>(sz, op, id); }