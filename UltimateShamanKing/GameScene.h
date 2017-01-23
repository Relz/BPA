#ifndef ULTIMATE_SHAMAN_KING_GAMESCENE_H
#define ULTIMATE_SHAMAN_KING_GAMESCENE_H

#include "TmxLevel.h"
#include "Units/Player.h"
#include "Units/Enemy.h"
#include "constant.h"

class CGameScene
{
public:
	CGameScene();
	void Init();
	void InitEnemies(const std::vector<TmxObject> & enemies);
	void Draw(sf::RenderTarget &target) const;

	CPlayer player;
	std::vector<CEnemy*> enemies;
	std::vector<TmxObject> coins;
	std::vector<TmxObject> collisionBlocks;
	std::vector<TmxObject> environmentObjects;
private:
	TmxLevel m_level;
};


#endif //ULTIMATE_SHAMAN_KING_GAMESCENE_H
