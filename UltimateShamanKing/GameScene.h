#ifndef ULTIMATE_SHAMAN_KING_GAMESCENE_H
#define ULTIMATE_SHAMAN_KING_GAMESCENE_H

#include "constant.h"
#include "TmxLevel.h"
#include "Units/Player.h"
#include "Units/Beloved.h"
#include "Units/Villain.h"
#include "Units/VillainSpirit.h"
#include "Units/Enemy.h"
#include "Fire.h"
#include "Dialog.h"
#include "SkillPanel.h"

class CGameScene
{
public:
	CGameScene();
	void Init();
	void InitEnemies(const std::vector<TmxObject> & enemies);
	void DrawTiles(sf::RenderTarget &target) const;

	CPlayer player;
	CBeloved beloved;
	CVillain villain;
	CVillainSpirit villainSpirit;
	CFire fire;
	CDialog dialog;
	CSkillPanel skillPanel;
	std::vector<CEnemy*> enemies;
	std::vector<TmxObject> collisionBlocks;
	std::vector<TmxObject> environmentObjects;
	std::vector<TmxObject> deadLines;
	std::vector<TmxObject> actionLines;
	float mapLeftBorder = 0;
	float mapRightBorder = 0;

	std::vector<CEnemy*> enemiesToIgnore;
	std::vector<CSnowball*> snowballsToIgnore;

private:
	TmxLevel m_level;
};


#endif //ULTIMATE_SHAMAN_KING_GAMESCENE_H
