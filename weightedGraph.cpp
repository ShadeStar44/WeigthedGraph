// Weigthed Graph for navigation
// By: Alexander N Olson
//
//Check there is path from src and dest 

#include<iostream>
#include <list>

using namespace std;

class weightedGraph {
public:
    int size;
    list<pair<int, int>>* adjlist;

    weightedGraph(int s) {
        adjlist = new list<pair<int, int>>[s];
        size = s;
    }
    void addEdge(int u, int v, int w) {
        adjlist[u].push_back(make_pair(v, w));
        adjlist[v].push_back(make_pair(u, w));
    }
    void removeEdge(int u, int v) {
        for (int j = 0; j <= maxW(); j++) {
            adjlist[u].remove(make_pair(v, j));
            adjlist[v].remove(make_pair(u, j));
        }
    }
    void modEdge(int u, int v, int w) {
        removeEdge(u, v);
        addEdge(u, v, w);
    }
    void addVector() {
        list<pair<int, int>>* temp;
        temp = adjlist;
        size++;
        adjlist = new list<pair<int, int>>[size];
        for (int j = 0; j < size-1; j++) {
            adjlist[j].swap(temp[j]);
        }
    }
    void removeVector(int u) {
        adjlist[u].clear();
        for (int j = 0; j < size; j++) {
            for (int i = 0; i <= maxW(); i++) {
                adjlist[j].remove(make_pair(u, i));
            }
        }
    }
    int maxW() {
        int mW = 0;
        for (int i = 0; i < size; i++) {
            for (auto j : adjlist[i]) {
                if (j.second > mW) {
                    mW = j.second;
                }
            }
        }
        return mW;
    }
    void printGraph() {
        for (int i = 0; i < size; i++) {
            cout << "Current Location:" << i << endl ;
            for (auto it : adjlist[i]) {
                cout <<"    Destination: " << it.first << " Distance(Miles):" << it.second << endl;
            }
            cout << endl;
        }
    }
};

int main() {
    weightedGraph mygraph(5);
    
    mygraph.addEdge(0, 1, 20);
    mygraph.addEdge(0, 2, 15);
    mygraph.addEdge(0, 3, 10);
    mygraph.addEdge(0, 4, 5);
    mygraph.addEdge(0, 4, 1);
    mygraph.printGraph();
    cout <<"Orginal Size:" << mygraph.size << endl;
    cout << endl << endl;
    mygraph.addVector();
    mygraph.addEdge(0, 5, 50);
    cout << "Added Vector Size:" << mygraph.size << endl;
    mygraph.printGraph();
    mygraph.removeVector(3);
    cout << "Removed 3rd Vector Size:" << mygraph.size << endl;
    mygraph.printGraph();


    return 0;
}