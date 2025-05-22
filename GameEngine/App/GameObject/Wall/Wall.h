#pragma once
#include"CLEYERA.h"


class Wall:public CLEYERA::Component::ObjectComponent {
public:
  Wall() {};
  ~Wall() {};

  void Init() override;

  void Update() override;


private:
};
