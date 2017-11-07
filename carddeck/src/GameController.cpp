#include "GameController.h"

using namespace CPoker;

CPoker::GameController::GameController()
  : m_round(IGameController::Round::WaitGameStart)
  , m_pPlayer1(nullptr)
  , m_pPlayer2(nullptr)
  , m_pPlayer3(nullptr)
  , m_pButton(nullptr)
{
}

void CPoker::GameController::startGame(std::vector<IPlayer*> apPlayers)
{
}

void CPoker::GameController::playerDoneItsMove(IPlayer* pPlayer)
{
}

void CPoker::GameController::cardsDealt(CardsDealtCallback dealtCardsCb)
{
  return dealtCardsCb(m_pPlayer1, IGameController::Round::FiveCards);
}

void CPoker::GameController::gameFinished(GameFinishedCallback gameFinishedCb)
{
  //bool isFantasy = calculateFantasyCase();
  return gameFinishedCb(false);
}
