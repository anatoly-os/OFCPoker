#include "GameController.h"

#include "PokerDeck.h"
#include "Player.h"

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

void CPoker::GameController::startGame(const std::vector<IPlayer::ID>& ids)
{
  m_pDeck.reset(new PokerDeck());
  m_pDeck->shuffle();
  m_round = IGameController::Round::WaitGameStart;

  m_pPlayer1.reset(new Player(ids[0].id));
  m_pPlayer2.reset(new Player(ids[1].id));
  m_button = m_pPlayer1->id();
  m_activePlayer = m_pPlayer2->id();
  //temp double nextRound() to skip fantasy
  m_round = nextRound();
  m_round = nextRound();
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
  return m_round;
}

IPlayer::ID CPoker::GameController::activePlayer() const
{
  return m_activePlayer;
}

IDeck::CardsList CPoker::GameController::getCardsForActivePlayer() const
{
  switch (m_round)
  {
  case Round::FiveCards:
  {
    return m_pDeck->deal(5);
  }
  case Round::ThreeCards1:
  case Round::ThreeCards2:
  case Round::ThreeCards3:
  case Round::ThreeCards4:
    return m_pDeck->deal(3);
  default:
    return IDeck::CardsList();
  }
}

void CPoker::GameController::playerFinished(const IDeck::CardsList& chosenCards)
{
  //test case - add all cards to the top row
  //test case - no fantasies so active player is next player
  if (m_pPlayer1->id() == activePlayer())
  {
    m_pPlayer1->setTopRowCards(chosenCards);
    m_activePlayer = m_pPlayer2->id();
  }
  else if (m_pPlayer2->id() == activePlayer())
  {
    m_pPlayer2->setTopRowCards(chosenCards);
    m_activePlayer = m_pPlayer1->id();
  }
  
  switch (m_round)
  {
  case Round::FiveCards:
  {
    if (m_pPlayer1->ingameCardsCount() == 5 &&
        m_pPlayer2->ingameCardsCount() == 5)
      m_round = nextRound();
    break;
  }
  case Round::ThreeCards1:
  {
    if (m_pPlayer1->ingameCardsCount() == 7 &&
      m_pPlayer2->ingameCardsCount() == 7)
      m_round = nextRound();
    break;
  }
  case Round::ThreeCards2:
  {
    if (m_pPlayer1->ingameCardsCount() == 9 &&
      m_pPlayer2->ingameCardsCount() == 9)
      m_round = nextRound();
    break;
  }
  case Round::ThreeCards3:
  {
    if (m_pPlayer1->ingameCardsCount() == 11 &&
      m_pPlayer2->ingameCardsCount() == 11)
      m_round = nextRound();
    break;
  }
  case Round::ThreeCards4:
  {
    if (m_pPlayer1->ingameCardsCount() == 13 &&
      m_pPlayer2->ingameCardsCount() == 13)
      m_round = nextRound();
    break;
  }
  default:
    m_round = nextRound();
  }
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
