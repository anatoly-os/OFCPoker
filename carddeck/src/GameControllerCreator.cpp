#include "../include/GameControllerCreator.h"
#include "GameController.h"

std::unique_ptr<CPoker::IGameController> CPoker::GameControllerCreator::create()
{
  return std::unique_ptr<CPoker::IGameController>(new GameController());
}