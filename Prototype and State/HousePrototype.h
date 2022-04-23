#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"

class House : public DestroyableGroundObject
{
public:

	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() const override;

	DestroyableGroundObject* clone() {
		return new House(*this);
	}

private:
	friend class SBomber;
	const uint16_t score = 40;
};

