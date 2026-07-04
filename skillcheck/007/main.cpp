#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <stack>
#include <cmath>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

#ifndef LOCAL
#define debug(...)
#endif

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
    #endif

    string s;
    cin >> s;

    vector<ll> count(26, 0);
    stack<ll> st;

    ll m = 1;
    ll p = -1;
    for (char c : s) {
        if (c - 'a' >= 0 && c - 'a' < 26) {
            if (p == -1) {
                count[c-'a'] += m;
            }
            else {
                count[c-'a'] += m * p;
            }
            
            p = -1;
        }
        else if (c - '0' >= 0 && c - '0' < 10) {
            if (p == -1) p = c - '0';
            else {
                p *= 10LL;
                p += c - '0';
            }
        }
        else if (c == '(') {
            m *= p;
            st.push(p);
            p = -1;
        }
        else if (c == ')') {
            m /= st.top();
            st.pop();
        }
    }

    rep (i, 26) {
        cout << (char)('a' + i) << ' ' << count[i] << '\n';
    }

    return 0;
}