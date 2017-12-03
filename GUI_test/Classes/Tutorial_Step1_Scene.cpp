#include "Tutorial_Step1_Scene.h"
#include "GUICardDealer.h"

#include "carddeck\include\GameControllerCreator.h"
#include "carddeck\include\IPlayer.h"
#include "carddeck\include\IDeck.h"

#include <future>

USING_NS_CC;

Scene * TutorialStep1::scene()
{
  return TutorialStep1::create();
}

bool TutorialStep1::init()
{
  if (!Scene::init())
    return false;

  m_pGameController = CPoker::GameControllerCreator::create();
  m_playerId = CPoker::IPlayer::ID(1);

  drawBackground();
  drawDeck();
  drawCardHolders();
  drawSelectFrame();

  drawButtons();

  return true;
}

void TutorialStep1::drawBackground()
{
  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();

  auto sprite = Sprite::create("BackGround.png");
  sprite->setPosition(Vec2(visibleSize / 2) + origin);
  this->addChild(sprite, -1);
}

void TutorialStep1::drawDeck()
{
  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();

  m_pCardDeck = Sprite::create("cards_back.png");
  m_pCardDeck->setPosition(origin.x + Vec2(m_pCardDeck->getContentSize() / 2).x + m_cFramePadding,
    origin.y + Vec2(visibleSize).y - Vec2(m_pCardDeck->getContentSize() / 2).y - m_cFramePadding);
  addChild(m_pCardDeck, 2);
}

void TutorialStep1::drawDealtCardsBack()
{
  if (m_pDealtCardsBack.empty())
  {
    for (size_t i = 0; i < 3; ++i)
    {
      auto pCard = Sprite::create("cards_back.png");
      m_pDealtCardsBack.insert(pCard);
      addChild(pCard, 3);
    }    
  }

  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();
  for (auto& back : m_pDealtCardsBack)
  {
    back->setPosition(origin.x + Vec2(back->getContentSize() / 2).x + m_cFramePadding,
      origin.y + Vec2(visibleSize).y - Vec2(back->getContentSize() / 2).y - m_cFramePadding);
  }
}

void TutorialStep1::drawDealtCardsFront(const CPoker::IDeck::CardsList& cards)
{
  auto origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  if (m_pDealtCardsFront.empty())
  {
    for (size_t i = 0; i < cards.size(); ++i)
    {
      auto sprite = Sprite::create(std::string("cards_") + cards[i]->toString() + std::string(".png"));
      m_pDealtCardsFront.insert(sprite);
      m_cardsConvertor[sprite] = cards[i];
      sprite->setVisible(false);
      addChild(sprite, 20);
    }
  }

  //find proper place for event listeners initialization
  if (!m_pTouchEventListener)
  {
    m_pTouchEventListener = EventListenerTouchOneByOne::create();
    m_pTouchEventListener->setSwallowTouches(true);
    m_pTouchEventListener->onTouchBegan = CC_CALLBACK_2(TutorialStep1::onTouchBegan, this);
    m_pTouchEventListener->onTouchMoved = CC_CALLBACK_2(TutorialStep1::onTouchMoved, this);
    m_pTouchEventListener->onTouchEnded = CC_CALLBACK_2(TutorialStep1::onTouchEnded, this);
    m_dummySpriteNotToReleaseTouchListener = Sprite::create();
    m_dummySpriteNotToReleaseTouchListener->setVisible(false);
    addChild(m_dummySpriteNotToReleaseTouchListener);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(m_pTouchEventListener, m_dummySpriteNotToReleaseTouchListener);
  }

  for (auto& card : m_pDealtCardsFront)
    _eventDispatcher->addEventListenerWithSceneGraphPriority(m_pTouchEventListener->clone(), card);
}

