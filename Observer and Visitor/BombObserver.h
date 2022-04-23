#pragma once

#include "DynamicObject.h"
#include "SBomber.h"

class Observer
{
public:
	virtual bool HandleInsideCheck(Bomb* pBomb) {
		for (auto it = m_views.begin(); it != m_views.end(); ++it) {
			if (*it == observer) m_views.erase(it);
		}
	};
};

class Subject {
	std::vector <Observer*> m_views;
public:
	void AddObserver(Observer* observ) {
		m_views.push_back(observ);
	}

	void removeObserver(Observer* observer){
		for (auto it = m_views.begin(); it != m_views.end(); ++it) {
			if (*it == observer) m_views.erase(it);
		}
	}

};

class Bomb : public DynamicObject, Observer, SBomber
{
public:

	static const uint16_t BombCost = 10; // стоимость бомбы в очках

	void Draw() const override;

	void CheckDestoyableObjects(Bomb* pBomb)
	{
		vector<DestroyableGroundObject*> vecDestoyableObjects = SBomber::FindDestoyableGroundObjects();
		const double size = pBomb->GetWidth();
		const double size_2 = size / 2;
		for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
		{
			const double x1 = pBomb->GetX() - size_2;
			const double x2 = x1 + size;

			if (vecDestoyableObjects[i]->isInside(x1, x2))
			{
				SBomber::score += vecDestoyableObjects[i]->GetScore();
				SBomber::DeleteStaticObj(vecDestoyableObjects[i]);
			}
		}
	}

private:
	

};

