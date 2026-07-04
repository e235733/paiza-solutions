#pragma once
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>
#include <string_view>
#include <algorithm>
using namespace std;

// --- 1. 前方宣言 (互いに呼び合うために必要) ---
template <typename T, typename U> ostream& operator<<(ostream& os, const pair<T, U>& p);
template <typename T> ostream& operator<<(ostream& os, const vector<T>& v);
template <typename T> ostream& operator<<(ostream& os, const deque<T>& v);
template <typename T> ostream& operator<<(ostream& os, const set<T>& v);
template <typename T> ostream& operator<<(ostream& os, const multiset<T>& v);
template <typename T> ostream& operator<<(ostream& os, const unordered_set<T>& v);
template <typename T> ostream& operator<<(ostream& os, const unordered_multiset<T>& v);
template <typename T, typename U> ostream& operator<<(ostream& os, const map<T, U>& m);
template <typename T, typename U> ostream& operator<<(ostream& os, const unordered_map<T, U>& m);
template <typename T, typename U> ostream& operator<<(ostream& os, const unordered_multimap<T, U>& m);
template <typename T> ostream& operator<<(ostream& os, queue<T> q);
template <typename T> ostream& operator<<(ostream& os, stack<T> s);
template <typename T> ostream& operator<<(ostream& os, priority_queue<T> q);

// --- 2. 各種コンテナの出力実装 ---

// pair: (a, b)
template <typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

// 汎用コンテナ出力関数 (内部用)
template <typename T>
void debug_print_container(ostream& os, const T& v, string_view open, string_view close) {
    os << open;
    bool first = true;
    for (const auto& x : v) {
        if (!first) os << ", ";
        os << x;
        first = false;
    }
    os << close;
}

// vector, deque: [a, b, c]
template <typename T> ostream& operator<<(ostream& os, const vector<T>& v) { debug_print_container(os, v, "[", "]"); return os; }
template <typename T> ostream& operator<<(ostream& os, const deque<T>& v) { debug_print_container(os, v, "[", "]"); return os; }

// set, multiset, unordered_set, unordered_multiset: {a, b, c}
template <typename T> ostream& operator<<(ostream& os, const set<T>& v) { debug_print_container(os, v, "{", "}"); return os; }
template <typename T> ostream& operator<<(ostream& os, const multiset<T>& v) { debug_print_container(os, v, "{", "}"); return os; }
template <typename T> ostream& operator<<(ostream& os, const unordered_set<T>& v) { debug_print_container(os, v, "{", "}"); return os; }
template <typename T> ostream& operator<<(ostream& os, const unordered_multiset<T>& v) { debug_print_container(os, v, "{", "}"); return os; }

// map, unordered_map, unordered_multimap: {(k, v), (k, v)}
template <typename T, typename U> ostream& operator<<(ostream& os, const map<T, U>& m) { debug_print_container(os, m, "{", "}"); return os; }
template <typename T, typename U> ostream& operator<<(ostream& os, const unordered_map<T, U>& m) { debug_print_container(os, m, "{", "}"); return os; }
template <typename T, typename U> ostream& operator<<(ostream& os, const unordered_multimap<T, U>& m) { debug_print_container(os, m, "{", "}"); return os; }

// queue, stack, priority_queue (コピーして中身を出す)
template <typename T> ostream& operator<<(ostream& os, queue<T> q) {
    os << "queue[";
    bool first = true;
    while (!q.empty()) { if(!first) os << ", "; os << q.front(); q.pop(); first = false; }
    return os << "]";
}
template <typename T> ostream& operator<<(ostream& os, stack<T> s) {
    os << "stack[";
    // stackは上から見るので一旦vectorに移すなど工夫が必要だが、簡易的に上から出す
    vector<T> v; while(!s.empty()) { v.push_back(s.top()); s.pop(); }
    reverse(v.begin(), v.end()); // 下から順に表示したい場合
    bool first = true; for(const auto& x : v) { if(!first) os << ", "; os << x; first = false; }
    return os << "]";
}
template <typename T> ostream& operator<<(ostream& os, priority_queue<T> q) {
    os << "pq[";
    bool first = true;
    while (!q.empty()) { if(!first) os << ", "; os << q.top(); q.pop(); first = false; }
    return os << "]";
}

// --- 3. debugマクロ本体 ---
void debug_out() { cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << H;
    if (sizeof...(T) > 0) cerr << ", ";
    debug_out(T...);
}

#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
