#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include "Meals.h"


CompositeMeal* BreakfastPan(){
    CompositeMeal* breakfast = new CompositeMeal;
    breakfast->addMeal(new morningPancake);
    breakfast->addMeal(new Drinkcoffee);
    return breakfast;
}

CompositeMeal* LunchPan(){
    CompositeMeal* lunch = new CompositeMeal;
    lunch->addMeal(new lunchPancake);
    lunch->addMeal(new chocolatePancake);
    lunch->addMeal(new Drinktea);
    return lunch;
}

CompositeMeal* DinnerPan(){
    CompositeMeal* dinner = new CompositeMeal;
    dinner->addMeal(new potatoPancake);
    dinner->addMeal(new jamPancake);
    dinner->addMeal(new Drinkpepsi);

    return dinner;
}

CompositeMeal* SpicyPan(){
    CompositeMeal* spicy = new CompositeMeal;
    spicy->addMeal(new mexicanPancake);
    spicy->addMeal(new falafelPancake);
    spicy->addMeal(new Icepistachio);
    spicy->addMeal(new Drinkpepsi);
    return spicy;
}

int main() {
    CompositeMeal* meal = new CompositeMeal;
    meal->addMeal(BreakfastPan());

    std::cout << "BreakfastPan combo consist of "
        << meal->getPrice() << std::endl;

    delete meal;

    meal->addMeal(LunchPan());

    std::cout << "LunchPan combo consist of "
        << meal->getPrice() << std::endl;

    delete meal;

    meal->addMeal(DinnerPan());

    std::cout << "DinnerPan combo consist of "
        << meal->getPrice() << std::endl;

    delete meal;

    meal->addMeal(SpicyPan());

    std::cout << "SpicyPan combo consist of "
        << meal->getPrice() << std::endl;

    delete meal;

    return 0;
}

