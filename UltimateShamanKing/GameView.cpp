// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "stdafx.h"
#include "GameView.h"

CGameView::CGameView(const sf::Vector2u screenSize)
		:m_menuView(screenSize)
{
	m_windowSize = screenSize;
	InitWindow();
	InitCamera();

	float scale = m_windowSize.x * CAMERA_ZOOM / m_gameOver.GetBackgroundWidth();
	m_gameOver.SetBackgroundScale(scale, scale);

	InitMenu();
}

void CGameView::InitWindow()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = ANTIALIASING_LEVEL;
	m_window.create(sf::VideoMode(m_windowSize.x, m_windowSize.y), WINDOW_TITLE, sf::Style::Close, settings);
	m_window.setFramerateLimit(60);
}

void CGameView::InitCamera()
{
	m_camera.reset(sf::FloatRect(0.0f, 0.0f, m_windowSize.x, m_windowSize.y));
	m_camera.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	m_camera.zoom(CAMERA_ZOOM);
}

void CGameView::InitMenu()
{
	m_menuView.SetBackgroundChangingTimeSec(10);

	MenuItem *menuItemStartGame = new MenuItem("Start Game", m_isGameStarted);
	MenuItem *menuItemHistory = new MenuItem("Story", m_showStory);
	m_menuView.AddMenuItem(menuItemStartGame);
	m_menuView.AddMenuItem(menuItemHistory);
}

void CGameView::GameLoop()
{
	bool enterReleased = true;
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
			else if (m_isGameStarted && !m_gameScene.player.IsAlive() && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				m_gameScene.Init();
			}
			else if (!m_gameScene.dialog.IsEmpty() && enterReleased && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				m_gameScene.dialog.NextReplica();
				enterReleased = false;
			}
			else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				enterReleased = true;
			}
		}
		m_window.clear(BACKGROUND_COLOR);
		if (m_isGameStarted)
		{
			if (m_gameScene.player.IsAlive())
			{
				UpdateGameScene();
				DrawGameScene();
			}
			else
			{
				ShowGameOverScreen();
			}
		}
		else
		{
			m_menuView.Draw(m_window);
			m_menuView.Process(m_window);
		}
		m_window.display();
	}
}

void CGameView::UpdateGameScene()
{
	CPlayer & player = m_gameScene.player;
	CBeloved & beloved = m_gameScene.beloved;
	CVillain & villain = m_gameScene.villain;
	CFire & fire = m_gameScene.fire;
	CVillainSpirit & villainSpirit = m_gameScene.villainSpirit;
	CDialog & dialog = m_gameScene.dialog;
	if (dialog.IsEmpty())
	{
		player.Process(m_gameScene.collisionBlocks);
		beloved.UpdateDirection(player.GetLeft());
		beloved.Process(m_gameScene.collisionBlocks);
		villain.UpdateDirection(player.GetLeft());
		villain.Process(m_gameScene.collisionBlocks);
		villainSpirit.UpdateDirection(player.GetLeft());
		villainSpirit.Process(m_gameScene.collisionBlocks);
		ProcessEnemies(m_gameScene.enemies, player);
		if (player.DoesAttacking())
		{
			TryPlayerToAttackEnemies(player, m_gameScene.enemies);
		}
		else if (!m_enemiesToIgnore.empty())
		{
			m_enemiesToIgnore.clear();
		}
		TryPlayerToDieFromDeadLine(player, m_gameScene.deadLines);
		CleanDeadBodies(m_gameScene.enemies);
		UpdatePlayerCamera(player);
		TryPlayerToRunAction(player, m_gameScene.actionLines);
		if (dialog.IsJustClosed())
		{
			StealBeloved();
		}
	}
	FireState fireState = FireState::SLEEP;
	fire.Process(fireState);
	if (fireState == FireState::DISSAPPEARED && fire.DoesInvokeDialogAfterProccessing())
	{
		sf::Vector2f avatarPositionYoh(m_camera.getCenter().x - m_camera.getSize().x / 2, m_camera.getSize().y - player.GetDialogAvatarAngry()->getGlobalBounds().height);
		sf::Vector2f avatarPositionHao(m_camera.getCenter().x - m_camera.getSize().x / 2, m_camera.getSize().y - villain.GetDialogAvatarNormal()->getGlobalBounds().height);
		dialog.Add(new CReplica(player.GetName(), player.GetDialogAvatarAngry(), L"Хао! Отпусти ее, сейчас же!", avatarPositionYoh, m_camera.getSize().x));
		dialog.Add(new CReplica(villain.GetName(), villain.GetDialogAvatarNormal(), L"Не так быстро, дорогой братец. И почему такой серьезный? =)", avatarPositionHao, m_camera.getSize().x));
		dialog.Add(new CReplica(player.GetName(), player.GetDialogAvatarAngry(), L"Что тебе нужно?!", avatarPositionYoh, m_camera.getSize().x));
		dialog.Add(new CReplica(villain.GetName(), villain.GetDialogAvatarNormal(), L"И неужели она тебе так дорога? Ну что же, докажи это =)", avatarPositionHao, m_camera.getSize().x));
	}
}

