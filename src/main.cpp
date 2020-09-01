#include <utility>

#include "olcPixelGameEngine.h"
#include "olcPGEX_Graphics2D.h"

#include "globals.h"
#include "Player.h"

extern const int scrWidth = 640;
extern const int scrHeight = 480;
extern const float pi = 3.141592654F;

class SolarExpress : public olc::PixelGameEngine
{
private:
	Player *player;
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
		const std::pair<float, float> startPosition(0.0F, 0.0F);

		player = new Player(
			olc::vf2d(startPosition.first, startPosition.second),
			olc::vf2d(0.0F, 0.0F),
			0.5F,
			100.0F,
			"./sprites/ship.png"
		);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		handleUserInput(fElapsedTime);
		player->step(fElapsedTime);

		Clear(olc::BLACK);
		DrawPlayer();

		return true;
	}

	bool OnUserDestroy() override
	{
		delete player;

		return true;
	}

private:
	void handleUserInput(float fElapsedTime)
	{
		if (GetKey(olc::Key::W).bHeld) {
			player->thrust(fElapsedTime);
		}
		if (GetKey(olc::Key::A).bHeld) {
			player->rotate(1.0F * fElapsedTime);
		}
		if (GetKey(olc::Key::D).bHeld) {
			player->rotate(-1.0F * fElapsedTime);
		}
		if (GetKey(olc::Key::S).bHeld) {
			player->thrust(fElapsedTime, false);
		}
	}

	void DrawPlayer()
	{
		transform.Reset();
		transform.Translate(-player->sprOffsetX, -player->sprOffsetY);
		transform.Rotate((player->angle - 0.5F) * pi);
		transform.Translate(player->pos.x, player->pos.y);

		auto& tRef = transform;
		gfx.DrawSprite(player->sprite, tRef);

		Draw(player->pos.x, player->pos.y, olc::RED); // Center of ship - testing
	}
};

int main()
{
	SolarExpress game;
	if (game.Construct(scrWidth, scrHeight, 1, 1))
		game.Start();
	return 0;
}
