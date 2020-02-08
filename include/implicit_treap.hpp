unsigned long xor128() {
    static unsigned long x=123456789, y=362436069, z=521288629, w=88675123;
    unsigned long t=(x^(x<<11));
    x=y; y=z; z=w;
    return ( w=(w^(w>>19))^(t^(t>>8)) );
}

template <class Op1, class Op2, class Op3>
class implicit_treap {
    Op1 op1;
    Op2 op2;
    Op3 op3;
    int id1;
    int id2;

    auto& op2_eq(int& x, int y){ return x = op2(x, y); }
    auto& op3_eq(int& x, int y){ return x = op3(x, y); }

    struct node_type {
        int key, get_acc, lazy;
        int priority, cnt;
        bool rev;
        node_type *l, *r;
        node_type(int key, int priority, int get_acc, int lazy)
            : key(key), get_acc(get_acc), lazy(lazy), priority(priority), cnt(1), rev(false), l(nullptr), r(nullptr)
            {}
    };
    using pointer = node_type *;
    pointer root = nullptr;

    node_type * make_node(int key) {
        return new node_type(key, xor128(), id1, id2);
    }

    int cnt(pointer t) {
        return t ? t->cnt : 0;
    }

    int get_min(pointer t) {
        return t ? t->get_acc : id1;
    }

    void update_cnt(pointer t) {
        if (t) {
            t->cnt = 1 + cnt(t->l) + cnt(t->r);
        }
    }

    void update_min(pointer t) {
        if (t) {
            t->get_acc = op1(t->key, op1(get_min(t->l), get_min(t->r))); // key == value, now
        }
    }

    void pushup(pointer t) {
        update_cnt(t), update_min(t);
    }

    void pushdown(pointer t) {
        if (t && t->rev) {
            t->rev = false;
            std::swap(t->l, t->r);
            if (t->l) t->l->rev ^= 1;
            if (t->r) t->r->rev ^= 1;
        }
        if (t && t->lazy != id2) {
            if (t->l) {
                op3_eq(t->l->lazy, t->lazy);
                op2_eq(t->l->get_acc, t->lazy);
            }
            if (t->r) {
                op3_eq(t->r->lazy, t->lazy);
                op3_eq(t->r->get_acc, t->lazy);
            }
            op2_eq(t->key, t->lazy); // key == value, now
            t->lazy = id2;
        }
        pushup(t);
    }

    void split(pointer t, int key, pointer& l, pointer& r) {
        if (!t) {
            l = r = nullptr;
            return;
        }
        pushdown(t);
        int implicit_key = cnt(t->l) + 1;
        if (key < implicit_key) {
            split(t->l, key, l, t->l), r = t;
        } else {
            split(t->r, key - implicit_key, t->r, r), l = t;
        }
        pushup(t);
    }

    void insert(pointer& t, int key, pointer item) {
        pointer t1, t2;
        split(t, key, t1, t2);
        merge(t1, t1, item);
        merge(t, t1, t2);
    }

    void merge(pointer& t, pointer l, pointer r) {
        pushdown(l);
        pushdown(r);
        if (!l || !r) {
            t = l ? l : r;
        } else if (l->priority > r->priority) {
            merge(l->r, l->r, r), t = l;
        } else {
            merge(r->l, l, r->l), t = r;
        }
        pushup(t);
    }

    void erase(pointer& t, int key) {
        pointer t1, t2, t3;
        split(t, key + 1, t1, t2);
        split(t1, key, t1, t3);
        merge(t, t1, t2);
    }

    void act(pointer t, int l, int r, int x) {
        pointer t1, t2, t3;
        split(t, l, t1, t2);
        split(t2, r - l, t2 , t3);
        op3_eq(t2->lazy, x);
        op2_eq(t2->get_acc, x);
        merge(t2, t2, t3);
        merge(t, t1, t2);
    }

    int get_acc(pointer t, int l, int r) {
        pointer t1, t2, t3;
        split(t, l, t1, t2);
        split(t2, r - l, t2, t3);
        int ret = t2->get_acc;
        merge(t2, t2, t3);
        merge(t, t1, t2);
        return ret;
    }

    void reverse(pointer t, int l, int r) {
        if (l > r) return;
        pointer t1, t2, t3;
        split(t, l, t1, t2);
        split(t2, r - l, t2, t3);
        t2->rev ^= 1;
        merge(t2, t2, t3);
        merge(t, t1, t2);
    }

    void rotate(pointer t, int l, int m, int r) {
        reverse(t, l, r);
        reverse(t, l, l + r - m);
        reverse(t, l + r - m, r);
    }

public:
    implicit_treap(Op1 op1, Op2 op2, Op3 op3, int id1, int id2)
        : op1(op1), op2(op2), op3(op3), id1(id1), id2(id2){}

    void insert(int pos, int x) {
        insert(root, pos, make_node(x));
    }

    void act(int l, int r, int x) {
        act(root, l, r, x);
    }

    int get_acc(int l, int r) {
        return get_acc(root, l, r);
    }

    void erase(int pos) {
        erase(root, pos);
    }

    void reverse(int l, int r) {
        reverse(root, l, r);
    }

    void rotate(int l, int m, int r) {
        rotate(root, l, m, r);
    }

    auto collect() {
        std::vector<int> ret;
        auto dfs = [&] (auto&&dfs, pointer t) -> void {
            if (!t) return;
            this->pushdown(t); // workaround for GCC 5
            dfs(dfs, t->l);
            ret.emplace_back(t->key);
            dfs(dfs, t->r);
        };
        dfs(dfs, root);
        return ret;
    }
};

template <class Op1 ,class Op2, class Op3>
auto make_implicit_treap(Op1 op1, Op2 op2, Op3 op3, int id1, int id2) {
    return implicit_treap<Op1, Op2, Op3>(op1, op2, op3, id1, id2);
}
