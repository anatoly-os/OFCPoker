#pragma once

#include "../include/ICard.h"
#include <map>

namespace CPoker
{
  class NamesHelper
  {
  public:
    static std::string toString(const ICard::Suit& suit);
    static std::string toString(const ICard::Value& value);
  };
}