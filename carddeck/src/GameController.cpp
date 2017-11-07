#include "GameController.h"

#include "PokerDeck.h"

using namespace CPoker;

CPoker::GameController::GameController()
  : m_round(IGameController::Round::WaitGameStart)
  , m_pPlayer1(nullptr)
  , m_pPlayer2(nullptr)
  , m_pPlayer3(nullptr)
  , m_pButton(nullptr)
  , m_pDeck(new PokerDeck())
{
  m_pDeck->shuffle();
}

void CPoker::GameController::startGame(std::vector<IPlayer*> apPlayers)
{
  while (m_round != Round::WaitPostGameFinish)
  {
    m_cardsDealtCb(m_pDeck->deal(5), apPlayers[0], Round::FiveCards);
  }
  m_gameFinishedCb;
}

void CPoker::GameController::playerDoneItsMove(IPlayer* pPlayer)
{
  m_round = nextRound();
}

void CPoker::GameController::setCardsDealtCallback(CardsDealtCallback dealtCardsCb)
{
  m_cardsDealtCb = dealtCardsCb;
}

void CPoker::GameController::setGameFinishedCallback(GameFinishedCallback gameFinishedCb)
{
  m_gameFinishedCb = gameFinishedCb;
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
