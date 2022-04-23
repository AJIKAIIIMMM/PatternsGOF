#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"

class House : public DestroyableGroundObject
{
public:

	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	virtual void Draw() const override;
	friend class HouseBuilderA;
private:

	char look[7][14];

	const uint16_t score = 40;
};

class HouseBuilder {
protected:
    House* house = nullptr;
public:
    virtual void createHouse() {}
    virtual void createWall() {}
    virtual void createRoof() {}
    virtual void createChimney() {}
    virtual void createWindow() {}
    virtual House* getHouse() const { return house; }

    virtual ~HouseBuilder() { }
};

class HouseBuilderA: public HouseBuilder{
public:
    void createHouse() override {
        house = new House;
    }
    void createRoof() {
        for (int i = 5; i < 9; i++) {
            house->look[0][i] = '#';
        }
        for (int i = 1; i < 5; i++) {
            house->look[1][i] = '#';
        }
        for (int i = 9; i < 13; i++) {
            house->look[1][i] = '#';
        }
    }
    void createWall() {
        for (int i = 2; i < 7; i++) {
            house->look[i][0] = '#';
        }
        for (int i = 2; i < 7; i++) {
            house->look[i][13] = '#';
        }
    }
    void createChimney() {
        house->look[0][11] = '#';
    }
    void createWindow() {
        house->look[4][5] = '#';
        house->look[4][8] = '#';
        for (int i = 5; i < 9; i++) {
            house->look[5][i] = '#';
        }
    }

};

class HouseDirector {
public:
    House* createHouseWithoutChimney(HouseBuilder& builder) {
        builder.createHouse();
        builder.createRoof();
        builder.createWall();
        builder.createWindow();
        return builder.getHouse();
    }
    House* createHouseWithChimney(HouseBuilder& builder) {
        MyTools::SetColor(CC_Yellow);
        builder.createHouse();
        builder.createRoof();
        builder.createWall();
        builder.createChimney();
        builder.createWindow();
        return builder.getHouse();
    }
};

// Переделанная функция Draw
void House::Draw() const
{
    MyTools::SetColor(CC_Yellow);
    GotoXY(x, y - 6);
    for (int i = 0; i < 14; i++) {
        cout << look[0][i];
    }
    GotoXY(x, y - 5);
    for (int i = 0; i < 14; i++) {
        cout << look[1][i];
    }
    GotoXY(x, y - 4);
    for (int i = 0; i < 14; i++) {
        cout << look[2][i];
    }
    GotoXY(x, y - 3);
    for (int i = 0; i < 14; i++) {
        cout << look[3][i];
    }
    GotoXY(x, y - 2);
    for (int i = 0; i < 14; i++) {
        cout << look[4][i];
    }
    GotoXY(x, y - 1);
    for (int i = 0; i < 14; i++) {
        cout << look[5][i];
    }
    GotoXY(x, y);
    for (int i = 0; i < 14; i++) {
        cout << look[6][i];
    }
}


// Вызов в конструкторе SBomber
int choice = 0;
do {
    HouseDirector director;
    HouseBuilder builder;
    HouseBuilderA builderA;
    std::cout << "Which house would you like to construct?\n";
    std::cout << "1)With chimney\n2)Without chimney\n";
    std::cin >> choice;
    House* pHouse = nullptr;
    switch (choice) {
    case 1:
        House * pHouse = director.createHouseWithChimney();
        break;
    case 2:
        House * pHouse = director.createHouseWithoutChimney();
        break;
    default: continue;
    }
    if (pHouse != nullptr) break;
} while (true);
pHouse->SetWidth(13);
pHouse->SetPos(80, groundY - 1);
vecStaticObj.push_back(pHouse);