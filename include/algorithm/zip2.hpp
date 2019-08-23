template <typename InputIterator1,
          typename InputIterator2, typename OutputIterator>
constexpr OutputIterator
  zip2(InputIterator1 first1,
      InputIterator1 last1,
      InputIterator2 first2,
      OutputIterator result)
{
  while (first1 != last1)
  {
    *result = std::make_pair(*first1, *first2);
    result++, first1++, first2++;
  }
  return result;
}
