#include "WallManager.h"

void WallManager::Init() {

    name_ = VAR_NAME(WallManager);

  for (size_t i = 0; i < 2; i++) {

    std::shared_ptr<Wall> wall = std::make_shared<Wall>();
    if (i == 0) {
      wall->SetName("Wall");
    } else {
      char name[16];
      std::snprintf(name, sizeof(name), "Wall.%03zu", i);
      wall->SetName(name);
    }
    wall->Init();
    walls_.push_back(wall);
    objComponents_.push_back(wall);
  }
}

void WallManager::Update() {

  for (std::weak_ptr<Wall> obj : walls_) {

    obj.lock()->Update();
  }
}