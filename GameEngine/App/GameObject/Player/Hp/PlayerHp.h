#pragma once
#include "CLEYERA.h"

/// <summary>
/// Hp管理
/// </summary>
class PlayerHp : public CLEYERA::Component::JsonCompornent {
public:
  PlayerHp() {};
  ~PlayerHp() {};

  void Init();

  void ImGuiUpdate();

  void CalcHp(int32_t attackPower);

private:
  int32_t hp_;

  std::string name_="PlayerHp";
};
