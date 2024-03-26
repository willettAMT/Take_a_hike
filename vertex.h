#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
/**********************************************************************
 * 
**********************************************************************/

#ifndef VERTEX_H
#define VERTEX_H

const int LETTER{1};
const int IGNORE{1000};

struct ERR
{
    int code;
    std::string msg{""};
};

struct vertex
{
    public:
        std::string intersection; // name of intersection
        struct trail* head; // head pointer to LLL of edges (trails)
                                      // helper funcs
        int display();
        int clean();
        int insert(struct trail& edge);
        int take_trail(std::string& name, vertex*&);
    private:
        int insert(trail*& curr, trail& edge);
        int take_trail(trail*& curr, std::string& name, vertex*& match);
        int display(struct trail*& edge);
};

struct trail // edge
{
    // funcs
    int create_trail(float& bLen, float& bEle, std::string& bName); // adds data members to trail instance
    int copy_data(trail& to_copy); // adds data members to trail instance
    int clean(); // cleans object of data

    // data members
    std::string trail_name;
    float length;
    float ele_gain;
    vertex* start; // pointer to start vertex
    vertex* connection;// pointer to connecting vertex 
    trail* next; // pointer to next trail (edge) 
};

class Graph
{
    public:
        Graph();
        ~Graph();
        int build_filled(const int& size); // build pre-constructed adjacency list
        int build_empty(const int& size); // build user-defined adjacency list
        int insert(std::string& start, std::string& intersection, trail& to_add); // inserts trail into adjacency list
        int display_all(); // displays all values in adjacency_list and the edges
        int add_intersection(int& i, std::string& input); // adds intersection to adjacency list
        int take_a_hike(std::string& start); // search adjacency_list for vertex
                                        // if found, perform DFS
    private:
        //int add_visited(vertex*& to_add);
        //int take_a_hike(vertex& curr, std::vector<int>& visited);
        int take_a_hike(vertex& curr, std::vector<vertex*>& visited);
        int find_location(std::string desti, vertex*& ptr); // returns ptr for matching string value in adjacency list
        int find_location(std::string desti);
        int list_size;
        vertex* adjacency_list;
};

/*
 * [v1, v2, v3, v4, v5, v6, v7, v8, v9, v10]
 *  E2  E8  E10 E7  E3  E9  E4  E5  E6  E1
 *  E9  E1  E4  E10 E6  E2  E5  E3  E7  E8
 *  E3  E9  E6  E6  E5  E3  E9  E2  E1  E8
 */  
// v1 -> v2 -> v9 -> v3
// v2 -> v8 -> v1 -> v9

//util functions
void readInput(char& input);
void readInput(int& input);
void readInput(float& input);
void menu(int& iBuf);
void hike_menu(std::string& idx);
void lost();

#endif


