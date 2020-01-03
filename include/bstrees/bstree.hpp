enum class bstree_side {
  left,
  right
};

struct bstree_node_base {
  using this_type = bstree_node_base;
  std::weak_ptr<bstree_node_base> child[2];
  std::weak_ptr<bstree_node_base> parent;
};

template < class Value >
struct bstree_node : public bstree_node_base {
  Value value;
  bstree_node(Value value) : value(value){}
}; // bstree_node

bstree_node_base* bstree_increment(const bstree_node_base* node);
bstree_node_base* bstree_decrement(const bstree_node_base* node);
bstree_node_base* bstree_get_min_child(const bstree_node_base* node);
bstree_node_base* bstree_get_max_child(const bstree_node_base* node);
void bstree_insert(bstree_node_base* node,
                   bstree_node_base* parent,
                   bstree_node_base* anchor,
                   bstree_side insertion_side);
void rbtree_erase(bstree_node_base* node,
                  bstree_node_base* anchor);


template <typename T, typename Pointer, typename Reference>
struct bstree_iterator {
  using this_type = bstree_iterator<T, Pointer, Reference>;
  using iterator = bstree_iterator<T, T*, T&>;
  using const_iterator = bstree_iterator<T, T*, T&>;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using node_type = bstree_node<T>;
  using pointer = Pointer;
  using reference = Reference;
  using iterator_category = std::bidirectional_iterator_tag;

public:
  node_type* node;

public:
  bstree_iterator();
  explicit bstree_iterator(const node_type* node);
  bstree_iterator(const iterator& x);

  reference operator*() const { return node->value; }
  pointer   operator->() const { return &node->value; }

  bstree_iterator& operator++();
  bstree_iterator  operator++(int);

  bstree_iterator& operator--();
  bstree_iterator  operator--(int);

}; // bstree_iterator

// template <typename Compare, bool /*isEmpty*/ = is_empty<Compare>::value>
// struct bs_base_compare_ebo {
// protected:
//   bs_base_compare_ebo() : mCompare() {}
//   bs_base_compare_ebo(const Compare& compare) : mCompare(compare) {}

//   Compare& get_compare() { return mCompare; }
//   const Compare& get_compare() const { return mCompare; }

//   template <typename T>
//   bool compare(const T& lhs, const T& rhs) 
//   {
//     return mCompare(lhs, rhs);
//   }

//   template <typename T>
//   bool compare(const T& lhs, const T& rhs) const
//   {
//     return mCompare(lhs, rhs);
//   }

// private:
//   Compare mCompare;
// };
