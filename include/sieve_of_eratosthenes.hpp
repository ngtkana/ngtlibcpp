template <size_t N>
class sieve_of_eratosthenes {
        std::bitset<N> is_prime_;

    public:
        constexpr sieve_of_eratosthenes(){
            is_prime_ = ~is_prime_;
            is_prime_.reset(0), is_prime_.reset(1);
            for (size_t p = 2; p < N; p++) {
                if (!is_prime_.test(p)) continue;
                for (size_t j = 2; j * p < N; j++) {
                    is_prime_.reset(p * j);
                }
            }
        }

        // Return the bitset testing if a number is prime.
        constexpr const auto& is_prime() const {return is_prime_;}

        // Returns the vector of prime numbers.
        template <typename T>
        auto primes() const {
            std::vector<T> primes{}; 
            for (size_t i = 0; i < N; i++) {
                if (is_prime_.test(i)) primes.push_back(i);
            }
            return primes;
        }
};