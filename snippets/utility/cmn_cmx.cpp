template<typename T, typename U>
inline auto cmn (T& a, U b) {if (a > b) {a = b; return true;} return false;}
template<typename T, typename U>
inline auto cmx (T& a, U b) {if (a < b) {a = b; return true;} return false;}