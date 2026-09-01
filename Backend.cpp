#include <iostream>
#include <random>
#include <ctime>
#include <map>

using namespace std;

class dice;
class board
{
public:
    int grid[100];

    map<int, int> port;
    board()
    {
        // Snakes
        port[99] = 8;
        port[92] = 73;
        port[84] = 77;
        port[25] = 5;
        port[49] = 11;
        port[62] = 42;

        // Ladders
        port[8] = 64;
        port[78] = 95;
        port[52] = 77;
        port[22] = 45;
        port[65] = 93;
        port[4] = 42;
    }
};
class Player
{

    int roll = 0;
    int previous = 0;
    int current = 0;
    int intermediate = 0;
    int final = 0;
    char temp;

public:
    string name;
    void getMove(dice &d1);
    void setMove(board &b1);
    void currentState();
    bool isFinished();
    void greet();
};

class dice
{
    mt19937 gen;
    uniform_int_distribution<int> range;

public:
    dice() : gen(random_device{}()), range(1, 6) {}

    int randomRoll()
    {
        return range(gen);
    }
};

/************************************************************************ */
void Player ::greet()
{
    system("cls");
    cout << "\n\tSNAKE AND LADDERS\n";
    cout<<"\t\t\t\tPress Q to quit"<<endl;
}

void Player::getMove(dice &d1)
{
    cout << "\nPress any key roll the dice" << endl;
    cin >> temp;
    if (temp == 'q' || temp == 'Q')
    {
        exit(0);
    }
    else
        roll = d1.randomRoll();
}

void Player::setMove(board &b1)
{
    previous = current;
    intermediate = current + roll;

    if (intermediate > 100)
    {
        final = current;
        return;
    }

    if (b1.port.find(intermediate) != b1.port.end())
    {
        final = b1.port[intermediate];
    }
    else
    {
        final = intermediate;
    }

    current = final;
}

void Player::currentState()
{
    cout << "Rolled: " << roll << " \n| From: " << previous;

    if (intermediate > 100)
    {
        cout << " \n| Overshot 100! Stayed at square " << current << "\n";
    }
    else if (final != intermediate)
    {
        if (final > intermediate)
        {
            cout << " -> Landed on " << intermediate << " \n-> LADDER to square " << final << "\n";
        }
        else
        {
            cout << " -> Landed on " << intermediate << " \n-> SNAKE down to square " << final << "\n";
        }
    }
    else
    {
        cout << " -> Moved to square " << final << "\n";
    }
}

bool Player::isFinished()
{
    return current == 100;
}
void setupPlayers(vector<Player> &player)
{
    for (size_t i = 0; i < player.size(); ++i)
    {
        cout << "Enter Name for Player " << (i + 1) << ": ";
        cin >> player[i].name;
    }
};
int main()
{
    system("cls");
    cout<<"\n\tSNAKE AND LADDERS\n";
    
    int count;
    cout << "Enter Player Number: " << endl;
    cin >> count;
    if (count <= 0)
    {
        cerr << "Invalid player count.\n";
        return 1;
    }
    int turn = 0;
    
    int turnCount = 0;
    vector<Player> player(count);
    dice d1;
    board b1;
    setupPlayers(player);
    player[turn].greet();
    while (true)
    {
        turnCount++;
       cout << "\n----------------------------------------";
        cout << "\nTurn of " << player[turn].name << " (Player " << turn + 1 << "):";
        player[turn].getMove(d1);
        player[turn].setMove(b1);
        player[turn].currentState();
        if (player[turn].isFinished())
        {
            break;
        }
        turn++;
        if (turn == (count))
        {
            turn = 0;
        }
    }

    cout << "\nGame won in " << turnCount << " turns!\n";
    cout << "\nGame won by player: " << player[turn].name << "\n";
    return 0;
}



 