#include <iostream>
#include <StateAutomat.h>


int main()
{
    StateCoinContext* pStateCoinContext = new StateCoinContext(new HavingCoinState());
    StateCoffeeContext* pStateCoffeeContext = new StateCoffeeContext(new SellCoffeeState());
    StateButtonContext* pStateButtonContext = new StateButtonContext(new ReleasedButtonState());
    if (pStateCoinContext != nullptr && pStateCoffeeContext != nullptr && pStateButtonContext != nullptr)
    {
        pStateCoinContext->DropCoin();
        pStateButtonContext->PressButton();
        pStateCoffeeContext->CoffeeAvailable();
        pStateButtonContext->ReleaseButton();
        pStateCoffeeContext->CoffeeUnAvailable();
        pStateCoinContext->ReturnCoin();
        delete pStateCoinContext, pStateButtonContext, pStateCoffeeContext;
    }
    return 0;
}

