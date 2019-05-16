template<typename T>
class run_length_encoding {
  vector<pair<int, T>> rle;
  public:
    run_length_encoding(
        vector<T> input
      ) :
      rle(0)
      {
        int cnt = 0;
        for (auto it = input.begin(); it != input.end(); it++) {
          auto jt = next(it); cnt++;
          if (jt == input.end() || *it != *jt) {
            rle.emplace_back(cnt, *it);
            cnt = 0;
          }
        }
      }
    auto const& code () const {return rle;}
};