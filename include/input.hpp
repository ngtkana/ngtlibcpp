template<class T>struct input_iterator{
    int n;
    input_iterator(int n):n(n){}
    input_iterator&operator++(){--n;return*this;}
    T operator*()const{T x;std::cin>>x;return x;}
};
template<class T>bool operator!=(input_iterator<T>lhs,input_iterator<T>rhs){return lhs.n!=rhs.n;}
template<class T>class input{
        int n;
    public:
        input(int n):n(n){}
        input_iterator<T> begin()const{return input_iterator<T>(n);}
        input_iterator<T> end()const{return input_iterator<T>(0);}
};
