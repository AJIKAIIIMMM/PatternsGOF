#pragma once

#include "DynamicObject.h"

class Bomb : public DynamicObject
{
public:

	static const uint16_t BombCost = 10; // стоимость бомбы в очках

	void Draw() const override;

private:

};


class BombDecorator : public DynamicObject {
public:
    Bomb bomb;

};


void BombDecorator::SetPos(double nx, double ny)  { bomb.SetPos(nx, ny); }
uint16_t BombDecorator::GetWidth() const { return bomb.GetWidth(); }

void BombDecorator::Move(uint16_t time) 
{
    bomb.Move(time * 1.6);
}

void BombDecorator::Draw() const
{
    bomb.Draw();
    // Некоторое изменение внешнего вида бомбы
    GotoXY(bomb.GetX(), bomb.GetY() - 1);
    cout << "|";
}