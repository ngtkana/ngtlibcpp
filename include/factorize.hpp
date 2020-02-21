inline auto factorize(long long x) {
    std::vector<std::pair<long long,int>> ret;
    for (long long p=2;p*p<=x;p++) {
        int m=0;
        for (;x%p==0;m++)
            {x /= p; }
        if (m>0)
            {ret.emplace_back(p, m);}
    }
    if (1<x)
        {ret.emplace_back(x,1);}
    return ret;
}
