#pragma once

class Monster {
protected:
    int hp;
    int atk;
    int def;
public:
    Monster() : hp(0), atk(0), def(0) {}
    virtual void changeHp(int change) = 0;
    virtual void changeAtk(int change) = 0;
    virtual void changeDef(int change) = 0;

    virtual ~Monster() {}
};

class Player {
protected:
    int hp;
    int atk;
    int def;
public:
    Player(int hp, int atk, int def) : hp(hp), atk(atk), def(def){}
    inline int getHp() const {
        return hp;
    }

    inline int getAtk() const {
        return atk;
    }

    inline int getDef() const {
        return def;
    }
};


class Orc : public Monster {
private:
    Player* player;
    std::string type;
    int averagePower;
public:
    Orc(Player* player) : player(player), type("Orc") {
        averagePower = (player->getHp() + player->getAtk() + player->getDef())/3;
        if (averagePower < 50) {
            changeHp(50);
            changeAtk(15);
            changeDef(5);
        }
        else if(averagePower > 50 && averagePower < 100){
            changeHp(75);
            changeAtk(25);
            changeDef(10);
        }
        else if (averagePower > 100) {
            changeHp(100);
            changeAtk(35);
            changeDef(15);
        }
    }

    inline void changeHp(int change) {
        hp += change;
    }

    inline void changeAtk(int change) {
        atk += change;
    }

    inline void changeDef(int change) {
        def += change;
    }

    void printOrc() {
        std::cout << type << " HP: " << hp << " ATK: " << atk << " DEF: " << def << std::endl;
    }

};

