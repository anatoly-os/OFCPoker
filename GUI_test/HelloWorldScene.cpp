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

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    ////////////////////////////////////////////////////
    //init private data
    m_pPlayer1.reset(new Player(1));
    m_pPlayer2.reset(new Player(2));
    m_pGameController.reset(new GameController());
    ////////////////////////////////////////////////////

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        CC_CALLBACK_1(HelloWorld::playerFinished,this));
    
    closeItem->setPosition(origin + Vec2(visibleSize) - Vec2(closeItem->getContentSize() / 2));

    // create menu, it's an autorelease object
    auto menuClose = Menu::create(closeItem, nullptr);
    menuClose->setPosition(Vec2::ZERO);
    this->addChild(menuClose, 1);


    auto runItem = MenuItemImage::create(
      "StartNormal.png",
      "StartSelected.png",
      CC_CALLBACK_0(HelloWorld::startGame, this));

    runItem->setPosition(origin + Vec2(runItem->getContentSize() / 2));

    // create menu, it's an autorelease object
    auto menuRun = Menu::create(runItem, nullptr);
    menuRun->setPosition(Vec2::ZERO);
    this->addChild(menuRun, 1);


    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize / 2) + origin);

    // add the sprite as a child to this layer
    this->addChild(sprite);
    
    return true;
}

void HelloWorld::nextMove()
{
  const auto visibleSize = Director::getInstance()->getVisibleSize();
  const auto origin = Director::getInstance()->getVisibleOrigin();
  {
    auto label = Label::createWithTTF(std::to_string(m_pGameController->activePlayer().id), "fonts/arial.ttf", TITLE_FONT_SIZE);
    label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height);
    addChild(label, 1, m_PlayerLabelTag);
  }

  if (m_pGameController->round() != IGameController::Round::WaitPostGameFinish)
  {
    auto dealtCards = m_pGameController->getCardsForActivePlayer();

    removeChildByTag(m_CardsLabelsTag);
    for (size_t i = 0; i < dealtCards.size(); ++i)
    {
      auto label = Label::createWithTTF(dealtCards[i]->toString(), "fonts/arial.ttf", TITLE_FONT_SIZE);
      // position the label on the center of the screen
      label->setPosition(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - (2 + i) * label->getContentSize().height);
      label->setColor(Color3B::RED);

      // add the label as a child to this layer
      this->addChild(label, 1, m_CardsLabelsTag);
    }

    //test case - chosen cards are get from GUI player choice
    m_chosenCards.clear();
    m_chosenCards.push_back(dealtCards[0]);
    m_chosenCards.push_back(dealtCards[1]);
  }
}

void HelloWorld::playerFinished(Ref* sender)
{
  m_pGameController->playerFinished(m_chosenCards);
  nextMove();
}

void HelloWorld::startGame()
{
  std::vector<IPlayer::ID> ids;
  ids.push_back(m_pPlayer1->id());
  ids.push_back(m_pPlayer2->id());
  m_pGameController->startGame(ids);
  nextMove();
}
