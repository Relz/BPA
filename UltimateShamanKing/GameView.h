#ifndef ULTIMATE_SHAMAN_KING_GAMEVIEW_H
#define ULTIMATE_SHAMAN_KING_GAMEVIEW_H

#include "constant.h"
#include "TmxLevel.h"
#include "GameScene.h"
#include "Units/Player.h"

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
	void EnemiesMoveProcess(std::vector<CEnemy*> & enemies);

	sf::RenderWindow m_window;
	sf::View m_camera;
	sf::Vector2u m_windowSize;
	CGameScene m_gameScene;
};


#endif //ULTIMATE_SHAMAN_KING_GAMEVIEW_H
