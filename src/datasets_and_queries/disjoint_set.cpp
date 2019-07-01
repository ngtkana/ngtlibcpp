class disjoint_set {
	int n;
	std::vector<int> prt;
	public:
		disjoint_set (int n)
			: n(n), prt(n, -1)
			{
			}
			inline bool is_root (int x) const {
				return prt[x] < 0;
			}
			inline int size (int x) {
				return -prt[find(x)];
			}
			inline bool equiv (int x, int y) {
				return find(x) == find(y);
			}
			int find (int x) {
				return (is_root(x) ? x : (prt[x] = find(prt[x])));
			}
			inline bool unite (int x, int y) {
				x = find(x); y = find(y);
				if (x == y) return false;
				if (size(x) < size(y)) std::swap(x, y);
				prt[x] += prt[y];
				prt[y] = x;
				return true;
			}
};