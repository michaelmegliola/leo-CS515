#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <algorithm>
#include <queue>
using namespace std;

/**
 * CS515 Program 12
 * File: mynetwork.cpp
 * Name: Leo Megliola
 * Section: L2R
 * Date: May 6, 2021
 * Collaboration Declaration:
 * Assistance received from online resources
 * 		c++ docs, geeks for geeks, techiedelight
 */

class DisjointSet {
public:
    string find(string key) {   //returns representative
        if (parent[key] != key)
            parent[key] = find(parent[key]);    //_path compression
        return parent[key];
    }

    int size() {
        return parent.size();
    }

    bool set_union(string a, string b) {    //implements union by rank
        string rep_a = find(a);
        string rep_b = find(b);

        if (rep_a == rep_b)                 //a and b are in the same set
            return false;

        if (rank[rep_a] > rank[rep_b])      //join sets that contain a and b
            parent[rep_b] = rep_a;
        else if (rank[rep_a] < rank[rep_b])
            parent[rep_a] = rep_b;
        else {
            parent[rep_a] = rep_b;
            rank[rep_b]++;
        }
        return true;
    }

    void insert(string key) {
        parent[key] = key;  //each key starts parented to itself
        rank[key] = 0;
    }

private:
    map<string, string> parent;
    map<string, int> rank;
};

class Graph {
public:
    ~Graph() {
        delete[] _nodearray;
    }

    bool read_file(string fname) {  //read file to build graph
        stringstream s;
        ifstream infile;
        infile.open(fname);
        if (!infile)
            return false;
        if (infile.fail()) {        //handles file open error
            cout << "error opening " << fname << " for input." << endl;
            return false;
        }

        s << infile.rdbuf();    //read entire file
        infile.close();

        string word;            //to store individual words
        string a="", b="", c="";
        while (s >> a >> b >> c) {
            if (_first_node == "")
            	_first_node = a;
            if (a=="" || b=="" || c=="")
                break;
            if (a != b) {       //create new edge
                edge e;
                e.a = a;
                e.b = b;
                e.weight = stoi(c);
                _q.push(e);     //push onto p-q
                _nodes.insert(a);   //maintain a set of unique nodes
                _nodes.insert(b);
                _size++;
            }
        }
        _nodearray = new string[_nodes.size()];     //sort an array of node names, used for printing
        int i = 0;
        for (set<string>::iterator it = _nodes.begin(); it != _nodes.end(); it++) {
            _nodearray[i++] = *it;
        }
        sort(_nodearray, _nodearray + _nodes.size());
        return true;
    }

    void print_nodes() {    //prints nodes in alphabetical order
        for (int i = 0; i < _nodes.size(); i++)
            cout << _nodearray[i] << endl;
    }

    string first_node() {
        return _first_node;
    }

    bool exists(string key) {
        return _nodes.find(key) == _nodes.end();
    }

    void kruskal() {            //build MST from graph

        DisjointSet ds;         //create disjoint set of nodes
        for (set<string>::iterator it = _nodes.begin(); it != _nodes.end(); it++)
            ds.insert(*it);

        while (!_q.empty()) {   //use greedy logic to merge disjoint sets
            if (ds.find(_q.top().a) != ds.find(_q.top().b)) {
                ds.set_union(_q.top().a, _q.top().b);
                _mst[_q.top().a].push_front(_q.top().b);
                _mst[_q.top().b].push_front(_q.top().a);
            }
            _q.pop();
        }
    }

    list<string> find(string parent, string dest) {         //outer find
        _path.clear();
        find(parent, parent, dest);
        return _path;
    }

    bool find(string parent, string cur, string dest) {     //recursive, inner find
        if (cur == dest) {
            _path.push_front(dest);
            return true;
        }
        for (string adj:_mst[cur]) {
            if (adj != parent)
                if (find(cur, adj, dest)) {
                    _path.push_front(cur);
                    return true;
                };
        }
        return false;
    }

private:
    struct edge {
        string a; string b; int weight;
    };
    struct compare_edge {   //puts the edges in ascending order
        bool operator() (edge const& e1, edge const& e2) {
            return e1.weight > e2.weight;
        }
    };
    priority_queue<edge, vector<edge>, compare_edge> _q;
    map<string, list<string> > _mst;
    list<string> _path;
    set<string> _nodes;
    string* _nodearray;
    string _first_node = "";
    int _size = 0;

    static bool compare_edges(edge x, edge y) { //comparison function for sorting edges
        return x.weight > y.weight;
    }
};

int main(int argc, char ** argv) {
    //main reads the file, constructs the MST, then runs the user interface
    if (argc != 2) {
        cout << "usage: mynetwork <filename>" << endl;
        return 0;
    }

    Graph g;
    if (!g.read_file(argv[1]))  //read the file
        return 0;

    g.kruskal();                        //construct MST

    stack<string> path;
    path.push(g.first_node());

    while (true) {                      //run user interface
        cout << "<" << path.top() << "># ";
        string cmd, arg;

        cin >> cmd;
        if (!(cmd == "ping" || cmd == "exit" || cmd == "ssh")) {
            cout << "unknown command" << endl;
            continue;
        }
        if (cmd == "exit") {
            path.pop();
            if (path.empty())
                break;
        }
        else {
            cin >> arg;
            if (g.exists(arg)) {
                cout << "Cannot find node. Available nodes are:" << endl;
                g.print_nodes();
                continue;
            }
            if (cmd == "ping") {
                cout << " From: " << path.top() << endl;
                list<string> result = g.find(path.top(), arg);
                list<string>::iterator it = result.begin();
                it++;
                while (it != result.end()) {
                    cout << "   To: " << *it << endl;
                    it++;
                }
            } else {
                path.push(arg);
            }
        }
    }
    return 0;
}
