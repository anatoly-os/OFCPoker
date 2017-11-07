#pragma once

#include "../include/IGameController.h"
#include "../include/IDeck.h"

#include <map>
#include <memory>

namespace CPoker
{
  class GameController : public IGameController
  {
  public:
    GameController();
    
    void startGame(std::vector<IPlayer*> apPlayers) override;
    void playerDoneItsMove(IPlayer* pPlayer) override;

    void setCardsDealtCallback(CardsDealtCallback dealtCardsCb) override;
    void setGameFinishedCallback(GameFinishedCallback gameFinishedCb) override;

  private:
    enum class IngamePlayerStatus
    {
      WaitForGameStart,
      WaitForFantasy,
      WaitForCards,
      WaitForPostGameFinish
    };

    Round nextRound();

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
    std::unique_ptr<IDeck> m_pDeck;

    CardsDealtCallback m_cardsDealtCb;
    GameFinishedCallback m_gameFinishedCb;
  };
}
