template <typename InputIterator, typename OutputIterator>
constexpr OutputIterator
  coenumerate(InputIterator  first,
              InputIterator  last,
              OutputIterator result)
{
  int cnt = 0;
  while (first != last)
  {
    *result = std::make_pair(*first, cnt);
    result++, first++, cnt++;
  }
  return result;
}