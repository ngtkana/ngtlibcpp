struct splay_node {
  splay_node * left, * right, *parent;
  int size, value, minimum;

  splay_node() {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    size = 1;
  }

  void rotate() {
    splay_node *pp, *p, *c;
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

splay_node * get(int ind, splay_node * root) {
  splay_node * now = root;
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

typedef splay_node sn;

sn * merge(sn *lroot, sn* rroot) {
  if (!lroot) return rroot;
  if (!rroot) return lroot;
  lroot = get(lroot->size - 1, lroot);
  lroot->right = rroot;
  rroot->parent = lroot;
  lroot->update();
  return lroot;
}

std::pair<sn*, sn*> split(int left_cnt, sn* root) {
  if (left_cnt == 0) return {nullptr, root};
  if (left_cnt == root->size) return {root, nullptr};
  root = get(left_cnt, root);
  sn * lroot, * rroot;
  lroot = root->left;
  rroot = root;
  rroot->left = nullptr;
  lroot->parent = nullptr;
  rroot->update();
  return {lroot, rroot};
}

sn * insert(int ind, sn * node, sn * root) {
  auto trees = split(ind, root);
  sn * lroot = trees.first;
  sn * rroot = trees.second;
  return merge( merge(lroot, node), rroot);
}

std::pair<sn*, sn*> remove(int ind, sn * root) {
  root = get(ind, root);
  sn * lroot = root->left;
  sn * rroot = root->right;
  if (lroot) lroot->parent = nullptr;
  if (rroot) rroot->parent = nullptr;
  root->left = nullptr;
  root->right = nullptr;
  root->update();
  return {merge(lroot, rroot), root};
}
