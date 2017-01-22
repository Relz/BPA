#ifndef ULTIMATE_SHAMAN_KING_GAMEVIEW_H
#define ULTIMATE_SHAMAN_KING_GAMEVIEW_H

#include "constant.h"
#include "TmxLevel.h"
#include "GameScene.h"
#include "Units/Player.h"
#include "Units/Enemy.h"

class CGameView
{
public:
	CGameView(const sf::Vector2u screenSize);
	void GameLoop();
private:
	void UpdateGameScene();
	void SetCameraCenter(float cameraX, float cameraY);
	void DrawGameScene();
	void DrawTmxObjects(const std::vector<TmxObject> & tmxObjects);
	void DrawEnemies(const std::vector<CEnemy*> & enemies);
	void ProcessEnemies(std::vector<CEnemy*> & enemies);
	bool DoesPlayerAttackEnemy(const CEnemy * enemy) const;
	void TryPlayerToAttackEnemies(const std::vector<CEnemy*> & enemies);
	void CleanDeadBodies(std::vector<CEnemy*> & enemies) const;

	sf::RenderWindow m_window;
	sf::View m_camera;
	sf::Vector2u m_windowSize;
	CGameScene m_gameScene;
	std::vector<CEnemy*> m_enemiesToIgnore;
};


#endif //ULTIMATE_SHAMAN_KING_GAMEVIEW_H
