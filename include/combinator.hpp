template< typename F >
class fixed_point : F {
    public:
        explicit constexpr fixed_point (F&& f) noexcept
            : F(std::forward< F >(f)) {}
        template< typename ... Args >
        constexpr decltype(auto) operator()(Args&& ... args) const
            { return F::operator()(*this, std::forward< Args >(args)...); }
};
template< typename F >
static inline constexpr decltype(auto) fix (F&& f) noexcept
    { return fixed_point< F >{std::forward< F >(f)}; }
