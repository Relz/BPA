#ifndef ULTIMATE_SHAMAN_KING_GAMESCENE_H
#define ULTIMATE_SHAMAN_KING_GAMESCENE_H

#include "TmxLevel.h"
#include "Units/Player.h"
#include "Units/Beloved.h"
#include "Units/Enemy.h"
#include "constant.h"

class CGameScene
{
public:
	CGameScene();
	void Init();
	void InitEnemies(const std::vector<TmxObject> & enemies);
	void DrawTiles(sf::RenderTarget &target) const;

	CPlayer player;
	CBeloved beloved;
	std::vector<CEnemy*> enemies;
	std::vector<TmxObject> collisionBlocks;
	std::vector<TmxObject> environmentObjects;
	std::vector<TmxObject> deadLines;
	float mapLeftBorder = 0;
	float mapRightBorder = 0;

private:
	TmxLevel m_level;
};


#endif //ULTIMATE_SHAMAN_KING_GAMESCENE_H
