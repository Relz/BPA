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
	beloved.SetSprite("../res/Images/anna.png", 2.5);
	villain.SetSprite("../res/Images/Sprites/hao.png", {0, 0, 29, 47}, 4.7);
	villainSpirit.SetSprite("../res/Images/spirit_of_fire.png", 2.5);
	fire.SetSprite("../res/Images/Sprites/fire.png", {0, 0, 256, 248}, 4);
	collisionBlocks = m_level.GetAllObjectsByType(TMX_COLLISION_BLOCK_TYPE);
	environmentObjects = m_level.GetAllObjectsByType(TMX_ENVIRONMENT_TYPE);
	deadLines = m_level.GetAllObjectsByType(TMX_DEAD_LINE_TYPE);
	actionLines = m_level.GetAllObjectsByType(TMX_ACTION_LINE_TYPE);
	mapLeftBorder = m_level.GetMapLeftBorder();
	mapRightBorder = m_level.GetMapRightBorder();
	Init();
}

void CGameScene::Init()
{
	sf::Vector2f playerPosition(m_level.GetPlayerRect().left, m_level.GetPlayerRect().top);
	player.Init(playerPosition, PLAYER_SPEED_X, PLAYER_SPEED_UP, PLAYER_SPEED_DOWN, GRAVITY, 0, 100, 30);
	sf::Vector2f belovedPosition(m_level.GetBelovedRect().left, m_level.GetBelovedRect().top);
	beloved.Init(belovedPosition, PLAYER_SPEED_X, PLAYER_SPEED_UP, PLAYER_SPEED_DOWN, GRAVITY, 0, 80, 0);
	sf::Vector2f villainPosition(m_level.GetVillainRect().left, m_level.GetVillainRect().top);
	villain.Init(villainPosition, PLAYER_SPEED_X, PLAYER_SPEED_UP, PLAYER_SPEED_DOWN, GRAVITY, 0, 100, 0);
	villain.Hide();
	sf::Vector2f villainSpiritPosition(m_level.GetVillainSpiritRect().left, m_level.GetVillainSpiritRect().top);
	villainSpirit.Init(villainSpiritPosition, PLAYER_SPEED_X, PLAYER_SPEED_UP, PLAYER_SPEED_DOWN, GRAVITY, 0, 100, 0);
	villainSpirit.Hide();
	sf::Vector2f firePosition(villainSpiritPosition.x - 100, villainSpiritPosition.y - 250);
	fire.SetPosition(firePosition);
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