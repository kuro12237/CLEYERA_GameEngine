#include "WallManager.h"

void WallManager::Init() {

    name_ = VAR_NAME(WallManager);

  for (size_t i = 0; i < 2; i++) {

    std::shared_ptr<Wall> wall = std::make_shared<Wall>();
    wall->SetName("Wall" + std::to_string(i));
    wall->Init();
    objComponents_.push_back(wall);
  }
}

void WallManager::Update() {

  for (std::weak_ptr<Wall> obj : walls_) {

    obj.lock()->Update();
  }
}