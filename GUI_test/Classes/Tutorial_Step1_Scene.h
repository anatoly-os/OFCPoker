#ifndef __TUTORIAL1_SCENE_H__
#define __TUTORIAL1_SCENE_H__

#include "cocos2d.h"

#include "carddeck\include\IGameController.h"
#include <utility>

class TutorialStep1 : public cocos2d::Scene
{
public:
  using SpritesArray = std::set<cocos2d::Sprite*>;
  using SpritePtr = cocos2d::Sprite*;
  using MenuItemPtr = cocos2d::MenuItemImage*;

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
  void drawDealtCardsBack();
  void drawDealtCardsFront(const CPoker::IDeck::CardsList& cards);
  void animateCardDealing();
  void drawCardHolders();
  void drawPlayerCardsHolders();
  void drawDealtCardsHolders();

  void drawSelectFrame();
  void drawNewGameButton();
  void drawReadyButton();
  void drawButtons();
  void clearCards();

  bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
  void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
  void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

  TutorialStep1::SpritePtr checkIntersection(SpritePtr pActiveCard, SpritesArray sprites);

  //logic
  void nextMove();
  void dealCards();

private:
  //GUI
  SpritesArray m_pDealtCardsBack;
  SpritesArray m_pDealtCardsFront;
  std::map<SpritePtr, CPoker::ICard*> m_cardsConvertor;
  SpritesArray m_playerCards;
  SpritesArray m_activePlayerCards;
  SpritesArray m_pCardsHolders;
  SpritePtr m_pCardFrame;
  SpritePtr m_pCardDeck;
  SpritePtr m_dealtCardsLargeHolder;
  SpritesArray m_dealtCardsHolders;
  MenuItemPtr m_pNewGameButton;
  MenuItemPtr m_pReadyButton;
  cocos2d::Vec2 m_initialDragCardPosition;
  cocos2d::Vec2 m_initialDragTouchPosition;

  cocos2d::EventListenerTouchOneByOne* m_pTouchEventListener;
  SpritePtr m_dummySpriteNotToReleaseTouchListener;
  const int m_cFramePadding = 10;

  //backend data
  std::unique_ptr<CPoker::IGameController> m_pGameController;
  CPoker::IPlayer::ID m_playerId;
  CPoker::IDeck::CardsList m_chosenCards;
};

#endif // __TUTORIAL1_SCENE_H__

