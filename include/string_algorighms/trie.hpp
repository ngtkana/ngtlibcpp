
template <int Num, typename ConvertFn>
class trie
{
  struct node
  {
    int                   sz;
    std::vector<int>      ids;
    std::array <int, Num> nxt;

    node():
      sz  (0),
      ids ()
      {
        std::fill(nxt.begin(), nxt.end(), -1);
      }

     auto& next(int i) {return nxt.at(i);}
  };

  std::vector<node> storage;
  ConvertFn         f;

  void insert_impl(const std::string& s, int id)
  {
    std::vector<int> seq(s.length());
    std::transform(s.begin(), s.end(), seq.begin(), f);
    auto pos = 0;
    for (auto x : seq)
    {
      auto& now      = storage.at(pos);
      auto& next_pos = now.next(x);
      now.sz++;
      if (next_pos == -1)
      {
        next_pos = storage.size();
        storage.emplace_back();
      }
      pos = next_pos;
    }
    auto& now = storage.at(pos);
    now.sz++;
    now.ids.emplace_back(id);
  }

public:
  trie()=default;
  trie(const trie&)=default;
  trie(trie&&)=default;
  trie& operator=(const trie&)=default;
  trie& operator=(trie&&)=default;

  trie(const ConvertFn& f):
    storage {node{}},
    f       (f)
    {}

  // The id is automatically issued.
  void insert(const std::string& s)
  {
    insert_impl(s, storage.front().sz);
  }

  // Return the ids.
  auto find(const std::string& s) -> std::vector<int>
  {
    std::vector<int> seq(s.length());
    std::transform(s.begin(), s.end(), seq.begin(), f);
    auto pos = 0;
    for (auto x : seq)
    {
      auto& now = storage.at(pos);
      pos = now.next(x);
      if (pos == -1) return{};
    }
    return storage.at(pos).ids;
  }
};

template <int Num, typename ConvertFn>
auto make_trie(const ConvertFn& f)
{
  return trie<Num, ConvertFn>(std::move(f));
}