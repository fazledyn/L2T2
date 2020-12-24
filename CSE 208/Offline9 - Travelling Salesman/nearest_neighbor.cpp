#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <list>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;


/**
 * Shortest path for TSP with Nearest Neighbour Heuristic algorithm
 * @param source int
 */

double graph::nn_tsp(int source) {
    if (this->is_empty_graph()) return 0;

    cout << "Nearest Neighbour Algorithm Calculating shortest path for TSP ... " << endl;
    print_current_time();
    cout << endl;

    int _v_size = this->get_size();
    if (source < 0 || source >= _v_size)
        source = 0;
    this->source = source;


    set<int> visited_v;
    visited_v.insert(source);

    // Loop to find the nearest vertex for current vertex till all vertices are marked visted
    int current_v = source;
    this->m_dis = 0;

    while ((int)visited_v.size() < _v_size) {

        pair<int, double> nearest_v = this->get_unvisited_nearest_neighbour(current_v, visited_v);
        this->m_dis += nearest_v.second;

        if (current_v == source) {
            this->tsp_s_path.cur_v = nearest_v.first;
            this->tsp_s_path.distance = nearest_v.second;
        } else {
            this->tsp_s_path.unvisited.insert(this->tsp_s_path.unvisited.begin(), nearest_v.first);
            this->tsp_s_path.distance += nearest_v.second;
        }

        // Set current vertex to the nearest neighbour and mark it as visited
        current_v = nearest_v.first;
        visited_v.insert(current_v);

        // If it's the last one, add the distance between it and the source vertex
        if (visited_v.size() == _v_size) {
            this->m_dis += this->get_cost(current_v, source);
        }
    }

    cout << "Nearest Neighbour Algorithm Completed Calculating shortest path for TSP." << endl;
    print_current_time();
    cout << endl;

    return this->m_dis;
}

/**
 * Print the shortest path cost result
 */
void graph::print_result() {
    // Print Result
    vector<int>::iterator iter_v;
    cout << "Minimum distance is " << this->m_dis << endl;
    cout << "The shortest path is " << this->source << "->" << this->tsp_s_path.cur_v;
    for (iter_v = this->tsp_s_path.unvisited.begin(); iter_v != this->tsp_s_path.unvisited.end(); iter_v++)
        cout << "->" << *iter_v;
    cout << "->" << this->source << endl;
}


/**
 * Get nearest neighbour to the vertex
 * @param int source : source vertex
 * @param set<int> : visited vertices
 * @return pair<int, double> : nearest vertex and the distance
 */
pair<int, double> twodarray_graph::get_unvisited_nearest_neighbour(int source, set<int> visited_v) {
    int _v_size = this->get_size();

    double min_dist = INF_WEIGHT;
    int nearest_v = source;

    for (int i = 0; i < _v_size; ++i) {

        if (i == source || visited_v.find(i) != visited_v.end())
            continue;

        double alt_dist = this->get_cost(source, i);
        if (min_dist > alt_dist) {
            min_dist = alt_dist;
            nearest_v = i;
        }

    }

    return pair<int, double>(nearest_v, min_dist);
}

