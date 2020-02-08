// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_VILLAINSPIRIT_H
#define ULTIMATE_SHAMAN_KING_VILLAINSPIRIT_H

#include "Unit.h"

class CVillainSpirit : public CUnit
{
public:
	void Process(const std::vector<TmxObject> & collisionBlocks) override;
	void UpdateDirection(float playerLeft);
};


#endif //ULTIMATE_SHAMAN_KING_VILLAINSPIRIT_H
