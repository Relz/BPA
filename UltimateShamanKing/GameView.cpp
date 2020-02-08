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
		ProcessCoins(m_gameScene.coins);
		if (!player.IsWithShield())
		{
			if (player.IsAttacking() || player.IsUsingCloudstrike())
			{
				TryPlayerToAttackEnemies(player, m_gameScene.enemies);
			}
			else if (!m_gameScene.enemiesToIgnore.empty())
			{
				m_gameScene.enemiesToIgnore.clear();
			}
		}
		TryPlayerToDieFromDeadLine(player, m_gameScene.deadLines);
		TryPlayerToRunAction(player, m_gameScene.actionLines);
		if (dialog.IsJustClosed())
		{
			RunAction(dialog.GetActionAfterDialogClosing());
		}
		TryPlayerToUseSkill(player.GetUsingSkill());
		TryPlayerToFinishLevel(player);
		UpdatePlayerCamera(player);
		UpdateSkillPanel();
		UpdateMoneyPanel(player.GetMoney());
	}
	FireState fireState = FireState::SLEEP;
	fire.Process(fireState);
	if (fireState == FireState::DISSAPPEARED)
	{
		RunAction(fire.GetActionAfterProcessing());
	}
}

void CGameView::DrawGameScene()
{
	m_gameScene.DrawTiles(m_window);
	DrawTmxObjects(m_gameScene.environmentObjects);
	DrawEnemies(m_gameScene.enemies);
	DrawCoins(m_gameScene.coins);
	m_gameScene.player.Draw(m_window);
	m_gameScene.villainSpirit.Draw(m_window);
	m_gameScene.beloved.Draw(m_window);
	m_gameScene.villain.Draw(m_window);
	m_gameScene.fire.Draw(m_window);
	m_gameScene.dialog.Draw(m_window);
	m_gameScene.skillPanel.Draw(m_window, m_gameScene.player.IsWithSpirit());
	m_gameScene.moneyPanel.Draw(m_window);
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
		if (enemy->GetSnowball() != nullptr)
		{
			enemy->GetSnowball()->Draw(m_window);
		}
	}
}

void CGameView::DrawCoins(const std::vector<CCoin*> & coins)
{
	for (const CCoin * coin : coins)
	{
		coin->Draw(m_window);
	}
}

void CGameView::UpdateSkillPanel()
{
	CSkillPanel & skillPanel = m_gameScene.skillPanel;
	skillPanel.SetPosition(sf::Vector2f(m_camera.getCenter().x - m_windowSize.x / 2 * CAMERA_ZOOM,
	                                    m_camera.getCenter().y - skillPanel.GetHeight() / 2));
}

void CGameView::UpdateMoneyPanel(float money)
{
	CMoneyPanel & moneyPanel = m_gameScene.moneyPanel;
	moneyPanel.SetMoney(money);
	moneyPanel.SetPosition(sf::Vector2f(m_camera.getCenter().x - m_windowSize.x / 2 * CAMERA_ZOOM, 0));
}

void CGameView::RemoveSnowballFromIgnored(CSnowball * snowball)
{
	std::vector<CSnowball*> & snowballsToIgnore = m_gameScene.snowballsToIgnore;
	auto snowballToRemove = std::find(snowballsToIgnore.begin(), snowballsToIgnore.end(), snowball);
	if (snowballToRemove != snowballsToIgnore.end())
	{
		snowballsToIgnore.erase(snowballToRemove);
	}
}

void CGameView::CreateNewSnowball(CEnemy * enemy, float playerLeft)
{
	float directionX = 0;
	directionX = (playerLeft < enemy->GetLeft()) ? -1 : 1;
	RemoveSnowballFromIgnored(enemy->GetSnowball());
	enemy->CreateNewSnowball(directionX);
}

bool CGameView::TrySnowballToTouchPlayer(CSnowball * enemySnowball, CPlayer & player) const
{
	bool result = false;
	Collision collisionWithPlayer;
	CUnit::GetCollision(enemySnowball->GetTextureFloatRect(),
	                    player.GetRect(),
	                    player.GetFutureRect(),
	                    player.GetLastDirection().x,
	                    player.GetWidth(),
	                    collisionWithPlayer);

	if (collisionWithPlayer.Any())
	{
		result = true;
		if ((collisionWithPlayer.right && !(player.IsWithShield() && player.GetLastDirection().x == 1))
		    || (collisionWithPlayer.left && !(player.IsWithShield() && player.GetLastDirection().x == -1))
			|| ((collisionWithPlayer.top || collisionWithPlayer.bottom) && !collisionWithPlayer.right && !collisionWithPlayer.left))
		{
			player.ReduceHP(enemySnowball->GetStrength());
		}
	}
	return result;
}

