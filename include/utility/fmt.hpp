// require gcc >= 7.1.0
template < class ... Keys >
class fmt_t {
    using storage_t = std::tuple< Keys ... >;
    storage_t storage;
    static constexpr std::size_t N = sizeof ... (Keys);

    // is_exact_match_impl
    template < std::size_t I, class Value >
      auto is_exact_match_impl(long, Value) const
        { return false; }

    template < std::size_t I, class Value,
      std::enable_if_t<
        std::is_same< std::decay_t< Value > , char >::value
        == std::is_same< std::tuple_element_t< I, storage_t >, char >::value,
      std::nullptr_t > = nullptr,
      class = decltype(std::declval< Value >() == std::get< I >(std::declval< storage_t >())) >
      auto is_exact_match_impl(int, Value x) const
        { return x == std::get< I >(storage); }

    template < class Value, std::size_t ... Is >
      auto find_exact_match_impl(Value x, std::integer_sequence< std::size_t, Is ... >) const {
        auto ret = false;
        (void)std::initializer_list< std::nullptr_t >
          { (ret |= is_exact_match_impl< Is >(int{}, x), nullptr) ...  };
        return ret;
      }

    template < class Value >
      auto exists_exact_match(Value x) const
      {  return find_exact_match_impl(x, std::make_index_sequence< N >()); }

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
      { return exists_exact_match(x) ? std::string{'_'} : usual_format(int{}, x); }

  public:
    fmt_t()=default;
    template < Keys ... > fmt_t(Keys&& ... keys ) : storage(keys ... ){}

    template < class Value > std::string operator()(Value&& x) const
      { return format(x); }
};
template < class ... Keys > auto fmt(Keys&& ... keys)
  { return fmt_t< Keys ... >(std::forward< Keys >(keys) ... ); }
