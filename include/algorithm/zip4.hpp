template <typename InputIterator1,
          typename InputIterator2,
          typename InputIterator3,
          typename InputIterator4,
          typename OutputIterator>
constexpr OutputIterator
  zip4(InputIterator1 first1,
      InputIterator1 last1,
      InputIterator2 first2,
      InputIterator3 first3,
      InputIterator4 first4,
      OutputIterator result)
{
  while (first1 != last1)
  {
    *result = std::make_tuple(*first1, *first2, *first3, *first4);
    result++, first1++, first2++, first3++, first4++;
  }
  return result;
}

