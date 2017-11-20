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
  drawDealButton();
  drawDeck();

  return true;
}

void TutorialStep1::drawBackground()
{
  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();

  auto sprite = Sprite::create("BackGround.png");
  sprite->setPosition(Vec2(visibleSize / 2) + origin);
  this->addChild(sprite);
}

void TutorialStep1::drawDealButton()
{
  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();

  m_pDealCardMenuItem = MenuItemImage::create(
    "PlayerDoneEnabled.png",
    "PlayerDoneClicked.png",
    "PlayerDoneDisabled.png",
    CC_CALLBACK_0(TutorialStep1::dealCard, this));

  m_pDealCardMenuItem->setPosition(origin.x - Vec2(m_pDealCardMenuItem->getContentSize() / 2).x + Vec2(visibleSize).x,
    origin.y + Vec2(m_pDealCardMenuItem->getContentSize() / 2).y);
  m_pDealCardMenuItem->setEnabled(true);

  auto menuRun = Menu::create(m_pDealCardMenuItem, nullptr);
  menuRun->setPosition(Vec2::ZERO);
  this->addChild(menuRun, 1);
}

void TutorialStep1::drawDeck()
{
  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();

  auto spriteDeck = Sprite::create(
    "cards_back.png"
  );

  spriteDeck->setPosition(origin.x + Vec2(spriteDeck->getContentSize() / 2).x + m_cFramePadding,
    origin.y + Vec2(visibleSize).y - Vec2(spriteDeck->getContentSize() / 2).y - m_cFramePadding);

  addChild(spriteDeck, 2);
}

//cb
void TutorialStep1::dealCard()
{
  drawCardBack();
  drawCardFront(false);
  animateCardDealing();
  initializeTouchListeners();
}

void TutorialStep1::drawCardBack()
{
  if (m_pDealtCardsBack.empty())
  {
    m_pDealtCardsBack.resize(3);
    m_pDealtCardsBack[0] = Sprite::create("cards_back.png");
    m_pDealtCardsBack[1] = Sprite::create("cards_back.png");
    m_pDealtCardsBack[2] = Sprite::create("cards_back.png");
    addChild(m_pDealtCardsBack[0], 3);
    addChild(m_pDealtCardsBack[1], 2);
    addChild(m_pDealtCardsBack[2], 1);
  }

  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();
  for (auto back : m_pDealtCardsBack)
  {
    back->setPosition(origin.x + Vec2(back->getContentSize() / 2).x + m_cFramePadding,
      origin.y + Vec2(visibleSize).y - Vec2(back->getContentSize() / 2).y - m_cFramePadding);
  }
}

void TutorialStep1::drawCardFront(bool visible)
{
  if (m_pDealtCardsFront.empty())
  {
    m_pDealtCardsFront.resize(3);
    m_pDealtCardsFront[0] = Sprite::create("cards_Ah.png");
    m_pDealtCardsFront[1] = Sprite::create("cards_Kh.png");
    m_pDealtCardsFront[2] = Sprite::create("cards_Qh.png");
    addChild(m_pDealtCardsFront[0], 4);
    addChild(m_pDealtCardsFront[1], 5);
    addChild(m_pDealtCardsFront[2], 6);
  }

  auto origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  for (auto sprite : m_pDealtCardsFront)
  {
    sprite->setPosition(origin.x + Vec2(visibleSize).x / 2,
      origin.y + Vec2(visibleSize).y - Vec2(sprite->getContentSize() / 2).y - m_cFramePadding);
    sprite->setVisible(visible);
  }
}

void TutorialStep1::animateCardDealing()
{
  auto disableDealBtn = CallFunc::create([this]()
  {
    m_pDealCardMenuItem->setEnabled(false);
  });

  auto origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 startPosition = m_pDealtCardsBack[0]->getPosition();
  Vec2 endPosition = m_pDealtCardsBack[0]->getPosition() + Vec2(Vec2(visibleSize).x - 2 * m_cFramePadding - Vec2(m_pDealtCardsBack[0]->getContentSize()).x, 0);
  auto deal1Actions = CPoker::GUICardDealer::dealCard(m_pDealtCardsFront[0], m_pDealtCardsBack[0], startPosition, endPosition);
  auto deal2Actions = CPoker::GUICardDealer::dealCard(m_pDealtCardsFront[1], m_pDealtCardsBack[1], startPosition, endPosition - Vec2(Vec2(m_pDealtCardsBack[0]->getContentSize()).x, 0));
  auto deal3Actions = CPoker::GUICardDealer::dealCard(m_pDealtCardsFront[2], m_pDealtCardsBack[2], startPosition, endPosition - 2 * Vec2(Vec2(m_pDealtCardsBack[0]->getContentSize()).x, 0));
  auto enableDealBtn = CallFunc::create([this]()
  {
    m_pDealCardMenuItem->setEnabled(true);
  });
  auto delayTime1 = DelayTime::create(0.1f);
  auto delayTime2 = DelayTime::create(0.2f);
  auto sequence1 = Sequence::create(disableDealBtn, deal1Actions, nullptr);
  auto sequence2 = Sequence::create(delayTime1, deal2Actions, nullptr);
  auto sequence3 = Sequence::create(delayTime2, deal3Actions, enableDealBtn, nullptr);
  m_pDealtCardsBack[0]->runAction(sequence1);
  m_pDealtCardsBack[1]->runAction(sequence2);
  m_pDealtCardsBack[2]->runAction(sequence3);
}

void TutorialStep1::initializeTouchListeners()
{
  auto eventListener = EventListenerTouchOneByOne::create();
  eventListener->setSwallowTouches(true);
  eventListener->onTouchBegan = CC_CALLBACK_2(TutorialStep1::onTouchBegan, this);
  eventListener->onTouchMoved = CC_CALLBACK_2(TutorialStep1::onTouchMoved, this);
  eventListener->onTouchEnded = CC_CALLBACK_2(TutorialStep1::onTouchEnded, this);

  _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, m_pDealtCardsFront[0]);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener->clone(), m_pDealtCardsFront[1]);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener->clone(), m_pDealtCardsFront[2]);
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
}

void TutorialStep1::onTouchEnded(Touch * touch, Event * event)
{
  auto activeSprite = static_cast<Sprite*>(event->getCurrentTarget());
  activeSprite->setPosition(m_movedSpriteInitPosition);
}
