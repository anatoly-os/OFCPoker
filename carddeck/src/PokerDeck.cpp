#include "PokerDeck.h"
#include "PokerCard.h"

using namespace CPoker;

CPoker::PokerDeck::PokerDeck()
{
  initializeFullDeck();
}

CPoker::PokerDeck::~PokerDeck()
{
}

void CPoker::PokerDeck::shuffle()
{
  return;
}

IDeck::CardsList CPoker::PokerDeck::deal(const unsigned int numberOfCardsToDeal /*= 1*/)
{
  IDeck::CardsList alreadyDealtCards;
  if (m_aCards.empty())
    return alreadyDealtCards;

  for (unsigned int i = 0; i < numberOfCardsToDeal; ++i)
  {
    const auto& card = m_aCards[m_aCards.size() - 1];
    alreadyDealtCards.push_back(card);
    m_aAlreadyDealtCards.push_back(card);
    m_aCards.pop_back();
  }
  
  return alreadyDealtCards;
}

IDeck::CardsList CPoker::PokerDeck::cardsInDeck() const
{
  return m_aCards;
}

IDeck::CardsList CPoker::PokerDeck::dealtCards() const
{
  return CardsList();
}

void CPoker::PokerDeck::initializeFullDeck()
{
  m_aCards.resize(52);
  static const int csSuitsCount = static_cast<int>(ICard::Suit::Count);
  static const int csValuesCount = static_cast<int>(ICard::Value::Count);
  for (unsigned int suit = 0; suit < csSuitsCount; ++suit)
    for (unsigned int value = 0; value < csValuesCount; ++value)
      m_aCards[value + suit * csValuesCount] = new PokerCard(static_cast<ICard::Suit>(suit), static_cast<ICard::Value>(value));
}
