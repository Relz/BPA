// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "GameScene.h"

CGameScene::CGameScene()
{
	if (!m_level.LoadFromFile(TMX_PATH))
	{
		throw std::invalid_argument("Failed to load \"" + TMX_PATH + "\"");
	}
	player.SetSprite("../res/Images/Sprites/yoh.png", {6, 2, 30, 42}, 5);
	float leftPosition = static_cast<float>(m_level.GetPlayerRect().left);
	float topPosition = static_cast<float>(m_level.GetPlayerRect().top);
	player.Init({leftPosition, topPosition}, PLAYER_SPEED_X, PLAYER_SPEED_UP, PLAYER_SPEED_DOWN, GRAVITY);
	coins = m_level.GetAllObjectsByName(TMX_COIN);
	enemies = m_level.GetAllObjectsByName(TMX_ENEMIES);
	collisionBlocks = m_level.GetAllObjectsByType(TMX_COLLISION_BLOCK);
	environmentObjects = m_level.GetAllObjectsByType(TMX_ENVIRONMENT);
}

void CGameScene::Draw(sf::RenderTarget &target) const
{
	m_level.Draw(target);
}