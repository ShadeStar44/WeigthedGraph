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

    //edge functions
    void addEdge(string l1, string l2, int w) {
        adjlist[placeToVal(l1)].push_back(make_pair(placeToVal(l2), w));
        adjlist[placeToVal(l2)].push_back(make_pair(placeToVal(l1), w));
    }
    void removeEdge(string l1, string l2) {
        for (int j = 0; j < maxW(); j++) {
            adjlist[placeToVal(l1)].remove(make_pair(placeToVal(l2), j));
            adjlist[placeToVal(l2)].remove(make_pair(placeToVal(l1), j));
        }
    }
    void modEdge(string u, string v, int w) {
        removeEdge(u, v);
        addEdge(u, v, w);
    }

    //add node using name
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

    //remove edge
    void removeVector(string nL) {

        list<pair<int, int>>* temp;
        temp = new list<pair<int, int>>[size - 1];
        for (int k = 0; k != placeToVal(nL); k++) {
            temp[k] = adjlist[k];
        }
        for (int j = placeToVal(nL); j < size - 1; j++) {
            temp[j] = adjlist[j + 1];
        }
        adjlist = new list<pair<int, int>>[size - 1];
        adjlist = temp;
        removeLocation(nL);
    }

    //find max weight
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

    //prints all edges + nodes 
    void printGraph() {
        for (int q = 0; q < size; q++) {
            cout << "Current Location:" << valToPlace(q) << endl;
            for (auto it : adjlist[q]) {
                cout << "    Destination: " << valToPlace(it.first) << " Distance(Miles):" << it.second << endl;
            }
            cout << endl;
        }
    }

    //create node
    void addLocation(string nL) {
        for (int i = 0; i < size; i++) {
            if (locations.at(i) == "") {
                locations.at(i) = nL;
                break;
            }
        }
    }

    //remove node
    void removeLocation(string nL) {
        vector<string> tempLoc;
        tempLoc.resize(size);
        for (int i = 0; i < placeToVal(nL); i++) {
            tempLoc.at(i) = (locations.at(i));
        }
        for (int u = placeToVal(nL); u < size - 1; u++) {
            tempLoc.at(u) = (locations.at(u + 1));
        }
        locations = tempLoc;
        size -= 1;
    }

    //convert string name to node int
    int placeToVal(string p) {
        for (int i = 0; i < size; i++) {
            if ((locations.at(i) == (p))) {
                return i;
            }
        }return -1;
    }

    //convert node int to string name
    string valToPlace(int v) {
        if (v > locations.size() || v < 0) {
            return "Error: Invlaid input";
        }
        return locations.at(v);
    }

    //---------------
    //Search Algorithms
    //---------------


    void BFS(int startVal) {
        vector<bool> visited(size, false); //Visited Array
        queue<int> myQ; //BFS Queue

        //Initialize values
        visited[startVal] = true;
        myQ.push(startVal);
        int nodeVal = startVal;

        //BFS Algorithm
        while (!myQ.empty()) {
            nodeVal = myQ.front();
            cout << valToPlace(myQ.front());
            myQ.pop();

            for (auto it : adjlist[nodeVal]) {
                if (!visited[it.first]) {
                    myQ.push(it.first);
                    visited[it.first] = true;
                }
            }
            if (!myQ.empty()) {
                cout << "-->";
            }
        }
        cout << endl;
    }
    void DFS(int startVal) {
        vector<bool> visited(size, false); //Visited Array
        stack<int> myStack; //DFS Stack

        //Set visited states to false
        for (int i = 0; i < size; i++) {
            visited[i] = false;
        }

        //Initialize values
        visited[startVal] = true;
        myStack.push(startVal);
        int nodeVal = startVal;

        while (!myStack.empty()) {
            nodeVal = myStack.top();
            cout << valToPlace(myStack.top());
            myStack.pop();

            for (auto it : adjlist[nodeVal]) {
                if (!visited[it.first]) {
                    myStack.push(it.first);
                    visited[it.first] = true;
                }
            }
            if (!myStack.empty()) {
                cout << "-->";
            }
        }
        cout << endl;
    }

    void SPF(int startVal) {
        //distance vector to be output, needs initializiation with infinity (numeric_limits)
        vector<int> dist; 
        dist.resize(size);
        for (int i = 0; i < size; i++) {
            dist[i] = numeric_limits<int>::max();
        }

        //last node vector to keep track of the last node visited in shortest path
        vector<int> last(size, startVal);

        //priority queue of type pair<int,int> used to keep track of <node, distance to start>
        priority_queue<pair<int,int>, vector<pair<int, int>>, greater<pair<int, int>>> tempDist;

        dist[startVal] = 0;//initializing starting distance as zero
        tempDist.push(make_pair(startVal, 0));//initialize priority queue with starting node and distance of 0

        //Dijkstra's Algorithm // goes through priority queue, adding neighbors of current node to queue and deleting current node from queue after finalizing distance.
        //Iterates from start to neighbors, then to their neighbors and so on.
        while (!tempDist.empty()) {
            int tempLoc = tempDist.top().first;
            tempDist.pop();

            for (auto neighbor : adjlist[tempLoc]) {
                if (dist[neighbor.first] > dist[tempLoc] + neighbor.second) {
                    dist[neighbor.first] = dist[tempLoc] + neighbor.second;
                    last[neighbor.first] = tempLoc;
                    tempDist.push(make_pair(neighbor.first, dist[neighbor.first] + neighbor.second));
                }
            }

        }

        //output results
        for (int i = 0; i < size; i++) {
            cout << "From " << valToPlace(startVal) << " to " << valToPlace(i) << " is " << dist[i];
            if (last[i] != startVal) {
                cout << " and a last node of " << valToPlace(last[i]);
            }
            cout << endl;
        }



    }

    void Astar(int startVal, int endVal, vector<vector<int>> h) {
        //list to be exported
        list<int> closedList;
        //bool vectors to keep track of what nodes are in the closed list/what nodes have been considered
        vector<bool> closedCheck(size, false);
        vector<bool> openCheck(size, false);
        //int vector to keep track of g value for each node
        vector<int> gVal(size);
        //pair<fval, node> to itterate through neighbors before storing in closedList or passing
        priority_queue<int, vector<int>, greater<int>> openList;

        //initialize first node at startVal
        gVal[startVal] = 0;
        openList.push( startVal);

        //A* algo, 
        while (!openList.empty()) {
            int tempNd = openList.top();
            openList.pop();

            //if the current node is the destination, add it to the closed list and break
            if (tempNd == endVal) {
                closedList.push_back(tempNd);
                break;
            }

            //iterate through neighbors
            for (auto neighbor : adjlist[tempNd]) {
                //set gval for neighbor
                int newGVal = gVal[tempNd] + neighbor.second;
                //check if neighbor is in closed/open already
                if (!closedCheck[neighbor.first] && !openCheck[neighbor.first]) {
                    //checks if path to neighbor is better
                    if (newGVal > gVal[neighbor.first]) {
                        gVal[neighbor.first] = newGVal;
                        openList.push( neighbor.first);
                        openCheck[neighbor.first] = true;
                    }
                }
            }


            closedList.push_back(tempNd);
            closedCheck[tempNd] = true;
        }

        //temp variable for last g value
        int lastG = 0;
        //print closed list and distances between nodes and final distance traveled
        for (int node : closedList) {
            if (gVal[node] > 0) {
                cout << "<-" << gVal[node] - lastG << "->" << valToPlace(node);
            }
            else {
                cout << valToPlace(node);
            }
            lastG = gVal[node];
        }
        cout << endl << "Total Distance: " << lastG << endl;
    }
};



