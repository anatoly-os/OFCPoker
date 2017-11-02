#pragma once

#include <list>
#include "ICard.h"
#include "Exports.h"

namespace CPoker
{
  class ICard;
  
  CARDDECK_API class IDeck
  {
  public:
    virtual ~IDeck() {}

    using CardsList = std::list<ICard*>;

    virtual void shuffle() = 0;

    //sequence in list corresponds to dealing sequence
    virtual CardsList deal(const unsigned int numberOfCardsToDeal) = 0;
    virtual CardsList cardsInDeck() const = 0;
    virtual CardsList dealtCards() const = 0;
  };
}
