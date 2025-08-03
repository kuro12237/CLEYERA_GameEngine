#include "WallManager.h"

void WallManager::Init() {

  name_ = VAR_NAME(WallManager);

  for (size_t i = 0; i < 53; i++) {
    std::shared_ptr<Wall> wall = std::make_shared<Wall>();
    wall->Init();
    walls_.push_back(wall);

    objectManager_->CreateObject<Wall>("wall", std::move(wall));
  }
}

void WallManager::Update() {
  objectManager_;
  for (std::weak_ptr<Wall> obj : walls_) {

    if (obj.lock()) {

      obj.lock()->Update();
    }
  }
}