void TutorialStep1::animateCardDealing()
{
  std::vector<FiniteTimeAction*> dealActions;
  auto frontCardsIt = m_pDealtCardsFront.begin();
  auto backCardsIt = m_pDealtCardsBack.begin();
  auto holderIt = m_dealtCardsHolders.begin();
  Vec2 startPosition = (*m_pDealtCardsBack.begin())->getPosition();
  while (frontCardsIt != m_pDealtCardsFront.end() ||
         backCardsIt != m_pDealtCardsBack.end())
  {
    dealActions.push_back(CPoker::GUICardDealer::dealCard(*frontCardsIt, *backCardsIt, startPosition, (*holderIt)->getPosition()));
    ++frontCardsIt;
    ++backCardsIt;
    ++holderIt;
  }
    
  FiniteTimeAction* delayTime1 = DelayTime::create(0.1f);
  FiniteTimeAction* delayTime2 = DelayTime::create(0.2f);
  auto sequence2 = Sequence::create(delayTime1, dealActions[1], nullptr);
  auto sequence3 = Sequence::create(delayTime2, dealActions[2], nullptr);
  std::vector<FiniteTimeAction*> sequences = { dealActions[0], sequence2, sequence3 };
  auto actIt = sequences.begin();
  for (auto& backCard : m_pDealtCardsBack)
  {
    backCard->runAction(*actIt);
    ++actIt;
  }
}

void TutorialStep1::drawCardHolders()
{
  drawPlayerCardsHolders();
  drawDealtCardsHolders();
}

void TutorialStep1::drawPlayerCardsHolders()
{
  if (m_pCardsHolders.empty())
  {
    for (size_t i = 0; i < 3; ++i)
    {
      auto pCard = Sprite::create("cards_place.png");
      m_pCardsHolders.insert(pCard);
      addChild(pCard, 2);
    }
  }

  auto origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  int shiftMult = 0;
  for (auto& card : m_pCardsHolders)
  {
    Vec2 holderPosition{ origin.x + (2 + shiftMult) * m_cFramePadding + (1 + shiftMult * 2) * Vec2(card->getContentSize() / 2).x,
      origin.y + m_cFramePadding + Vec2(card->getContentSize() / 2).y };
    card->setPosition(holderPosition);
    ++shiftMult;
  }
}

void TutorialStep1::drawDealtCardsHolders()
{
  if (m_dealtCardsHolders.empty())
  {
    for (size_t i = 0; i < 3; ++i)
    {
      auto pCard = Sprite::create("cards_place.png");
      m_dealtCardsHolders.insert(pCard);
      addChild(pCard, 2);
    }
  }

  auto origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  int shiftMult = 0;
  for (auto& card : m_dealtCardsHolders)
  {
    Vec2 holderPosition{ m_pCardDeck->getPositionX() + Vec2(visibleSize).x - (1 + shiftMult) * Vec2(m_pCardDeck->getContentSize()).x - (2 + shiftMult) * m_cFramePadding,
      m_pCardDeck->getPositionY() };
    card->setPosition(holderPosition);
    card->setVisible(true);
    //card->setVisible(false);
    ++shiftMult;
  }
}

void TutorialStep1::drawSelectFrame()
{
  m_pCardFrame = Sprite::create("cards_frame_h.png");
  m_pCardFrame->setOpacity(150);
  addChild(m_pCardFrame, 3);
  m_pCardFrame->setVisible(false);
}

void TutorialStep1::drawNewGameButton()
{
  m_pNewGameButton = MenuItemImage::create(
    "NewGame.png",
    "NewGame.png",
    "NewGame_dis.png",
    CC_CALLBACK_0(TutorialStep1::startGame, this));

  m_pNewGameButton->setPosition(m_pReadyButton->getPositionX(), m_pReadyButton->getPositionY() + Vec2(m_pNewGameButton->getContentSize()).y + m_cFramePadding);

  auto menu = Menu::create(m_pNewGameButton, nullptr);
  menu->setPosition(Vec2::ZERO);
  addChild(menu, 10);
}

