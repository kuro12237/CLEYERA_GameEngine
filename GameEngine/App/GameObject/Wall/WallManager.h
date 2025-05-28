#pragma once
#include "Wall.h"

class WallManager : public CLEYERA::Component::ManagerCompornent {
public:
  WallManager() {};
  ~WallManager() {};

  void Init() override;

  void Update() override;

private:
  std::list<std::shared_ptr<Wall>> walls_;
};