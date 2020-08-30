#include "olcPixelGameEngine.h"

#include "globals.h"
#include "Player.h"

extern const int scrWidth = 640;
extern const int scrHeight = 480;

class SolarExpress : public olc::PixelGameEngine
{
private:
	Player player;
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
		player = Player(
			olc::vf2d(0.0F, 0.0F),
			olc::vf2d(0.0F, 0.0F),
			0.0F,
			100.0F,
			sprPlayer->width,
			sprPlayer->height
		);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetKey(olc::Key::W).bHeld) {
			player.thrust(fElapsedTime);
		}
		if (GetKey(olc::Key::A).bHeld) {
			player.rotate(-1.0F * fElapsedTime);
		}
		if (GetKey(olc::Key::D).bHeld) {
			player.rotate(1.0F * fElapsedTime);
		}
		if (GetKey(olc::Key::S).bHeld) {
			player.thrust(fElapsedTime, false);
		}

		player.step(fElapsedTime);

		Clear(olc::BLACK);
		DrawSprite(player.pos, sprPlayer);

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
	if (game.Construct(scrWidth, scrHeight, 1, 1))
		game.Start();
	return 0;
}
