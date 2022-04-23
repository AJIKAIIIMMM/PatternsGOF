#pragma once

#include <conio.h>
#include <windows.h>

#include "MyTools.h"
#include "SBomber.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"


//ֲûחמג לועמהמג
void SBomber::CheckObjects()
{
    WriteToLog(string(__FUNCTION__) + " was invoked");
    CollisionDetector* detector = new CollisionDetector;
    detector->CheckPlaneAndLevelGUI();
    detector->CheckBombsAndGround();
};

class Collision : public SBomber {
public:
    virtual void CheckPlaneAndLevelGUI() = 0;
    virtual void CheckBombsAndGround() = 0;
    virtual void CheckDestoyableObjects(Bomb* pBomb);
};

class CollisionDetector {
    Collision* collision;
public:
    void CheckPlaneAndLevelGUI() {
        if (collision->FindPlane()->GetX() > collision->FindLevelGUI()->GetFinishX())
        {
            collision->exitFlag = true;
        }
    }
    void CheckBombsAndGround() {
        vector<Bomb*> vecBombs = collision->FindAllBombs();
        Ground* pGround = collision->FindGround();
        const double y = pGround->GetY();
        for (size_t i = 0; i < vecBombs.size(); i++)
        {
            if (vecBombs[i]->GetY() >= y) // 
            {
                pGround->AddCrater(vecBombs[i]->GetX());
                CheckDestoyableObjects(vecBombs[i]);
                collision->DeleteDynamicObj(vecBombs[i]);
            }
        }
    }
    void CheckDestoyableObjects(Bomb* pBomb) {
        vector<Bomb*> vecBombs = collision->FindAllBombs();
        Ground* pGround = collision->FindGround();
        const double y = pGround->GetY();
        for (size_t i = 0; i < vecBombs.size(); i++)
        {
            if (vecBombs[i]->GetY() >= y) 
            {
                pGround->AddCrater(vecBombs[i]->GetX());
                CheckDestoyableObjects(vecBombs[i]);
                collision->DeleteDynamicObj(vecBombs[i]);
            }
        }
    }

};