#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <memory>

#include "carddeck\include\IGameController.h"
#include "carddeck\include\IPlayer.h"
#include "carddeck\include\IDeck.h"

class HelloWorld : public cocos2d::Scene
{
public:
    virtual bool init() override;

    static cocos2d::Scene* scene();

    // a selector callback
    void playerFinished(Ref* sender);
    void startGame();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
  //TODO: move to separate service classes
  //logic
  void nextMove();
  void processChosenCards(const CPoker::IDeck::CardsList& cards);
  /////////

  //GUI
  void drawActivePlayer();
  void clearActivePlayer();
  void drawCards(const CPoker::IDeck::CardsList& cards);
  void clearCards();
  void drawGameFinished();
  void clearGameFinished();

  void drawStartGameButton();
  void drawDoneButton();
  void drawBackground();
  //////////

private:
  std::unique_ptr<CPoker::IGameController> m_pGameController;
  
  //dummy players (switch to ID in future and ask ID from server during connect routine)
  std::unique_ptr<CPoker::IPlayer> m_pPlayer1;
  std::unique_ptr<CPoker::IPlayer> m_pPlayer2;

  CPoker::IDeck::CardsList m_chosenCards;

  std::vector<int> m_cardLabelsTags;
  const int m_playerLabelTag = 100;
  const int m_gameIsFinishedTag = 1000;

  cocos2d::MenuItemImage* m_pNextMoveMenuItem;
  cocos2d::MenuItemImage* m_pStartGameMenuItem;
};

#endif // __HELLOWORLD_SCENE_H__
