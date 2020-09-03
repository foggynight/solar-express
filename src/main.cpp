#include <array>
#include <cstdlib>
#include <string>
#include <utility>

#include "olcPixelGameEngine.h"
#include "olcPGEX_Graphics2D.h"

#include "globals.h"
#include "Player.h"

extern const int scrWidth = 640;
extern const int scrHeight = 480;
extern const float pi = 3.141592654F;

/* Game states. */
enum class State {
	MAINMENU,
	OPTIONS,
	INGAME
};

/* Main menu options. */
enum class MMItem {
	NONE,
	START,
	OPTIONS,
	QUIT
};

class SolarExpress : public olc::PixelGameEngine
{
private:
	State state;
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
		state = State::MAINMENU;

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
		switch (state) {
			case State::MAINMENU: {
				MMItem item = getItemMM();
				drawMM(item);
				updateStateMM(item);
			} break;

			case State::OPTIONS: {
				Clear(olc::BLACK);
				olc::vi2d size = GetTextSize("Not yet implemented.");
				DrawString(
					scrWidth / 2 - size.x / 2,
					scrHeight / 2 - size.y / 2,
					"Not yet implemented."
				);
			} break;

			case State::INGAME: {
				userInputIG(fElapsedTime);
				player->step(fElapsedTime);

				Clear(olc::BLACK);
				drawPlayerIG();
			} break;
		};

		return true;
	}

	bool OnUserDestroy() override
	{
		delete player;

		return true;
	}

private: // Main menu functions
	/**
	 * Draw the main menu.
	 *
	 * @param item Menu item under cursor
	 * @param bPressed Was item pressed
	 **/
	void drawMM(MMItem item)
	{
		/* Draw the game title */
		olc::vi2d titleSize = GetTextSize("Solar Express");
		unsigned int titleScale = 3U;
		DrawString(
			scrWidth / 2 - titleSize.x * titleScale / 2,
			scrHeight / 3 - 30,
			"Solar Express",
			olc::WHITE,
			titleScale
		);
		DrawLine(100, scrHeight/3 + 5, scrWidth-101, scrHeight/3 + 5);

		/* Draw the menu items */
		std::array<std::string, 3> menuStrArr {
			"Start",
			"Options",
			"Quit"
		};
		unsigned int itemHeight = scrHeight / 3 + 50;
		for (int i = 0; i < 3; ++i) {
			olc::Pixel color = olc::WHITE;
			if (i+1 == (int)item) color = olc::RED;

			olc::vi2d size = GetTextSize(menuStrArr[i]);
			unsigned int scale = 2U;
			DrawString(
				scrWidth / 2 - size.x * scale / 2,
				itemHeight,
				menuStrArr[i],
				color,
				scale
			);
			itemHeight += 50;
		}
	}

	/** Get menu item under cursor. */
	MMItem getItemMM()
	{
		int x = GetMouseX();
		int y = GetMouseY();

		if (x < scrWidth / 3 || x > scrWidth / 3 * 2)
			return MMItem::NONE;

		int listY = scrHeight / 3 + 50;
		for (int i = 1; i < 4; ++i) {
			if (y >= listY - 10 && y <= listY + 30)
				return (MMItem)i;
			listY += 50;
		}

		return MMItem::NONE;
	}

	/**
	 * Update the game state based on main menu items.
	 *
	 * @param item Item under cursor
	 **/
	void updateStateMM(MMItem item)
	{
		if (GetMouse(0).bPressed) {
			if (item == MMItem::START) state = State::INGAME;
			else if (item == MMItem::OPTIONS) state = State::OPTIONS;
			else if (item == MMItem::QUIT) exit(0);
		}
	}

private: // In game functions
	/**
	 * Handle in-game user input.
	 *
	 * @param fElapsedTime Amount of time since last frame (seconds)
	 */
	void userInputIG(float fElapsedTime)
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

	/** Draw the player to screen. */
	void drawPlayerIG()
	{
		transform.Reset();
		transform.Translate(-player->sprOffsetX, -player->sprOffsetY);
		transform.Rotate((player->angle - 0.5F) * pi);
		transform.Translate(player->pos.x, player->pos.y);

		auto& tRef = transform;
		gfx.DrawSprite(player->sprite, tRef);
	}
};

int main()
{
	SolarExpress game;
	if (game.Construct(scrWidth, scrHeight, 1, 1))
		game.Start();
	return 0;
}
