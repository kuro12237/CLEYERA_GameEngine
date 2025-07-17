#pragma once
#include "CLEYERA.h"

class TestUI : public SpriteComponent {
public:
  TestUI() {};
  ~TestUI() {};

  void Init() override;

  void Update() override;

  void ImGuiUpdate() override;

private:
};
