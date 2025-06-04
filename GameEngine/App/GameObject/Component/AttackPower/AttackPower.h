#pragma once
#include "CLEYERA.h"

class AttackPower {
public:
  AttackPower();
  ~AttackPower();

  void Init();

#pragma region Set

  void SetPower(const int32_t p) { power_ = p; };

#pragma endregion

#pragma region Get

  int32_t GetPower() { return power_; }

#pragma endregion

private:
  int32_t power_ = 100;
};
