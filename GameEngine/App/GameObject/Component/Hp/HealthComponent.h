#pragma once
#include "CLEYERA.h"

/// <summary>
/// PlayerHP管理
/// </summary>
class HealthComponent : public CLEYERA::Component::JsonCompornent {
public:
  HealthComponent() {};
  ~HealthComponent() {};

  void Init();

  void ImGuiUpdate();

  void CalcHp(int32_t attackPower);

  void SetName(const std::string name) { name_ = name; }

private:
  int32_t hp_;

  float interval_ = 0.0f;
  float intarvalMax_ = 0.5f;

  std::string directory_ = "Hp";
  std::string name_ ="";
};
