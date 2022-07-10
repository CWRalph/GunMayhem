#include "pch.h"
#include "Gun.h"

Gun::Gun(const string& str)
{
	string buffer = "";
	short counter = 0;
	std::stringstream ss(str);
	while (ss >> buffer)
	{
		++counter;
		switch (counter)
		{
		case 2:
		{
			textureKey = new string(buffer);
			bullet = new Bullet(buffer);

			//adds space and line breaks to the guns name to be used to print on the Player UI
			*displayName += buffer[0];
			short length = (short)buffer.length();

			bool AR = false, SMG = false;
			if (SMG = (buffer.find("SMG") != string::npos)) length -= 3;
			else if (AR = (buffer.find("AR") != string::npos)) length -= 2;

			for (short i = 1; i < length; i++)
			{
				if (displayName->length() % 12 == 0)
					displayName->insert(displayName->begin() + displayName->find_last_of(' '), '\n');

				if (buffer[i] == std::toupper(buffer[i]))
					*displayName += ' ';
				*displayName += buffer[i];
			}

			if (AR)
			{
				if (displayName->length() + 3 >= 12)
					*displayName += '\n';
				*displayName += " AR";
			}
			else if (SMG)
			{
				if (displayName->length() + 4 >= 12)
					*displayName += '\n';
				*displayName += " SMG";
			}

		} break;
		case 3:
		{
			rateOfFire = new const double((100 - stod(buffer)) * 0.005);
		} break;
		case 4:
		{
			double temp = stod(buffer);
			if (temp > 100)	ammo = new short((short)temp);
			else ammo = new short(short(temp * 0.5));
			
		}break;
		case 5:
		{
			weight = new const float(stof(buffer) * 3.9f);
		} break;
		case 6:
		{
			float n = stof(buffer), mul = 2.8f;
			if (n > 40.f) mul = 2.5f;
			if (n > 65.f) mul = 2.2f;
			if (n > 80.f) mul = 1.9f;
			recoil = new const float(n * mul);
		} break;
		}
	}
	if (!(ammo && recoil && weight && rateOfFire && textureKey && bullet))
		TraceLog(LOG_WARNING, "GUN: missing critical data");
}

void Gun::UpdateAmmoCount(const short& a)
{
	 *ammo += a; 
}

void Gun::Draw(const Rectangle& XYHS, const Direction& d) const
{
	if (this == nullptr) return;

	Rectangle source = { 0.0f, 0.0f, (float)textures[*textureKey].width, (float)textures[*textureKey].height };
	float temp = 0.f;
	float tempY = 0.38f;
	if (d == Direction::Left)
	{
		source.width *= -1;
		temp = (float)textures[*textureKey].width * XYHS.height;
		tempY = 0.3f;
	}

	Rectangle dest = { XYHS.x - temp, XYHS.y + XYHS.width * tempY, (float)textures[*textureKey].width * XYHS.height, (float)textures[*textureKey].height * XYHS.height };
	DrawTexturePro(textures[*textureKey], source, dest, { 0.0f, 0.0f }, 0.0f, WHITE);
}
