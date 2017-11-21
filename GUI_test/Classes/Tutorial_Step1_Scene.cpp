#include "Tutorial_Step1_Scene.h"
#include "GUICardDealer.h"

USING_NS_CC;

Scene * TutorialStep1::scene()
{
  return TutorialStep1::create();
}

bool TutorialStep1::init()
{
  if (!Scene::init())
    return false;

  drawBackground();
  drawDeck();
  drawCardHolders();

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

  m_pCardDeck = MenuItemImage::create("cards_back.png", "cards_back.png", CC_CALLBACK_0(TutorialStep1::dealCard, this));
  m_pCardDeck->setPosition(origin.x + Vec2(m_pCardDeck->getContentSize() / 2).x + m_cFramePadding,
    origin.y + Vec2(visibleSize).y - Vec2(m_pCardDeck->getContentSize() / 2).y - m_cFramePadding);

  auto menuRun = Menu::create(m_pCardDeck, nullptr);
  menuRun->setPosition(Vec2::ZERO);
  addChild(menuRun, 2);
}

//cb
void TutorialStep1::dealCard()
{
  drawCardBack();
  drawCardFront();
  animateCardDealing();
}

void TutorialStep1::drawCardBack()
{
  if (m_pDealtCardsBack.empty())
  {
    m_pDealtCardsBack.resize(3);
    m_pDealtCardsBack[0] = Sprite::create("cards_back.png");
    m_pDealtCardsBack[1] = Sprite::create("cards_back.png");
    m_pDealtCardsBack[2] = Sprite::create("cards_back.png");
    for (auto& card : m_pDealtCardsBack)
      addChild(card, 1);
  }

  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();
  for (auto& back : m_pDealtCardsBack)
  {
    back->setPosition(origin.x + Vec2(back->getContentSize() / 2).x + m_cFramePadding,
      origin.y + Vec2(visibleSize).y - Vec2(back->getContentSize() / 2).y - m_cFramePadding);
  }
}

void TutorialStep1::drawCardFront()
{
  if (m_pDealtCardsFront.empty())
  {
    m_pDealtCardsFront.resize(3);

    m_pDealtCardsFront[0] = Sprite::create("cards_Ah.png");
    m_pDealtCardsFront[1] = Sprite::create("cards_Kh.png");
    m_pDealtCardsFront[2] = Sprite::create("cards_Qh.png");
    for (auto& sprite : m_pDealtCardsFront)
      addChild(sprite, 5);   
  }

  auto origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  for (auto& sprite : m_pDealtCardsFront)
  {
    sprite->setPosition(origin.x + Vec2(visibleSize).x / 2,
      origin.y + Vec2(visibleSize).y - Vec2(sprite->getContentSize() / 2).y - m_cFramePadding);
    sprite->setVisible(false);
  }

  //find proper place for event listeners initialization
  m_pTouchEventListener = EventListenerTouchOneByOne::create();
  m_pTouchEventListener->setSwallowTouches(true);
  m_pTouchEventListener->onTouchBegan = CC_CALLBACK_2(TutorialStep1::onTouchBegan, this);
  m_pTouchEventListener->onTouchMoved = CC_CALLBACK_2(TutorialStep1::onTouchMoved, this);
  m_pTouchEventListener->onTouchEnded = CC_CALLBACK_2(TutorialStep1::onTouchEnded, this);

  _eventDispatcher->addEventListenerWithSceneGraphPriority(m_pTouchEventListener, m_pDealtCardsFront[0]);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(m_pTouchEventListener->clone(), m_pDealtCardsFront[1]);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(m_pTouchEventListener->clone(), m_pDealtCardsFront[2]);
}

