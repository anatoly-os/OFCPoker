#include "PokerDeck.h"
#include "PokerCard.h"

#include <random>
#include <xutility>

using namespace CPoker;

CPoker::PokerDeck::PokerDeck()
{
  initializeFullDeck();
}

CPoker::PokerDeck::~PokerDeck()
{
  for (auto pCard : m_aCards)
    delete pCard;
  m_aCards.clear();

  for (auto pCard : m_aAlreadyDealtCards)
    delete pCard;
  m_aAlreadyDealtCards.clear();
}

void CPoker::PokerDeck::shuffle()
{
  /* 
  /  Fisher–Yates shuffle modern algo (wiki)
  /
  /  for i from n−1 downto 1 do
  /    j ← random integer such that 0 ≤ j ≤ i
  /    exchange a[j] and a[i]
  */

  //seed the RNG
  std::random_device rd;
  std::mt19937 mt(rd());

  int shuffledIdx = m_aCards.size() - 1;
  for (auto it = m_aCards.rbegin(); (shuffledIdx > 0) && (it != m_aCards.rend()); ++it, --shuffledIdx)
  {
    std::uniform_int_distribution<> dis(0, shuffledIdx);
    const int randomIndex = dis(mt);

    if (*it != m_aCards[randomIndex])
      std::swap(m_aCards[randomIndex], *it);
  }
}

IDeck::CardsList CPoker::PokerDeck::deal(const unsigned int numberOfCardsToDeal /*= 1*/)
{
  IDeck::CardsList alreadyDealtCards;
  if (m_aCards.empty())
    return alreadyDealtCards;

  for (unsigned int i = 0; i < numberOfCardsToDeal; ++i)
  {
    const auto& card = m_aCards[m_aCards.size() - 1];
    alreadyDealtCards.push_back(card);
    m_aAlreadyDealtCards.push_back(card);
    m_aCards.pop_back();
  }
  
  return alreadyDealtCards;
}

IDeck::CardsList CPoker::PokerDeck::cardsInDeck() const
{
  return m_aCards;
}

IDeck::CardsList CPoker::PokerDeck::dealtCards() const
{
  return m_aAlreadyDealtCards;
}

void CPoker::PokerDeck::initializeFullDeck()
{
  m_aCards.resize(52);
  static const int csSuitsCount = static_cast<int>(ICard::Suit::Count);
  static const int csValuesCount = static_cast<int>(ICard::Value::Count);
  for (unsigned int suit = 0; suit < csSuitsCount; ++suit)
    for (unsigned int value = 0; value < csValuesCount; ++value)
      m_aCards[value + suit * csValuesCount] = new PokerCard(static_cast<ICard::Suit>(suit), static_cast<ICard::Value>(value));
}
