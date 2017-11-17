#ifndef __TUTORIAL1_SCENE_H__
#define __TUTORIAL1_SCENE_H__

#include "cocos2d.h"

class TutorialStep1 : public cocos2d::Scene
{
public:
  virtual bool init() override;

  static cocos2d::Scene* scene();

  //deal card cb
  void TutorialStep1::dealCard();

  // implement the "static create()" method manually
  CREATE_FUNC(TutorialStep1);

private:
  void drawBackground();
  void drawDealButton();
  void drawDeck();
  void drawCardBack();
  void drawCardFront(bool visible);
  void animateCardDealing();

private:
  cocos2d::MenuItemImage* m_pDealCardMenuItem;
  std::vector<cocos2d::Sprite*> m_pDealtCardsBack;
  std::vector<cocos2d::Sprite*> m_pDealtCardsFront;

  const int m_cFramePadding = 10;
};

#endif // __TUTORIAL1_SCENE_H__
