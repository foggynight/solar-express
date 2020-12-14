/* --- solar-express ---
 *
 * Space delivery game.
 *
 * Copyright (C) 2020 Robert Coffey
 * Licensed under the GNU GPLv2
 */

#include <array>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>

#include "olcPixelGameEngine.h"
#include "olcPGEX_Graphics2D.h"

#include "globals.h"
#include "Asteroid.h"
#include "Level.h"
#include "Player.h"

/* Game states */
enum class State {
	MAINMENU,
	OPTIONS,
	SELECTLEVEL,
	LOADLEVEL,
	INGAME
};

/* Main menu options */
enum class MMItem {
	NONE = -1,
	START,
	OPTIONS,
	QUIT
};

class SolarExpress : public olc::PixelGameEngine
{
private: // Global members
	State state;

private: // Level members
	std::size_t levelCount = 1;
	int levelNumber;
	Level *level;

private: // Player members
	Player *player;

private: // In game members
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

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		switch (state) {
		case State::MAINMENU: {
			MMItem item = getItemMM();

			Clear(olc::BLACK);
			drawMM(item);

			updateStateMM(item);
		} break;

		case State::SELECTLEVEL: {
			int item = getItemLS();

			Clear(olc::BLACK);
			drawLS(item);

			updateStateLS(item);
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

		case State::LOADLEVEL: {
			std::stringstream levelPath;
			levelPath << "level-" << levelNumber << ".data";

			std::ifstream levelFile;
			levelFile.open("./levels/" + levelPath.str());

			loadLevelDataLL(levelFile);
			loadPlayerDataLL(levelFile);

			levelFile.close();
			state = State::INGAME;
		} break;

		case State::INGAME: {
			userInputIG(fElapsedTime);

			for (auto obstacle : level->obstacleVec)
				obstacle->step(fElapsedTime);
			player->step(fElapsedTime);

			Clear(olc::BLACK);
			drawObstaclesIG();
			drawPlayerIG();
		} break;
		}

		return true;
	}

	bool OnUserDestroy() override
	{
		delete player;
		delete level;

		return true;
	}

private: // Main menu functions
	/**
	 * Get menu item under the cursor.
	 *
	 * @return Menu item under the cursor
	 */
	MMItem getItemMM()
	{
		int x = GetMouseX();
		int y = GetMouseY();

		if (x < scrWidth / 3 || x > scrWidth / 3 * 2)
			return MMItem::NONE;

		int itemY = scrHeight / 3 + 50;
		for (int i = 0; i < 3; ++i) {
			if (y >= itemY - 10 && y <= itemY + 30)
				return (MMItem)i;
			itemY += 50;
		}

		return MMItem::NONE;
	}

	/**
	 * Draw the main menu.
	 *
	 * @param item Item under the cursor
	 */
	void drawMM(MMItem item)
	{
		/* Draw the game title */
		olc::vi2d titleSize = GetTextSize("Solar Express");
		int titleScale = 3U;
		DrawString(
			scrWidth / 2 - titleSize.x * titleScale / 2,
			scrHeight / 3 - 30,
			"Solar Express",
			olc::WHITE,
			titleScale
		);
		DrawLine(200, scrHeight/3 + 5, scrWidth-201, scrHeight/3 + 5);

		/* Draw the menu items */
		std::array<std::string, 3> menuStrArr {
			"Start",
			"Options",
			"Quit"
		};
		int itemY = scrHeight / 3 + 50;
		int itemScale = 2U;
		for (int i = 0; i < 3; ++i) {
			olc::Pixel color = olc::WHITE;
			if (i == (int)item) color = olc::RED;

			olc::vi2d size = GetTextSize(menuStrArr[i]);
			DrawString(
				scrWidth / 2 - size.x * itemScale / 2,
				itemY,
				menuStrArr[i],
				color,
				itemScale
			);
			itemY += 50;
		}
	}