void TutorialStep1::drawReadyButton()
{
  m_pReadyButton = MenuItemImage::create(
    "Ready.png",
    "Ready.png",
    "Ready_dis.png",
    CC_CALLBACK_0(TutorialStep1::playerIsReady, this));

  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();
  m_pReadyButton->setPosition(origin.x + Vec2(visibleSize).x - Vec2(m_pReadyButton->getContentSize() / 2).x - m_cFramePadding,
    origin.y + Vec2(m_pReadyButton->getContentSize() / 2).y + 2 * m_cFramePadding);
  m_pReadyButton->setEnabled(false);

  auto menu = Menu::create(m_pReadyButton, nullptr);
  menu->setPosition(Vec2::ZERO);
  addChild(menu, 10);
}

void TutorialStep1::drawButtons()
{
  //order matters! positions depend on previously added buttons
  drawReadyButton();
  drawNewGameButton();
}

void TutorialStep1::clearCards()
{
  for (auto& card : m_pDealtCardsFront)
    removeChild(card);
  m_pDealtCardsFront.clear();

  for (auto& card : m_playerCards)
    removeChild(card);
  m_playerCards.clear();
}

bool TutorialStep1::onTouchBegan(Touch * touch, Event * event)
{
  auto activeSprite = static_cast<Sprite*>(event->getCurrentTarget());
  if (!activeSprite->getBoundingBox().containsPoint(touch->getLocation()))
    return false;

  m_initialDragCardPosition = activeSprite->getPosition();
  m_initialDragTouchPosition = touch->getLocation();
  activeSprite->setLocalZOrder(100);
  return true;
}

TutorialStep1::SpritePtr TutorialStep1::checkIntersection(SpritePtr pActiveCard, SpritesArray sprites)
{
  sprites.erase(pActiveCard);

  SpritePtr pHolderToPlaceIn = nullptr;
  auto it = std::find_if(sprites.begin(), sprites.end(), [pActiveCard](auto& holder)
  {
    return pActiveCard->getBoundingBox().containsPoint(holder->getPosition());
  });

  if (it != sprites.end())
    pHolderToPlaceIn = *it;

  return pHolderToPlaceIn;
}

void TutorialStep1::onTouchMoved(Touch * touch, Event * event)
{
  auto activeSprite = static_cast<Sprite*>(event->getCurrentTarget());
  activeSprite->setPosition(m_initialDragCardPosition + touch->getLocation() - m_initialDragTouchPosition);

  auto pHolderToPlaceIn = checkIntersection(activeSprite, m_pCardsHolders);
  if (!pHolderToPlaceIn)
    pHolderToPlaceIn = checkIntersection(activeSprite, m_dealtCardsHolders);

  if (pHolderToPlaceIn)
  {
    m_pCardFrame->setVisible(true);
    m_pCardFrame->setPosition(pHolderToPlaceIn->getPosition());
  }
  else
    m_pCardFrame->setVisible(false);
}

