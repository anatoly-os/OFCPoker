#pragma once

#include <string>

namespace CPoker
{
  class ICard
  {
  public:
    enum class Suit
    {
      Spades,
      Hearts,
      Diamonds,
      Clubs,
      Count
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
      Ace,
      Count
    };

    virtual ~ICard() {}

    virtual ICard::Suit suit() const = 0;
    virtual ICard::Value value() const = 0;

    virtual std::string toString() const = 0;
  };
}
