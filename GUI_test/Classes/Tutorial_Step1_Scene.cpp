#include "Tutorial_Step1_Scene.h"

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
  m_pDealtCardBack->setVisible(true);

  drawCardFront();
  m_pDealtCardFront->setVisible(false);

  animateCardDealing();
}

void TutorialStep1::drawCardBack()
{
  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();

  m_pDealtCardBack = Sprite::create(
    "cards_back.png"
  );

  m_pDealtCardBack->setPosition(origin.x + Vec2(m_pDealtCardBack->getContentSize() / 2).x + m_cFramePadding,
    origin.y + Vec2(visibleSize).y - Vec2(m_pDealtCardBack->getContentSize() / 2).y - m_cFramePadding);

  addChild(m_pDealtCardBack, 3);
}

void TutorialStep1::drawCardFront()
{
  m_pDealtCardFront = Sprite::create(
    "cards_Ah.png"
  );

  auto origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();

  m_pDealtCardFront->setPosition(origin.x + Vec2(visibleSize).x / 2,
    origin.y + Vec2(visibleSize).y - Vec2(m_pDealtCardFront->getContentSize() / 2).y - m_cFramePadding);
  m_pDealtCardFront->setRotation3D(Vec3(0, 90.0f, 0));
  m_pDealtCardFront->setFlippedX(true);

  addChild(m_pDealtCardFront, 4);
}

void TutorialStep1::animateCardDealing()
{
  auto visibleSize = Director::getInstance()->getVisibleSize();

  auto disableDealBtn = CallFunc::create([this]()
  {
    m_pDealCardMenuItem->setEnabled(false);
  });
  auto backMoveBy = MoveTo::create(m_cFlipTime, Vec2(Vec2(visibleSize).x / 2, m_pDealtCardBack->getPositionY()));
  auto backRotateBy = RotateBy::create(m_cFlipTime, Vec3(0, 90.0f, 0));
  auto backSpawner = Spawn::create(backMoveBy, backRotateBy, nullptr);
  auto afterBackFinished = CallFunc::create([this]()
  {
    m_pDealtCardBack->setVisible(false);
    m_pDealtCardFront->setVisible(true);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto frontMoveBy = MoveTo::create(m_cFlipTime, Vec2(Vec2(visibleSize).x - m_cFramePadding - Vec2(m_pDealtCardFront->getContentSize()).x / 2, m_pDealtCardFront->getPositionY()));
    auto frontRotateBy = RotateBy::create(m_cFlipTime, Vec3(0, 90.0f, 0));
    auto enableDealBtn = CallFunc::create([this]()
    {
      m_pDealCardMenuItem->setEnabled(true);
    });
    auto frontSpawner = Spawn::create(frontMoveBy, frontRotateBy, nullptr);
    auto frontSequence = Sequence::create(frontSpawner, enableDealBtn, nullptr);
    m_pDealtCardFront->runAction(frontSequence);
  });
  auto backSequence = Sequence::create(disableDealBtn, backSpawner, afterBackFinished, nullptr);
  m_pDealtCardBack->runAction(backSequence);
}
