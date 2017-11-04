#include "HelloWorldScene.h"
#include "AppMacros.h"

#include "DeckCreator.h"

USING_NS_CC;


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
    m_pDeck = CPoker::DeckCreator::createDeck();
    m_pDeck->shuffle();
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
                                        CC_CALLBACK_1(HelloWorld::showDealtCard,this));
    
    closeItem->setPosition(origin + Vec2(visibleSize) - Vec2(closeItem->getContentSize() / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
        
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize / 2) + origin);

    // add the sprite as a child to this layer
    this->addChild(sprite);
    
    return true;
}

void HelloWorld::showDealtCard(Ref* sender)
{
  const auto visibleSize = Director::getInstance()->getVisibleSize();
  const auto origin = Director::getInstance()->getVisibleOrigin();

  this->removeChildByName("card");

  if (m_pDeck->cardsInDeck().empty())
  {
    auto label = Label::createWithTTF("No more cards!", "fonts/arial.ttf", TITLE_FONT_SIZE);
    // position the label on the center of the screen
    label->setPosition(origin.x + visibleSize.width / 2,
      origin.y + visibleSize.height - label->getContentSize().height);

    auto cardsInDeck = m_pDeck->cardsInDeck().size();
    label->setColor(Color3B(255, 0, 0));

    // add the label as a child to this layer
    this->addChild(label, 1, "card");
  }

  auto aDealtCards = m_pDeck->deal();
  for (auto card : aDealtCards)
  {
    auto label = Label::createWithTTF(card->toString(), "fonts/arial.ttf", TITLE_FONT_SIZE);
    // position the label on the center of the screen
    label->setPosition(origin.x + visibleSize.width / 2,
      origin.y + visibleSize.height - label->getContentSize().height);

    auto cardsInDeck = m_pDeck->cardsInDeck().size();
    label->setColor(Color3B(cardsInDeck * 4, cardsInDeck * 3, cardsInDeck * 2));

    // add the label as a child to this layer
    this->addChild(label, 1, "card");
  }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
