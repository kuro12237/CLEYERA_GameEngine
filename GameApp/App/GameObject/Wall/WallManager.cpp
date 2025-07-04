#include "WallManager.h"

void WallManager::Init() {

    name_ = VAR_NAME(WallManager);

  for (size_t i = 0; i < 52; i++) {

    std::shared_ptr<Wall> wall = std::make_shared<Wall>();
    if (i == 0) {
      wall->SetName("wall");
    } else {
      char name[16];
      std::snprintf(name, sizeof(name), "wall.%03zu", i);
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