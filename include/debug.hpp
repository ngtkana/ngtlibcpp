void debug_impl() { std::cerr << std::endl; }
template <typename Head, typename... Tail>
void debug_impl(Head head, Tail... tail) { std::cerr << " " << head; debug_impl(tail...); }
#define DEBUG 1
#if DEBUG
#define debug(...)\
    do {\
        std::cerr << std::boolalpha << "[" << #__VA_ARGS__ << "]:";\
        debug_impl(__VA_ARGS__);\
        std::cerr << std::noboolalpha;\
    } while (false)
#else
#define debug(...) {}
#endif
