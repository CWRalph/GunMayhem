#include "pch.h"
#include "Clicker.h"

void Clicker::UpdatePosition()
{
	(*this->collider).x = (float)GetMouseX();
	(*this->collider).y = (float)GetMouseY();
}
