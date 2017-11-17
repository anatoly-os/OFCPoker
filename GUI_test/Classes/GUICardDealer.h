#pragma once

#include "cocos2d.h"

namespace CPoker
{
  /*
    @pBackSprite must be placed correctly to the initial position
    Animation will be played as follows:
    1. Card back moves to end position
    2. Back sprite rotates inplace to be invisible
    3. Front sprite rotates inplace to be visible
  */
  class GUICardDealer
  {
  public:
    static cocos2d::Action* dealCard(cocos2d::Sprite* pFrontSprite, cocos2d::Sprite* pBackSprite,
      const cocos2d::Vec2& start, const cocos2d::Vec2& end);
  };
}