void CGameView::DrawGameScene()
{
	m_gameScene.DrawTiles(m_window);
	DrawTmxObjects(m_gameScene.environmentObjects);
	DrawEnemies(m_gameScene.enemies);
	m_gameScene.player.Draw(m_window);
	m_gameScene.villainSpirit.Draw(m_window);
	m_gameScene.beloved.Draw(m_window);
	m_gameScene.villain.Draw(m_window);
	m_gameScene.fire.Draw(m_window);
	m_gameScene.dialog.Draw(m_window);
}

void CGameView::ShowGameOverScreen()
{
	m_gameOver.SetWindowCenter(m_camera.getCenter());
	m_gameOver.SetWindowSize(sf::Vector2u(m_windowSize.x * CAMERA_ZOOM, m_windowSize.y * CAMERA_ZOOM));
	m_gameOver.Draw(m_window);
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

void CGameView::CreateNewSnowball(CEnemy * enemy, float playerLeft)
{
	float directionX = 0;
	if (playerLeft< enemy->GetLeft())
	{
		directionX = -1;
	}
	else
	{
		directionX = 1;
	}
	auto tempSnowball = std::find(m_snowballsToIgnore.begin(), m_snowballsToIgnore.end(), enemy->GetSnowball());
	if (tempSnowball != m_snowballsToIgnore.end())
	{
		m_snowballsToIgnore.erase(tempSnowball);
	}
	enemy->CreateNewSnowball(directionX);
}

void CGameView::TryToKillPlayer(CSnowball * enemySnowball, CPlayer & player)
{
	Collision collisionWithPlayer;
	CUnit::GetCollision(enemySnowball->GetTextureFloatRect(),
	                    player.GetSpriteRect(),
	                    player.GetSpriteRect(),
	                    player.GetDirection().x,
	                    player.GetWidth(),
	                    collisionWithPlayer);

	if (collisionWithPlayer.left || collisionWithPlayer.right)
	{
		player.ReduceHP(enemySnowball->GetStrength());
		m_snowballsToIgnore.push_back(enemySnowball);
		enemySnowball->Hide();
	}
}

void CGameView::ProcessEnemies(std::vector<CEnemy*> & enemies, CPlayer & player)
{
	for (CEnemy * enemy : enemies)
	{
		enemy->Process(m_gameScene.collisionBlocks);
		if (enemy->IsAlive())
		{
			if (enemy->GetSnowball() == nullptr || enemy->GetSnowball()->GetLivingTimeSec() > enemy->GetSnowball()->GetMaxLivingTimeSec())
			{
				CreateNewSnowball(enemy, player.GetLeft());
			}
			enemy->GetSnowball()->Process();
			enemy->GetSnowball()->Draw(m_window);
			bool snowballNotProcessed = std::find(m_snowballsToIgnore.begin(), m_snowballsToIgnore.end(), enemy->GetSnowball()) == m_snowballsToIgnore.end();
			if (snowballNotProcessed)
			{
				TryToKillPlayer(enemy->GetSnowball(), player);
			}
		}
	}
}

void CGameView::SetCameraCenter(float cameraX, float cameraY)
{
	m_camera.setCenter(cameraX, cameraY);
	m_window.setView(m_camera);
}

bool CGameView::DoesPlayerAttackEnemy(const CPlayer & player, const CEnemy * enemy) const
{
	Collision collisionWithEnemy;
	CUnit::GetCollision(enemy->GetSpriteRect(),
	                    player.GetSpriteRect(),
	                    player.GetSpriteRect(),
	                    player.GetDirection().x,
	                    player.GetWidth(),
	                    collisionWithEnemy);

	sf::Vector2f playerDirection = player.GetLastDirection();
	return ((collisionWithEnemy.left && playerDirection.x == -1) || (collisionWithEnemy.right && playerDirection.x == 1));
}

void CGameView::TryPlayerToAttackEnemies(const CPlayer & player, const std::vector<CEnemy*> & enemies)
{
	for (CEnemy * enemy : enemies)
	{
		bool enemyNotProcessed = std::find(m_enemiesToIgnore.begin(), m_enemiesToIgnore.end(), enemy) == m_enemiesToIgnore.end();
		if (enemyNotProcessed && enemy->IsAlive() && DoesPlayerAttackEnemy(player, enemy))
		{
			m_enemiesToIgnore.push_back(enemy);
			enemy->SetImpuls(player.GetDirection().x * 5.0f, enemy->GetUpSpeed() * 2.0f);
			enemy->ReduceHP(player.GetStrength());
		}
	}
}

void CGameView::TryPlayerToDieFromDeadLine(CPlayer & player, const std::vector<TmxObject> & deadLines)
{
	Collision collisionWithDeadLine;
	for (const TmxObject & deadLine : deadLines)
	{
		CUnit::GetCollision(deadLine.rect,
		                    player.GetSpriteRect(),
		                    player.GetSpriteRect(),
		                    player.GetDirection().x,
		                    player.GetWidth(),
		                    collisionWithDeadLine);
		if (collisionWithDeadLine.Any())
		{
			player.Die();
		}
	}
}


void CGameView::CleanDeadBodies(std::vector<CEnemy *> &enemies) const
{
	for (auto it = enemies.begin(); it != enemies.end(); ++it)
	{
		if (!(*it)->IsAlive() && (*it)->GetDyingClockSec() >= (*it)->GetDyingTimeSec())
		{
			enemies.erase(it);
			break;
		}
	}
}

void CGameView::UpdatePlayerCamera(const CPlayer & player)
{
	float mapLeftBorder = m_gameScene.mapLeftBorder;
	float mapRightBorder = m_gameScene.mapRightBorder;
	float cameraXPosition = player.GetPosition().x + m_windowSize.x / 2 / CAMERA_ZOOM;
	if (cameraXPosition - m_windowSize.x < mapLeftBorder)
	{
		cameraXPosition = mapLeftBorder + m_windowSize.x;
	}
	else if (cameraXPosition + m_windowSize.x > mapRightBorder)
	{
		cameraXPosition = mapRightBorder - m_windowSize.x;
	}
	SetCameraCenter(cameraXPosition, m_windowSize.y);
}

void CGameView::TryPlayerToRunAction(const CPlayer & player, std::vector<TmxObject> & actionLines)
{
	Collision collisionWithActionLine;
	for (auto it = actionLines.begin(); it != actionLines.end(); ++it)
	{
		CUnit::GetCollision(it->rect,
		                    player.GetSpriteRect(),
		                    player.GetSpriteRect(),
		                    player.GetDirection().x,
		                    player.GetWidth(),
		                    collisionWithActionLine);
		if (collisionWithActionLine.Any())
		{
			actionLines.erase(it);
			AppearVillain();
			break;
		}
	}
}

void CGameView::AppearVillain()
{
	m_gameScene.fire.Show(true);
	m_gameScene.villain.Show();
	m_gameScene.villainSpirit.Show();
}

void CGameView::StealBeloved()
{
	m_gameScene.fire.Show(false);
	m_gameScene.villain.Hide();
	m_gameScene.villainSpirit.Hide();
	m_gameScene.beloved.Hide();
}
