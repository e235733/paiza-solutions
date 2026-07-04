#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <climits>
#include <cassert>
#include <chrono>
#include <random>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <bitset>
#include <utility>
#include <tuple>
#include <algorithm>
#include <numeric>
#include <functional>
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

    vector<int> dr = {-1, -1, 0, 1, 1, 1, 0, -1};
    vector<int> dc = {0, 1, 1, 1, 0, -1, -1, -1};

    int h, w;
    cin >> h >> w;
    vector M(h, vector<char>(w));
    map<char, vector<int>> pr, pc;
    map<char, set<char>> P, C;
    rep (i, h) rep (j, w) {
        char a;
        cin >> a;
        M[i][j] = a;

        pr[a].push_back(i);
        pc[a].push_back(j);
        if (!P.contains(a)) {
            P[a] = {};
            C[a] = {};
        }
    }
    debug(M);

    int n;
    cin >> n;
    rep (i, n) {
        char a, b;
        cin >> a >> b;
        P[b].insert(a);
        C[a].insert(b);
    }
    debug(P);
    debug(C);


    while (P.size()) {
        vector<char> era;
        for (auto &[a, p] : P) {
            if (!p.size()) {
                debug(a);
                era.push_back(a);
                
                int len = pr[a].size();
                rep (i, len) {
                    if (M[pr[a][i]][pc[a][i]] == '-') continue;
                    rep (j, 8) {
                        int nr = pr[a][i] + dr[j];
                        int nc = pc[a][i] + dc[j];

                        if (nr == -1 || nr == h || nc == -1 || nc == w) continue;
                        if (M[nr][nc] == '-') continue;

                        if (C[a].contains(M[nr][nc])) M[nr][nc] = '-';
                    }
                }
            }
        }
        debug(era);
        for (char e : era) {
            P.erase(e);
        }
        for (auto &[a, p] : P) {
            for (char e : era) {
                p.erase(e);
            }
        }
        debug(P);
    }

    rep (i, h) {
        rep (j, w) {
            if (j == w-1) cout << M[i][j];
            else cout << M[i][j] << ' ';
        }
        cout << '\n';
    }


    return 0;
}