#pragma once

#include "IScene.h"
#include"../testCamera.h"
#include"TestObject.h"

class DebugScene : public SceneCompornent {
 public:
   DebugScene() {}
   ~DebugScene() {};

   void Init() override;

   void Update() override;

   void ImGuiUpdate() override;

 private:
   std::unique_ptr<TestCamera> camera = nullptr;

 std::shared_ptr<TestObject> object = nullptr;

   std::shared_ptr<TestObject> objectb = nullptr;



};
