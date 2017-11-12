#include "Player.h"

using namespace CPoker;

CPoker::Player::Player(int id)
{
  m_id.id = id;
}

IPlayer::ID CPoker::Player::id() const
{
  return m_id;
}

void CPoker::Player::setId(const IPlayer::ID& id)
{
  m_id = id;
}

IDeck::CardsList CPoker::Player::topRow() const
{
  return m_top;
}

IDeck::CardsList CPoker::Player::midRow() const
{
  return m_mid;
}

IDeck::CardsList CPoker::Player::bottomRow() const
{
  return m_bottom;
}

IDeck::CardsList CPoker::Player::foldZone() const
{
  return IDeck::CardsList();
}

int CPoker::Player::ingameCardsCount() const
{
  return m_top.size() + m_mid.size() + m_bottom.size();
}
