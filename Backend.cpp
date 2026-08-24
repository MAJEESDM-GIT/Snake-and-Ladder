#include <iostream>
#include <random>
#include<map>
using namespace std;
//define board dice player snake ladder 
class dice;
class board{
    int size[100];
    int roll;
    int current;
    int intermediate;
    int final;
    public:
    void getMove(dice& d1);
    void setMove();
    void snake_ladder();
};
class dice{
    int roll;
    int turn;
    public:
    int randomRoll();
};
void board::getMove(dice& d1){
    roll = d1.randomRoll();
}
void board::setMove(){
    current = 0;
    intermediate = current + roll;



}
void board::snake_ladder(){
    map<int,int>port;
    //snake
    port[99]=8;
    port[92]=73;
    port[84]=77;
    port[25]=5;
    port[49]=11;
    port[62]=42;
//ladder
port[99]=8;
    port[78]=95;
    port[42]=77;
    port[22]=45;
    port[65]=92;
    port[4]=42;


}
int dice::randomRoll(){
        random_device rd;
        mt19937 rolls(rd());
        uniform_int_distribution<int>range(1,6);
        roll = range(rolls);
}
int main(){
    board b1;
    dice d1;
    b1.getMove(d1);
    
    return 0;
}