// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_GAMEVIEW_H
#define ULTIMATE_SHAMAN_KING_GAMEVIEW_H

#include "constant.h"
#include "TmxLevel.h"
#include "GameScene.h"
#include "Screens/GameOverView.h"
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
	void DrawCoins(const std::vector<CCoin*> & coins);
	void ProcessEnemies(std::vector<CEnemy*> & enemies, CPlayer & player);
	void ProcessCoins(std::vector<CCoin*> & coins);
	bool DoesPlayerAttackEnemy(const CPlayer & player, const CEnemy * enemy) const;
	void TryPlayerToPickUpCoin(CPlayer & player, CCoin* coin);
	void TryPlayerToAttackEnemies(CPlayer & player, const std::vector<CEnemy*> & enemies);
	void TryPlayerToDieFromDeadLine(CPlayer & player, const std::vector<TmxObject> & deadLines);
	void CleanDeadBodies(std::vector<CEnemy*> & enemies);
	void CreateNewSnowball(CEnemy * enemy, float playerLeft);
	void RemoveSnowballFromIgnored(CSnowball * enemy);
	bool TrySnowballToTouchPlayer(CSnowball * enemySnowball, CPlayer & player) const;
	bool TrySnowballToTouchCollisionBlocks(CSnowball * enemySnowball, const std::vector<TmxObject> & collisionBlocks) const;
	void UpdatePlayerCamera(const CPlayer & player);
	void AddToDialog(CUnit * unit, sf::Sprite * avatarSprite, const std::wstring & message);
	void TryPlayerToRunAction(const CPlayer & player, std::vector<TmxObject> & actionLines);
	void RunAction(const std::string & basic_string);
	void AppearVillain();
	void StealBeloved();
	void TryPlayerToUseSkill(int usingSkill);
	void TryPlayerToFinishLevel(CPlayer & player);

	sf::RenderWindow m_window;
	sf::View m_camera;
	sf::Vector2u m_windowSize;
	CGameScene m_gameScene;

	CGameOverView m_gameOver;
	CMenuView m_menuView;
	bool m_isGameStarted = false;
	bool m_showStory = false;

	void UpdateSkillPanel();
	void UpdateMoneyPanel(float money);
};


#endif //ULTIMATE_SHAMAN_KING_GAMEVIEW_H
