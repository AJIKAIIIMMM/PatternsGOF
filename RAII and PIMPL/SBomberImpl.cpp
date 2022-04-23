
#include <conio.h>
#include <windows.h>
#include <algorithm>

#include "MyTools.h"
#include "SBomber.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"


using namespace std;
using namespace MyTools;


class SBomber::SBomberImpl {
public:
    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
    bool exitFlag;
    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;


    SBomberImpl():exitFlag(false),
        startTime(0),
        finishTime(0),
        deltaTime(0),
        passedTime(0),
        fps(0),
        bombsNumber(10),
        score(0) {
        WriteToLog(string(__FUNCTION__) + " was invoked");

        Plane* p = new Plane;
        p->SetDirection(1, 0.1);
        p->SetSpeed(4);
        p->SetPos(5, 10);
        vecDynamicObj.push_back(p);

        LevelGUI* pGUI = new LevelGUI;
        pGUI->SetParam(passedTime, fps, bombsNumber, score);
        const uint16_t maxX = GetMaxX();
        const uint16_t maxY = GetMaxY();
        const uint16_t offset = 3;
        const uint16_t width = maxX - 7;
        pGUI->SetPos(offset, offset);
        pGUI->SetWidth(width);
        pGUI->SetHeight(maxY - 4);
        pGUI->SetFinishX(offset + width - 4);
        vecStaticObj.push_back(pGUI);

        Ground* pGr = new Ground;
        const uint16_t groundY = maxY - 5;
        pGr->SetPos(offset + 1, groundY);
        pGr->SetWidth(width - 2);
        vecStaticObj.push_back(pGr);

        Tank* pTank = new Tank;
        pTank->SetWidth(13);
        pTank->SetPos(30, groundY - 1);
        vecStaticObj.push_back(pTank);

        pTank = new Tank;
        pTank->SetWidth(13);
        pTank->SetPos(50, groundY - 1);
        vecStaticObj.push_back(pTank);

        House* pHouse = new House;
        pHouse->SetWidth(13);
        pHouse->SetPos(80, groundY - 1);
        vecStaticObj.push_back(pHouse);

        /*
        Bomb* pBomb = new Bomb;
        pBomb->SetDirection(0.3, 1);
        pBomb->SetSpeed(2);
        pBomb->SetPos(51, 5);
        pBomb->SetSize(SMALL_CRATER_SIZE);
        vecDynamicObj.push_back(pBomb);
        */
    }

    
};



SBomber::~SBomber()
{
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        if (vecDynamicObj[i] != nullptr)
        {
            delete vecDynamicObj[i];
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        if (vecStaticObj[i] != nullptr)
        {
            delete vecStaticObj[i];
        }
    }
}

SBomber::SBomber(const SBomber& other) : pImpl(new SBomberImpl(*other.pImpl)){};

SBomber& SBomber::operator=(SBomber& other) {
    std::swap(pImpl, other.pImpl);
    return other;
};

void SBomber::MoveObjects()
{
    WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < pImpl->vecDynamicObj.size(); i++)
    {
        if (pImpl->vecDynamicObj[i] != nullptr)
        {
            pImpl->vecDynamicObj[i]->Move(pImpl->deltaTime);
        }
    }
};

void SBomber::CheckObjects()
{
    WriteToLog(string(__FUNCTION__) + " was invoked");

    CheckPlaneAndLevelGUI();
    CheckBombsAndGround();
};

void SBomber::CheckPlaneAndLevelGUI()
{
    if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX())
    {
        pImpl->exitFlag = true;
    }
}

void SBomber::CheckBombsAndGround() 
{
    vector<Bomb*> vecBombs = FindAllBombs();
    Ground* pGround = FindGround();
    const double y = pGround->GetY();
    for (size_t i = 0; i < vecBombs.size(); i++)
    {
        if (vecBombs[i]->GetY() >= y) // Пересечение бомбы с землей
        {
            pGround->AddCrater(vecBombs[i]->GetX());
            CheckDestoyableObjects(vecBombs[i]);
            DeleteDynamicObj(vecBombs[i]);
        }
    }

}

void SBomber::CheckDestoyableObjects(Bomb * pBomb)
{
    vector<DestroyableGroundObject*> vecDestoyableObjects = FindDestoyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
    {
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecDestoyableObjects[i]->isInside(x1, x2))
        {
            pImpl->score += vecDestoyableObjects[i]->GetScore();
            DeleteStaticObj(vecDestoyableObjects[i]);
        }
    }
}

void SBomber::DeleteDynamicObj(DynamicObject* pObj)
{
    auto it = pImpl->vecDynamicObj.begin();
    for (; it != pImpl->vecDynamicObj.end(); it++)
    {
        if (*it == pObj)
        {
            pImpl->vecDynamicObj.erase(it);
            break;
        }
    }
}

