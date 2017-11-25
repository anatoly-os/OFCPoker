#include "carddeck\src\GameController.h"
#include <memory>

namespace CPoker
{
  class GameControllerCreator
  {
  public:
    static std::unique_ptr<CPoker::IGameController> createGame()
    {
      return std::make_unique<CPoker::GameController>();
    }
  };
}