bool CGameView::TrySnowballToTouchCollisionBlocks(CSnowball * enemySnowball, const std::vector<TmxObject> & collisionBlocks) const
{
	bool result = false;
	Collision collisionWithBlocks;
	for (const TmxObject & collisionBlock : collisionBlocks)
	{
		CUnit::GetCollision(collisionBlock.rect,
		                    enemySnowball->GetTextureFloatRect(),
		                    enemySnowball->GetTextureFloatRect(),
		                    enemySnowball->GetDirectionX(),
		                    enemySnowball->GetTextureFloatRect().width,
		                    collisionWithBlocks);
		if (collisionWithBlocks.Any())
		{
			result = true;
			break;
		}
	}
	return result;
}

void CGameView::CleanDeadBodies(std::vector<CEnemy *> & enemies)
{
	for (auto it = enemies.begin(); it != enemies.end(); ++it)
	{
		if (!(*it)->IsAlive() && (*it)->GetDyingClockSec() >= (*it)->GetDyingTimeSec())
		{
			RemoveSnowballFromIgnored((*it)->GetSnowball());
			enemies.erase(it);
			break;
		}
	}
}

void CGameView::ProcessEnemies(std::vector<CEnemy*> & enemies, CPlayer & player)
{
	std::vector<CSnowball*> & snowballsToIgnore = m_gameScene.snowballsToIgnore;
	for (CEnemy * enemy : enemies)
	{
		enemy->Process(m_gameScene.collisionBlocks);
		if (!enemy->IsAlive())
		{
			RemoveSnowballFromIgnored(enemy->GetSnowball());
			enemy->DestroySnowball();
			continue;
		}
		if (enemy->GetSnowball() == nullptr || enemy->GetSnowball()->GetLivingTimeSec() > enemy->GetSnowball()->GetMaxLivingTimeSec())
		{
			RemoveSnowballFromIgnored(enemy->GetSnowball());
			enemy->DestroySnowball();
			CreateNewSnowball(enemy, player.GetLeft());
		}
		CSnowball * enemySnowball = enemy->GetSnowball();
		bool snowballNotProcessed = std::find(snowballsToIgnore.begin(), snowballsToIgnore.end(), enemySnowball) == snowballsToIgnore.end();
		if (snowballNotProcessed)
		{
			enemy->GetSnowball()->Process();
			if (TrySnowballToTouchPlayer(enemySnowball, player) || TrySnowballToTouchCollisionBlocks(enemySnowball, m_gameScene.collisionBlocks))
			{
					m_gameScene.snowballsToIgnore.push_back(enemySnowball);
					enemySnowball->Hide();
			}
		}
	}
	CleanDeadBodies(enemies);
}

void CGameView::ProcessCoins(std::vector<CCoin*> & coins)
{
	for (CCoin * coin : coins)
	{
		coin->Process();
		TryPlayerToPickUpCoin(m_gameScene.player, coin);
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
	                    player.GetFutureSpriteRect(),
	                    player.GetLastDirection().x,
	                    player.GetWidth(),
	                    collisionWithEnemy);

	sf::Vector2f playerDirection = player.GetLastDirection();
	return ((collisionWithEnemy.left && playerDirection.x == -1) || (collisionWithEnemy.right && playerDirection.x == 1));
}

void CGameView::TryPlayerToPickUpCoin(CPlayer & player, CCoin * coin)
{
	std::vector<CCoin*> & coins = m_gameScene.coins;
	Collision collisionWithCoin;
	CUnit::GetCollision(coin->GetSpriteRect(),
	                    player.GetSpriteRect(),
	                    player.GetFutureSpriteRect(),
	                    player.GetLastDirection().x,
	                    player.GetWidth(),
	                    collisionWithCoin);
	if (collisionWithCoin.Any())
	{
		auto coinIt = std::find(coins.begin(), coins.end(), coin);
		if (coinIt != coins.end())
		{
			player.IncreaseMoney(coin->GetValue());
			coins.erase(coinIt);
		}
	}
}

void CGameView::TryPlayerToAttackEnemies(CPlayer & player, const std::vector<CEnemy*> & enemies)
{
	std::vector<CEnemy*> & enemiesToIgnore = m_gameScene.enemiesToIgnore;
	for (CEnemy * enemy : enemies)
	{
		bool enemyNotProcessed = std::find(enemiesToIgnore.begin(), enemiesToIgnore.end(), enemy) == enemiesToIgnore.end();
		if (enemyNotProcessed && enemy->IsAlive() && DoesPlayerAttackEnemy(player, enemy))
		{
			enemiesToIgnore.push_back(enemy);
			enemy->SetImpuls(player.GetDirection().x * 5.0f, enemy->GetUpSpeed() * 2.0f);
			enemy->ReduceHP(player.IsUsingCloudstrike() ? player.GetStrength() * 3 : player.GetStrength());
			if (!enemy->IsAlive())
			{
				player.IncreaseSP(10);
			}
		}
	}
}

