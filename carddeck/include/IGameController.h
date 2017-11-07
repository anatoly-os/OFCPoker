#pragma once

#include "IPlayer.h"

#include <vector>
#include <functional>

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

    using CardsDealtCallback = std::function<void(IPlayer*, Round)>;
    using GameFinishedCallback = std::function<void(bool)>;

    //call to start a game
    virtual void startGame(std::vector<IPlayer*>) = 0;

    //call to continue game after player is done his/her move
    virtual void playerDoneItsMove(IPlayer*) = 0;

    //callback to react on dealing cards to a player
    virtual void cardsDealt(CardsDealtCallback) = 0;

    //callback to react on finishing game
    //@bool - shows whether next round is fantasy round
    virtual void gameFinished(GameFinishedCallback) = 0;
  };
}
