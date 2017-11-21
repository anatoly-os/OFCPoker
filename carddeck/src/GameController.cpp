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
  m_button = m_pPlayer1->id();
  m_activePlayer = m_pPlayer1->id();
  //temp double nextRound() to skip fantasy
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

IDeck::CardsList CPoker::GameController::dealCardsForActivePlayer() const
{
  switch (m_round)
  {
  case Round::Fantasy:
    return m_pDeck->deal(14);
  case Round::FiveCards:
    return m_pDeck->deal(5);
  case Round::ThreeCards1:
  case Round::ThreeCards2:
  case Round::ThreeCards3:
  case Round::ThreeCards4:
    return m_pDeck->deal(3);
  default:
    return IDeck::CardsList();
  }
}

IDeck::CardsList CPoker::GameController::playerIngameCards(const IPlayer::ID& playerId) const
{
  if (playerId == m_pPlayer1->id())
    return m_pPlayer1->ingameCards();
  else if (playerId == m_pPlayer2->id())
    return m_pPlayer2->ingameCards();
  else if (playerId == m_pPlayer3->id())
    return m_pPlayer3->ingameCards();

  return IDeck::CardsList();
}

void CPoker::GameController::playerFinished(const IDeck::CardsList& chosenCards)
{
  //temp decision for 1st MVP
  m_pPlayer1->setTopRowCards(chosenCards);

  /*
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
  */

  //temp decision for 1st MVP
  const int ingameCardsCountPlr1 = m_pPlayer1->ingameCards().size();
  switch (m_round)
  {
  case Round::ThreeCards1:
  {
    if (ingameCardsCountPlr1 == 2)
      m_round = nextRound();
    break;
  }
  case Round::ThreeCards2:
  {
    if (ingameCardsCountPlr1 == 3)
      m_round = nextRound();
    break;
  }
  default:
    m_round = nextRound();
  }

  /*
  const int ingameCardsCountPlr1 = m_pPlayer1->ingameCards().size();
  const int ingameCardsCountPlr2 = m_pPlayer2->ingameCards().size();
  switch (m_round)
  {
  case Round::FiveCards:
  {
    if (ingameCardsCountPlr1 == 5 && ingameCardsCountPlr2 == 5)
      m_round = nextRound();
    break;
  }
  case Round::ThreeCards1:
  {
    if (ingameCardsCountPlr1 == 7 && ingameCardsCountPlr2 == 7)
      m_round = nextRound();
    break;
  }
  case Round::ThreeCards2:
  {
    if (ingameCardsCountPlr1 == 9 && ingameCardsCountPlr2 == 9)
      m_round = nextRound();
    break;
  }
  case Round::ThreeCards3:
  {
    if (ingameCardsCountPlr1 == 11 && ingameCardsCountPlr2 == 11)
      m_round = nextRound();
    break;
  }
  case Round::ThreeCards4:
  {
    if (ingameCardsCountPlr1 == 13 && ingameCardsCountPlr2 == 13)
      m_round = nextRound();
    break;
  }
  default:
    m_round = nextRound();
  }
  */
}

CPoker::IGameController::Round CPoker::GameController::nextRound()
{
  //temp decision for 1st MVP
  switch (m_round)
  {
  case Round::WaitGameStart: return Round::ThreeCards1;
  case Round::ThreeCards1: return Round::ThreeCards2;
  case Round::WaitPostGameFinish: return Round::WaitGameStart;
  default:
    return Round::WaitGameStart;
  }
  /*
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
  */
}
