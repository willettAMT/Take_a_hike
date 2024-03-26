#include "vertex.h"
#include <string>

using namespace std;

int test(Graph& park);
const int BUF{30};

int main (void)
{
    Graph park;
    trail buf_trail;
    string input, bName, enter, desti;
    char cBuf;
    int iBuf, i{0}, j{0};
    float bLen, bEle;

    while (j < 20)
    {
        cout << "\n\n\n\n"<<endl;
        ++j;
    }

    cout << "Pre-load intersections? (y)es or (n)o\n>> ";
    readInput(cBuf);

    if (cBuf == 'y')
        park.build_filled(5);
    else
    {
        cout << "Enter the amount of intersections "
            << "you want to use" << endl;
        cout << ">> ";
        readInput(iBuf);

        park.build_empty(iBuf);
        while (i < iBuf)
        {
            cout << "\nEnter name of intersection\n>> ";
            getline(cin, input);
            park.add_intersection(i, input);
            ++i;
        }
    }

    do
    {
        do { menu(iBuf); } while (iBuf < 0 && iBuf > 4); // handles menu choices out of bounds

        switch (iBuf)
        {
            case 1:
                cout << "Enter name of starting intersection: ";
                getline(cin, enter, '\n');
                cout << "Enter name of connecting intersection: ";
                getline(cin, desti, '\n');
                cout << "Enter name of trail: ";
                getline(cin, bName, '\n');
                cout << "Enter length of trail (kilometers): ";
                readInput(bLen); 
                cout << "Enter elevation gain (meters): ";
                readInput(bEle);
                try
                {
                    buf_trail.create_trail(bLen, bEle, bName); // adds data members to trail instance
                    park.insert(enter, desti, buf_trail);
                }
                catch (ERR error)
                {
                    cerr << error.code << endl;
                    cerr << error.msg << endl;
                }
                break;
            case 2:
                try
                {
                    park.display_all();
                }
                catch (ERR error)
                {
                    cerr << error.code << endl;
                    cerr << error.msg << endl;
                }
                break;
            case 3:
                cout << "Enter starting point of your hike\n>> ";
                getline(cin, input);
                try
                {
                    park.take_a_hike(input);
                }
                catch (ERR error)
                {
                    cerr << error.code << " + " << error.msg << endl;
                }
                break;
            case 4:
                cout << "Quitting" << endl;
                break;
            default:
                break;
        }
    } while (iBuf != 4);
    i = 0;
    return 0;
}
