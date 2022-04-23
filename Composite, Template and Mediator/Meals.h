#pragma once

class Meal {
public:
    virtual int getPrice() = 0;
    virtual std::string getName() = 0;
    void addMeal(Meal* p) {
        assert(false);
    }
    virtual ~Meal() {}
};


class morningPancake : public Meal {
public:
    morningPancake() {}
    int getPrice() {
        return 240;
    };
    std::string getName() {
        return "Morning pancake";
    };
};

class lunchPancake : public Meal {
public:
    lunchPancake() {}
    int getPrice() {
        return 280;
    };
    std::string getName() {
        return "Lunch pancake";
    };
};

class mexicanPancake : public Meal {
public:
    mexicanPancake() {}
    int getPrice() {
        return 270;
    };
    std::string getName() {
        return "Mexican pancake";
    };
};

class potatoPancake : public Meal {
public:
    potatoPancake() {}
    int getPrice() {
        return 210;
    };
    std::string getName() {
        return "Potato pancake";
    };
};

class mushroomPancake : public Meal {
public:
    mushroomPancake() {}
    int getPrice() {
        return 220;
    };
    std::string getName() {
        return "Mushroom pancake";
    };
};

class falafelPancake : public Meal {
public:
    falafelPancake() {}
    int getPrice() {
        return 270;
    };
    std::string getName() {
        return "Falafel pancake";
    };
};

class chocolatePancake : public Meal {
public:
    chocolatePancake() {}
    int getPrice() {
        return 260;
    };
    std::string getName() {
        return "Chocolate pancake";
    };
};

class bananaPancake : public Meal {
public:
    bananaPancake() {}
    int getPrice() {
        return 260;
    };
    std::string getName() {
        return "Banana pancake";
    };
};

class jamPancake : public Meal {
public:
    jamPancake() {}
    int getPrice() {
        return 190;
    };
    std::string getName() {
        return "Jam pancake";
    };
};

class IcebananaSplit : public Meal {
public:
    IcebananaSplit() {}
    int getPrice() {
        return 260;
    };
    std::string getName() {
        return "Banana Split";
    };
};

class IceberryScream : public Meal {
public:
    IceberryScream() {}
    int getPrice() {
        return 260;
    };
    std::string getName() {
        return "Berry ice cream";
    };
};

class IcehotBrauni : public Meal {
public:
    IcehotBrauni() {}
    int getPrice() {
        return 310;
    };
    std::string getName() {
        return "Hot Brauni";
    };
};

class IcetuttiFruity : public Meal {
public:
    IcetuttiFruity() {}
    int getPrice() {
        return 240;
    };
    std::string getName() {
        return "Tutti Fruity";
    };
};

class Icevanilla : public Meal {
public:
    Icevanilla() {}
    int getPrice() {
        return 180;
    };
    std::string getName() {
        return "Vanilla ice cream";
    };
};

class Icepistachio : public Meal {
public:
    Icepistachio() {}
    int getPrice() {
        return 230;
    };
    std::string getName() {
        return "Pistachio ice cream";
    };
};

class Drinkpepsi : public Meal {
public:
    Drinkpepsi() {}
    int getPrice() {
        return 120;
    };
    std::string getName() {
        return "Pepsi";
    };
};

class Drinkcoffee : public Meal {
public:
    Drinkcoffee() {}
    int getPrice() {
        return 80;
    };
    std::string getName() {
        return "Coffee";
    };
};

class Drinktea : public Meal {
public:
    Drinktea() {}
    int getPrice() {
        return 50;
    };
    std::string getName() {
        return "Tea";
    };
};

class CompositeMeal : public Meal {
public:
    std::string getName() override {
        std::string name = " ";
        return name;
    }
    int getPrice() {
        int total = 0;
        for (int i = 0; i < c.size(); ++i) {
            std::cout << c[i]->getName() << " " << c[i]->getPrice() << std::endl;
            total += c[i]->getPrice();
        }
        return total;
    }
    void addMeal(Meal* p) {
        c.push_back(p);
    }
    ~CompositeMeal() {
        for (int i = 0; i < c.size(); ++i)
            delete c[i];
    }
private:
    std::vector<Meal*> c;
};