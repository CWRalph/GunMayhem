#pragma once
#include "pch.h"
#include "Button.h" 
#include "Utils/VariableType.h"
#include "Utils/Defines.h"

class Perk
{
	const VariableType* type;
	Button* button;
	const char* name;

public:
	Perk(){}
	Perk(const VariableType& v, const float& x, const float& y, const char* fileName, const char* Name) : 
		button(new Button(x, y, fileName)), name(Name), type(new VariableType(v)) {}
	Perk(const Perk& p)
	{
		button = new Button(*p.button);
		type = new VariableType(*p.type);
		name = p.name;
	}

	Perk(Perk&& p) noexcept
	{
		button = p.button;
		type = p.type;
		name = p.name;

		p.button = nullptr;
		p.type = nullptr;
	}
	Perk& operator=(const Perk& p)
	{
		button = new Button(*p.button);
		type = new VariableType(*p.type);
		name = p.name;

		return *this;
	}

	~Perk()
	{
		if (button)
		{
			delete button;
			button = nullptr;
		}
		if (type)
		{
			delete type;
			type = nullptr;
		}
	}
						
	inline const VariableType& getType() const { return *type; }
	inline const Button& getButton() const { return *button; }
	inline const char* getName() const { return name; }
	void Draw(const Rectangle& pointer) const;
};


