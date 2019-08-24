template <typename Value>
struct dinic_edge
{
  int to; Value cap; int rev;
  dinic_edge(int to, Value cap, int rev): to(to), cap(cap), rev(rev){}
};

template <typename Value>
std::ostream& operator<< (std::ostream& os, const dinic_edge<Value>& e)
{
  return os
    << "dinic_edge{"
    << "to:" << e.to << ","
    << "cap:" << e.cap << ","
    << "rev:" << e.rev
    << "}";
}

template <typename Value>
class dinic {

  const int n, source, sink;
  std::vector<bool> ckd;
  std::vector<int> level;
  std::vector<std::vector<dinic_edge<Value>>> graph;
  static constexpr Value inf = std::numeric_limits<Value>::max();

  void bfs ()
  {
    std::queue<int> que;
    que.emplace(source); level.at(source) = 0;
    while (!que.empty())
    {
      auto crr = que.front(); que.pop();
      for (auto const& e : graph.at(crr))
      {
        if (e.cap == 0) continue;
        int nxt = e.to;
        if (level.at(nxt) != -1) continue;
        que.push(nxt);
        level.at(nxt) = level.at(crr) + 1;
      }
    }
  }

  auto dfs (int crr, int f = inf) -> Value
  {
      if (crr == sink) return f;
      ckd.at(crr) = true;
      for (auto& e : graph.at(crr))
      {
        auto nxt = e.to;
        if (ckd.at(nxt) || e.cap == 0 || level.at(crr) >= level.at(nxt)) continue;
        auto d = dfs(nxt, std::min(f, e.cap));
        if (d > 0)
        {
          e.cap -= d;
          graph.at(nxt).at(e.rev).cap += d;
          return d;
        }
      }
      level.at(crr) = -1;
      return 0;
  }

  public:
    dinic (int n, int source, int sink) :
      n(n), source(source), sink(sink), graph(n)
      {}
    void insert(int u, int v, Value c)
    {
      int k = graph.at(u).size();
      int l = graph.at(v).size();
      graph.at(u).emplace_back(v, c, l);
      graph.at(v).emplace_back(u, 0, k);
    }

    Value build()
    {
      Value ret = 0;
      while (true)
      {
        level.assign(n, -1);
        bfs();
        if (level.at(sink) == -1) return ret;
        ckd.assign(n, false);
        while (true)
        {
          Value f = dfs(source);
          if (f == 0) break;
          ret += f;
        }
      }
    }
};