void CGameView::TryPlayerToDieFromDeadLine(CPlayer & player, const std::vector<TmxObject> & deadLines)
{
	Collision collisionWithDeadLine;
	for (const TmxObject & deadLine : deadLines)
	{
		CUnit::GetCollision(deadLine.rect,
		                    player.GetRect(),
		                    player.GetRect(),
		                    player.GetLastDirection().x,
		                    player.GetWidth(),
		                    collisionWithDeadLine);
		if (collisionWithDeadLine.Any())
		{
			player.Die();
		}
	}
}

void CGameView::UpdatePlayerCamera(const CPlayer & player)
{
	float mapLeftBorder = m_gameScene.mapLeftBorder;
	float mapRightBorder = m_gameScene.mapRightBorder;
	float cameraXPosition = player.GetPosition().x + (float)m_windowSize.x / 2 / CAMERA_ZOOM;
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

void CGameView::AddToDialog(CUnit * unit, sf::Sprite * avatarSprite, const std::wstring & message)
{
	m_gameScene.dialog.Add(new CReplica(unit->GetName(), avatarSprite, m_camera, message));
}

void CGameView::TryPlayerToRunAction(const CPlayer & player, std::vector<TmxObject> & actionLines)
{
	Collision collisionWithActionLine;
	for (auto it = actionLines.begin(); it != actionLines.end(); ++it)
	{
		CUnit::GetCollision(it->rect,
		                    player.GetRect(),
		                    player.GetFutureRect(),
		                    player.GetLastDirection().x,
		                    player.GetWidth(),
		                    collisionWithActionLine);
		if (collisionWithActionLine.Any())
		{
			RunAction(it->name);
			actionLines.erase(it);
			break;
		}
	}
}

void CGameView::RunAction(const std::string & actionName)
{
	if (actionName.empty())
	{
		return;
	}
	CDialog & dialog = m_gameScene.dialog;
	CPlayer & player = m_gameScene.player;
	CBeloved & beloved = m_gameScene.beloved;
	CVillain & villain = m_gameScene.villain;
	if (actionName == TMX_ACTION_GAME_BEGINNING)
	{
		AddToDialog(&player, player.GetDialogAvatarAngry(), L"Что происходит?! Почему все стали себя так странно вести?");
		AddToDialog(&player, player.GetDialogAvatarNormal(), L"И где Анна?");
	}
	else if (actionName == TMX_ACTION_BELOVED_FOUND)
	{
		AddToDialog(&player, player.GetDialogAvatarNormal(), L"Вот ты где!");
		AddToDialog(&beloved, beloved.GetDialogAvatarNormal(), L"Йо!");
	}
	else if (actionName == TMX_ACTION_VILLAIN_APPEARING)
	{
		AppearVillain();
	}
	else if (actionName == ACTION_VILLAIN_APPEARED)
	{
		dialog.SetActionAfterDialogClosing(ACTION_FIRE_VILLAIN_DISAPPEARING);
		AddToDialog(&villain, villain.GetDialogAvatarNormal(), L"Не так быстро, дорогой братец.");
		AddToDialog(&player, player.GetDialogAvatarAngry(), L"Хао! Отпусти ее, сейчас же!");
		AddToDialog(&villain, villain.GetDialogAvatarNormal(), L"И почему такой серьезный? =)");
		AddToDialog(&player, player.GetDialogAvatarAngry(), L"Что тебе нужно?!");
		AddToDialog(&villain, villain.GetDialogAvatarNormal(), L"И неужели она тебе так дорога? Ну что же, докажи это =)");
	}
	else if (actionName == ACTION_FIRE_VILLAIN_DISAPPEARING)
	{
		StealBeloved();
	}
}

void CGameView::AppearVillain()
{
	m_gameScene.fire.SetActionAfterProcessing(ACTION_VILLAIN_APPEARED);
	m_gameScene.fire.Show();
	m_gameScene.villain.Show();
	m_gameScene.villainSpirit.Show();
}

void CGameView::StealBeloved()
{
	m_gameScene.fire.Show();
	m_gameScene.villain.Hide();
	m_gameScene.villainSpirit.Hide();
	m_gameScene.beloved.Hide();
}

void CGameView::TryPlayerToUseSkill(int usingSkill)
{
	CSkill * skill = m_gameScene.skillPanel.GetSkillByIndex(usingSkill);
	if (skill == nullptr)
	{
		return;
	}
	CPlayer & player = m_gameScene.player;
	if (player.IsWithSpirit() || !skill->IsCanBeUsedOnlyWithSpirit())
	{
		player.UseSkill(skill->GetName(), skill->GetSpReduce());
	}
}

void CGameView::TryPlayerToFinishLevel(CPlayer & player)
{
	sf::FloatRect playerRect = player.GetFutureSpriteRect();
	if (playerRect.left + playerRect.width > m_gameScene.mapRightBorder)
	{
		m_gameScene.LoadLevelFromTmx(TMX_PATH_LEVEL_0);
		m_gameScene.Init();
	}
}
