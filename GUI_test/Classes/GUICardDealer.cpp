#include "GUICardDealer.h"

using namespace CPoker;
using namespace cocos2d;

Action* CPoker::GUICardDealer::dealCard(Sprite * pFrontSprite,
  Sprite * pBackSprite,
  const cocos2d::Vec2 & start,
  const cocos2d::Vec2 & end)
{
  static const float cFlipTime = 0.5f;

  pBackSprite->setVisible(true);
  pFrontSprite->setVisible(false);
  pBackSprite->setPosition(start);
  pBackSprite->setRotation3D(Vec3(0, 0, 0));

  auto afterBackFinished = CallFunc::create([=]()
  {
    pBackSprite->setVisible(false);
    pFrontSprite->setVisible(true);

    pFrontSprite->setRotation3D(Vec3(0, -90.0f, 0));
    pFrontSprite->setPosition(end);

    auto frontRotateBy = RotateBy::create(cFlipTime / 2, Vec3(0, 90.0f, 0));
    pFrontSprite->runAction(frontRotateBy);
  });
  auto backMoveTo = MoveTo::create(cFlipTime, end);
  auto backRotateBy = RotateBy::create(cFlipTime / 2, Vec3(0, 90.0f, 0));
  auto delayWhileFrontFinished = DelayTime::create(cFlipTime / 2);
  return Sequence::create(backMoveTo, backRotateBy, afterBackFinished, delayWhileFrontFinished, nullptr);
}
