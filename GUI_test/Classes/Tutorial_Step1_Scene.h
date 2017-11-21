#ifndef __TUTORIAL1_SCENE_H__
#define __TUTORIAL1_SCENE_H__

#include "cocos2d.h"

#include "carddeck\include\IGameController.h"

class TutorialStep1 : public cocos2d::Scene
{
public:
  using SpritesArray = std::vector<cocos2d::Sprite*>;

  virtual bool init() override;

  static cocos2d::Scene* scene();

  // implement the "static create()" method manually
  CREATE_FUNC(TutorialStep1);

  //callbacks
  void startGame();
  void playerIsReady();

private:
  //GUI
  void drawBackground();
  void drawDeck();
  void drawCardBack();
  void drawCardFront(const CPoker::IDeck::CardsList& cards);
  void animateCardDealing();
  void drawCardHolders();
  void drawNewGameButton();
  void drawReadyButton();
  void drawButtons();

  bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
  void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
  void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

  //logic
  void nextMove();
  void dealCards();

private:
  //GUI
  SpritesArray m_pDealtCardsBack;
  SpritesArray m_pDealtCardsFront;
  //each card holder keeps 3 sprites: background with opacity, black frame and yellow frame
  std::vector<SpritesArray> m_pCardsHolders;
  cocos2d::Sprite* m_pCardDeck;
  cocos2d::MenuItemImage* m_pNewGameButton;
  cocos2d::MenuItemImage* m_pReadyButton;
  cocos2d::Vec2 m_movedSpriteInitPosition;
  cocos2d::Vec2 m_initialTouchPosition;

  cocos2d::EventListenerTouchOneByOne* m_pTouchEventListener;
  const int m_cFramePadding = 10;

  //backend data
  std::unique_ptr<CPoker::IGameController> m_pGameController;
  CPoker::IPlayer::ID m_playerId;
  CPoker::IDeck::CardsList m_chosenCards;
};

#endif // __TUTORIAL1_SCENE_H__

