template < class Value >
struct vending_machine{
  Value i;
  vending_machine (Value i) : i(i){}
  auto issue() { return i++; }
  auto peek() const { return i; }
};