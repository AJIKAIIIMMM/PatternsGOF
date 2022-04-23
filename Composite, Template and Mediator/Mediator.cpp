#include <iostream>
#include <vector>
#include "Mediator.h"


class Calendar {
public:
    enum Days {
        MONDAY,
        TUESDAY,
        WENDSDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY,
        SUNDAY
    };
private:
    Days m_day;
public:
    Calendar(Days day) : m_day(day) {}
    Days getDay() { return m_day; }

};


class Coffee {
private:
    Mediator* cmediator;
public:
    Coffee(Mediator* cmediator) : cmediator(cmediator) {
        doCoffee();
    }

    void doCoffee() {
        if(cmediator->checkDayForCoffe()) std::cout << "Starting coffee" << std::endl;
    }

};

class TeaPot{
private:
    Mediator* cmediator;
public:
    TeaPot(Mediator* cmediator) : cmediator(cmediator) {
        doTea();
    }

    void doTea() {
        if (cmediator->checkDayForTea()) std::cout << "Starting tea" << std::endl;
    }

};

class Alarm{
private:      
    Mediator* cmediator;
public:
    Alarm(Mediator* cmediator)  : cmediator(cmediator) {
        doAlarm();
    }

    void doAlarm() {
        if (cmediator->checkDayForTea())
            std::cout << "DO NOT ALARM" << std::endl;
        else if (cmediator->checkDayForCoffe())
            std::cout << "Rise and shine, Mr. Freeman" << std::endl;
        else if (cmediator->checkGarbageDay())
            std::cout << "It's garbage day. GET UP" << std::endl;
    }
};


int main(){
    Calendar monday(Calendar::MONDAY);
    Mediator mediator(&monday);
    Coffee cof(&mediator);
    TeaPot tea(&mediator); 
    Alarm alarm(&mediator);

    return 0;
}
