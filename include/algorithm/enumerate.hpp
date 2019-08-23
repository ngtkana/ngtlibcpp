template <typename InputIterator, typename OutputIterator>
constexpr OutputIterator
  enumerate(InputIterator  first,
              InputIterator  last,
              OutputIterator result)
{
  int cnt = 0;
  while (first != last)
  {
    *result = std::make_pair(cnt, *first);
    result++, first++, cnt++;
  }
  return result;
}