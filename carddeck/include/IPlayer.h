#pragma once

#include "IDeck.h"

namespace CPoker
{
  class IPlayer
  {
  public:
    enum class State
    {
      WaitForGameStart,
      WaitForFantasyCards,
      WaitForCards,
      WaitForPostGameActivities
    };

    struct ID
    {
      ID()
        : ID(0)
      {}

      explicit ID(int inId)
        : id(inId)
      {}

      int id = 0;

      inline bool operator==(const ID& playerId) const
      {
        return id == playerId.id;
      }

    private:
      const ID operator+(const ID&) = delete;
      const ID operator*(const ID&) = delete;
      const ID operator-(const ID&) = delete;
    };

    virtual ID id() const = 0;
    virtual void setId(const IPlayer::ID&) = 0;

    virtual IDeck::CardsList topRow() const = 0;
    virtual IDeck::CardsList midRow() const = 0;
    virtual IDeck::CardsList bottomRow() const = 0;
    virtual IDeck::CardsList foldZone() const = 0;

    virtual void insertTopRowCards(const IDeck::CardsList&) = 0;
    virtual void insertMidRowCards(const IDeck::CardsList&) = 0;
    virtual void insertBottomRowCards(const IDeck::CardsList&) = 0;
    virtual void insertFoldZoneCards(const IDeck::CardsList&) = 0;

    virtual IDeck::CardsList ingameCards() const = 0;
  };
}