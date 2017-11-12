#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <memory>

#include "carddeck\include\IGameController.h"
#include "carddeck\include\IPlayer.h"

class HelloWorld : public cocos2d::Scene
{
public:
    virtual bool init() override;

    void nextMove();

    static cocos2d::Scene* scene();

    // a selector callback
    void playerFinished(Ref* sender);
    void startGame();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
  std::unique_ptr<CPoker::IGameController> m_pGameController;
  
  //dummy players
  std::unique_ptr<CPoker::IPlayer> m_pPlayer1;
  std::unique_ptr<CPoker::IPlayer> m_pPlayer2;

  const int m_CardsLabelsTag = 1;
  const int m_PlayerLabelTag = 2;
};

#endif // __HELLOWORLD_SCENE_H__