int main() {
    //weighted graph with 11 nodes
    weightedGraph mygraph(11);

    //heuristic values, straightline distance from city to city
    //col/row formatted in same order cities are initialized (Durango = 0, Mancos = 1, etc)
    vector<vector<int>> heuristic{
        {0,23,39,40,33,37,56,9,16,39,39},
        {23,0,16,43,40,15,15,14,39,47,47},
        {39,16,0,47,49,10,39,30,55,60,55},
        {40,43,47,0,14,54,26,40,49,81,13},
        {33,40,49,14,0,53,38,32,35,71,8},
        {37,15,10,54,53,0,49,29,53,52,60},
        {56,15,39,26,38,49,0,50,67,90,39},
        {9,14,30,40,32,29,50,0,25,42,40},
        {16,39,55,49,35,53,67,25,0,41,42},
        {39,47,60,81,71,52,90,42,41,0,78},
        {39,47,55,13,8,60,39,40,42,78,0}
    };

    //initialize nodes
    mygraph.addLocation("Durango");
    mygraph.addLocation("Mancos");
    mygraph.addLocation("Cortez");
    mygraph.addLocation("Farmington");
    mygraph.addLocation("Aztec");
    mygraph.addLocation("Dolores");
    mygraph.addLocation("Shiprock");
    mygraph.addLocation("Hesperus");
    mygraph.addLocation("Bayfield");
    mygraph.addLocation("Silverton");
    mygraph.addLocation("Bloomfield");

    //initialize edges
    mygraph.addEdge("Durango", "Bayfield", 21);
    mygraph.addEdge("Durango", "Aztec", 38);
    mygraph.addEdge("Durango", "Hesperus", 13);
    mygraph.addEdge("Durango", "Silverton", 48);

    mygraph.addEdge("Aztec", "Farmington", 15);
    mygraph.addEdge("Aztec", "Durango", 38);
    mygraph.addEdge("Aztec", "Bloomfield", 9);

    mygraph.addEdge("Bloomfield", "Farmington", 14);
    mygraph.addEdge("Bloomfield", "Aztec", 9);

    mygraph.addEdge("Farmington", "Bloomfield", 14);
    mygraph.addEdge("Farmington", "Aztec", 15);
    mygraph.addEdge("Farmington", "Shiprock", 28);
    mygraph.addEdge("Farmington", "Hesperus", 46);

    mygraph.addEdge("Shiprock", "Cortez", 42);
    mygraph.addEdge("Shiprock", "Farmington", 28);

    mygraph.addEdge("Cortez", "Shiprock", 42);
    mygraph.addEdge("Cortez", "Dolores", 12);
    mygraph.addEdge("Cortez", "Mancos", 18);

    mygraph.addEdge("Dolores", "Cortez", 12);
    mygraph.addEdge("Dolores", "Mancos", 18);

    mygraph.addEdge("Mancos", "Cortez", 18);
    mygraph.addEdge("Mancos", "Dolores", 18);
    mygraph.addEdge("Mancos", "Hesperus", 17);

    mygraph.addEdge("Hesperus", "Mancos", 17);
    mygraph.addEdge("Hesperus", "Durango", 13);
    mygraph.addEdge("Hesperus", "Farmington", 46);

    mygraph.addEdge("Silverton", "Durango", 48);

    mygraph.addEdge("Bayfield", "Durango", 21);

    mygraph.printGraph();

    mygraph.BFS(mygraph.placeToVal("Durango"));

    mygraph.DFS(mygraph.placeToVal("Durango"));

    mygraph.SPF(mygraph.placeToVal("Durango"));

    mygraph.Astar(mygraph.placeToVal("Cortez"), mygraph.placeToVal("Farmington"), heuristic);

    return 0;
}
