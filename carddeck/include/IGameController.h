#pragma once

#include "IPlayer.h"
#include "IDeck.h"

#include <map>

namespace CPoker
{
  class IGameController
  {
  public:
    enum class Round
    {
      WaitGameStart,
      Fantasy,
      FiveCards,
      ThreeCards1,
      ThreeCards2,
      ThreeCards3,
      ThreeCards4,
      WaitPostGameFinish
    };

    using PlayerStates = std::map<IPlayer::ID, IPlayer::State>;

    virtual void startGame(const std::vector<IPlayer::ID>&) = 0;
    virtual IPlayer::ID button() const = 0;
    virtual PlayerStates playerStates() const = 0;

    virtual Round round() const = 0;
    virtual IPlayer::ID activePlayer() const = 0;
    virtual IDeck::CardsList getCardsForActivePlayer() const = 0;

    virtual void playerFinished(const IDeck::CardsList&) = 0;
  };
}
