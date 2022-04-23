#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"



class TankAdaptee {
public:

	TankAdaptee() : x(0.0), y(0.0), width(0) { }

	void Paint();
	bool __fastcall isInRange(double x1, double x2) const;

	inline uint16_t GetScore() const { return score; }

	inline void SetPos(double nx, double ny) { x = nx; y = ny; }
	inline double GetY() const { return y; }
	inline double GetX() const { return x; }

	inline void SetWidth(uint16_t widthN) { width = widthN; }
	inline uint16_t GetWidth() const { return width; }

protected:

	double x, y;
	uint16_t width;
	const uint16_t score = 30;
};

class TankAdapter : public DestroyableGroundObject {
private:
	TankAdaptee* tank;
public:
	TankAdapter(TankAdaptee& tank) : tank(&tank) {}

	void SetPos(double nx, double ny)
	{
		tank->SetPos(nx, ny);
	}


	uint16_t GetWidth() const
	{
		return tank->GetWidth();
	}


	void Draw() const
	{
		tank->Paint();
	};


	bool __fastcall isInside(double x1, double x2) const
	{
		tank->isInRange(x1, x2);
	};

	inline uint16_t GetScore() const override {
		tank->GetScore();
	};

	inline double GetY() const {
		tank->GetY();
	};

	inline double GetX() const {
		tank->GetX();
	};

	inline void SetWidth(uint16_t widthN) {
		tank->SetWidth(widthN);
	};
};


/*Переопределенные вызовы*/

//vector<DestroyableGroundObject*> SBomber::FindDestoyableGroundObjects() const
//{
//	vector<DestroyableGroundObject*> vec;
//	TankAdaptee tank;
//	DestroyableGroundObject* pTank = new TankAdapter(tank);
//	House* pHouse;
//	for (size_t i = 0; i < vecStaticObj.size(); i++)
//	{
//		pTank = dynamic_cast<TankAdapter*>(vecStaticObj[i]);
//		if (pTank != nullptr)
//		{
//			vec.push_back(pTank);
//			continue;
//		}
//
//		pHouse = dynamic_cast<House*>(vecStaticObj[i]);
//		if (pHouse != nullptr)
//		{
//			vec.push_back(pHouse);
//			continue;
//		}
//	}
//
//	return vec;
//}
//
//
//SBomber::SBomber()
//	: exitFlag(false),
//	startTime(0),
//	finishTime(0),
//	deltaTime(0),
//	passedTime(0),
//	fps(0),
//	bombsNumber(10),
//	score(0)
//{
//	WriteToLog(string(__FUNCTION__) + " was invoked");
//
//	Plane* p = new Plane;
//	p->SetDirection(1, 0.1);
//	p->SetSpeed(4);
//	p->SetPos(5, 10);
//	vecDynamicObj.push_back(p);
//
//	LevelGUI* pGUI = new LevelGUI;
//	pGUI->SetParam(passedTime, fps, bombsNumber, score);
//	const uint16_t maxX = GetMaxX();
//	const uint16_t maxY = GetMaxY();
//	const uint16_t offset = 3;
//	const uint16_t width = maxX - 7;
//	pGUI->SetPos(offset, offset);
//	pGUI->SetWidth(width);
//	pGUI->SetHeight(maxY - 4);
//	pGUI->SetFinishX(offset + width - 4);
//	vecStaticObj.push_back(pGUI);
//
//	Ground* pGr = new Ground;
//	const uint16_t groundY = maxY - 5;
//	pGr->SetPos(offset + 1, groundY);
//	pGr->SetWidth(width - 2);
//	vecStaticObj.push_back(pGr);
//
//	TankAdaptee tank;
//	GameObject* pTank = new TankAdapter(tank);
//	pTank->SetWidth(13);
//	pTank->SetPos(30, groundY - 1);
//	vecStaticObj.push_back(pTank);
//
//	pTank = new TankAdapter(tank);
//	pTank->SetWidth(13);
//	pTank->SetPos(50, groundY - 1);
//	vecStaticObj.push_back(pTank);
//
//	House* pHouse = new House;
//	pHouse->SetWidth(13);
//	pHouse->SetPos(80, groundY - 1);
//	vecStaticObj.push_back(pHouse);
//
//}