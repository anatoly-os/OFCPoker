#pragma once

#include "../include/IGameController.h"

#include <memory>

namespace CPoker
{
  class GameController : public IGameController
  {
  public:
    GameController();
    
    void startGame(const std::vector<IPlayer::ID>&) override;
    IPlayer::ID button() const override;
    PlayerStates playerStates() const override;

    Round round() const override;
    IPlayer::ID activePlayer() const override;
    IDeck::CardsList dealCardsForActivePlayer() const override;

    IDeck::CardsList playerIngameCards(const IPlayer::ID&) const override;

    void playerFinished(const IDeck::CardsList& top, const IDeck::CardsList& mid, const IDeck::CardsList& bottom) override;

  private:
    Round nextRound();

  private:
    //non copyable
    GameController(const GameController&) = delete;
    GameController& operator=(const GameController&) = delete;

  private:
    IGameController::Round m_round;

    std::unique_ptr<IPlayer> m_pPlayer1;
    std::unique_ptr<IPlayer> m_pPlayer2;
    std::unique_ptr<IPlayer> m_pPlayer3;
    IPlayer::ID m_activePlayer;
    IPlayer::ID m_button;

    std::unique_ptr<IDeck> m_pDeck;
  };
}
