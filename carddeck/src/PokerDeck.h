#pragma once

#include "../include/IDeck.h"

namespace CPoker
{
  class PokerDeck : public IDeck
  {
  public:
    explicit PokerDeck();
    virtual ~PokerDeck() override;

    void shuffle() override;

    //sequence in list corresponds to dealing sequence
    CardsList deal(const unsigned int numberOfCardsToDeal) override;
    CardsList cardsInDeck() const override;
    CardsList dealtCards() const override;

  private:
    IDeck::CardsList m_aCards;
  };
}