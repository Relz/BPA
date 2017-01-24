#ifndef ULTIMATE_SHAMAN_KING_GAMEVIEW_H
#define ULTIMATE_SHAMAN_KING_GAMEVIEW_H

#include "constant.h"
#include "TmxLevel.h"
#include "GameScene.h"
#include "Units/Player.h"
#include "Units/Enemy.h"
#include "Screens/GameOver.h"
#include "Screens/MenuView.h"

class CGameView
{
public:
	CGameView(const sf::Vector2u screenSize);
	void GameLoop();
private:
	void InitWindow();
	void InitCamera();
	void InitMenu();
	void UpdateGameScene();
	void SetCameraCenter(float cameraX, float cameraY);
	void DrawGameScene();
	void ShowGameOverScreen();
	void DrawTmxObjects(const std::vector<TmxObject> & tmxObjects);
	void DrawEnemies(const std::vector<CEnemy*> & enemies);
	void ProcessEnemies(std::vector<CEnemy*> & enemies);
	bool DoesPlayerAttackEnemy(const CEnemy * enemy) const;
	void TryPlayerToAttackEnemies(const std::vector<CEnemy*> & enemies);
	void TryPlayerToDieFromDeadLine(const std::vector<TmxObject> & tmxObjects);
	void CleanDeadBodies(std::vector<CEnemy*> & enemies) const;
	void CreateNewSnowball(CEnemy * enemy);
	void TryToKillPlayer(CSnowball * enemySnowball);

	sf::RenderWindow m_window;
	sf::View m_camera;
	sf::Vector2u m_windowSize;
	CGameScene m_gameScene;
	std::vector<CEnemy*> m_enemiesToIgnore;
	std::vector<CSnowball*> m_snowballsToIgnore;

	CGameOver m_gameOver;
	CMenuView m_menuView;
	bool m_isGameStarted = false;
	bool m_showStory = false;
};


#endif //ULTIMATE_SHAMAN_KING_GAMEVIEW_H
