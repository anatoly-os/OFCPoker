#ifndef __TUTORIAL1_SCENE_H__
#define __TUTORIAL1_SCENE_H__

#include "cocos2d.h"

class TutorialStep1 : public cocos2d::Scene
{
public:
  using SpritesArray = std::vector<cocos2d::Sprite*>;

  virtual bool init() override;

  static cocos2d::Scene* scene();

  //deal card cb
  void TutorialStep1::dealCard();

  // implement the "static create()" method manually
  CREATE_FUNC(TutorialStep1);

private:
  void drawBackground();
  void drawDeck();
  void drawCardBack();
  void drawCardFront();
  void animateCardDealing();
  void drawCardHolders();

  bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
  void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
  void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

private:
  SpritesArray m_pDealtCardsBack;
  SpritesArray m_pDealtCardsFront;
  //each card holder keeps 3 sprites: background with opacity, black frame and yellow frame
  std::vector<SpritesArray> m_pCardsHolders;
  cocos2d::MenuItemImage* m_pCardDeck;
  cocos2d::Vec2 m_movedSpriteInitPosition;
  cocos2d::Vec2 m_initialTouchPosition;
  cocos2d::EventListenerTouchOneByOne* m_pTouchEventListener;

  const int m_cFramePadding = 10;
};

#endif // __TUTORIAL1_SCENE_H__

