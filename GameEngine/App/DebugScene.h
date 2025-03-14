#pragma once

#include "IScene.h"

class DebugScene : public SceneCompornent {
 public:
   DebugScene() {}
   ~DebugScene() {};

   void Init() override;

   void Update() override;

 private:
   std::shared_ptr<CLEYERA::Model3d::Game3dObject> gameObj_ = nullptr;
   Math::Vector::Vec3 scale_ = {1.0f, 1.0f, 1.0f};
   Math::Vector::Vec3 rotate_ = {};
   Math::Vector::Vec3 translate_ = {};
};
