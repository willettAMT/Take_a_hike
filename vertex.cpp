#include "vertex.h"
#include <cctype>

using namespace std;
/**********************************************************************
 * 
**********************************************************************/
// Graph Members

Graph::Graph()
{
    adjacency_list = nullptr;
}

Graph::~Graph()
{
    int i = 0;
    while (i < list_size)
    {
        adjacency_list[i].clean();
        ++i;
    }
    delete [] adjacency_list;
    list_size = 0;
}

int Graph::display_all()
{
    int i{0};

    while (i < list_size)
    {
        cout << adjacency_list[i].intersection << " trails" <<endl;
        cout << setfill('-') << setw(65) << ' ' << endl;
        adjacency_list[i].display();
        cout << setfill(' ') << endl << endl;
        ++i;
    }

    return 1;
}

int Graph::build_filled(const int& size)
{
    int i{0};
    string preLoad[5]{"Deer Trail",
                      "Kettle Creek",
                      "Meadow Valley",
                      "White Plains",
                      "Lily Pad Pond"};

    adjacency_list = new vertex[size];

    cout << "Intersections Loaded:" <<endl;
    cout << setfill('-') << setw(65) << ' ' << setfill(' ') << endl;
    while (i < size)
    {
        adjacency_list[i].intersection = preLoad[i];
        adjacency_list[i].head = nullptr;
        cout << adjacency_list[i].intersection << endl;
        ++i;
    }

    list_size = size;

    return 1;
}

int Graph::build_empty(const int& size)
{
    int i = 0;
    adjacency_list = new vertex[size];
    while (i < size)
    {
        adjacency_list[i].head = nullptr;
        ++i;
    }

    list_size = size;

    return 1;
}

int Graph::add_intersection(int& i, string& input)
{
    ERR error;
    if (input.at(0) == '\0')
    {
        error.code = 911;
        error.msg = "Input empty";
        throw error;
    }

    adjacency_list[i].intersection = input;
    cout << adjacency_list[i].intersection << endl;
    return 1;
}

int Graph::find_location(string desti, vertex*& match) // arguments: match string, reference to vertex pointer
{
    int i{0};

    while ((i < list_size - 1) && adjacency_list[i].intersection != desti)
        ++i;

    if (adjacency_list[i].intersection == desti)
    {
        match = &adjacency_list[i]; // update match by reference (reference to the vertex on the adjacency list)
        return 1;
    }

    return 0;
}

int Graph::insert(std::string& start, std::string& intersection, trail& to_add)  // arguments: string start, string intersection, partially filled trail instance
{
    ERR error;
    
    vertex* start_vertex = nullptr;
    vertex* connection_vertex = nullptr;

    find_location(start, start_vertex); // arguments: string start (for matching), pointer (by reference) to return match
    find_location(intersection, connection_vertex); // arguments: string start (for matching), pointer (by reference) to return match

    if (!start_vertex || !connection_vertex)
    {
        error.code = 911;
        error.msg = "Location doesn't exist";
        throw error;
    }

    to_add.start = start_vertex;// adding ptr from adjacency list to trail object
    to_add.connection = connection_vertex;// adding ptr from adjacency list to trail object
    (*start_vertex).insert(to_add); 

    return 1;
}


int Graph::take_a_hike(string& start)
{
    ERR error;

    vector<vertex*>visited; // initiate a vector to use as visited list
    vertex* pStart = nullptr;

    find_location(start, pStart); // finds location matching string passed in from client
    
    if (!pStart)
    {
        error.code = 451;
        error.msg = "Field cannot be blank";
        throw error;
    }

    visited.push_back(pStart);
    return take_a_hike(*pStart, visited);
}

int Graph::take_a_hike(vertex& curr, vector<vertex*>& visited)
{
    // visited is a vector<int> tracking vertices visited
    // curr is current vertex
    string trail;
    int count{0};
    vertex* desti = nullptr;

    cout << endl << endl;
    cout << curr.intersection << endl; 
    cout << setfill('-') << setw(65) << ' ' << setfill(' ') << endl;
    curr.display();
    hike_menu(trail); // displays 'hike menu' and updates string trail

    if (trail == "quit")
        return 0;

    curr.take_trail(trail, desti); // returns index of trail's connecting vertex
              
    if (!desti)
        return 0;
    // initiate an iterator to count number of 'desti' values in vector
    for (vector<vertex*>::iterator i = visited.begin(); i != visited.end(); ++i)
        if ((*i)->intersection == curr.intersection)
            ++count;

    if (count < 2) // if less than 2, push value onto vector and 'take_a_hike'
    {
        visited.push_back(desti);
        take_a_hike(*desti, visited);
    }
    else
    {
        lost();
        take_a_hike((*visited[visited.size() - 2]), visited);
    }

    return 1;
}

