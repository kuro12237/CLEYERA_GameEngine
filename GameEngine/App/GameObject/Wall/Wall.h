#pragma once
#include"CLEYERA.h"

/// <summary>
/// 壁
/// </summary>
class Wall:public CLEYERA::Component::ObjectComponent {
public:
  Wall() {};
  ~Wall() {};

  void Init() override;

  void Update() override;


private:
};
