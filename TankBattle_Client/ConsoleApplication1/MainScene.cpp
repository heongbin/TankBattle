#include "MainScene.h"

MainScene::MainScene()
{
}


MainScene::~MainScene()
{
	delete player1;
	delete player2;
	delete block;
	delete item;
	delete projectile;
	delete text;
}

void MainScene::Init()
{
	int map[MAP_HEIGHT][MAP_WIDTH];

	
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		map[i][0] = 3;
		map[i][1] = 3;
		map[i][MAP_WIDTH - 2] = 3;
		map[i][MAP_WIDTH - 1] = 3;
	}
	for (int i = 0; i < MAP_WIDTH; ++i)
	{
		map[0][i] = 3;
		map[1][i] = 3;
		map[MAP_HEIGHT - 2][i] = 3;
		map[MAP_HEIGHT - 1][i] = 3;
	}

	//중앙 세로 외벽
	for(int i = 2; i < 8; ++i)
	{
		for (int j = 24; j < 27; ++j)
		{
			map[i][j] = 3;
		}
	}
	for (int i = 22; i < 28; ++i)
	{
		for (int j = 24; j < 27; ++j)
		{
			map[i][j] = 3;
		}
	}
	
	// 중앙 가로 외벽
	for (int i = 14; i < 17; ++i)
	{
		for (int j = 2; j < 10; ++j)
		{
			map[i][j] = 3;
		}
	}
	for (int i = 14; i < 17; ++i)
	{
		for (int j = 40; j < 48; ++j)
		{
			map[i][j] = 3;
		}
	}

	// 중앙 파괴되는 벽
	for (int i = 13; i < 18; ++i)
	{
		map[i][21] = 2;
		map[i][29] = 2;
	}
	for (int i = 21; i < 29; ++i)
	{
		map[13][i] = 2;
		map[17][i] = 2;
	}

	map[15][25] = 4; // powerup
	map[5][40] = 5;
	map[24][9] = 5;
	

	player1 = new Player;
	player1->SetX(3);
	player1->SetY(3);
	player1->SetDir(4);
	player1->SetSize(TANK_SIZE);
	player1->SetHP(5);
	player1->SetDamage(1);
	player1->SetImage(p1Img);

	player2 = new Player; 
	player2->SetX(44);
	player2->SetY(24);
	player2->SetDir(3);
	player2->SetSize(TANK_SIZE);
	player2->SetHP(5);
	player2->SetDamage(1);
	player2->SetImage(p2Img);

	text = new UI("TIME", 55, 3);
	ui.push_back(*text);
	text = new UI("SCORE", 55, 5);
	ui.push_back(*text);

	text = new UI("PLAYER 1", 55, 10);
	ui.push_back(*text);
	text = new UI("HP", 55, 12);
	ui.push_back(*text);
	text = new UI("ATK", 55, 14);
	ui.push_back(*text);

	text = new UI("PLAYER 2", 55, 20);
	ui.push_back(*text);
	text = new UI("HP", 55, 22);
	ui.push_back(*text);
	text = new UI("ATK", 55, 24);
	ui.push_back(*text);

	time.SetX(65);
	time.SetY(3);

	score.SetX(65);
	score.SetY(5);

	p1hp.SetX(65);
	p1hp.SetY(12);

	p1atk.SetX(65);
	p1atk.SetY(14);

	p2hp.SetX(65);
	p2hp.SetY(22);
	 
	p2atk.SetX(65);
	p2atk.SetY(24);

	
	// 배열 읽어서 그리기
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			if (map[i][j] == 5) // HPup
			{
				Item* item = new Item;
				item->SetX(j);
				item->SetY(i);
				item->SetKind(2); // HP
				item->SetSize(ITEM_SIZE);
				item->SetImage(hpupImg);
				items.push_back(*item);

			}

			if (map[i][j] == 4) // powerup
			{
				Item* item = new Item;
				item->SetX(j);
				item->SetY(i);
				item->SetKind(1); // power
				item->SetSize(ITEM_SIZE);
				item->SetImage(powerupImg);
				items.push_back(*item);

			}

			if (map[i][j] == 3)
			{
				Block* block = new Block; // 체력3 = 무적
				block->SetX(j);
				block->SetY(i);
				block->SetSize(BLOCK_SIZE);
				block->SetHP(3);
				block->SetImage(solidblockImg);
				blocks.push_back(*block);
			}
			if (map[i][j] == 2)
			{
				Block* block = new Block; // 완전한블록
				block->SetX(j);
				block->SetY(i);
				block->SetSize(BLOCK_SIZE);
				block->SetHP(2);
				block->SetImage(blockImg);
				blocks.push_back(*block);
			}
			if (map[i][j] == 1)
			{
				Block* block = new Block; // 반파된블록
				block->SetX(j);
				block->SetY(i);
				block->SetSize(BLOCK_SIZE);
				block->SetHP(1);
				block->SetImage(brokenblockImg);
				blocks.push_back(*block);
			}
		}
	}


	// 게임종료 타이머
	timer.SetTimeout(GAME_TIME);
}

