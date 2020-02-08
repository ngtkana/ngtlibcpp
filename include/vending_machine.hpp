template < class Value >
struct vending_machine{
    Value i;
    vending_machine(Value i) : i(i){}
    auto issue() { return i++; }
    auto peek() const { return i; }
};
template < class Value >
auto make_vending_machine(Value i)
    { return vending_machine< Value >(i); }
