template <class Key>
class fmt_t {
    Key key;

    template <class Value>
    auto is_exact_match(long, Value) const {
      return false;
    }

    template <class Value, class = decltype(std::declval< Value >() == key)>
    auto is_exact_match(int, Value x) const {
      return x == key;
    }


    // tuple_format_impl
    template < class Tuple,  std::size_t ... Is >
    std::string tuple_format_impl(const Tuple& tuple, std::integer_sequence< std::size_t, Is ... >) const {
      std::string ret = "(";
      (void)std::initializer_list< std::nullptr_t >
        { (ret = ret + (Is == 0 ? "" : ",") + format(std::get< Is >(tuple)), nullptr) ... };
      return ret + ")";
    }

    // usual_format
    template < class Value >
    std::string usual_format(long, Value x) const
      { return std::to_string(x); }

    template < class Value, std::enable_if_t< std::is_same< std::decay_t< Value >, char >::value, std::nullptr_t > = nullptr >
    std::string usual_format(int, Value c) const
      { return std::string{'\''} + std::string{c} + std::string{'\''}; }

    std::string usual_format(int, char const* s) const
      { return "\"" + std::string(s) + "\""; }

    std::string usual_format(int, std::string const s) const
      { return "\"" + s + "\""; }

    template < class Container, class = typename Container::value_type >
    std::string usual_format(int, Container const & v) const {
      return "{" + std::accumulate(v.begin(), v .end(), std::string{},
        [this](auto const& s, auto const x) { return s + (s.empty() ? "" : ",") + this->format(x); })
        + "}";
    }

    template < class Tuple, std::size_t N = std::tuple_size< Tuple >::value >
    std::string usual_format(int, Tuple const& tuple) const
      { return tuple_format_impl(tuple, std::make_index_sequence< N >()); }

    // format
    template < class Value > std::string format(Value&& x) const
      { return is_exact_match(int{}, x) ? std::string{'_'} : usual_format(int{}, x); }

  public:
    fmt_t()=default;
    fmt_t(Key&& key) : key(key){}

    template < class Value > std::string operator()(Value&& x) const
      { return format(x); }
};
template <class Key> auto fmt(Key key)
  { return fmt_t<Key>(std::forward<Key>(key)); }