// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "GameScene.h"

CGameScene::CGameScene()
{
	if (!m_level.LoadFromFile(TMX_PATH))
	{
		throw std::invalid_argument("Failed to load \"" + TMX_PATH + "\"");
	}
	player.SetSprite("../res/Images/Sprites/yoh.png", {6, 2, 30, 42}, 5);
	beloved.SetSprite("../res/Images/anna.png", {0, 0, 52, 86}, 2.5);
	collisionBlocks = m_level.GetAllObjectsByType(TMX_COLLISION_BLOCK_TYPE);
	environmentObjects = m_level.GetAllObjectsByType(TMX_ENVIRONMENT_TYPE);
	deadLines = m_level.GetAllObjectsByType(TMX_DEAD_LINE_TYPE);
	mapLeftBorder = m_level.GetMapLeftBorder();
	mapRightBorder = m_level.GetMapRightBorder();
	Init();
}

void CGameScene::Init()
{
	float leftPlayerPosition = m_level.GetPlayerRect().left;
	float topPlayerPosition = m_level.GetPlayerRect().top;
	player.Init({leftPlayerPosition, topPlayerPosition}, PLAYER_SPEED_X, PLAYER_SPEED_UP, PLAYER_SPEED_DOWN, GRAVITY, 0, 100, 30);
	float leftBelovedPosition = m_level.GetBelovedRect().left;
	float topBelovedPosition = m_level.GetBelovedRect().top;
	beloved.Init({leftBelovedPosition, topBelovedPosition}, PLAYER_SPEED_X, PLAYER_SPEED_UP, PLAYER_SPEED_DOWN, GRAVITY, 0, 80, 0);
	InitEnemies(m_level.GetAllObjectsByType(TMX_ENEMY_TYPE));
}

void CGameScene::InitEnemies(const std::vector<TmxObject> & enemies)
{
	this->enemies.clear();
	for (const TmxObject & enemyObject : enemies)
	{
		CEnemy *enemy = new CEnemy;
		enemy->SetSprite("../res/Images/Sprites/monster.png", {6, 0, 30, 42}, 5);
		enemy->Init({enemyObject.rect.left, enemyObject.rect.top}, MONSTER_SPEED_X, MONSTER_SPEED_UP, MONSTER_SPEED_DOWN, GRAVITY, 5, 3, 100, 5);
		this->enemies.push_back(enemy);
	}
}

void CGameScene::DrawTiles(sf::RenderTarget &target) const
{
	m_level.Draw(target);
}