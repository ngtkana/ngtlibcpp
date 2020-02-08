template <class T>
void unique(std::vector<T> & v) {
    std::sort(v.begin(), v.end());
    v.resize(std::unique(v.begin(), v.end()) - v.begin());
}
