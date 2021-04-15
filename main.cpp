#include <vector>
#include <cassert>
#include <tuple>

#include "Graph.h"
#include "WeightGraph.h"

bool Task1() {

    // Добавление ребра
    {
        vector<pair<int, int>> r1 = {{1, 2}, {2, 3}, {3, 4}};
        Graph g1(r1);

        g1.addRibs({1, 3});

        vector<pair<int, int>> r2 =  {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
        Graph g2(r2);

        assert(g1 == g2);
    }

    // Добавление вершины
    {
        vector<pair<int, int>> r1 = {{1, 2}, {2, 3}, {3, 4}};
        Graph g1(r1);

        g1.addVert(6);
        assert(g1.getVerts() == set<int>({1, 2, 3, 4, 6}));
    }

    // Удаление вершины (1)
    {
        vector<pair<int, int>> r1 = {{1, 2}, {2, 3}, {3, 4}};
        Graph g1(r1);

        assert(!g1.removeVert(6));
    }

    // Удаление вершины (2)
    {
        vector<pair<int, int>> r1 = {{1, 2}, {2, 3}, {3, 4}};
        Graph g1(r1);

        vector<pair<int, int>> r2 = {{2, 3}, {3, 4}};
        Graph g2(r2);

        assert(g1.removeVert(1));
        assert(g1 == g2);
    }

    // Удаление ребра (1)
    {
        vector<pair<int, int>> r1 = {{1, 2}, {2, 3}, {3, 4}};
        Graph g1(r1);

        assert(!g1.removeRibs({1, 4}));
    }

    // Удаление ребра (2)
    {
        vector<pair<int, int>> r1 = {{1, 2}, {2, 3}, {3, 4}};
        Graph g1(r1);

        vector<pair<int, int>> r2 = {{2, 3}, {3, 4}};
        Graph g2(r2);
        g2.addVert(1);

        assert(g1.removeRibs({1, 2}));
        assert(g1 == g2);
    }

    return true;
}


// Для данной вершины орграфа вывести все «выходящие» соседние вершины
void Task1a_1() {
    {
        vector<pair<int, int>> r1 = {{1, 3}, {1, 2}, {2, 3}, {3, 4}, {3, 5}, {4, 5},
                                     {2, 5}, {2, 6}, {6, 5}, {6, 7}, {7, 5}};
        Graph g(r1, true);

        assert(g.task1a1(1) == set<int>({2, 3}));
        assert(g.task1a1(2) == set<int>({3, 5, 6}));
        assert(g.task1a1(3) == set<int>({4, 5}));
    }
}


// Вывести  полустепень исхода данной вершины орграфа
void Task1a_2() {
    {
        vector<pair<int, int>> r1 = {{1, 3}, {1, 2}, {2, 3}, {3, 4}, {3, 5}, {4, 5},
                                     {2, 5}, {2, 6}, {6, 5}, {6, 7}, {7, 5}};
        Graph g(r1, true);

        assert(g.task1a2(1) == 2);
        assert(g.task1a2(2) == 3);
        assert(g.task1a2(3) == 2);
    }
}


// Построить орграф, являющийся дополнением данного орграфа
void Task1b_3() {
    {
        vector<pair<int, int>> r1 = {{1, 3}, {1, 2}, {2, 3}, {3, 4}, {3, 5},
                                     {4, 5}, {2, 5}, {5, 1}};
        Graph g1(r1, true);

        vector<pair<int, int>> r2 = {{1, 5}, {5, 4}, {4, 3}, {3, 2}, {2, 1},
                                     {1, 4}, {4, 1}, {3, 1}, {2, 4}, {4, 2},
                                     {5, 3}, {5, 2}};
        Graph g2(r2, true);

        assert(g1.task1b3() == g2);
    }
}


// Связный ли граф
void Task2_4() {
    vector<pair<int, int>> r1 = {{1, 3}, {1, 2}, {4, 5}, {5, 6}, {7, 8}};
    Graph g(r1);

    assert(g.task2_4() == false);

    vector<pair<int, int>> r2 = {{2, 8}, {1, 2}, {1, 5}, {5, 6}, {6, 8}};
    Graph g2(r2);

    assert(g2.task2_4() == true);
}


// Посчитать количество связных компонент графа
void Task2_5() {
    vector<pair<int, int>> r1 = {{1, 3}, {1, 2}, {4, 5}, {5, 6}, {7, 8}};
    Graph g(r1);

    assert(g.task2_5() == 3);

    g.addVert(10);
    assert(g.task2_5() == 4);

}


// Найти каркас минимального веса
void Task3() {
    //Test1
    {
        vector<tuple<int, int, int>> r1 = {{1, 2, 1}, {2, 3, 4}, {1, 3, 3}};
        WeightGraph g1(r1);

        auto ans = g1.Kraskal();
        auto res = ans.first;
        int cost = ans.second;

//        cout << res;

        assert(cost == 4);
    }

    //Test2
    {
        vector<tuple<int, int, int>> r1 = {{1, 3, 7}, {1, 2, 4}, {2, 3, 9}, {3, 4, 11}, {3, 5, 10}, {4, 5, 5},
                                          {2, 5, 15}, {2, 6, 6}, {6, 5, 12}, {6, 7, 13}, {7, 5, 8}};
        WeightGraph g1(r1);

        auto ans = g1.Kraskal();
        auto res = ans.first;
        int cost = ans.second;

//        cout << res;

        assert(cost == 40);
    }
}


//Определить, существует ли путь длиной не более L между двумя заданными вершинами графа
void Task4a_1() {
    vector<tuple<int, int, int>> r1 = {{1, 2, 1}, {2, 3, 4}, {1, 3, 3}, {2, 5, 5}, {5, 6, 10},
                                       {3, 7, 8}, {6, 7, 1}};
    WeightGraph g1(r1);

    int st = 2, fn = 6, L = 13;
    assert(g1.task4a_1(st, fn, L) == true);
    L = 12;
    assert(g1.task4a_1(st, fn, L) == false);

    st = 1; fn = 5; L = 5;
    assert(g1.task4a_1(st, fn, L) == false);

    L = 7;
    assert(g1.task4a_1(st, fn, L) == true);
}


// Определить, есть ли в графе вершина, минимальные стоимости путей
// от которой до остальных в сумме не превосходят P
void Task4b_2() {
    vector<tuple<int, int, int>> r1 = {{1, 2, 1}, {2, 3, 4}, {1, 3, 3}, {2, 5, 5}, {5, 6, 10},
                                       {3, 7, 8}, {6, 7, 1}};
    WeightGraph g1(r1);

    auto d = g1.floyd();

//    for (auto [v, p] : d) {
//        cout << v << " : ";
//        for (auto [u, pp] : p) {
//            cout << "(" << u << ", " << pp << ") ";
//        }
//        cout << endl;
//    }

    assert(g1.task4b_2(50) == true);
    assert(g1.task4b_2(33) == true);
    assert(g1.task4b_2(0) == false);
    assert(g1.task4b_2(20) == false);
}

// Определить, есть ли в графе вершина, каждая из минимальных стоимостей пути
// от которой до остальных не превосходит N
void Task4c_3() {
    vector<tuple<int, int, int>> r1 = {{1, 2, 1}, {2, 3, 4}, {1, 3, 3}, {2, 5, 5}, {5, 6, 10},
                                       {3, 7, 8}, {6, 7, 1}};
    WeightGraph g1(r1);

    auto d = g1.floyd();

    for (auto [v, p] : d) {
        cout << v << " : ";
        for (auto [u, pp] : p) {
            cout << "(" << u << ", " << pp << ") ";
        }
        cout << endl;
    }

    assert(g1.task4c_3(9) == true);
    assert(g1.task4c_3(10) == true);
    assert(g1.task4c_3(12) == true);
    assert(g1.task4c_3(14) == true);
    assert(g1.task4c_3(13) == true);

    assert(g1.task4c_3(8) == false);
    assert(g1.task4c_3(7) == false);
    assert(g1.task4c_3(5) == false);
    assert(g1.task4c_3(0) == false);

}

int main() {

    ifstream in("../input.txt");
    ofstream out("../output.txt");

    Task1();

    Task1a_1();
    Task1a_2();
    Task1b_3();

    Task2_4();
    Task2_5();

    Task3();

    Task4a_1();
    Task4b_2();
    Task4c_3();

    return 0;
}