void MainScene::Update(int* keyboard)
{
	player1->Update();
	player2->Update();

	// 받은 키보드 입력값에 따른 처리
	if (!player1->GetIsDead())
	{
		if (keyboard[0]) {
			player1->SetY((player1->GetY() - 1));
			player1->SetDir(1);

			if (CollisionManager::GetInstance()->SquareCollisionCheck(player1, player2))
			{
				player1->SetY((player1->GetY() + 1));
			}
			else
			{
				for (auto i = blocks.begin(); i != blocks.end(); ++i)
				{
					if (CollisionManager::GetInstance()->SquareCollisionCheck(player1, &*i))
					{
						player1->SetY((player1->GetY() + 1));
						break;
					}
				}
			}

		}
		if (keyboard[1]) {
			player1->SetY((player1->GetY() + 1));
			player1->SetDir(2);

			if (CollisionManager::GetInstance()->SquareCollisionCheck(player1, player2))
			{
				player1->SetY((player1->GetY() - 1));
			}
			else
			{
				for (auto i = blocks.begin(); i != blocks.end(); ++i)
				{
					if (CollisionManager::GetInstance()->SquareCollisionCheck(player1, &*i))
					{
						player1->SetY((player1->GetY() - 1));
						break;
					}
				}
			}
		}
		if (keyboard[2]) {
			player1->SetX((player1->GetX() - 1));
			player1->SetDir(3);
			if (CollisionManager::GetInstance()->SquareCollisionCheck(player1, player2))
			{
				player1->SetX((player1->GetX() + 1));
			}
			else
			{
				for (auto i = blocks.begin(); i != blocks.end(); ++i)
				{
					if (CollisionManager::GetInstance()->SquareCollisionCheck(player1, &*i))
					{
						player1->SetX((player1->GetX() + 1));
						break;
					}
				}
			}
		}
		if (keyboard[3]) {
			player1->SetX((player1->GetX() + 1));
			player1->SetDir(4);
			if (CollisionManager::GetInstance()->SquareCollisionCheck(player1, player2))
			{
				player1->SetX((player1->GetX() - 1));
			}
			else
			{
				for (auto i = blocks.begin(); i != blocks.end(); ++i)
				{
					if (CollisionManager::GetInstance()->SquareCollisionCheck(player1, &*i))
					{
						player1->SetX((player1->GetX() - 1));
						break;
					}
				}
			}
		}
		if (keyboard[4]) {
			if (projectiles1.size() < 5)
			{
				Projectile* p = projPool.PopObject();
				if (p)
				{
					p->SetX(player1->GetX() + 1);
					p->SetY(player1->GetY() + 1);
					p->SetDir(player1->GetDir());
					p->SetSize(PROJECTILE_SIZE);
					p->SetDamage(player1->GetDamage());
					if (player1->GetDamage() == 1)
						p->SetImage(projImg);
					else
						p->SetImage(powerprojImg);

					projectiles1.push_back(*p);
				}
			}
		}

	}


	
	if (!player2->GetIsDead())
	{
		if (keyboard[5]) {
			player2->SetY((player2->GetY() - 1));
			player2->SetDir(1);

			if (CollisionManager::GetInstance()->SquareCollisionCheck(player1, player2))
			{
				player2->SetY((player2->GetY() + 1));
			}
			else
			{
				for (auto i = blocks.begin(); i != blocks.end(); ++i)
				{
					if (CollisionManager::GetInstance()->SquareCollisionCheck(player2, &*i))
					{
						player2->SetY((player2->GetY() + 1));
						break;
					}
				}
			}
		}
		if (keyboard[6]) {
			player2->SetY((player2->GetY() + 1));
			player2->SetDir(2);

			if (CollisionManager::GetInstance()->SquareCollisionCheck(player1, player2))
			{
				player2->SetY((player2->GetY() - 1));
			}
			else
			{
				for (auto i = blocks.begin(); i != blocks.end(); ++i)
				{
					if (CollisionManager::GetInstance()->SquareCollisionCheck(player2, &*i))
					{
						player2->SetY((player2->GetY() - 1));
						break;
					}
				}
			}
		}
		if (keyboard[7]) {
			player2->SetX((player2->GetX() - 1));
			player2->SetDir(3);
			if (CollisionManager::GetInstance()->SquareCollisionCheck(player1, player2))
			{
				player2->SetX((player2->GetX() + 1));
			}
			else
			{
				for (auto i = blocks.begin(); i != blocks.end(); ++i)
				{
					if (CollisionManager::GetInstance()->SquareCollisionCheck(player2, &*i))
					{
						player2->SetX((player2->GetX() + 1));
						break;
					}
				}
			}
		}
		if (keyboard[8]) {
			player2->SetX((player2->GetX() + 1));
			player2->SetDir(4);
			if (CollisionManager::GetInstance()->SquareCollisionCheck(player1, player2))
			{
				player2->SetX((player2->GetX() - 1));
			}
			else
			{
				for (auto i = blocks.begin(); i != blocks.end(); ++i)
				{
					if (CollisionManager::GetInstance()->SquareCollisionCheck(player2, &*i))
					{
						player2->SetX((player2->GetX() - 1));
						break;
					}
				}
			}
		}
		if (keyboard[9]) {
			if (projectiles2.size() < 5)
			{
				Projectile* p = projPool.PopObject();
				if (p)
				{
					p->SetX(player2->GetX() + 1);
					p->SetY(player2->GetY() + 1);
					p->SetDir(player2->GetDir());
					p->SetSize(PROJECTILE_SIZE);
					p->SetDamage(player2->GetDamage());
					if (player2->GetDamage() == 1)
						p->SetImage(projImg);
					else
						p->SetImage(powerprojImg);

					projectiles2.push_back(*p);
				}
			}
		}
	}
	
	
	// 상황에 따른 이미지 변경
	switch (player1->GetDir())
	{
	case 1:
		p1Img[1] = 'l';
		p1Img[3] = ' ';
		p1Img[5] = ' ';
		p1Img[7] = ' ';
		break;
	case 2:
		p1Img[1] = ' ';
		p1Img[3] = ' ';
		p1Img[5] = ' ';
		p1Img[7] = 'l';
		break;
	case 3:
		p1Img[1] = ' ';
		p1Img[3] = '-';
		p1Img[5] = ' ';
		p1Img[7] = ' ';
		break;
	case 4:
		p1Img[1] = ' ';
		p1Img[3] = ' ';
		p1Img[5] = '-';
		p1Img[7] = ' ';
		break;

	}
	switch (player2->GetDir())
	{
	case 1:
		p2Img[1] = 'l';
		p2Img[3] = ' ';
		p2Img[5] = ' ';
		p2Img[7] = ' ';
		break;
	case 2:
		p2Img[1] = ' ';
		p2Img[3] = ' ';
		p2Img[5] = ' ';
		p2Img[7] = 'l';
		break;
	case 3:
		p2Img[1] = ' ';
		p2Img[3] = '-';
		p2Img[5] = ' ';
		p2Img[7] = ' ';
		break;
	case 4:
		p2Img[1] = ' ';
		p2Img[3] = ' ';
		p2Img[5] = '-';
		p2Img[7] = ' ';
		break;

	}

	// 탄환 이동
	for (auto i = projectiles1.begin(); i != projectiles1.end(); ++i)
	{
		i->Move();

	}
	for (auto i = projectiles2.begin(); i != projectiles2.end(); ++i)
	{
		i->Move();

	}

	// 탱크와 아이템 충돌 
	for (auto i = items.begin(); i != items.end(); )
	{
		if (CollisionManager::GetInstance()->SquareCollisionCheck(&*i, player1))
		{
			if (i->GetKind() == 1)
			{
				player1->SetDamage(player1->GetDamage() + 1);
			}
			else if (i->GetKind() == 2)
			{
				player1->SetHP(player1->GetHP() + HP_UP);
			}

			i = items.erase(i); 
		}
		else
		{
			++i;
		}
		
	}
	for (auto i = items.begin(); i != items.end(); )
	{
		if (CollisionManager::GetInstance()->SquareCollisionCheck(&*i, player2))
		{
			if (i->GetKind() == 1)
			{
				player2->SetDamage(player2->GetDamage() + 1);
			}
			else if (i->GetKind() == 2)
			{
				player2->SetHP(player2->GetHP() + HP_UP);
			}

			i = items.erase(i); 
		}
		else
		{
			++i;
		}

	}

	// 총알과 플레이어 충돌
	if (!player2->GetIsDead())
	{
		for (auto i = projectiles1.begin(); i != projectiles1.end(); )
		{
			if (CollisionManager::GetInstance()->SquareCollisionCheck(&*i, player2))
			{
				player2->SetHP(player2->GetHP() - i->GetDamage());
				if (player2->GetHP() <= 0)
				{
					player2->SetHP(0);
					p1score++;
					player2->Death();

				}
				projPool.ReturnObject(&*i);
				i = projectiles1.erase(i);

			}
			else
			{
				i++;
			}
		}
	}
	if (!player1->GetIsDead())
	{
		for (auto i = projectiles2.begin(); i != projectiles2.end(); )
		{
			if (CollisionManager::GetInstance()->SquareCollisionCheck(&*i, player1))
			{
				player1->SetHP(player1->GetHP() - i->GetDamage());
				if (player1->GetHP() <= 0)
				{
					player1->SetHP(0);
					p2score++;
					player1->Death();
				}
				projPool.ReturnObject(&*i);
				i = projectiles2.erase(i);

			}
			else
			{
				i++;
			}
		}

	}
	
	// 블록과 총알 충돌시 처리(블록 체력 3이면 무적)
	for (auto j = blocks.begin(); j != blocks.end(); ++j)
	{
		for (auto i = projectiles1.begin(); i != projectiles1.end(); )
		{
			if (CollisionManager::GetInstance()->SquareCollisionCheck(&*i, &*j))
			{
				if (j->GetHP() < 3)
				{
					j->SetHP(j->GetHP() - i->GetDamage());
				}

				projPool.ReturnObject(&*i);
				i = projectiles1.erase(i);

			}
			else
			{

				i++;
			}
		}
		for (auto i = projectiles2.begin(); i != projectiles2.end(); )
		{
			if (CollisionManager::GetInstance()->SquareCollisionCheck(&*i, &*j))
			{
				if (j->GetHP() < 3)
				{
					j->SetHP(j->GetHP() - i->GetDamage());
				}

				projPool.ReturnObject(&*i);
				i = projectiles2.erase(i);

			}
			else
			{

				i++;
			}
		}
	}

	// 블록 잔여 체력에 따른 처리
	for (auto i = blocks.begin(); i != blocks.end(); )
	{
		if (i->GetHP() == 2)
			i->SetImage(blockImg);
		if (i->GetHP() == 1)
			i->SetImage(brokenblockImg);
		if (i->GetHP() <= 0)
			i = blocks.erase(i);
		else
			++i;
	}

	// 밖에나간 총알 삭제
	for (auto i = projectiles1.begin(); i != projectiles1.end();)
	{
		if (i->GetX() > SCREEN_WIDTH || i->GetX() < 0 || i->GetY() > SCREEN_HEIGHT || i->GetY() < 0)
		{
			projPool.ReturnObject(&*i);
			i = projectiles1.erase(i);

		}
		else
		{
			i++;
		}
	}
	for (auto i = projectiles2.begin(); i != projectiles2.end();)
	{
		if (i->GetX() > SCREEN_WIDTH || i->GetX() < 0 || i->GetY() > SCREEN_HEIGHT || i->GetY() < 0)
		{
			projPool.ReturnObject(&*i);
			i = projectiles2.erase(i);

		}
		else
		{
			i++;
		}
	}

	timer.Update();
	

	// UI 변경
	time.SetString(std::to_string(timer.GetTimeout() - timer.GetTime()));
	score.SetString(std::to_string(p1score) + " : " + std::to_string(p2score));
	p1hp.SetString(std::to_string(player1->GetHP()));
	p2hp.SetString(std::to_string(player2->GetHP()));
	p1atk.SetString(std::to_string(player1->GetDamage()));
	p2atk.SetString(std::to_string(player2->GetDamage()));

	std::string s ;
	for (int i = 0; i < 10; ++i)
	{
		s += std::to_string(keyboard[i]) + " ";
	}
	
	if (timer.Timeout())
	{
		SceneManager::GetInstance()->SetScore(p1score, p2score);
		SceneManager::GetInstance()->SceneChange(SceneManager::eEnd);
	}
}

