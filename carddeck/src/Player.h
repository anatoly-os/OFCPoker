#pragma once

#include "../include/IPlayer.h"

namespace CPoker
{
  class Player : public IPlayer
  {
  public:
    //temp decision
    explicit Player(int id);
    
    IPlayer::ID id() const override;
    void setId(const IPlayer::ID&) override;

    IDeck::CardsList topRow() const override;
    IDeck::CardsList midRow() const override;
    IDeck::CardsList bottomRow() const override;
    IDeck::CardsList foldZone() const override;

    virtual void insertTopRowCards(const IDeck::CardsList&) override;
    virtual void insertMidRowCards(const IDeck::CardsList&) override;
    virtual void insertBottomRowCards(const IDeck::CardsList&) override;
    virtual void insertFoldZoneCards(const IDeck::CardsList&) override;

    IDeck::CardsList ingameCards() const override;

  private:
    IPlayer::ID m_id;

    IDeck::CardsList m_top;
    IDeck::CardsList m_mid;
    IDeck::CardsList m_bottom;
    IDeck::CardsList m_foldZone;
  };
}
