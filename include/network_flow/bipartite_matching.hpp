class bipartite_matching
{
    int L, R;
    std::vector<std::vector<int>> graph;
    std::vector<int> match_list, level;

    bool bfs()
    {
      std::fill(level.begin(), level.end(), -1);
      std::queue<int> que;
      for (int i = 0; i < L; i++)
      {
        if (match_list.at(i) < 0)
        {
          level.at(i) = 0;
          que.emplace(i);
        }
      }
      bool ret = false;
      while (!que.empty())
      {
        auto crr = que.front(); que.pop();
        for (auto nxt : graph.at(crr))
        {
          if (level.at(nxt) != -1) continue;
          level.at(nxt) = level.at(crr) + 1;
          auto w = match_list.at(nxt);
          if (w == -1)
          {
            ret = true;
          }
          else if (level.at(w) == -1)
          {
            level.at(w) = level.at(crr) + 1;
            que.emplace(w);
          }
        }
      }
      return ret;
    }

    bool dfs(int crr)
    {
      for (auto nxt : graph.at(crr))
      {
        assert(level.at(nxt) <= level.at(crr) + 1);
        if (level.at(nxt) < level.at(crr) + 1) continue;
        level.at(nxt) = -1;
        auto w = match_list.at(nxt);
        if (w == -1 || dfs(w))
        {
          match_list.at(nxt) = crr;
          match_list.at(crr) = nxt;
          level.at(crr) = -1;
          return true;
        }
      }
      level.at(crr) = -1;
      return false;
    }

  public:
    bipartite_matching()=default;
    bipartite_matching(int L, int R):
      L(L), R(R), graph(L + R), match_list(L + R, -1), level(L + R)
      {}

    void insert_edge(int u, int v)
    {
      v += L;
      graph.at(u).emplace_back(v);
      graph.at(v).emplace_back(u);
    }


    int build ()
    {
      auto ret = 0;
      while (bfs())
      {
        for (int i = 0; i < L; i++)
        {
          if (match_list.at(i) == -1 && dfs(i))
          {
            ret++;
          }
        }
      }
      return ret;
    }

    auto match() const {return match_list;}
};