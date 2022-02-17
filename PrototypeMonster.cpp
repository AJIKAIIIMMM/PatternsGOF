#include <iostream>
#include <vector>
#include <MonsterPrototype.h>

int main()
{
    Player* player = new Player(100, 23, 15);
    std::vector<Orc*> area;

    area.push_back(new Orc(player));

    Player* player1 = new Player(200, 50, 20);
    area.push_back(new Orc(player1));


    Player* player2 = new Player(300, 70, 30);
    area.push_back(new Orc(player2));

    for (Orc* ptr : area) {
        ptr->printOrc();
    }

}