void MainScene::Render()
{
	// Draw 처리
	Screen::GetInstance()->begin();
	Screen::GetInstance()->clearScreen();

	if(!player1->GetIsDead())
	Screen::GetInstance()->Draw(player1->GetImage(), player1->GetSize(), player1->GetSize(), player1->GetX(), player1->GetY());
	if (!player2->GetIsDead())
	Screen::GetInstance()->Draw(player2->GetImage(), player2->GetSize(), player2->GetSize(), player2->GetX(), player2->GetY());

	for (auto i = projectiles1.begin(); i != projectiles1.end(); ++i)
	{
		Screen::GetInstance()->Draw(i->GetImage(), i->GetSize(), i->GetSize(), i->GetX(), i->GetY());
	}
	for (auto i = projectiles2.begin(); i != projectiles2.end(); ++i)
	{
		Screen::GetInstance()->Draw(i->GetImage(), i->GetSize(), i->GetSize(), i->GetX(), i->GetY());
	}

	for (auto i = blocks.begin(); i != blocks.end(); ++i)
	{
		Screen::GetInstance()->Draw(i->GetImage(), i->GetSize(), i->GetSize(), i->GetX(), i->GetY());
	}

	for (auto i = items.begin(); i != items.end(); ++i)
	{
		Screen::GetInstance()->Draw(i->GetImage(), i->GetSize(), i->GetSize(), i->GetX(), i->GetY());
	}

	for (auto i = ui.begin(); i != ui.end(); ++i)
	{
		i->DrawString();
	}

	time.DrawString();
	score.DrawString();
	p1hp.DrawString();
	p1atk.DrawString();
	p2hp.DrawString();
	p2atk.DrawString();

	Screen::GetInstance()->end();
	Screen::GetInstance()->present();
}