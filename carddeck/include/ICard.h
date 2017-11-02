#pragma once

#include "Exports.h"

namespace CPoker
{
  CARDDECK_API class ICard
  {
  public:
    enum class Suit
    {
      Spades,
      Hearts,
      Diamonds,
      Clubs
    };

    enum class Value
    {
      Deuce,
      Three,
      Four,
      Five,
      Six,
      Seven,
      Eight,
      Nine,
      Ten,
      Jack,
      Queen,
      King,
      Ace
    };

    virtual ~ICard() {}

    virtual ICard::Suit suit() const = 0;
    virtual ICard::Value value() const = 0;
  };
}
