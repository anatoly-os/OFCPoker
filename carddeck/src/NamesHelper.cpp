#include "NamesHelper.h"

using namespace CPoker;

std::string CPoker::NamesHelper::toString(const ICard::Suit & suit)
{
  static const std::map<ICard::Suit, std::string> m_suitNameMapping
  {
    { ICard::Suit::Spades, "Spades"},
    { ICard::Suit::Hearts, "Hearts" },
    { ICard::Suit::Diamonds, "Diamonds" },
    { ICard::Suit::Clubs, "Clubs" }
  };

  return m_suitNameMapping.at(suit);
}

std::string CPoker::NamesHelper::toString(const ICard::Value & value)
{
  static const std::map<ICard::Value, std::string> m_valueNameMapping
  {
    { ICard::Value::Deuce, "Deuce" },
    { ICard::Value::Three, "Three" },
    { ICard::Value::Four, "Four" },
    { ICard::Value::Five, "Five" },
    { ICard::Value::Six, "Six" },
    { ICard::Value::Seven, "Seven" },
    { ICard::Value::Eight, "Eight" },
    { ICard::Value::Nine, "Nine" },
    { ICard::Value::Ten, "Ten" },
    { ICard::Value::Jack, "Jack" },
    { ICard::Value::Queen, "Queen" },
    { ICard::Value::King, "King" },
    { ICard::Value::Ace, "Ace" }
  };

  return m_valueNameMapping.at(value);
}
