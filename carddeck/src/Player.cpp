#include "Player.h"

using namespace CPoker;

CPoker::Player::Player()
{
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
  return IDeck::CardsList();
}

IDeck::CardsList CPoker::Player::midRow() const
{
  return IDeck::CardsList();
}

IDeck::CardsList CPoker::Player::bottomRow() const
{
  return IDeck::CardsList();
}

IDeck::CardsList CPoker::Player::foldZone() const
{
  return IDeck::CardsList();
}
