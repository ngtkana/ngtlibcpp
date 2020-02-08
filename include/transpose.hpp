template < typename Value >
auto transpose(std::vector< std::vector< Value > > const& grid) {
    int h = grid.size();
    int w = grid.front().size();
    auto ret = std::vector< std::vector< Value > > (w, std::vector< Value >(h));
    for (auto i = 0; i < h; i++) {
        for(auto j = 0; j < w; j++) {
            ret.at(j).at(i) = grid.at(i).at(j);
        }
    }
    return ret;
}
