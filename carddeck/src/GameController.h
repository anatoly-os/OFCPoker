#pragma once

#include "../include/IGameController.h"

#include <map>

namespace CPoker
{
  class GameController : public IGameController
  {
  public:
    GameController();
    
    void startGame(std::vector<IPlayer*> apPlayers) override;
    void playerDoneItsMove(IPlayer* pPlayer) override;

    void cardsDealt(CardsDealtCallback dealtCardsCb) override;
    void gameFinished(GameFinishedCallback gameFinishedCb) override;

  private:
    enum class IngamePlayerStatus
    {
      WaitForGameStart,
      WaitForFantasy,
      WaitForCards,
      WaitForPostGameFinish
    };

  private:
    //non copyable
    GameController(const GameController&) = delete;
    GameController& operator=(const GameController&) = delete;

  private:
    IGameController::Round m_round;
    IPlayer* m_pPlayer1; //optional
    IPlayer* m_pPlayer2; //optional
    IPlayer* m_pPlayer3; //optional
    IPlayer* m_pButton;
    std::map<IPlayer*, IngamePlayerStatus> m_playersStatuses;
  };
}