void SBomber::DeleteStaticObj(GameObject* pObj)
{
    auto it = pImpl->vecStaticObj.begin();
    for (; it != pImpl->vecStaticObj.end(); it++)
    {
        if (*it == pObj)
        {
            pImpl->vecStaticObj.erase(it);
            break;
        }
    }
}

vector<DestroyableGroundObject*> SBomber::FindDestoyableGroundObjects() const
{
    vector<DestroyableGroundObject*> vec;
    Tank* pTank;
    House* pHouse;
    for (size_t i = 0; i < pImpl->vecStaticObj.size(); i++)
    {
        pTank = dynamic_cast<Tank*>(pImpl->vecStaticObj[i]);
        if (pTank != nullptr)
        {
            vec.push_back(pTank);
            continue;
        }

        pHouse = dynamic_cast<House*>(pImpl->vecStaticObj[i]);
        if (pHouse != nullptr)
        {
            vec.push_back(pHouse);
            continue;
        }
    }

    return vec;
}

Ground* SBomber::FindGround() const
{
    Ground* pGround;

    for (size_t i = 0; i < pImpl->vecStaticObj.size(); i++)
    {
        pGround = dynamic_cast<Ground *>(pImpl->vecStaticObj[i]);
        if (pGround != nullptr)
        {
            return pGround;
        }
    }

    return nullptr;
}

vector<Bomb*> SBomber::FindAllBombs() const
{
    vector<Bomb*> vecBombs;

    for (size_t i = 0; i < pImpl->vecDynamicObj.size(); i++)
    {
        Bomb* pBomb = dynamic_cast<Bomb*>(pImpl->vecDynamicObj[i]);
        if (pBomb != nullptr)
        {
            vecBombs.push_back(pBomb);
        }
    }

    return vecBombs;
}

Plane* SBomber::FindPlane() const
{
    for (size_t i = 0; i < pImpl->vecDynamicObj.size(); i++)
    {
        Plane* p = dynamic_cast<Plane*>(pImpl->vecDynamicObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

LevelGUI* SBomber::FindLevelGUI() const
{
    for (size_t i = 0; i < pImpl->vecStaticObj.size(); i++)
    {
        LevelGUI* p = dynamic_cast<LevelGUI*>(pImpl->vecStaticObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

void SBomber::ProcessKBHit()
{
    int c = _getch();

    if (c == 224)
    {
        c = _getch();
    }

    WriteToLog(string(__FUNCTION__) + " was invoked. key = ", c);

    switch (c) {

    case 27: // esc
        pImpl->exitFlag = true;
        break;

    case 72: // up
        FindPlane()->ChangePlaneY(-0.25);
        break;

    case 80: // down
        FindPlane()->ChangePlaneY(0.25);
        break;

    case 'b':
        DropBomb();
        break;

    case 'B':
        DropBomb();
        break;

    default:
        break;
    }
}

void SBomber::DrawFrame()
{
    WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < pImpl->vecDynamicObj.size(); i++)
    {
        if (pImpl->vecDynamicObj[i] != nullptr)
        {
            pImpl->vecDynamicObj[i]->Draw();
        }
    }

    for (size_t i = 0; i < pImpl->vecStaticObj.size(); i++)
    {
        if (pImpl->vecStaticObj[i] != nullptr)
        {
            pImpl->vecStaticObj[i]->Draw();
        }
    }

    GotoXY(0, 0);
    pImpl->fps++;

    FindLevelGUI()->SetParam(pImpl->passedTime, pImpl->fps, pImpl->bombsNumber, pImpl->score);
}

void SBomber::TimeStart()
{
    WriteToLog(string(__FUNCTION__) + " was invoked");
    pImpl->startTime = GetTickCount64();
}

void SBomber::TimeFinish()
{
    pImpl->finishTime = GetTickCount64();
    pImpl->deltaTime = uint16_t(pImpl->finishTime - pImpl->startTime);
    pImpl->passedTime += pImpl->deltaTime;

    WriteToLog(string(__FUNCTION__) + " deltaTime = ", (int)pImpl->deltaTime);
}

void SBomber::DropBomb()
{
    if (pImpl->bombsNumber > 0)
    {
        WriteToLog(string(__FUNCTION__) + " was invoked");

        Plane* pPlane = FindPlane();
        double x = pPlane->GetX() + 4;
        double y = pPlane->GetY() + 2;

        Bomb* pBomb = new Bomb;
        pBomb->SetDirection(0.3, 1);
        pBomb->SetSpeed(2);
        pBomb->SetPos(x, y);
        pBomb->SetWidth(SMALL_CRATER_SIZE);

        pImpl->vecDynamicObj.push_back(pBomb);
        pImpl->bombsNumber--;
        pImpl->score -= Bomb::BombCost;
    }
}
