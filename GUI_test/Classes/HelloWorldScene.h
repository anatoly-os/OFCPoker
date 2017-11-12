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
  void drawPlayers();
  void drawFirstPlayer(bool isActive);
  void drawSecondPlayer(bool isActive);
  void highlightActivePlayer();
  int playerTagIdx(const CPoker::IPlayer::ID & id);
  void clearPlayer(const CPoker::IPlayer::ID & id);
  void drawFirstPlayerCards(const CPoker::IDeck::CardsList& cards);
  void drawSecondPlayerCards(const CPoker::IDeck::CardsList & cards);
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
  CPoker::IPlayer::ID m_player1Id;
  CPoker::IPlayer::ID m_player2Id;

  CPoker::IDeck::CardsList m_chosenCards;

  //0-99
  const int m_cPlayer1CardsStartTag = 0;
  std::vector<int> m_cardLabelsTagsPlayer1;
  //100-199
  const int m_cPlayer2CardsStartTag = 100; 
  std::vector<int> m_cardLabelsTagsPlayer2;
  //200-299
  const int m_cplayer3CardsStartTag = 200;
  std::vector<int> m_cardLabelsTagsPlayer3;
  //1000-9999
  std::vector<int> m_playerLabelsTags;
  //10000-99999
  const int m_gameIsFinishedTag = 10000;

  cocos2d::MenuItemImage* m_pNextMoveMenuItem;
  cocos2d::MenuItemImage* m_pStartGameMenuItem;
  const int m_cPlayerGroupShiftX = 70; //TODO: replace with resolution dependent value
  const int m_cPlayerGroupShiftY = 30; //TODO: replace with resolution dependent value
  cocos2d::Vec2 m_player1GroupShift;
  cocos2d::Vec2 m_player2GroupShift;
};

#endif // __HELLOWORLD_SCENE_H__
