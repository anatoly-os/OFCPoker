#include "HelloWorldScene.h"
#include "AppMacros.h"

#include "carddeck\src\GameController.h"
#include "carddeck\src\Player.h"

USING_NS_CC;

using namespace CPoker;

Scene* HelloWorld::scene()
{
  return HelloWorld::create();
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
        return false;
    
    //init game server (connect to one in future)
    m_pGameController.reset(new GameController());
    /////////////////////////////

    drawStartGameButton();
    drawDoneButton();
    drawBackground();
  
    return true;
}

void HelloWorld::nextMove()
{
  if (m_pGameController->round() != IGameController::Round::WaitPostGameFinish)
  {
    clearGameFinished();
    drawActivePlayer();

    auto dealtCards = m_pGameController->getCardsForActivePlayer();
    drawCards(dealtCards);

    processChosenCards(dealtCards);
  }
  else
  {
    clearActivePlayer();
    clearCards();
    drawGameFinished();

    m_pNextMoveMenuItem->setEnabled(false);
    m_pStartGameMenuItem->setEnabled(true);
  }
}

void HelloWorld::processChosenCards(const IDeck::CardsList& cards)
{
  //test case - chosen cards are get from GUI player choice
  //here we get first N needed cards
  m_chosenCards.clear();
  switch (m_pGameController->round())
  {
  case IGameController::Round::Fantasy:
    m_chosenCards.insert(m_chosenCards.end(), cards.begin(), cards.begin() + 13);
    break;
  case IGameController::Round::FiveCards:
    m_chosenCards.insert(m_chosenCards.end(), cards.begin(), cards.end());
    break;
  case IGameController::Round::ThreeCards1:
  case IGameController::Round::ThreeCards2:
  case IGameController::Round::ThreeCards3:
  case IGameController::Round::ThreeCards4:
    m_chosenCards.insert(m_chosenCards.end(), cards.begin(), cards.begin() + 2);
    break;
  }
}

void HelloWorld::playerFinished(Ref* sender)
{
  m_pGameController->playerFinished(m_chosenCards);
  nextMove();
}

void HelloWorld::startGame()
{
  m_pNextMoveMenuItem->setEnabled(true);
  m_pStartGameMenuItem->setEnabled(false);

  m_pPlayer1.reset(new Player(1));
  m_pPlayer2.reset(new Player(2));

  std::vector<IPlayer::ID> ids;
  ids.push_back(m_pPlayer1->id());
  ids.push_back(m_pPlayer2->id());
  m_pGameController->startGame(ids);
  nextMove();
}

void HelloWorld::drawActivePlayer()
{
  const auto visibleSize = Director::getInstance()->getVisibleSize();
  const auto origin = Director::getInstance()->getVisibleOrigin();

  clearActivePlayer();
  auto label = Label::createWithTTF(std::to_string(m_pGameController->activePlayer().id), "fonts/arial.ttf", TITLE_FONT_SIZE);
  label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height);
  label->setColor(Color3B::BLUE);
  addChild(label, 1, m_playerLabelTag);
}

void HelloWorld::clearActivePlayer()
{
  removeChildByTag(m_playerLabelTag);
}

void HelloWorld::drawCards(const IDeck::CardsList& cards)
{
  const auto visibleSize = Director::getInstance()->getVisibleSize();
  const auto origin = Director::getInstance()->getVisibleOrigin();

  clearCards();
  for (size_t i = 0; i < cards.size(); ++i)
  {
    auto label = Label::createWithTTF(cards[i]->toString(), "fonts/arial.ttf", TITLE_FONT_SIZE);
    label->setPosition(origin.x + visibleSize.width / 2,
      origin.y + visibleSize.height - (2 + i) * label->getContentSize().height);
    label->setColor(Color3B::RED);

    m_cardLabelsTags.push_back(i);
    this->addChild(label, 1, i);
  }
}

void HelloWorld::clearCards()
{
  for (auto cardTag : m_cardLabelsTags)
    removeChildByTag(cardTag);
  m_cardLabelsTags.clear();
}

void HelloWorld::drawGameFinished()
{
  const auto visibleSize = Director::getInstance()->getVisibleSize();
  const auto origin = Director::getInstance()->getVisibleOrigin();

  auto label = Label::createWithTTF("Game is finished", "fonts/arial.ttf", TITLE_FONT_SIZE);
  label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height);
  label->setColor(Color3B::WHITE);
  addChild(label, 1, m_gameIsFinishedTag);
}

void HelloWorld::clearGameFinished()
{
  removeChildByTag(m_gameIsFinishedTag);
}

void HelloWorld::drawStartGameButton()
{
  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();
  
  m_pStartGameMenuItem = MenuItemImage::create(
    "StartGameEnabled.png",
    "StartGameClicked.png",
    "StartGameDisabled.png",
    CC_CALLBACK_0(HelloWorld::startGame, this));

  m_pStartGameMenuItem->setPosition(origin + Vec2(visibleSize) - Vec2(m_pStartGameMenuItem->getContentSize() / 2));
  m_pStartGameMenuItem->setEnabled(true);

  auto menuClose = Menu::create(m_pStartGameMenuItem, nullptr);
  menuClose->setPosition(Vec2::ZERO);
  this->addChild(menuClose, 1);
}

void HelloWorld::drawDoneButton()
{
  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();

  m_pNextMoveMenuItem = MenuItemImage::create(
    "PlayerDoneEnabled.png",
    "PlayerDoneClicked.png",
    "PlayerDoneDisabled.png",
    CC_CALLBACK_1(HelloWorld::playerFinished, this));

  m_pNextMoveMenuItem->setPosition(origin.x - Vec2(m_pNextMoveMenuItem->getContentSize() / 2).x + Vec2(visibleSize).x,
    origin.y + Vec2(m_pNextMoveMenuItem->getContentSize() / 2).y);
  m_pNextMoveMenuItem->setEnabled(false);

  auto menuRun = Menu::create(m_pNextMoveMenuItem, nullptr);
  menuRun->setPosition(Vec2::ZERO);
  this->addChild(menuRun, 1);
}

void HelloWorld::drawBackground()
{
  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();

  auto sprite = Sprite::create("BackGround.png");
  sprite->setPosition(Vec2(visibleSize / 2) + origin);
  this->addChild(sprite);
}
