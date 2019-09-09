template < typename Cost >
class dijkstra {
    int                 n;
    int                 start;
    Cost                inf;
    std::vector< Cost > dist;
    std::vector< std::vector< std::pair< Cost, int > > > graph;

  public:
    dijkstra()=default;
    dijkstra(int n, int start, Cost inf) :
      n(n), start(start), inf(inf), dist(n, inf), graph(n){}

    void insert(int i, int j, Cost cost)
      { graph.at(i).emplace_back(cost, j); }

    void build() {
      std::priority_queue<
        std::pair< Cost, int >,
        std::vector< std::pair< Cost, int > >,
        std::greater< std::pair< Cost, int > >> que;
      que.emplace(0, start);
      while (!que.empty()) {
        Cost d; int crr; std::tie(d, crr) = que.top(); que.pop();
        if (dist.at(crr) <= d) continue;
        dist.at(crr) = d;
        for (auto pair : graph.at(crr)) {
          Cost cost; int nxt; std::tie(cost, nxt) = pair;
          if (dist.at(nxt) <= d + cost) continue;
          que.emplace(d + cost, nxt);
        }
      }
    }

    auto collect() const { return dist; }

    auto at(int i) const { return dist.at(i); }
};