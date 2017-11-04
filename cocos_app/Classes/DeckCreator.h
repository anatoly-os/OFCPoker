#include "carddeck\src\PokerDeck.h"
#include <memory>

namespace CPoker
{
  class DeckCreator
  {
  public:
    static std::unique_ptr<CPoker::IDeck> createDeck()
    {
      return std::make_unique<CPoker::PokerDeck>();
    }
  };
}