#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <sstream>
#include <climits>
using namespace std;

//#define DEBUG_PRINT 1

void printGraph(map<char, list<char> > &graph)
{
    map<char, list<char> >::iterator graph_it;
    list<char>::iterator it;

    for (graph_it = graph.begin();
         graph_it != graph.end(); graph_it++)
    {
        cout << (*graph_it).first << ": ";
        for (it = (*graph_it).second.begin();
             it != (*graph_it).second.end(); it++)
            cout << *it << " ";
        cout << endl;
    }
}

/**
 * See https://www-m9.ma.tum.de/graph-algorithms/spp-dijkstra/index_en.html
 * @param graph
 * @param dist_parent
 * @param start
 * @param end
 */
void dijkstra(map<char, list<char> > &graph, char start, char end) {
    map<char, pair<int, char> > dist_parent;
    for (map<char, list<char> >::iterator it = graph.begin(); it != graph.end(); it++) {
        dist_parent[it->first] = pair<int, char>(INT_MAX, 0);
    }
    priority_queue<pair<int, char> > q;
    set<char> in_q;
    dist_parent[start] = pair<int, char>(0, 0);//distance=0, parent=NULL
    q.push(pair<int, char>(0, start)); in_q.insert(start);
    while (!q.empty()) {
        pair<int, char> min = q.top(); q.pop(); in_q.erase(min.second);
        list<char> edges = graph[min.second];   //get edges from that entry
        for (list<char>::iterator it = edges.begin(); it != edges.end(); it++) { //loop over edges
            int distance = min.first+1;
            char parent = min.second;
            if (in_q.find(*it) != in_q.end() && dist_parent[*it].first > distance) { //if node is in queue
                dist_parent[*it].first = distance;
                dist_parent[*it].second = parent;
                list<pair<int, char> > temp;
                while (!q.empty()) {
                    pair<int, char> entry = q.top(); q.pop();
                    if (entry.second == *it)
                        entry.first = distance;
                    temp.push_front(entry);
                }
                for (list<pair<int, char> >::iterator it1 = temp.begin(); it1 != temp.end(); it1++)
                    q.push(*it1);

            } else if (dist_parent[*it].second == 0) {
                dist_parent[*it].first = distance;
                dist_parent[*it].second = parent;
                q.push(pair<int, char>(-distance, *it));
                in_q.insert(*it);
            }
        }
    }
    list<char> path;
    path.push_front(end);
    bool path_found = dist_parent[path.front()].second != 0;
    while (path.front() != start && path_found)
        path.push_front(dist_parent[path.front()].second);

    cout << "from " << start << " to " << end << " : ";
    if (path_found) {
        cout << "path found." << endl;
        for (list<char>::iterator it = path.begin(); it != path.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    } else {
        cout << "path not found." << endl;
    }

}

int main() {

    // build the graph
    map<char, list<char> > graph;

    char v1, v2, start, end;

    while((cin >> v1) && v1 != '?')
    {
        if (!(cin >> v2))
            break;
        graph[v1].push_back(v2);
    }

#ifdef DEBUG_PRINT
    printGraph(graph);
#endif

    //Process queries
    while (cin >> start >> end)
    {
        dijkstra(graph, start, end);
        cin >> v1; //grab the next '?'
        if (v1 != '?')
            break;
    }
}