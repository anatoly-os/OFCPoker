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

void CPoker::Player::insertTopRowCards(const IDeck::CardsList& cards)
{
  m_top.insert(m_top.end(), cards.begin(), cards.end());
}

void CPoker::Player::insertMidRowCards(const IDeck::CardsList& cards)
{
  m_mid.insert(m_mid.end(), cards.begin(), cards.end());
}

void CPoker::Player::insertBottomRowCards(const IDeck::CardsList& cards)
{
  m_bottom.insert(m_bottom.end(), cards.begin(), cards.end());
}

void CPoker::Player::insertFoldZoneCards(const IDeck::CardsList& cards)
{
  m_foldZone.insert(m_foldZone.end(), cards.begin(), cards.end());
}

IDeck::CardsList CPoker::Player::ingameCards() const
{
  IDeck::CardsList cards{ m_top };
  cards.insert(cards.end(), m_mid.begin(), m_mid.end());
  cards.insert(cards.end(), m_bottom.begin(), m_bottom.end());
  return cards;
}
