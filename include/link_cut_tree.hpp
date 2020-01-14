struct link_cut_node {
  link_cut_node * left, * right, *parent;
  int size, value, minimum;

  link_cut_node() {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    size = 1;
  }

  void rotate() {
    link_cut_node *pp, *p, *c;
    p = this->parent;
    pp = p->parent;

    if (p->left==this) {
      c = this->right;
      this->right = p;
      p->left = c;
    }
    else {
      c = this->left;
      this->left = p;
      p->right = c;
    }

    if (pp && pp->left==p) pp->left = this;
    if (pp && pp->right==p) pp->right = this;
    this->parent = pp;
    p->parent = this;
    if (c) c->parent = p;

    p->update();
    this->update();
  }
  int state() {
    if (!parent) return 0;
    if (parent->left==this) return 1;
    if (parent->right==this) return -1;
    return {};
  }
  void splay() {
    while (this->state() != 0) {
      if (this->parent->state()==0) {
        this->rotate();
      }
      else if (this->state() == this->parent->state()) {
        this->parent->rotate();
        this->rotate();
      } else {
        this->rotate();
        this->rotate();
      }
    }
  }
  void update() {
    this->size = 1;
    this->minimum = this->value;
    if (this->left) {
      this->size += this->left->size;
      this->minimum = std::min(this->minimum, this->left->minimum);
    }
    if (this->right) {
      this->size += this->right->size;
      this->minimum = std::min(this->minimum, this->right->minimum);
    }
  }
};

link_cut_node * get(int ind, link_cut_node * root) {
  link_cut_node * now = root;
  while (true) {
    int lsize = now->left ? now->left->size : 0;
    if (ind < lsize) {
      now = now->left;
    }
    if (ind == lsize) {
      now->splay();
      return now;
    }
    if (lsize < ind) {
      now = now->right;
      ind = ind - lsize - 1;
    }
  }
}

typedef link_cut_node lcn;

lcn * merge(lcn *lroot, lcn* rroot) {
  if (!lroot) return rroot;
  if (!rroot) return lroot;
  lroot = get(lroot->size - 1, lroot);
  lroot->right = rroot;
  rroot->parent = lroot;
  lroot->update();
  return lroot;
}

std::pair<lcn*, lcn*> split(int left_cnt, lcn* root) {
  if (left_cnt == 0) return {nullptr, root};
  if (left_cnt == root->size) return {root, nullptr};
  root = get(left_cnt, root);
  lcn * lroot, * rroot;
  lroot = root->left;
  rroot = root;
  rroot->left = nullptr;
  lroot->parent = nullptr;
  rroot->update();
  return {lroot, rroot};
}

lcn * insert(int ind, lcn * node, lcn * root) {
  auto trees = split(ind, root);
  lcn * lroot = trees.first;
  lcn * rroot = trees.second;
  return merge( merge(lroot, node), rroot);
}

std::pair<lcn*, lcn*> remove(int ind, lcn * root) {
  root = get(ind, root);
  lcn * lroot = root->left;
  lcn * rroot = root->right;
  if (lroot) lroot->parent = nullptr;
  if (rroot) rroot->parent = nullptr;
  root->left = nullptr;
  root->right = nullptr;
  root->update();
  return {merge(lroot, rroot), root};
}

void access(lcn *v) {
  while (true) {
    v->splay();
    v->right = nullptr;
    v->update();
    if (!v->parent) break;
    v->parent->splay();
    v->parent->right = v;
    v->parent->update();
  }
}

void link(lcn *c, lcn *p) {
  c->parent = p;
}

void cut(lcn *c) {
  assert(c);
  access(c);
  assert(c->left);
  c->left->parent = nullptr;
  c->left = nullptr;
  c->update();
}

lcn *root(lcn *v) {
  access(v);
  lcn *now = v;
  while (now->left) {
    now = now->left;
  }
  return now;
}