	/**
	 * Update the game state based on main menu selection.
	 *
	 * @param item Item under the cursor
	 */
	void updateStateMM(MMItem item)
	{
		if (GetMouse(0).bPressed) {
			if (item == MMItem::START) state = State::SELECTLEVEL;
			else if (item == MMItem::OPTIONS) state = State::OPTIONS;
			else if (item == MMItem::QUIT) exit(0);
		}
	}

private: // Select level functions
	/**
	 * Draw the level selection menu.
	 *
	 * @param item Item under the cursor
	 */
	void drawLS(int item)
	{
		int listXStart = scrWidth / 2 - GetTextSize("Level n").x;
		int listYStart = scrHeight * 2 / 5;
		int listGap = 50;

		for (int i = 1; i <= levelCount; ++i) {
			olc::Pixel color = olc::WHITE;
			if (i == item) color = olc::RED;
			DrawString(
				listXStart,
				listYStart + (i-1) * listGap,
				"Level " + std::to_string(i),
				color,
				2U
			);
		}
	}

	/**
	 * Get level selection item under the cursor.
	 */
	int getItemLS()
	{
		int x = GetMouseX();
		int y = GetMouseY();

		if (x < scrWidth / 3 || x > scrWidth / 3 * 2)
			return 0;

		int itemY = scrHeight * 2 / 5;
		for (int i = 1; i <= levelCount; ++i) {
			if (y >= itemY - 10 && y <= itemY + 30)
				return i;
			itemY += 50;
		}

		return 0;
	}

	/**
	 * Update the game state based on level selection.
	 *
	 * @param item Item under the cursor
	 */
	void updateStateLS(int item)
	{
		if (item > 0 && GetMouse(0).bPressed) {
			levelNumber = item;
			state = State::LOADLEVEL;
		}
	}

private: // Load level functions
	/**
	 * Read a line from the input file delimited by delim, converted to a float.
	 *
	 * @param file Level data input file stream
	 * @param delim Character to delimit the line of data
	 *
	 * @return The string read from the file, converted to a float
	 */
	float readFloatLL(std::ifstream& file, char delim = '\n')
	{
		std::string buffer;
		std::getline(file, buffer, delim);
		return std::stof(buffer);
	}

	/**
	 * Setup the level, reading from a level data file.
	 *
	 * @param levelFile Input file stream
	 */
	void loadLevelDataLL(std::ifstream& levelFile)
	{
		level = new Level();

		level->startPosition.x = readFloatLL(levelFile, ' ');
		level->startPosition.y = readFloatLL(levelFile);

		level->startVelocity.x = readFloatLL(levelFile, ' ');
		level->startVelocity.y = readFloatLL(levelFile);

		level->goalPosition.x = readFloatLL(levelFile, ' ');
		level->goalPosition.y = readFloatLL(levelFile);
	}

	/**
	 * Setup the player, reading from a level data file.
	 *
	 * @param levelFile Input file stream
	 */
	void loadPlayerDataLL(std::ifstream& levelFile)
	{
		float angle = readFloatLL(levelFile);
		float acc = readFloatLL(levelFile);
		float maxSpeed = readFloatLL(levelFile);

		std::string path;
		std::getline(levelFile, path);

		player = new Player(
			level->startPosition,
			level->startVelocity,
			angle,
			acc,
			maxSpeed,
			path
		);
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
			player->rotate(fElapsedTime, 1.0F);
		}
		if (GetKey(olc::Key::D).bHeld) {
			player->rotate(fElapsedTime, -1.0F);
		}
		if (GetKey(olc::Key::S).bHeld) {
			player->thrust(fElapsedTime, false);
		}
	}

	/**
	 * Draw the player on screen.
	 */
	void drawPlayerIG()
	{
		transform.Reset();
		transform.Translate(-player->sprOffset.x, -player->sprOffset.y);
		transform.Rotate((player->angle - 0.5F) * pi);
		transform.Translate(player->pos.x, player->pos.y);

		gfx.DrawSprite(player->sprite, transform);
	}

	/**
	 * Draw the level obstacles on screen.
	 */
	void drawObstaclesIG()
	{
		for (auto obstacle : level->obstacleVec) {
			transform.Reset();
			transform.Translate(-obstacle->sprOffset.x, -obstacle->sprOffset.y);
			transform.Rotate(obstacle->angle * pi);
			transform.Translate(obstacle->pos.x, obstacle->pos.y);

			gfx.DrawSprite(obstacle->sprite, transform);
		}
	}
};

int main()
{
	SolarExpress game;
	if (game.Construct(scrWidth, scrHeight, 1, 1))
		game.Start();
	return 0;
}
