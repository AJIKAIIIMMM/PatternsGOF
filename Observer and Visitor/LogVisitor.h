#pragma once

#include <stdint.h>

#include "GameObject.h"

class DynamicObject : public GameObject 
{
public:

    DynamicObject() : speed(0.0), xDirction(0.0), yDirection(0) { }

    inline void SetSpeed(double sp) { speed = sp; }
    inline void SetDirection(double dx, double dy) { xDirction = dx; yDirection = dy; }
    
    virtual void Move(uint16_t time) { x += xDirction * speed * time * 0.001; y += yDirection * speed * time * 0.001; };

    virtual void __fastcall Accept(Visitor* v) = 0;

    inline double GetSpeed() { return speed;}

    inline std::pair <double, double> GetDirection() { 
        vector = std::make_pair(xDirction, yDirection);
        return vector;
    }

protected:
    std::pair <double, double> vector;
    double speed;
    double xDirction, yDirection;

};

class Visitor {
public:
    virtual void log (Bomb* bomb) = 0;
    virtual void log(Plane* plane) = 0;
   
};

class LogVisitor : public Visitor{
public:
    void log(Plane* plane) override{
        MyTools::WriteToLog("Speed of plane is ", plane->GetSpeed());
        MyTools::WriteToLog("Direction of plane is ", plane->GetDirection());
    }

    void log(Bomb* bomb) override {
        MyTools::WriteToLog("Speed of bomb is ", bomb->GetSpeed());
        MyTools::WriteToLog("Direction of bomb is ", bomb->GetDirection());
    }
};


//V faile SBomber.cpp

void SBomber::MoveObjects()
{
    WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        if (vecDynamicObj[i] != nullptr)
        {
            vecDynamicObj[i]->Move(deltaTime);
            vecDynamicObj[i]->Accept(LogVis);
        }
    }
};

//V faile SBomber.h bul sozdan object clasa LogVisitor
//V classi Plane.h i Bomb.h dobavil pereopredelenuye functions Accept

class Plane : public DynamicObject {
public:

    void Draw() const override;

    inline void ChangePlaneY(double dy) { yDirection += dy; }

    void __fastcall Accept(Visitor* v)override
    {
        v->log(this);
    }

private:

};

class Bomb : public DynamicObject
{
public:

    static const uint16_t BombCost = 10; // стоимость бомбы в очках

    void Draw() const override;

    void __fastcall Accept(Visitor* v)override
    {
        v->log(this);
    }

private:

};

//V MyTools.h i .cpp dobavil ewe odno opredeleniye function WriteToLog

void __fastcall WriteToLog(const std::string& str, std::pair <double, double> vector);

void __fastcall WriteToLog(const string& str, std::pair <double, double> vector)
{
    if (logOut.is_open())
    {
        logOut << GetCurDateTime() << " - " << str << vector.first << vector.second << endl;
    }
}
