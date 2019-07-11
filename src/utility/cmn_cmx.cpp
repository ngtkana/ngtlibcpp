template<typename T, typename U>
inline auto& cmn (T& a, U b) {return a = a <= b ? a : b;}
template<typename T, typename U>
inline auto& cmx (T& a, U b) {return a = a >= b ? a : b;}
