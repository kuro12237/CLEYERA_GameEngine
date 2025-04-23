#pragma once

#include "CLEYERA.h"

#include "../IPlayer.h"
#include "IPlayerBullet.h"
#include "PlayerBullet.h"

class PlayerBulletManager : public IPlayer,
                            public CLEYERA::Component::ManagerCompornent {
public:
  PlayerBulletManager() {};
  ~PlayerBulletManager() {};

  void Init() override;

  void Update() override;

  void PushBullet(std::shared_ptr<IPlayerBullet> b,
                  const Math::Vector::Vec3 &pos);

private:
  uint32_t num = 0;
  std::vector<std::shared_ptr<IPlayerBullet>> bullets_;
};
