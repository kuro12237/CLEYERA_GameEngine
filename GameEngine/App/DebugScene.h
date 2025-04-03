#pragma once

#include "IScene.h"
#include"../testCamera.h"


class DebugScene : public SceneCompornent {
 public:
   DebugScene() {}
   ~DebugScene() {};

   void Init() override;

   void Update() override;

   void ImGuiUpdate() override;

 private:
   std::unique_ptr<TestCamera> camera = nullptr;

   std::shared_ptr<CLEYERA::Model3d::Game3dObject> gameObj_ = nullptr;
   Math::Vector::Vec3 scale_ = {1.0f, 1.0f, 1.0f};
   Math::Vector::Vec3 rotate_ = {};
   Math::Vector::Vec3 translate_ = {};

   std::shared_ptr<CLEYERA::Model3d::Game3dObject> gameObjCube_ = nullptr;
   Math::Vector::Vec3 scaleCube_ = {1.0f, 1.0f, 1.0f};
   Math::Vector::Vec3 rotateCube_ = {};
   Math::Vector::Vec3 translateCube_ = {3.0f, 0.0f, 0.0f};
};
