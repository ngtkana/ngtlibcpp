auto make_failure_table (std::string w) -> std::vector<int>
{
    int n = w.length();
    std::vector<int> ret(n + 1, -1);
    int len = 0, pos = 1;
    while (pos < n) {
        if (w.at(pos) == w.at(len)) {
            ret.at(pos) = ret.at(len);
        } else {
            ret.at(pos) = len;
            len = ret.at(len);
            while (len >= 0 && w.at(len) != w.at(pos)) len = ret.at(len);
        }
        len++, pos++;
    }
    ret.at(pos) = len;
    return ret;
}

class kmp_algorithm
{
        std::string w;
        std::vector<int> failure_table;

    public:
        kmp_algorithm()=default;

        kmp_algorithm(const std::string& w) :
            w(w),
            failure_table(std::move(make_failure_table(this->w)))
            {}

        // Returns the starting positions of all the matches.
        auto search(std::string s) -> std::vector<int>
        {
            std::vector<int> ret;
            int pos_w = 0, pos_s = 0;
            while (pos_s < (int)s.length()) {
                if (s.at(pos_s) == w.at(pos_w)) {
                    pos_s++, pos_w++;
                    if (pos_w == (int)w.length()) {
                        ret.push_back(pos_s - pos_w);
                        pos_w = failure_table.at(pos_w);
                    }
                } else {
                    pos_w = failure_table.at(pos_w);
                    if (pos_w < 0) {
                        pos_s++, pos_w++;
                    }
                }
            }
            return ret;
        }
};