void TutorialStep1::animateCardDealing()
{
  auto origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 startPosition = m_pDealtCardsBack[0]->getPosition();
  Vec2 endPosition = m_pDealtCardsBack[0]->getPosition() + Vec2(Vec2(visibleSize).x - 2 * m_cFramePadding - Vec2(m_pDealtCardsBack[0]->getContentSize()).x, 0);
  FiniteTimeAction* deal1Actions = CPoker::GUICardDealer::dealCard(m_pDealtCardsFront[0], m_pDealtCardsBack[0], startPosition, endPosition);
  FiniteTimeAction* deal2Actions = CPoker::GUICardDealer::dealCard(m_pDealtCardsFront[1], m_pDealtCardsBack[1], startPosition, endPosition - Vec2(Vec2(m_pDealtCardsBack[0]->getContentSize()).x, 0));
  FiniteTimeAction* deal3Actions = CPoker::GUICardDealer::dealCard(m_pDealtCardsFront[2], m_pDealtCardsBack[2], startPosition, endPosition - 2 * Vec2(Vec2(m_pDealtCardsBack[0]->getContentSize()).x, 0));
  FiniteTimeAction* delayTime1 = DelayTime::create(0.1f);
  FiniteTimeAction* delayTime2 = DelayTime::create(0.2f);
  auto sequence2 = Sequence::create(delayTime1, deal2Actions, nullptr);
  auto sequence3 = Sequence::create(delayTime2, deal3Actions, nullptr);
  m_pDealtCardsBack[0]->runAction(deal1Actions);
  m_pDealtCardsBack[1]->runAction(sequence2);
  m_pDealtCardsBack[2]->runAction(sequence3);
}

void TutorialStep1::drawCardHolders()
{
  if (m_pCardsHolders.empty())
  {
    m_pCardsHolders.resize(3);
    for (auto& holder : m_pCardsHolders)
      holder.resize(3);

    for (auto& holder : m_pCardsHolders)
    {
      holder[0] = Sprite::create("cards_place.png");
      holder[0]->setOpacity(50);
      holder[1] = Sprite::create("cards_frame.png");
      holder[2] = Sprite::create("cards_frame_h.png");
      for (auto& inHolders : holder)
        addChild(inHolders, 4);
    }
  }

  auto origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  for (size_t i = 0; i < m_pCardsHolders.size(); ++i)
  {
    auto holderPics = m_pCardsHolders[i];
    Vec2 holderPosition{ origin.x + 2 * m_cFramePadding + (1 + i * 2) * Vec2(holderPics[0]->getContentSize() / 2).x,
                         origin.y + m_cFramePadding + Vec2(holderPics[0]->getContentSize() / 2).y };
    for (auto& inHolders : holderPics)
    {
      inHolders->setPosition(holderPosition);
      inHolders->setVisible(true);
    }

    holderPics[2]->setVisible(false);
  }
}

bool TutorialStep1::onTouchBegan(Touch * touch, Event * event)
{
  auto activeSprite = static_cast<Sprite*>(event->getCurrentTarget());
  if (!activeSprite->getBoundingBox().containsPoint(touch->getLocation()))
    return false;

  m_movedSpriteInitPosition = activeSprite->getPosition();
  m_initialTouchPosition = touch->getLocation();
  return true;
}

void TutorialStep1::onTouchMoved(Touch * touch, Event * event)
{
  auto activeSprite = static_cast<Sprite*>(event->getCurrentTarget());
  activeSprite->setPosition(m_movedSpriteInitPosition + touch->getLocation() - m_initialTouchPosition);

  for (auto& holder : m_pCardsHolders)
  {
    if (activeSprite->getBoundingBox().containsPoint(holder[0]->getPosition()))
    {
      holder[1]->setVisible(false);
      holder[2]->setVisible(true);
    }
    else
    {
      holder[1]->setVisible(true);
      holder[2]->setVisible(false);
    }
  }
}

void TutorialStep1::onTouchEnded(Touch * touch, Event * event)
{
  auto activeSprite = static_cast<Sprite*>(event->getCurrentTarget());
  
  bool cardPlacedInHolder = false;
  for (auto& holder : m_pCardsHolders)
  {
    if (activeSprite->getBoundingBox().containsPoint(holder[0]->getPosition()))
    {
      activeSprite->setPosition(holder[0]->getPosition());
      cardPlacedInHolder = true;
    }      
  }

  if (!cardPlacedInHolder)
    activeSprite->setPosition(m_movedSpriteInitPosition);
  
  for (auto& holder : m_pCardsHolders)
  {
    holder[1]->setVisible(true);
    holder[2]->setVisible(false);
  }
}
