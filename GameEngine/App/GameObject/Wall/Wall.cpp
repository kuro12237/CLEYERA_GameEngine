#include "Wall.h"

void Wall::Init() {

  // Modelの設定
  std::pair<std::string, std::string> str = {"Resources/Model/Wall", "Wall"};
  uint32_t handle = ObjectComponent::modelManager_->LoadModel(str.first, str.second);
  ObjectComponent::gameObject_->ChangeModel(handle);

  // コライダー作成
  ObjectComponent::CreateCollider(ColliderType::AABB);

  
}

void Wall::Update() { this->TransformUpdate(); }
