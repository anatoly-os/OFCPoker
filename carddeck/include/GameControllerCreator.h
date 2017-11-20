#pragma once

#include "IGameController.h"
#include <memory>

namespace CPoker
{
  class GameControllerCreator
  {
  public:
    static std::unique_ptr<IGameController> create();
  };
}