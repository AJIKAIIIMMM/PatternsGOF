#pragma once

class Mediator {
private:
    Calendar* calendar;
public:
    Mediator(Calendar* calendar) : calendar(calendar) {

    }
    bool checkDayForCoffe() {
        if (calendar->getDay() < 4 && calendar->getDay() >= 0)  return true;  //���������� true, ���� ������ ����
    }

    bool checkDayForTea() {
        if (calendar->getDay() > 4 && calendar->getDay() < 7)  return true;//���������� true, ���� ��������  
    }

    bool checkGarbageDay() {
        if (calendar->getDay() == 1 || calendar->getDay() == 3)  return true;//���������� true, ���� ������� ��� �������
    }
};