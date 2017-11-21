#include "NamesHelper.h"

using namespace CPoker;

std::string CPoker::NamesHelper::toString(const ICard::Suit & suit)
{
  static const std::map<ICard::Suit, std::string> m_suitNameMapping
  {
    { ICard::Suit::Spades, "s"},
    { ICard::Suit::Hearts, "h" },
    { ICard::Suit::Diamonds, "d" },
    { ICard::Suit::Clubs, "c" }
  };

  return m_suitNameMapping.at(suit);
}

std::string CPoker::NamesHelper::toString(const ICard::Value & value)
{
  static const std::map<ICard::Value, std::string> m_valueNameMapping
  {
    { ICard::Value::Deuce, "2" },
    { ICard::Value::Three, "3" },
    { ICard::Value::Four, "4" },
    { ICard::Value::Five, "5" },
    { ICard::Value::Six, "6" },
    { ICard::Value::Seven, "7" },
    { ICard::Value::Eight, "8" },
    { ICard::Value::Nine, "9" },
    { ICard::Value::Ten, "T" },
    { ICard::Value::Jack, "J" },
    { ICard::Value::Queen, "Q" },
    { ICard::Value::King, "K" },
    { ICard::Value::Ace, "A" }
  };

  return m_valueNameMapping.at(value);
}
