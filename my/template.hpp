#pragma once

using std::vector;
using std::pair;

template<class T> void chmin(T& a, T b) {
    a = std::min(a, b);
}

template<class T> void chmax(T& a, T b) {
    a = std::max(a, b);
}

template<class T> void print2d(vector<vector<T>> vv) {
    using std::cout;
    using std::endl;

    cout << "print2d start" << endl;
    for (vector<T> v : vv) {
        for (T i : v) {
            cout << i << ' ';
        }
        cout << endl;
    }
    cout << "print2d end" << endl;
}

template<class T> using Pairs = vector<pair<T, T>>;
