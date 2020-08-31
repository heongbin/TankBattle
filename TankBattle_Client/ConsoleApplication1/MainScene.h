#pragma once
#include <Windows.h>
#include <mutex>
#include <bitset>

#include "Scene.h"
#include "Player.h"
#include "Projectile.h"
#include "Block.h"
#include "Item.h"
#include "CollisionManager.h"
#include "ObjectPool.h"
#include "Screen.h"
#include "UI.h"
#include "Timer.h"
#include "SceneManager.h"

#define TANK_SIZE 3
#define PROJECTILE_SIZE 1
#define BLOCK_SIZE 1
#define ITEM_SIZE 1
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 30
#define MAP_WIDTH 50
#define MAP_HEIGHT 30
#define HP_UP	3
#define GAME_TIME 60.0f

class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

	virtual void Init();
	//virtual void Update();
	virtual void Update(int*);
	virtual void Render();

private:
	Player* player1;
	Player* player2;

	Block* block;
	Item* item;
	Projectile* projectile;

	UI* text;

	int p1score;
	int p2score;

	UI score;
	UI time;
	UI p1hp;
	UI p1atk;
	UI p2hp;
	UI p2atk;

	ObjectPool<Projectile> projPool;

	std::vector<Projectile> projectiles1;
	std::vector<Projectile> projectiles2;
	std::vector<Block> blocks;
	std::vector<Item> items;
	std::vector<UI> ui;

	Timer timer;

	
	char p1Img[9] = { char(1),'l',char(2),' ', '1', ' ',char(3), ' ',char(4) };
	char p2Img[9] = { char(1),'l',char(2),' ', '2', ' ',char(3), ' ',char(4) };
	char blockImg[1] = { 'W' };
	char brokenblockImg[1] = { 'w' };
	char solidblockImg[1] = { '#' };
	char projImg[1] = { 'o' };
	char powerprojImg[1] = { 'O' };
	char powerupImg[1] = { 'P' };
	char hpupImg[1] = { 'H' };
};
