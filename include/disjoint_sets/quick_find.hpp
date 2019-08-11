class quick_find
{
public:
  using size_type          = int;
  using node_type          = int;
  using group_type         = int;
  using group_array_type   = std::vector<node_type>;
  using members_array_type = std::vector<std::vector<node_type>>;

private:
  size_type          n;
  group_array_type   leader;
  members_array_type members;

public:
  quick_find (size_type n) : n(n), leader(n), members(n)
  {
    for (int i = 0; i < n; i++) {
      leader.at(i) = i;
    }
    for (int i = 0; i < n; i++) {
      members.at(i) = {i};
    }
  }

  bool       is_root (int x)        const {return find(x) == x;}

  size_type  size    (int x)        const {return members.at(x).size();}

  bool       is_equiv(int x, int y) const {return find(x) == find(y);}

  group_type find    (int x)        const {return leader.at(x);}

  // Returns `true` if x and y are newly connected.
  bool unite   (int x, int y) {
    if ((x = find(x)) == (y = find(y))) return false;
    if (size(x) > size(y)) std::swap(x, y);
    for (auto child : members.at(x))
    {
      leader.at(child) = y;
      members.at(y).push_back(child);
    }
    std::decay_t<decltype(members.at(x))>{}.swap(members.at(x));
    return true;
  }
};