#pragma once
#include "pch.h"

class Clicker
{
private:
	Rectangle* collider = new Rectangle;
public:
	Clicker() { *collider = { (float)GetMouseX(), (float)GetMouseY(), 5.f, 5.f}; }

	~Clicker()
	{
		if (!collider) return;

		delete this->collider;
		this->collider = nullptr;
	}

	const Rectangle& GetCollider() const { return *this->collider; }
	void UpdatePosition();
};

