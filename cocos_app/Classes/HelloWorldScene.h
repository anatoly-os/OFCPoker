#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <memory>

#include "carddeck\include\IDeck.h"

class HelloWorld : public cocos2d::Scene
{
public:
    virtual bool init() override;

    static cocos2d::Scene* scene();

    // a selector callback
    void showDealtCard(Ref* sender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
  std::unique_ptr<CPoker::IDeck> m_pDeck;
};

#endif // __HELLOWORLD_SCENE_H__
