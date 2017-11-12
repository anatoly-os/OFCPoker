#pragma once

#include "IDeck.h"

namespace CPoker
{
  class IPlayer
  {
  public:
    enum class State
    {
      WaitForGameStart,
      WaitForFantasyCards,
      WaitForCards,
      WaitForPostGameActivities
    };

    struct ID
    {
      int id = 0;

    private:
      const ID operator+(const ID&) = delete;
      const ID operator*(const ID&) = delete;
      const ID operator-(const ID&) = delete;
    };

    virtual ID id() const = 0;
    virtual void setId(const IPlayer::ID&) = 0;

    virtual IDeck::CardsList topRow() const = 0;
    virtual IDeck::CardsList midRow() const = 0;
    virtual IDeck::CardsList bottomRow() const = 0;
    virtual IDeck::CardsList foldZone() const = 0;

    virtual int ingameCardsCount() const = 0;
  };
}