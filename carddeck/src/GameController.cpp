#include "GameController.h"

#include "PokerDeck.h"

using namespace CPoker;

CPoker::GameController::GameController()
  : m_round(IGameController::Round::WaitGameStart)
  , m_pPlayer1(nullptr)
  , m_pPlayer2(nullptr)
  , m_pPlayer3(nullptr)
  , m_pDeck(new PokerDeck())
{
  m_pDeck->shuffle();
}

void CPoker::GameController::startGame(std::vector<IPlayer::ID>)
{
}

IPlayer::ID CPoker::GameController::button() const
{
  return m_button;
}

IGameController::PlayerStates CPoker::GameController::playerStates() const
{
  return PlayerStates();
}

IGameController::Round CPoker::GameController::round() const
{
  return Round();
}

IPlayer::ID CPoker::GameController::activePlayer() const
{
  return IPlayer::ID();
}

IDeck::CardsList CPoker::GameController::getCardsForActivePlayer() const
{
  return IDeck::CardsList();
}

void CPoker::GameController::playerFinished(const IPlayer::ID& id) const
{
}

CPoker::IGameController::Round CPoker::GameController::nextRound()
{
  switch (m_round)
  {
  case Round::WaitGameStart: return Round::Fantasy;
  case Round::Fantasy: return Round::FiveCards;
  case Round::FiveCards: return Round::ThreeCards1;
  case Round::ThreeCards1: return Round::ThreeCards2;
  case Round::ThreeCards2: return Round::ThreeCards3;
  case Round::ThreeCards3: return Round::ThreeCards4;
  case Round::ThreeCards4: return Round::WaitPostGameFinish;
  case Round::WaitPostGameFinish: return Round::WaitGameStart;
  default:
    return Round::WaitGameStart;
  }
}
