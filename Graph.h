#pragma once

#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

class Graph {
private:
    map<int, set<int>> g;
    set<int> verts;
    set<pair<int, int>> ribs;

public:
    // Конструкторы графа
    Graph(){};
    Graph(const vector<pair<int, int>> &gr, bool oriented = false) {
        for (auto& [v, u] : gr) {
            g[v].insert(u);
            verts.insert({v, u});
            ribs.insert({v, u});

            if (!oriented) {
                g[u].insert(v);
            }
        }
    }
    Graph(const map<int, set<int>> &g) : g{g} {
        for (auto& [v, lst] : g) {
            verts.insert(v);
            for (auto u : lst) {
                verts.insert(u);
                ribs.insert({v, u});
            }
        }
    }


    map<int, set<int>> getG() {
        return g;
    }
    set<int> getVerts() {
        return verts;
    }
    set<pair<int, int>> getRibs() {
        return ribs;
    }


    // Добавление вершины
    bool addVert(int v) {
        if (verts.count(v)) {
            return false;
        }
        verts.insert(v);
        g[v];

        return true;
    }


    // Удаление вершины
    bool removeVert(int v) {
        if (!verts.count(v)) {
            return false;
        }
        verts.erase(v);
        g.erase(v);
        for (auto& [u, lst] : g) {
            if (lst.count(v)) {
                lst.erase(v);
                if (ribs.count({u, v})) {
                    ribs.erase({u, v});
                }
                if (ribs.count({v, u})) {
                    ribs.erase({v, u});
                }
            }
        }
        return true;
    }


    // Добавление ребра
    bool addRibs(pair<int, int> r, bool oriented = false) {
        int v = r.first, u = r.second;

        if (ribs.count(r) || !oriented && ribs.count({u, v})) {
            return false;
        }

        ribs.insert(r);
        g[v].insert(u);
        if (!oriented) {
            g[u].insert(v);
        }

        return true;
    }


    // Удаление ребра
    bool removeRibs(pair<int, int> r, bool oriented = false) {
        int v = r.first, u = r.second;

        if (!oriented && !ribs.count(r) && !ribs.count({u, v})) {
            return false;
        }
        if (oriented && !ribs.count(r)) {
            return false;
        }
        if (ribs.count(r)) {
            ribs.erase(r);
        }
        else {
            ribs.erase({u, v});
        }

        g[v].erase(u);

        if (!oriented) {
            g[u].erase(v);
        }

        return true;
    }


    // Чтение графа из файла
    static Graph readGraph(istream& in = cin) {
        bool oriented;
        int n, m;
        in >> n >> m >> oriented;

        vector<pair<int, int>> g0(n);
        for (int i = 0; i < m; ++i) {
            in >> g0[i].first >> g0[i].second;
        }

        return Graph(g0, oriented);
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
            out << endl;
            out << "Ribs: " << ribs.size() << endl;
        }

        for (auto [v, u] : ribs) {
            out << v << " " << u << endl;
        }

    }


    // Для данной вершины орграфа вывести все «выходящие» соседние вершины
    set<int> task1a1(int v) {
        if (!verts.count(v)) {
            cout << "Такой вершины не существует";
        }
        set<int> k;
        for (auto& [u, to] : ribs) {
            if (u == v) {
                k.insert(to);
            }
        }
        return k;
    }


    // Вывести  полустепень исхода данной вершины орграфа
    int task1a2(int v) {
        if (!verts.count(v)) {
            cout << "Такой вершины не существует";
        }
        int k = 0;
        for (auto& [u, to] : ribs) {
            if (u == v) {
                k++;
            }
        }
        return k;
    }


    // Построить орграф, являющийся дополнением данного орграфа
    Graph task1b3() {

        vector<pair<int, int>> res;

        for (auto v : verts) {
            for (auto u : verts) {
                if (v != u && !ribs.count({v, u})) {
                    res.push_back({v, u});
                }
            }
        }


        return Graph(res, true);
    }


    // Посчитать количество связных компонент графа
    int task2_5() {
        if (verts.empty()) {
            return 0;
        }

        map<int, bool> used;
        for (auto v : verts) {
            used[v] = false;
        }

        int cnt = 0;
        for (auto [v, flag] : used) {
            if (!flag) {
                dfs(v, used);
                ++cnt;
            }
        }
        return cnt;
    }


    // Связный ли граф
    bool task2_4() {
        return task2_5() == 1;
    }


    // Обход в глубину
    void dfs(int v, map<int, bool>& used) {
        used[v] = true;

        for (auto to : g[v]) {
            if (!used[to]) {
                dfs(to, used);
            }
        }

    }
};


// Сравнение графов
bool operator==(Graph g1,  Graph g2) {
    return g1.getG() == g2.getG();
}

ostream& operator<<(ostream& os, const Graph& g) {
    g.printGraph(os);
    return os;
}