/************************************************************/
// Vertex Members
int vertex::clean()
{
    if (head)
    {
        trail* curr = head;
        while (curr)
        {
            trail* hold = curr->next;
            delete curr;
            curr = hold;
        }
        return 1;
    }
    else return 0;
}

int vertex::display()
{
    if (!head)
        return 0;

    return display(head);
}

int vertex::display(trail*& edge)
{
    if (!edge) return 1;
    
    cout << "Trail Name: " << edge->trail_name << " | Length: " << edge->length << " km"
        << " | Elevation Gain: " << edge->ele_gain << " m"
        << "\t| Intersection: " << edge->connection->intersection << endl;
    return display(edge->next);
}

int vertex::insert(trail& edge)
{
    if (!head)
    {
        head = new trail;
        head->copy_data(edge);
        head->next = nullptr;
        return 1;
    }

    trail* insertion = new trail;
    insertion->copy_data(edge);
    insertion->next = head;
    head = insertion;
    return 1;
}

int vertex::take_trail(std::string& name, vertex*& match)
{
    ERR error;

    if (!head)
    {
        error.code = 495;
        error.msg = "Trail does not exist";
        throw error;
    }

    return take_trail(head, name, match);
}

int vertex::take_trail(trail*& curr, string& name, vertex*& match)
{
    if (!curr) return 0;
    if (curr->trail_name == name)
    { 
        match = curr->connection;
        return 1;
    }
    return take_trail(curr->next, name, match);
}
/************************************************************/
// Trail Members

int trail::copy_data(trail& to_copy) // adds data members to trail instance
{
    start = to_copy.start;
    connection = to_copy.connection;
    trail_name = to_copy.trail_name;
    length = to_copy.length;
    ele_gain = to_copy.ele_gain;
    return 1;
}

int trail::create_trail(float& bLen, float& bEle, string& bName)
{
    ERR error;

    if (bName.at(0) == '\0')
    {
        error.code = 404;
        error.msg = "Name cannot be empty. Try again";
        throw error;
    }

    trail_name = bName;
    length = bLen;
    ele_gain = bEle;
    return 1;
}
    
int trail::clean() // cleans object of data
{
    trail_name = "";
    length = 0.0;
    ele_gain = 0.0;
    start = nullptr;
    connection = nullptr;
    
    return 1;
}
/************************************************************/
// Utilities
void readInput(char& input)
{
    char temp;

    cin >> temp;
    cin.ignore(IGNORE, '\n');
    temp = tolower(temp);

    while (temp != 'y' && temp != 'n')
    {
        cout << "Enter (y)es or (n)o\n\n>> ";
        cin.clear();
        cin >> temp;
        cin.ignore(IGNORE, '\n');
        temp = tolower(temp);
    }

    input = temp;
    cout<<endl;
}
    
void readInput(int& input)
{
    int temp;

    cin >> temp;
    cin.ignore(IGNORE, '\n');
    
    while (!cin || temp < 0)
    {
        cin.clear();
        cin.ignore(IGNORE, '\n');
        cout << "Invalid input" << endl;
        cout << ">> ";
        cin >> temp;
        cin.ignore(IGNORE, '\n');
    }

    input = temp;
}
 
void readInput(float& input)
{
    float temp;

    cin >> temp;
    cin.ignore(IGNORE, '\n');
    
    while (!cin || temp < 0)
    {
        cin.clear();
        cin.ignore(IGNORE, '\n');
        cout << "Invalid input" << endl;
        cout << ">> ";
        cin >> temp;
        cin.ignore(IGNORE, '\n');
    }

    input = temp;
}


void menu(int& iBuf)
{
    string menu{"Menu\n\nChoose from following options:"
        "\n1. Add trail\n2. Display all intersections\n"
            "3. Take a hike\n4. Quit\n\n>> "};
    cout << '\n' << menu; 
    readInput(iBuf);
    cout << endl;
}

void hike_menu(string& name)
{
    string hike_menu{"\n\nChoose which trail to take!\n\n"
        "Enter 'quit' to leave the hike"};
    cout << hike_menu << "\n>> ";
    getline(cin, name);
    cout << endl;
}

void lost()
{
    string lost{"\n\nYou seem lost... you are going in circles. "
        "You need to go back the way you came"};
    cout << lost << endl;
}






