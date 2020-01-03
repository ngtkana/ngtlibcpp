template <class T>
struct treap_set_node {
  using key_type = T;
  using value_type = T;
  T key;
  int priority;
  treap_set_node *l, *r;
  treap_set_node(T key, int priority)
    : key(key), priority(priority), l(nullptr), r(nullptr) {}
};


template <class T, class U>
struct treap_map_node {
  using key_type = T;
  using mapped_type = U;
  using value_type = std::pair<T,U>;
  T key;
  U mapped;
  int priority;
  treap_map_node *l, *r;
  treap_map_node(T key, U mapped, int priority)
    : key(key), mapped(mapped), priority(priority), l(nullptr), r(nullptr) {}
};

template <class Node> struct extract_key;

template <class T>
struct extract_key<treap_set_node<T>> {
  T operator()(treap_set_node<T>* t){ return t->key; }
};

template <class T, class U>
struct extract_key<treap_map_node<T,U>> {
  T operator()(treap_map_node<T,U>* t){ return t->key; }
};

template <class Node> struct extract_value;
template <class T>
struct extract_value<treap_set_node<T>> {
  T operator()(treap_set_node<T>* t){ return t->key; }
};
template <class T, class U>
struct extract_value<treap_map_node<T,U>> {
  std::pair<T,U> operator()(treap_map_node<T,U>* t){ return std::make_pair(t->key, t->mapped); }
};

template <class Node, bool HasUniqueKey>
class treap {
    std::size_t size_ = 0;

    using Tree = Node *;

    using key_type = typename Node::key_type;
    using value_type = typename Node::value_type;
    // using mapped_type = typename Node::mapped_type;

    extract_key<Node> key_fn{};
    extract_value<Node> value_fn{};

    Tree root = nullptr;

    void split(Tree t, key_type key, Tree& l, Tree& r, bool by_upper_bound) {
        if (!t) {
            l = r = nullptr;
        } else if (key < key_fn(t) || (key == key_fn(t) && !by_upper_bound)) {
            split(t->l, key, l, t->l, by_upper_bound), r = t;
        } else {
            split(t->r, key, t->r, r, by_upper_bound), l = t;
        }
    }

    void split_by_lower_bound(Tree t, key_type key, Tree& l, Tree& r) {
      split(t,key,l,r,false);
    }
    void split_by_upper_bound(Tree t, key_type key, Tree& l, Tree& r) {
      split(t,key,l,r,true);
    }
    void split_into_tree_parts(Tree t, key_type key, Tree& l, Tree& c, Tree& r) {
      Tree tmp;
      split_by_lower_bound(t, key, l, tmp);
      split_by_upper_bound(tmp, key, c, r);
    }

    void merge(Tree& t, Tree l, Tree r) {
      if (!l || !r) {
        t = l ? l : r;
      } else if (l->priority > r->priority) {
        merge(l->r, l->r, r), t = l;
      } else {
        merge(r->l, l, r->l), t = r;
      }
    }
    void merge_three_trees(Tree& t, Tree l, Tree c, Tree r) {
      Tree tmp;
      merge(tmp, c, r);
      merge(t, l, tmp);
    }

    void insert(Tree& t, Tree item) {
      if (!t) {
        t = item;
      } else if (item->priority > t->priority) {
        split_by_lower_bound(t, item->key, item->l, item->r), t = item;
      } else {
        insert(item->key < key_fn(t) ? t->l : t->r, item);
      }
    }

    void erase(Tree& t, key_type key) {
      Tree l,r,c;
      split_into_tree_parts(t, key, l, c, r);
      merge(t, l, r);
      size_ -= nuke(c);
    }

    std::size_t find(Tree& t, key_type key) {
      Tree l,r,c;
      split_into_tree_parts(t, key, l, c, r);
      std::size_t ans = count(c);
      merge_three_trees(t, l, c, r);
      return ans;
    }

    std::size_t nuke(Tree t) {
      if (!t) return 0;
      std::size_t ret = 1;
      ret += nuke(t->l);
      ret += nuke(t->r);
      delete t;
      return ret;
    }

    std::size_t count(Tree t) {
      if (!t) return 0;
      std::size_t ret = 1;
      ret += count(t->l);
      ret += count(t->r);
      return ret;
    }

    void collect_(std::vector<value_type>& v, Tree t) {
      if (!t) return;
      collect_(v, t->l);
      v.push_back(value_fn(t));
      collect_(v, t->r);
    }

  public:
    std::size_t size() const { return size_; }

    // set
    void insert(key_type key) {
      if (HasUniqueKey && find(key)) return;
      size_++;
      insert(root, new Node(key, xor128()));
    }

   // void insert(key_type key, mapped_type value) {
    //   if (HasUniqueKey && find(key)) return;
    //   size_++;
    //   insert(root, new Node(key, value, xor128()));
    // }

    // void insert_or_replace(key_type key, mapped_type value) {
    //   erase(key);
    //   size_++;
    //   insert(root, new Node(key, value, xor128()));
    // }

    void erase(key_type key) {
      erase(root, key);
    }

    std::size_t find(key_type key) {
      return find(root, key);
    }

    std::vector<value_type> collect(key_type x, key_type y) {
      std::vector<value_type> v;
      Tree l,r,c,tmp;
      split_by_lower_bound(root, x, l, tmp);
      split_by_upper_bound(tmp, y, c, r);
      collect_(v, c);
      merge(tmp, c, r);
      merge(root, l, tmp);
      return v;
    }
    std::vector<value_type> collect() {
      std::vector<value_type> v;
      collect_(v, root);
      return v;
    }
};

template <class T>
class set : public treap<treap_set_node<T>,true> {};
template <class T>
class multiset : public treap<treap_set_node<T>,false>{};

template <class T, class U>
class map : public treap<treap_map_node<T,U>,true> {};
template <class T, class U>
class multimap : public treap<treap_map_node<T,U>,false>{};
