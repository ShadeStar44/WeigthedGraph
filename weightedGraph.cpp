// Graph Map

#include<iostream>
#include<list>
#include<queue>

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
                cout << "Current Location: " << i << " -> " << endl;
                for (auto it : adjlist[i]) {
                    cout << "\t\t\tDestination: " << it.first << " Distance(Miles):" << it.second << endl;
                }
                cout << endl;
            }
        }

        void BFS(){
            bool visited[size]; //Visited Array
            queue<int> myQ; //BFS Queue

            //Set visited states to false
            for (int i = 0; i < size; i++){
                visited[i] = false;
            }
            
            //Initialize values
            visited[0] = true;
            myQ.push(0);
            int nodeVal = 0;

            //BFS Algorithm
            while (!myQ.empty()){
                nodeVal = myQ.front();
                cout << myQ.front() << " -> ";
                myQ.pop();

                for (auto it : adjlist[nodeVal]) {
                    if (!visited[it.first]){
                        myQ.push(it.first);
                        visited[it.first] = true;
                    }
                }
            }
        }
};

int main() {
    weightedGraph mygraph(10);
    
    mygraph.addEdge(0, 1, 20);
    mygraph.addEdge(1, 4, 20);
    mygraph.addEdge(4, 2, 20);
    mygraph.addEdge(4, 7, 20);
    mygraph.addEdge(2, 7, 20);
    mygraph.addEdge(7, 9, 20);
    mygraph.addEdge(7, 8, 20);
    mygraph.addEdge(5, 9, 20);
    mygraph.addEdge(5, 8, 20);
    mygraph.addEdge(3, 0, 20);
    mygraph.addEdge(3, 6, 20);
    mygraph.addEdge(3, 5, 20);
    mygraph.addEdge(6, 0, 20);
    mygraph.addEdge(5, 6, 20);

    mygraph.BFS(); //Peform BFS
    


    // ----- Temporarily Commented Out Testing ----- //

    //mygraph.printGraph();
    // cout <<"Orginal Size:" << mygraph.size << endl;
    // cout << endl << endl;
    // mygraph.addVector();
    // mygraph.addEdge(0, 5, 50);
    // cout << "Added Vector Size:" << mygraph.size << endl;
    // mygraph.printGraph();
    // mygraph.removeVector(3);
    // cout << "Removed 3rd Vector Size:" << mygraph.size << endl;
    // mygraph.printGraph();


    return 0;
}