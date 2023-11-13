// Weigthed Graph for navigation
// By: Alexander N Olson
//
//Check there is path from src and dest 

#include<iostream>
#include<list>
#include<vector>
#include<queue>
#include<stack>

using namespace std;

class weightedGraph {
public:
    int size;
    vector<string> locations;
    list<pair<int, int>>* adjlist;

    weightedGraph(int s) {
        adjlist = new list<pair<int, int>>[s];
        locations.resize(s);
        size = s;
    }
    void addEdge(string l1, string l2, int w) {
        adjlist[placeToVal(l1)].push_back(make_pair(placeToVal(l2), w));
        adjlist[placeToVal(l2)].push_back(make_pair(placeToVal(l1), w));
    }
    void removeEdge(string l1, string l2) {
        for (int j = 0; j < maxW(); j++) {
                adjlist[placeToVal(l1)].remove(make_pair(placeToVal(l2),j));
                adjlist[placeToVal(l2)].remove(make_pair(placeToVal(l1), j));
        }
    }
    void modEdge(string u, string v, int w) {
        removeEdge(u, v);
        addEdge(u, v, w);
    }
    void addVector(string nL) {
        size++;
        locations.resize(size);
        addLocation(nL);
        list<pair<int, int>>* temp;
        temp = adjlist;
        adjlist = new list<pair<int, int>>[size];
        for (int j = 0; j < size - 1; j++) {
            adjlist[j].swap(temp[j]);
        }
        temp = nullptr;
        delete temp;
    }
    void removeVector(string nL) {
        
        /*for (int i = 0; i < size; i++) {
            removeEdge(nL, valToPlace(i));
        }*/
        
        list<pair<int, int>>* temp;
        temp = new list<pair<int, int>>[size-1];
        for (int k = 0; k != placeToVal(nL); k++) {
            temp[k] = adjlist[k];
        }
        for (int j = placeToVal(nL); j < size - 1; j++) {
            temp[j] = adjlist[j+1];
        }
        adjlist = new list<pair<int, int>>[size-1];
        adjlist = temp;
        removeLocation(nL);
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
        for (int q = 0; q < size; q++) {
            cout << "Current Location:" << valToPlace(q) << endl ;
            for (auto it : adjlist[q]) {
                cout << it.first << endl;
                cout <<"    Destination: " << valToPlace(it.first) << " Distance(Miles):" << it.second << endl;
            }
            cout << endl;
        }
    }
    void addLocation(string nL) {
        for (int i = 0; i < size; i++) {
            if (locations.at(i) == "") {
                locations.at(i) = nL;
                break;
            }
        }
    }
    void removeLocation(string nL) {
        vector<string> tempLoc;
        tempLoc.resize(size);
        for (int i = 0; i< placeToVal(nL); i++) {
            tempLoc.at(i)=(locations.at(i));
        }
        for (int u = placeToVal(nL); u< size-1; u++) {
            tempLoc.at(u)=(locations.at(u+1));
        }
        locations = tempLoc;
        size-=1;
    }
    int placeToVal(string p) {
        for (int i = 0; i < size; i++) {
            if ((locations.at(i) == (p))) {
                return i;
            }
        }return -1;
    }
    string valToPlace(int v) {
        if (v > locations.size()|| v < 0) {
            return "Error: Invlaid input";
        }
        return locations.at(v);
    }

    //Search Algorithms
        void BFS(int startVal){
            bool visited[size]; //Visited Array
            queue<int> myQ; //BFS Queue

            //Set visited states to false
            for (int i = 0; i < size; i++){
                visited[i] = false;
            }
            
            //Initialize values
            visited[startVal] = true;
            myQ.push(startVal);
            int nodeVal = startVal;

            //BFS Algorithm
            while (!myQ.empty()){
                nodeVal = myQ.front();
                cout << valToPlace(myQ.front()) << " -> ";
                myQ.pop();

                for (auto it : adjlist[nodeVal]) {
                    if (!visited[it.first]){
                        myQ.push(it.first);
                        visited[it.first] = true;
                    }
                }
            }
        }
        void DFS(int startVal){
            bool visited[size]; //Visited Array
            stack<int> myStack; //DFS Stack

            //Set visited states to false
            for (int i = 0; i < size; i++){
                visited[i] = false;
            }
            
            //Initialize values
            visited[startVal] = true;
            myStack.push(startVal);
            int nodeVal = startVal;

            while (!myStack.empty()){
                nodeVal = myStack.top();
                cout << valToPlace(myStack.top()) << " -> ";
                myStack.pop();

                for (auto it : adjlist[nodeVal]) {
                    if (!visited[it.first]){
                        myStack.push(it.first);
                        visited[it.first] = true;
                    }
                }
            }
        }
};

int main() {
    weightedGraph mygraph(5);
    mygraph.addLocation("A");
    mygraph.addLocation("B");
    mygraph.addLocation("C");
    mygraph.addLocation("D");
    mygraph.addLocation("E");
    
    mygraph.addEdge("A", "B", 10);
    mygraph.addEdge("A", "C", 20);
    mygraph.addEdge("A", "D", 30);
    mygraph.addEdge("A", "E", 40);
    mygraph.addEdge("B", "E", 5);
    mygraph.addEdge("D", "E", 111);

    mygraph.BFS(mygraph.placeToVal("A"));
    cout << endl;
    mygraph.DFS(mygraph.placeToVal("A"));
    cout << endl;

    // mygraph.printGraph();
    // cout <<"Orginal Size:" << mygraph.size << endl;
    // cout << endl << endl;
    // mygraph.addVector("F");
    // mygraph.addEdge("A", "F", 50);
    // cout << "Added Vector Size:" << mygraph.size << endl;
    // mygraph.printGraph();
    // cout << endl << endl;
    // mygraph.removeVector("C");
    // cout << endl;
    // cout << "    Destination: " << mygraph.valToPlace(4) << endl;
    // for (auto it : mygraph.adjlist[0]) {
    //     cout << it.first << endl;
    //     cout << "    Destination: " << mygraph.valToPlace(it.first) << " Distance(Miles):" << it.second << endl;
    // }
    // cout << "Removed 3rd Vector Size:" << mygraph.size << endl;
    // for (int y = 0; y < mygraph.locations.size(); y++) {
    //     cout << mygraph.locations.at(y);
    // }cout << endl;
    // cout << mygraph.locations.size() << endl;
    // mygraph.printGraph();


    return 0;
}