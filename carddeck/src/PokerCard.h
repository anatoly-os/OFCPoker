#pragma once

#include "ICard.h"

namespace CPoker
{
  class PokerCard : public ICard
  {
  public:
    PokerCard();
    explicit PokerCard(const ICard::Suit& suit, const ICard::Value& value);
    virtual ~PokerCard() override;

    ICard::Suit suit() const override;
    ICard::Value value() const override;

  private:
    ICard::Suit m_suit;
    ICard::Value m_value;
  };
}