void TutorialStep1::onTouchEnded(Touch * touch, Event * event)
{
  auto activeSprite = static_cast<Sprite*>(event->getCurrentTarget());
  
  auto pHolderToPlaceIn = checkIntersection(activeSprite, m_pCardsHolders);
  if (pHolderToPlaceIn)
  {
    //if place card to card holder
    //  if previously placed player card in cardholder: place active to initial position
    //  else if active card in cardholder: swap active with underlying
    //  else: place card to cardholder
    if (checkIntersection(activeSprite, m_playerCards))
      activeSprite->setPosition(m_initialDragCardPosition);
    else
    {
      auto intersecedWithCard = checkIntersection(activeSprite, m_activePlayerCards);
      if (intersecedWithCard)
      {
        activeSprite->setPosition(pHolderToPlaceIn->getPosition());
        intersecedWithCard->setPosition(m_initialDragCardPosition);
        //active card is from dealt cards
        if (0 == m_activePlayerCards.count(activeSprite))
        {
          m_activePlayerCards.erase(intersecedWithCard);
          m_activePlayerCards.insert(activeSprite);
        }
      }
      else
      {
        activeSprite->setPosition(pHolderToPlaceIn->getPosition());
        //active card is from dealt cards
        if (0 == m_activePlayerCards.count(activeSprite))
          m_activePlayerCards.insert(activeSprite);

        if (m_activePlayerCards.size() == 3)
        {
          auto playerCardsWithoutActive = m_activePlayerCards;
          playerCardsWithoutActive.erase(activeSprite);
          auto leftmostcard = std::min_element(playerCardsWithoutActive.begin(), playerCardsWithoutActive.end(), [](auto& card1, auto& card2)
          {
            return card1->getPosition() < card2->getPosition();
          });
          (*leftmostcard)->setPosition(m_initialDragCardPosition);
          m_activePlayerCards.erase(*leftmostcard);
        }
      }      
    }
  }
  else
  {
    //place card not to placeholder
    pHolderToPlaceIn = checkIntersection(activeSprite, m_dealtCardsHolders);
    if (pHolderToPlaceIn)
    {
      m_activePlayerCards.erase(activeSprite);

      //place card to dealt cards placeholder
      //if intersects with dealt card: swap cards
      //else: place
      auto intersecedWithCard = checkIntersection(activeSprite, m_pDealtCardsFront);
      if (intersecedWithCard)
      {
        activeSprite->setPosition(pHolderToPlaceIn->getPosition());
        intersecedWithCard->setPosition(m_initialDragCardPosition);
      }
      else
        activeSprite->setPosition(pHolderToPlaceIn->getPosition());
    }
    else
      //no placeholders selected: place to initial position
      activeSprite->setPosition(m_initialDragCardPosition);
  }

  if (m_pGameController->round() == CPoker::IGameController::Round::ThreeCards1 && m_activePlayerCards.size() == 2)
    m_pReadyButton->setEnabled(true);
  else if (m_pGameController->round() == CPoker::IGameController::Round::ThreeCards2 &&
    m_playerCards.size() == 2 &&
    m_activePlayerCards.size() == 1)
    m_pReadyButton->setEnabled(true);
  else
    m_pReadyButton->setEnabled(false);

  activeSprite->setLocalZOrder(20);
  m_pCardFrame->setVisible(false);
}

void TutorialStep1::nextMove()
{
  if (m_pGameController->round() != CPoker::IGameController::Round::WaitPostGameFinish)
  {
    dealCards();
  }
  else
  {
    m_pNewGameButton->setEnabled(true);
  }
}

void TutorialStep1::startGame()
{
  m_pNewGameButton->setEnabled(false);
  clearCards();

  std::vector<CPoker::IPlayer::ID> players{ m_playerId };
  m_pGameController->startGame(players);
  nextMove();
}

void TutorialStep1::playerIsReady()
{
  m_pReadyButton->setEnabled(false);
  CPoker::IDeck::CardsList chosenCards;
  for (auto& card : m_pDealtCardsFront)
  {
    if (m_activePlayerCards.end() == m_activePlayerCards.find(card))
      removeChild(card);
    else
    {
      _eventDispatcher->pauseEventListenersForTarget(card);
      card->setColor(Color3B::GRAY);
      chosenCards.push_back(m_cardsConvertor[card]);
    }      
  }
  m_pDealtCardsFront.clear();

  m_playerCards.insert(m_activePlayerCards.begin(), m_activePlayerCards.end());
  m_activePlayerCards.clear();

  m_pGameController->playerFinished(chosenCards);
  nextMove();
}

void TutorialStep1::dealCards()
{
  auto dealtCards = m_pGameController->dealCardsForActivePlayer();
  drawDealtCardsBack();
  drawDealtCardsFront(dealtCards);
  animateCardDealing();
}
