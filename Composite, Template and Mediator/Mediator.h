#pragma once

class Mediator {
private:
    Calendar* calendar;
public:
    Mediator(Calendar* calendar) : calendar(calendar) {

    }
    bool checkDayForCoffe() {
        if (calendar->getDay() < 4 && calendar->getDay() >= 0)  return true;  //Возвращаем true, если будний день
    }

    bool checkDayForTea() {
        if (calendar->getDay() > 4 && calendar->getDay() < 7)  return true;//Возвращаем true, если выходной  
    }

    bool checkGarbageDay() {
        if (calendar->getDay() == 1 || calendar->getDay() == 3)  return true;//Возвращаем true, если вторник или четверг
    }
};