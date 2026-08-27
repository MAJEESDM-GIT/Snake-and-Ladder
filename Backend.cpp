#include <iostream>
#include <random>
#include <map>

using namespace std;

class dice;

class Player
{
    int roll = 0;
    int previous = 0;
    int current = 0;
    int intermediate = 0;
    int final = 0;
    map<int, int> port;

public:
    Player()
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
        port[42] = 77;
        port[22] = 45;
        port[65] = 92;
        port[4] = 42;
    }

    void getMove(dice &d1);
    void setMove();
    void currentState();
    bool isFinished();
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

void Player::getMove(dice &d1)
{
    roll = d1.randomRoll();
}

void Player::setMove()
{
    previous = current;
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
    else
    {
        final = intermediate;
    }

    current = final;
}

void Player::currentState()
{
    cout << "Rolled: " << roll << " | From: " << previous;

    if (intermediate > 100)
    {
        cout << " | Overshot 100! Stayed at square " << current << "\n";
    }
    else if (final != intermediate)
    {
        if (final > intermediate)
        {
            cout << " -> Landed on " << intermediate << " -> LADDER to square " << final << "\n";
        }
        else
        {
            cout << " -> Landed on " << intermediate << " -> SNAKE down to square " << final << "\n";
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

int main()
{   int count;
    cout << "Enter Player Number: "<<endl;
    cin>>count;
    if (count <= 0)
    {
        cerr << "Invalid player count.\n";
        return 1;
    }

    Player player[count];
    dice d1;

    int turn = 0;
    int turnCount = 0;
    
    while (true)
    {
        turnCount++;
        cout << "Turn of player : " << turn+1 << ": ";
        player[turn].getMove(d1);
        player[turn].setMove();
        player[turn].currentState();
      if (player[turn].isFinished())
        {
            break;
        }
      turn++;
      if(turn==(count)){
        turn=0;
      }
    }

    cout << "\nGame won in " << turnCount << " turns!\n";
    cout << "\nGame won by player: " << turn+1 << "\n";
    return 0;
}
