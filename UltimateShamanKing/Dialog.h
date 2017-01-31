// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_DIALOG_H
#define ULTIMATE_SHAMAN_KING_DIALOG_H

#include "Replica.h"

class CDialog
{
public:
	void Add(CReplica * replica);
	void NextReplica();
	bool IsEmpty() const;
	bool IsJustClosed();
	void Draw(sf::RenderTarget & target) const;

private:
	std::vector<CReplica*> m_vectorReplica;

	bool m_isJustClosed = false;
};


#endif //ULTIMATE_SHAMAN_KING_DIALOG_H
