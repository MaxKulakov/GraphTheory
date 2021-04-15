#pragma once

#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

class WeightGraph {
private:
    const int INF = 1e9;

    map<int, set<pair<int, int>>> g;
    set<int> verts;
    set<tuple<int, int, int>> ribs;
public:

    // Конструкторы
    WeightGraph(){};
    WeightGraph(const vector<tuple<int, int, int>> &gr, bool oriented = false) {
        for (auto& [v, u, w] : gr) {
            g[v].insert({u, w});
            verts.insert({v, u});
            ribs.insert({v, u, w});

            if (!oriented) {
                g[u].insert({v, w});
            }
        }
    }
    WeightGraph(const map<int, set<pair<int, int>>> &g) : g{g} {
        for (auto& [v, lst] : g) {
            verts.insert(v);
            for (auto& [u, w] : lst) {
                verts.insert(u);
                ribs.insert({v, u, w});
            }
        }
    }


    map<int, set<pair<int, int>>> getG() {
        return g;
    }
    set<int> getVerts() {
        return verts;
    }
    set<tuple<int, int, int>> getRibs() {
        return ribs;
    }


    // Чтение графа из файла
    static WeightGraph readGraph(istream& in = cin) {
        bool oriented;
        int n, m;
        in >> n >> m >> oriented;

        vector<tuple<int, int, int>> g0(n);
        for (int i = 0; i < m; ++i) {
            int v, u, w;
            in >> v >> u >> w;
            g0[i] = {v, u, w};
        }

        return WeightGraph(g0, oriented);
    }


    // Вывод графа
    void printGraph(ostream& out = cout, bool oriented = false, bool forFile = false) const {
        if (forFile) {
            out << verts.size() << " " << ribs.size() << " " << oriented << endl;
        }
        else {
            out << "Vertices: " << verts.size() << endl;
            for (auto v : verts) {
                out << v << " ";
            }
            cout << endl;
            out << "Ribs: " << ribs.size() << endl;
        }

        for (auto [v, u, w] : ribs) {
            out << v << " " << u << " " << w << endl;
        }

    }


    // Краскал
    pair<WeightGraph, int> Kraskal() {

        vector<tuple<int, int, int>> rs;
        for (auto& [v, u, w] : ribs) {
            rs.push_back({w, v, u});
        }

        sort(rs.begin(), rs.end());

        map<int, int> id;
        for (auto v: verts) {
            id[v] = v;
        }

        int ans = 0;
        vector<tuple<int, int, int>> r;

        for (auto& [w, v, u] : rs) {
            if (id[v] != id[u]) {
                ans += w;
                r.push_back({v, u, w});
                int old_id = id[v];
                int new_id = id[u];
                for (auto [v, i] : id) {
                    if (i == old_id) {
                        id[v] = new_id;
                    }
                }
            }
        }
        return {WeightGraph(r), ans};
    }


    //4a_1 Дейкстра
    map<int, int> dijkstra(int s) {
        map<int, int> d;
        for (auto v : verts) {
            d[v] = INF;
        }

        d[s] = 0;
        set<pair<int, int>> q;
        q.insert({d[s], s});

        while (!q.empty()) {
            int v = q.begin()->second;
            q.erase(q.begin());

            for (auto& [to, w] : g[v]) {
                if (d[v] + w < d[to]) {
                    q.erase({d[to], to});
                    d[to] = d[v] + w;
                    q.insert({d[to], to});
                }
            }
        }
        return d;
    }


    // Определить, существует ли путь длиной не более L между двумя заданными вершинами графа
    bool task4a_1(int st, int fn, int L) {
        auto res = dijkstra(st);
        return res[fn] <= L;
    }


    //4b_2 Флойд
    map<int, map<int, int>> floyd() {
        map<int, map<int, int>> d;

        for (auto v : verts) {
            for (auto u : verts) {
                d[v][u] = v == u ? 0 : INF;
            }
        }

        for (auto [v, u, w] : ribs) {
            d[v][u] = w;
            d[u][v] = w;
        }

        for (auto k : verts) {
            for (auto i : verts) {
                for (auto j : verts) {
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
        return d;
    }


    // Определить, есть ли в графе вершина, минимальные стоимости путей
    // от которой до остальных в сумме не превосходят P
    bool task4b_2(int P) {
        auto res = floyd();

        for (auto [v, p] : res) {
            int sum = 0;
            for (auto [u, d] : p) {
                sum += d;
            }

            if (sum <= P) {
                return true;
            }
        }

        return false;
    }


    // Определить, есть ли в графе вершина, каждая из минимальных стоимостей пути
    // от которой до остальных не превосходит N
    bool task4c_3(int N) {
        auto res = floyd();

        for (auto [v, p] : res) {
            int mx = 0;
            for (auto [u, d] : p) {
                mx = max(mx, d);
            }
            if (mx <= N) {
                return true;
            }
        }
        return false;
    }

};


bool operator==(WeightGraph g1,  WeightGraph g2) {
    return g1.getG() == g2.getG();
}


ostream& operator<<(ostream& os, const WeightGraph& g) {
    g.printGraph(os);
    return os;
}