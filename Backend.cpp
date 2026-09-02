#include <iostream>
#include <random>
#include <ctime>
#include <map>
#include <vector>
using namespace std;

void clear_buffer();
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
    // mt19937 gen{random_device{}()};
    mt19937 gen{static_cast<unsigned>(std::time(nullptr))};
    uniform_int_distribution<int> range{1, 6};

public:
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
    cout << "\t\t\t\tPress Q to quit" << endl;
}

void Player::getMove(dice &d1)
{
     cout << "\n -> Press ENTER (or type 'Q' to quit): ";
    cin.get(temp);

    if (temp == 'q' || temp == 'Q')
    {
        cout << "\nQuitting game...\n";
        exit(0);
    }
    
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

class room
{
public:
    int id;
    int capacity = 3;
    vector<Player> player;
    bool started = false;
    int start_game()
    {
    system("cls");
    cout << "=================================================================\n";
    cout << "                     SNAKES AND LADDERS GAME                     \n";
    cout << "=================================================================\n";

        int turn = 0;
        int turnCount = 0;
        dice d1;
        board b1;
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
            if (turn == (capacity))
            {
                turn = 0;
            }
        }

        cout << "\nGame won in " << turnCount << " turns!\n";
        cout << "\nGame won by player: " << player[turn].name << "\n";
        return 0;
    }
};
void clear_buffer()
{
    cin.clear();
    int ch;
    while ((ch = cin.get()) != '\n' && ch != EOF)
        ;
}
int main()
{

    map<int, room> Ac_rooms;
    // mt19937 gen{random_device{}()};
    mt19937 gen{static_cast<unsigned>(std::time(nullptr))};
    uniform_int_distribution<int> range{1000, 9999};
    while (true)
    {
        cout << "\n--- SNAKES & LADDERS ---\n";
        cout << "1. Create Room\n2. Join Room\n3. Exit\nChoose: ";
        int choice;

        cin >> choice;
        clear_buffer();
        if (choice == 1)
        {

            int code = range(gen);
            room newRoom;
            cout << "Enter Target Player Number: " << endl;
            cin >> newRoom.capacity;
            if (newRoom.capacity <= 0)
            {
                cerr << "Invalid player count.\n";
                exit(1);
            }
            newRoom.id = code;
            Player host;
            cout << "Enter Host Name: ";
            cin >> host.name;
            clear_buffer();
            newRoom.player.push_back(host);
            cout << "\nRoom created! Your Room Code is: " << code << "\n";
            system("cls");
             cout << "\n [*] ROOM CODE: " << code << " (Share this with other players)";
            Ac_rooms[code] = newRoom;
        }
        else if (choice == 2)
        {
            int code;
            cout << "Enter 4-Digit Room Code: ";

            cin >> code;
            clear_buffer();
            auto it = Ac_rooms.find(code);
            if (it != Ac_rooms.end())
            {
                room &r = it->second;
                if (r.player.size() >= (r.capacity))
                {
                    cout << "Room is already full!\n";
                    continue;
                }

                Player guest;
                cout << "Enter Player Name: ";

                cin >> guest.name;
                clear_buffer();
                r.player.push_back(guest);

                cout << "Joined room " << code << "! (" << r.player.size() << "/" << r.capacity << ")\n";

                if (r.player.size() == (r.capacity))
                {
                    cout << "Room full! Starting game...\n";
                    r.start_game();
                    Ac_rooms.erase(it);
                }
            }
            else
            {
                cout << "Room code not found!\n";
            }
        }
        else if (choice == 3)
        {
            cout << "Exiting program...\n";
            break;
        }
        else
        {
            cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}