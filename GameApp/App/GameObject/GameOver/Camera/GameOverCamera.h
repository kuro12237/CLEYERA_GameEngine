#pragma once
#include"CLEYERA.h"

class GameOverCamera :public CLEYERA::Component::CameraCompornent{
public:
  GameOverCamera() {};
  ~GameOverCamera() {};

  void Init() override;

  void Update() override;

private:
};
