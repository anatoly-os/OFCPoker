#pragma once

#include "../include/IPlayer.h"

namespace CPoker
{
  class Player : public IPlayer
  {
  public:
    Player();
    
    IPlayer::ID id() const override;
    void setId(const IPlayer::ID&) override;

    IDeck::CardsList topRow() const override;
    IDeck::CardsList midRow() const override;
    IDeck::CardsList bottomRow() const override;
    IDeck::CardsList foldZone() const override;

  private:
    IPlayer::ID m_id;

    IDeck::CardsList m_top;
    IDeck::CardsList m_mid;
    IDeck::CardsList m_bottom;
    IDeck::CardsList m_foldZone;
  };
}
