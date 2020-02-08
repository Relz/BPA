// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_BELOVED_H
#define ULTIMATE_SHAMAN_KING_BELOVED_H

#include "Unit.h"

class CBeloved : public CUnit
{
public:
	void Process(const std::vector<TmxObject> & collisionBlocks);
	void UpdateDirection(float playerLeft);

private:
};


#endif //ULTIMATE_SHAMAN_KING_BELOVED_H
