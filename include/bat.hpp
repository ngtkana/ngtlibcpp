template < class Value >
bool bat(Value x, std::size_t pos) { return (x >> pos) & Value{1}; }
