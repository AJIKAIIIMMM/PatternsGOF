#pragma once

class StateCoinContext;
class StateCoffeeContext;
class StateButtonContext;

class StateCoin {
private:
    std::string name;
public:
    StateCoin(const std::string& name) : name(name) {}

    const std::string& getName() const {
        return name;
    }

    virtual void DropCoin(StateCoinContext*) = 0;
    virtual void ReturnCoin(StateCoinContext*) = 0;
};

class StateCoffee {
private:
    std::string name;
public:
    StateCoffee(const std::string& name) : name(name) {}

    const std::string& getName() const {
        return name;
    }

    virtual void CoffeeAvailable(StateCoffeeContext*) = 0;
    virtual void CoffeeUnAvailable(StateCoffeeContext*) = 0;
};

class StateButton {
private:
    std::string name;
public:
    StateButton(const std::string& name) : name(name) {}

    const std::string& getName() const {
        return name;
    }

    virtual void PressButton(StateButtonContext*) = 0;
    virtual void ReleaseButton(StateButtonContext*) = 0;
};

class StateCoinContext {
private:
    StateCoin* state;
public:
    StateCoinContext(StateCoin* state) : state(state) {}


    void DropCoin() {
        std::cout << "Pocket full of " << state->getName() << "..." << std::endl;
        state->DropCoin(this);
    }
    void ReturnCoin() {
        std::cout << "Fulling " << state->getName() << " space in the pocket ..." << std::endl;
        state->ReturnCoin(this);
    }


    StateCoin* GetState() {
        return state;
    }

    void setState(StateCoin* newState) {
        std::cout << "Changing newState from " << state->getName()
            << " to " << newState->getName() << "..." << std::endl;
        delete state;
        state = newState;
    }

    virtual ~StateCoinContext() {
        delete state;
    }
};

class StateCoffeeContext {
private:
    StateCoffee* state;
public:
    StateCoffeeContext(StateCoffee* state) : state(state) {}

    void CoffeeAvailable() {
        std::cout << "There is " << state->getName() << "..." << std::endl;
        state->CoffeeAvailable(this);
    }
    void CoffeeUnAvailable() {
        std::cout << "Out of " << state->getName() << "..." << std::endl;
        state->CoffeeUnAvailable(this);
    }


    StateCoffee* GetState() {
        return state;
    }

    void setState(StateCoffee* newState) {
        std::cout << "Changing newState from " << state->getName()
            << " to " << newState->getName() << "..." << std::endl;
        delete state;
        state = newState;
    }

    virtual ~StateCoffeeContext() {
        delete state;
    }
};

class StateButtonContext {
private:
    StateButton* state;
public:
    StateButtonContext(StateButton* state) : state(state) {}

    void PressButton() {
        std::cout << "Pressing " << state->getName() << "..." << std::endl;
        state->PressButton(this);
    }
    void ReleaseButton() {
        std::cout << "Releasing " << state->getName() << "..." << std::endl;
        state->ReleaseButton(this);
    }

    StateButton* GetState() {
        return state;
    }

    void setState(StateButton* newState) {
        std::cout << "Changing newState from " << state->getName()
            << " to " << newState->getName() << "..." << std::endl;
        delete state;
        state = newState;
    }

    virtual ~StateButtonContext() {
        delete state;
    }
};


class HavingCoinState : public StateCoin {
public:
    HavingCoinState() : StateCoin("coins") {}
    void DropCoin(StateCoinContext* context) override;
    void ReturnCoin(StateCoinContext* context) override;
};

class NotHavingCoinState : public StateCoin {
public:
    NotHavingCoinState() : StateCoin("empty") {}

    void DropCoin(StateCoinContext* context) override;
    void ReturnCoin(StateCoinContext* context) override;
};

class SellCoffeeState : public StateCoffee {
public:
    SellCoffeeState() : StateCoffee("coffee") {}

    void CoffeeAvailable(StateCoffeeContext* state) override;
    void CoffeeUnAvailable(StateCoffeeContext* state) override;
};

class CoffeeSoldOutState : public StateCoffee {
public:
    CoffeeSoldOutState() : StateCoffee("any coffee") {}

    void CoffeeAvailable(StateCoffeeContext* state) override;
    void CoffeeUnAvailable(StateCoffeeContext* state) override;
};

class PressedButtonState : public StateButton {
public:
    PressedButtonState() : StateButton("Button is pressed") {}

    void PressButton(StateButtonContext* state) override;
    void ReleaseButton(StateButtonContext* state) override;
};

class ReleasedButtonState : public StateButton {
public:
    ReleasedButtonState() : StateButton("Button is free") {}

    void PressButton(StateButtonContext* state) override;
    void ReleaseButton(StateButtonContext* state) override;
};

void HavingCoinState::DropCoin(StateCoinContext* state) {
    state->setState(new NotHavingCoinState);
}

void HavingCoinState::ReturnCoin(StateCoinContext* state) {
    std::cout << "Do nothing" << std::endl;
}

void NotHavingCoinState::DropCoin(StateCoinContext* state) {
    std::cout << "Do nothing" << std::endl;
}

void NotHavingCoinState::ReturnCoin(StateCoinContext* state) {
    state->setState(new HavingCoinState);
}

void SellCoffeeState::CoffeeAvailable(StateCoffeeContext* state) {
    state->setState(new CoffeeSoldOutState);

}

void SellCoffeeState::CoffeeUnAvailable(StateCoffeeContext* state) {
    std::cout << "Do nothing" << std::endl;
}

void CoffeeSoldOutState::CoffeeAvailable(StateCoffeeContext* state) {
    std::cout << "Automat was fueld" << std::endl;
}

void CoffeeSoldOutState::CoffeeUnAvailable(StateCoffeeContext* state) {
    state->setState(new SellCoffeeState);
}

void PressedButtonState::PressButton(StateButtonContext* state) {
    std::cout << "Do nothing" << std::endl;
}

void PressedButtonState::ReleaseButton(StateButtonContext* state) {
    state->setState(new ReleasedButtonState);
}

void ReleasedButtonState::PressButton(StateButtonContext* state) {
    std::cout << "Button was released" << std::endl;
    state->setState(new PressedButtonState);
}

void ReleasedButtonState::ReleaseButton(StateButtonContext* state) {
    std::cout << "Do nothing" << std::endl;
}