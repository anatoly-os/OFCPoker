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
    m_playerLabelsTags.resize(3);
    /////////////////////////////////////////////

    //init game GUI
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const auto origin = Director::getInstance()->getVisibleOrigin();
    m_player1GroupShift = Vec2(origin.x + m_cPlayerGroupShiftX, origin.y + Vec2(visibleSize).y - m_cPlayerGroupShiftY);
    m_player2GroupShift = Vec2(origin.x + Vec2(visibleSize).x - m_cPlayerGroupShiftX, origin.y + Vec2(visibleSize).y - m_cPlayerGroupShiftY);
    m_playerLabelsTags[0] = 1000;
    m_playerLabelsTags[1] = 1001;
    m_playerLabelsTags[2] = 1002;
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
    highlightActivePlayer();

    auto dealtCards = m_pGameController->dealCardsForActivePlayer();
    if (m_pGameController->activePlayer() == m_player1Id)
      drawFirstPlayerCards(dealtCards);
    else
      drawSecondPlayerCards(dealtCards);

    processChosenCards(dealtCards);
  }
  else
  {
    drawFirstPlayer(false);
    drawSecondPlayer(false);
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
    m_chosenCards.insert(m_chosenCards.end(), cards.begin(), cards.begin() + 14); //14 is temp while choosing cards is not finished
    break;
  case IGameController::Round::FiveCards:
    m_chosenCards.insert(m_chosenCards.end(), cards.begin(), cards.end());
    break;
  case IGameController::Round::ThreeCards1:
  case IGameController::Round::ThreeCards2:
  case IGameController::Round::ThreeCards3:
  case IGameController::Round::ThreeCards4:
    m_chosenCards.insert(m_chosenCards.end(), cards.begin(), cards.begin() + 3); //3 is temp while choosing cards is not finished
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
  //logic part
  m_player1Id = IPlayer::ID(1);
  m_player2Id = IPlayer::ID(2);
  //GUI part
  clearCards(); 
  drawPlayers();
  m_pNextMoveMenuItem->setEnabled(true);
  m_pStartGameMenuItem->setEnabled(false);

  std::vector<IPlayer::ID> ids;
  ids.push_back(m_player1Id);
  ids.push_back(m_player2Id);
  m_pGameController->startGame(ids);
  nextMove();
}

void HelloWorld::drawPlayers()
{
  drawFirstPlayer(false);
  drawSecondPlayer(false);
}

void HelloWorld::drawFirstPlayer(bool isActive)
{
  const auto visibleSize = Director::getInstance()->getVisibleSize();
  const auto origin = Director::getInstance()->getVisibleOrigin();

  auto label = Label::createWithTTF(std::to_string(m_player1Id.id), "fonts/arial.ttf", TITLE_FONT_SIZE);
  label->setPosition(m_player1GroupShift);
  auto color = isActive ? Color3B::GREEN : Color3B::GRAY;
  label->setColor(color);
  addChild(label, 1, m_playerLabelsTags[0]);
}

void HelloWorld::drawSecondPlayer(bool isActive)
{
  const auto visibleSize = Director::getInstance()->getVisibleSize();
  const auto origin = Director::getInstance()->getVisibleOrigin();

  auto label = Label::createWithTTF(std::to_string(m_player2Id.id), "fonts/arial.ttf", TITLE_FONT_SIZE);
  label->setPosition(m_player2GroupShift);
  auto color = isActive ? Color3B::GREEN : Color3B::GRAY;
  label->setColor(color);
  addChild(label, 1, m_playerLabelsTags[1]);
}

void HelloWorld::highlightActivePlayer()
{
  const auto visibleSize = Director::getInstance()->getVisibleSize();
  const auto origin = Director::getInstance()->getVisibleOrigin();

  const auto activePlrId = m_pGameController->activePlayer();
  clearPlayer(activePlrId);
  if (activePlrId == m_player1Id)
  {
    drawFirstPlayer(true);
    drawSecondPlayer(false);
  }
  else if (activePlrId == m_player2Id)
  {
    drawFirstPlayer(false);
    drawSecondPlayer(true);
  }
}

int HelloWorld::playerTagIdx(const IPlayer::ID& id)
{
  return (m_player2Id == id) ? 1 : 0;
}

void HelloWorld::clearPlayer(const IPlayer::ID& id)
{
  removeChildByTag(m_playerLabelsTags[playerTagIdx(id)]);
}

void HelloWorld::drawFirstPlayerCards(const IDeck::CardsList& cards)
{
  const auto visibleSize = Director::getInstance()->getVisibleSize();
  const auto origin = Director::getInstance()->getVisibleOrigin();

  const int alreadyDealtCards = m_pGameController->playerIngameCards(m_player1Id).size();
  const int playerYShift = getChildByTag(m_playerLabelsTags[playerTagIdx(m_player1Id)])->getPositionY();
  for (size_t i = 0; i < cards.size(); ++i)
  {
    auto label = Label::createWithTTF(cards[i]->toString(), "fonts/arial.ttf", TITLE_FONT_SIZE / 2);
    label->setPosition(m_player1GroupShift.x,
      m_player1GroupShift.y - (alreadyDealtCards + i + 2) * label->getContentSize().height);
    label->setColor(Color3B::WHITE);

    int currTag = m_cPlayer1CardsStartTag + alreadyDealtCards + i;
    m_cardLabelsTagsPlayer1.push_back(currTag);
    this->addChild(label, 1, currTag);
  }
}

void HelloWorld::drawSecondPlayerCards(const IDeck::CardsList& cards)
{
  const auto visibleSize = Director::getInstance()->getVisibleSize();
  const auto origin = Director::getInstance()->getVisibleOrigin();

  const int alreadyDealtCards = m_pGameController->playerIngameCards(m_player2Id).size();
  const int playerYShift = getChildByTag(m_playerLabelsTags[playerTagIdx(m_player2Id)])->getPositionY();
  for (size_t i = 0; i < cards.size(); ++i)
  {
    auto label = Label::createWithTTF(cards[i]->toString(), "fonts/arial.ttf", TITLE_FONT_SIZE / 2);
    label->setPosition(m_player2GroupShift.x,
      m_player2GroupShift.y - (alreadyDealtCards + i + 2) * label->getContentSize().height);
    label->setColor(Color3B::WHITE);

    int currTag = m_cPlayer1CardsStartTag + alreadyDealtCards + i;
    m_cardLabelsTagsPlayer2.push_back(currTag);
    this->addChild(label, 1, currTag);
  }
}

void HelloWorld::clearCards()
{
  for (auto cardTag : m_cardLabelsTagsPlayer1)
    removeChildByTag(cardTag);
  m_cardLabelsTagsPlayer1.clear();
  
  for (auto cardTag : m_cardLabelsTagsPlayer2)
    removeChildByTag(cardTag);
  m_cardLabelsTagsPlayer2.clear();

  for (auto cardTag : m_cardLabelsTagsPlayer3)
    removeChildByTag(cardTag);
  m_cardLabelsTagsPlayer3.clear();
}

void HelloWorld::drawGameFinished()
{
  const auto visibleSize = Director::getInstance()->getVisibleSize();
  const auto origin = Director::getInstance()->getVisibleOrigin();

  auto label = Label::createWithTTF("Game has finished", "fonts/arial.ttf", TITLE_FONT_SIZE);
  label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height);
  label->setColor(Color3B::RED);
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
