// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Dialog.h"

void CDialog::Add(CReplica * replica)
{
	m_vectorReplica.push_back(replica);
}

void CDialog::NextReplica()
{
	if (!IsEmpty())
	{
		m_vectorReplica.erase(m_vectorReplica.begin());
		if (IsEmpty())
		{
			m_isJustClosed = true;
		}
	}
}

bool CDialog::IsEmpty() const
{
	return m_vectorReplica.empty();
}

bool CDialog::IsJustClosed()
{
	bool result = m_isJustClosed;
	if (result)
	{
		m_isJustClosed = false;
	}
	return result;
}

void CDialog::Draw(sf::RenderTarget & target) const
{
	if (!IsEmpty())
	{
		(*m_vectorReplica.begin())->Draw(target);
	}
}

void CDialog::SetActionAfterDialogClosing(const std::string & value)
{
	m_actionAfterDialogClosing = value;
}

std::string CDialog::GetActionAfterDialogClosing()
{
	std::string result = m_actionAfterDialogClosing;
	m_actionAfterDialogClosing = "";
	return result;
}
