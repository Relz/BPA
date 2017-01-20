// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "stdafx.h"
#include "GameView.h"

CGameView::CGameView(const sf::Vector2u screenSize)
{
	m_windowSize = screenSize;

	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	m_window.create(sf::VideoMode(screenSize.x, screenSize.y),
					WINDOW_TITLE,
					sf::Style::Close, settings);
	m_window.setFramerateLimit(60);

	m_camera.reset(sf::FloatRect(0.0f, 0.0f, screenSize.x, screenSize.y));
	m_camera.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	m_camera.zoom(2.0f);
}

void CGameView::GameLoop()
{
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
				break;
			}
		}
		m_window.clear(BACKGROUND_COLOR);
		if (m_gameScene.player.IsAlive())
		{
			UpdateGameScene();
			DrawGameScene();
		}
		else
		{
			std::cout << "Game Over!\n";
		}
		m_window.display();
	}
}

void CGameView::UpdateGameScene()
{
	CPlayer &player = m_gameScene.player;
	player.MoveProcess(m_gameScene.collisionBlocks);
	EnemiesMoveProcess(m_gameScene.enemies);
	if (player.DoesAttack())
	{
		TryPlayerToAttackEnemies(m_gameScene.enemies);
	}
	SetCameraCenter(player.GetPosition().x + m_windowSize.x / 4, m_windowSize.y);
}

void CGameView::DrawGameScene()
{
	m_gameScene.Draw(m_window);
	DrawTmxObjects(m_gameScene.environmentObjects);
	DrawTmxObjects(m_gameScene.coins);
	DrawEnemies(m_gameScene.enemies);
	m_gameScene.player.Draw(m_window);
}

void CGameView::DrawTmxObjects(const std::vector<TmxObject> & tmxObjects)
{
	for (const TmxObject & tmxObject : tmxObjects)
	{
		m_window.draw(tmxObject.sprite);
	}
}

void CGameView::DrawEnemies(const std::vector<CEnemy*> & enemies)
{
	for (const CEnemy * enemy : enemies)
	{
		enemy->Draw(m_window);
	}
}

void CGameView::EnemiesMoveProcess(std::vector<CEnemy*> & enemies)
{
	for (CEnemy * enemy : enemies)
	{
		enemy->MoveProcess(m_gameScene.collisionBlocks);
	}
}

void CGameView::SetCameraCenter(float cameraX, float cameraY)
{
	m_camera.setCenter(cameraX, cameraY);
	m_window.setView(m_camera);
}

bool CGameView::DoesPlayerAttackEnemy(const CEnemy * enemy) const
{
	/*const CPlayer & player = m_gameScene.player;

	float playerWidth = player.GetWidth();
	float playerHeight = player.GetHeight();

	float playerTopY = player.GetTop();
	float playerBottomY = playerTopY + playerHeight;
	float playerLeftX = player.GetLeft();
	float playerRightX = playerLeftX + playerWidth;

	float enemyWidth = enemy->GetWidth();
	float enemyHeight = enemy->GetHeight();

	float enemyTopY = enemy->GetTop();
	float enemyBottomY = enemyTopY + enemyHeight;
	float enemyLeftX = enemy->GetLeft();
	float enemyRightX = enemyLeftX + enemyWidth;

	bool playerPlacesInOneHorizontalWithTile = DoesObjectsPlacesInOneHorizontal(playerTopY, playerBottomY, enemyTopY, enemyBottomY);
	bool isLeftCollision = playerLeftX <= enemyRightX && playerRightX >= enemyRightX;
	bool isRightCollision = playerRightX >= enemyLeftX && playerLeftX <= enemyLeftX;

	return (playerPlacesInOneHorizontalWithTile && (isLeftCollision || isRightCollision));*/
	return false;
}

void CGameView::TryPlayerToAttackEnemies(std::vector<CEnemy*> & enemies) const
{
	for (CEnemy * enemy : enemies)
	{
		if (DoesPlayerAttackEnemy(enemy))
		{
			enemy->Die(enemies);
		}
	}
}