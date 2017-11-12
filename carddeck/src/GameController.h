#pragma once

#include "../include/IGameController.h"

#include <memory>

namespace CPoker
{
  class GameController : public IGameController
  {
  public:
    GameController();
    
    void startGame(std::vector<IPlayer::ID>) override;
    IPlayer::ID button() const override;
    PlayerStates playerStates() const override;

    Round round() const override;
    IPlayer::ID activePlayer() const override;
    IDeck::CardsList getCardsForActivePlayer() const override;

    virtual void playerFinished(const IPlayer::ID&) const override;

  private:
    Round nextRound();

  private:
    //non copyable
    GameController(const GameController&) = delete;
    GameController& operator=(const GameController&) = delete;

  private:
    IGameController::Round m_round;

    std::unique_ptr<IPlayer> m_pPlayer1; //optional
    std::unique_ptr<IPlayer> m_pPlayer2; //optional
    std::unique_ptr<IPlayer> m_pPlayer3; //optional
    IPlayer::ID m_button;

    std::unique_ptr<IDeck> m_pDeck;
  };
}
