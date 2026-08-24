#include <iostream>
#include <random>
#include <map>
using namespace std;
// define board dice player snake ladder
class dice;
class board
{
    int roll;
    int previous;
    int current;
    int intermediate;
    int final;
    map<int, int> port;

public:
    board()
    {
        current = 0;

        // snake
        port[99] = 8;
        port[92] = 73;
        port[84] = 77;
        port[25] = 5;
        port[49] = 11;
        port[62] = 42;
        // ladder
        port[8] = 64;
        port[78] = 95;
        port[42] = 77;
        port[22] = 45;
        port[65] = 92;
        port[4] = 42;
    }
    void getMove(dice &d1);
    void setMove();
    void current_state();
    int check();
};
class dice
{
    int roll;
    int turn;

public:
    int randomRoll();
};

/**********************************************************************************/

void board::getMove(dice &d1)
{
    roll = d1.randomRoll();
}
void board::setMove()
{   previous = current;
    intermediate = current + roll;
    if (intermediate > 100)
    {
        final = current;
        return;
    }
    if (port.find(intermediate) != port.end())
    {
        final = port[intermediate];
    }
    else final = intermediate;

    current = final;
}
void board::current_state()
{
    cout << "Current Position: " << current;
    cout << "Rolled: " << roll;

    if (intermediate > 100)
    {
        cout << " | Overshot 100! Stayed at square " << current << endl;
    }
    else if (final != intermediate)
    {   
        if (final > intermediate) {
            cout << " | Landed on " << intermediate << " -> LADDER to square " << final << endl;
        } else {
            cout << " | Landed on " << intermediate << " -> SNAKE down to square " << final << endl;
        }
    } else {
        cout << " | Moved to square " << final << endl;
    }
}

int board::check()
{
    return current==100;
}

/********************************************************************************** */
int dice::randomRoll()
{
    random_device rd;
    mt19937 rolls(rd());
    uniform_int_distribution<int> range(1, 6);
    roll = range(rolls);
    return roll;
}
int main()
{
    board b1;
    dice d1;
    while (!(b1.check()))
    {
        b1.getMove(d1);
        b1.setMove();
        b1.current_state();
    }
    return 0;
}