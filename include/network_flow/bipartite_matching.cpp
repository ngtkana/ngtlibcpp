class bipartite_matching {
  int x, y;
  dinic<int> dnc;
  public:
    bipartite_matching(int x, int y) :
      x(x), y(y), dnc([x, y]{
        dinic<int> dnc(1 + x + y + 1, 0, 1 + x + y);
        for (int i = 0; i < x; i++) dnc.insert(0, 1 + i, 1);
        for (int j = 0; j < y; j++) dnc.insert(1 + x + j, 1 + x + y, 1);
        return dnc;
      }())
      {}
    void insert (int i, int j) {
      dnc.insert(1 + i, 1 + x + j, 1);
    }
    int cal () {return dnc.cal();}
};