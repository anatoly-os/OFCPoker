#include "PokerDeck.h"

using namespace CPoker;

CPoker::PokerDeck::PokerDeck()
{
}

CPoker::PokerDeck::~PokerDeck()
{
}

void CPoker::PokerDeck::shuffle()
{
  return;
}

IDeck::CardsList CPoker::PokerDeck::deal(const unsigned int numberOfCardsToDeal)
{
  return CardsList();
}

IDeck::CardsList CPoker::PokerDeck::cardsInDeck() const
{
  return CardsList();
}

IDeck::CardsList CPoker::PokerDeck::dealtCards() const
{
  return CardsList();
}
