#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"

class SBomber
{
public:

    SBomber();
    ~SBomber();
    
    inline bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();



    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void __fastcall CheckDestoyableObjects(Bomb* pBomb);

    void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
    void __fastcall DeleteStaticObj(GameObject* pObj);

    Ground * FindGround() const;
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    std::vector<Bomb*> FindAllBombs() const;

    void DropBomb();

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    
    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
};

class Command
{
public:
    void setBomber(SBomber* pBomb)
    {
        pgame = pBomb;
    }   
    virtual void execute() = 0;
protected:
    SBomber* pgame;
};

class DeleteDynamic : public Command{
    DynamicObject* _Bomb;
public:
    DeleteDynamic(DynamicObject* pBomb, std::vector<DynamicObject*> &vecDynamicObj) : Command(pBomb), _Bomb(pBomb) {}
    void execute() { pgame->DeleteDynamicObj(_Bomb); }
};

class DeleteStatic : public Command{
    GameObject* _Obj;
public:
    DeleteStatic(GameObject* pObj, std::vector<DynamicObject*>& vecStaticObj) : Command(pObj), _Obj(pObj) {}
    void execute() { pgame->DeleteStaticObj(_Obj); }
};

class PlaneCommand : public Command {
public:
    PlaneCommand(Plane* _plane, std::vector<DynamicObject*>& vecDynamicObj, const uint16_t &bombsNumber) {}
    void execute() {
        pgame->FindPlane();
        pgame->FindAllBombs();
    }
};