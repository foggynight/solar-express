#include "olcPixelGameEngine.h"
#include "olcPGEX_Graphics2D.h"

#include "globals.h"
#include "Player.h"

extern const int scrWidth = 640;
extern const int scrHeight = 480;

const float pi = 3.141592654F;

class SolarExpress : public olc::PixelGameEngine
{
private:
	olc::Sprite *sprPlayer;
	Player player;
	olc::GFX2D gfx;
	olc::GFX2D::Transform2D transform;

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
			0.5F,
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
			player.rotate(1.0F * fElapsedTime);
		}
		if (GetKey(olc::Key::D).bHeld) {
			player.rotate(-1.0F * fElapsedTime);
		}
		if (GetKey(olc::Key::S).bHeld) {
			player.thrust(fElapsedTime, false);
		}

		player.step(fElapsedTime);

		Clear(olc::BLACK);

		float sprOffsetX = (float)(player.sprWidth) / 2.0F;
		float sprOffsetY = (float)(player.sprHeight) / 2.0F;

		transform.Reset();
		transform.Translate(-sprOffsetX, -sprOffsetY);
		transform.Rotate((player.angle - 0.5F) * pi);
		transform.Translate(player.pos.x, player.pos.y);

		auto& tRef = transform;
		gfx.DrawSprite(sprPlayer, tRef);

		Draw(player.pos.x, player.pos.y, olc::RED); // Center of ship - testing

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
