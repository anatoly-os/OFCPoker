#include "PokerCard.h"

using namespace CPoker;

CPoker::PokerCard::PokerCard()
  : PokerCard(ICard::Suit::Spades, ICard::Value::Deuce)
{
}

CPoker::PokerCard::PokerCard(const ICard::Suit & suit, const ICard::Value & value)
  : m_suit(suit)
  , m_value(value)
{
}

CPoker::PokerCard::~PokerCard()
{
}

ICard::Suit CPoker::PokerCard::suit() const
{
  return m_suit;
}

ICard::Value CPoker::PokerCard::value() const
{
  return m_value;
}
