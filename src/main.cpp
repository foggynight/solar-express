#include "olcPixelGameEngine.h"

class SolarExpress : public olc::PixelGameEngine
{
private:
	olc::Sprite *sprPlayer;

public:
	SolarExpress()
	{
		sAppName = "SolarExpress";
	}

public:
	bool OnUserCreate() override
	{
		sprPlayer = new olc::Sprite("./sprites/ship.png");

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);
		DrawSprite(0, 0, sprPlayer);

		return true;
	}

	bool OnUserDestroy() override
	{
		delete sprPlayer;

		return true;
	}
};

int main()
{
	SolarExpress game;
	if (game.Construct(640, 480, 1, 1))
		game.Start();
	return 0;
}
