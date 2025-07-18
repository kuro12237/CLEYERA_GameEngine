#pragma once
#include "Wall.h"

class WallManager : public CLEYERA::Component::ManagerComponent {
public:
  WallManager() {};
  ~WallManager() {};

  void Init() override;

  void Update() override;

private:
  std::list<std::weak_ptr<Wall>> walls_;
};