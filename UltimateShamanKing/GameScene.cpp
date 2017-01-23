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
	coins = m_level.GetAllObjectsByName(TMX_COIN);
	collisionBlocks = m_level.GetAllObjectsByType(TMX_COLLISION_BLOCK);
	environmentObjects = m_level.GetAllObjectsByType(TMX_ENVIRONMENT);
	Init();
}

void CGameScene::Init()
{
	float leftPosition = m_level.GetPlayerRect().left;
	float topPosition = m_level.GetPlayerRect().top;
	player.Init({leftPosition, topPosition}, PLAYER_SPEED_X, PLAYER_SPEED_UP, PLAYER_SPEED_DOWN, GRAVITY, 0, 1, 30);
	InitEnemies(m_level.GetAllObjectsByType(TMX_ENEMY));
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

void CGameScene::Draw(sf::RenderTarget &target) const
{
	m_level.Draw(target);
}