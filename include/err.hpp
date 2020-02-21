void err() { std::cout << $1 << std::endl; exit(0); }
#define require(exp) do { if (!(exp)) { err(); } } while(false)
