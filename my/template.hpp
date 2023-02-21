#pragma once

template<class T> void chmin(T& a, T b) {
    a = std::min(a, b);
}

template<class T> void chmax(T& a, T b) {
    a = std::max(a, b);
}

template<class T> void print2d(std::vector<std::vector<T>> vv) {
//    using std::vector
    using std::cout;
    using std::endl;

    cout << "print2d start" << endl;
    for (std::vector<T> v : vv) {
        for (T i : v) {
            cout << i << ' ';
        }
        cout << endl;
    }
    cout << "print2d end" << endl;
}

template<class T> using Pairs = std::vector<std::pair<T, T>>;
