#pragma once
#include "CLEYERA.h"

class GameClearCamera : public CLEYERA::Component::CameraCompornent {
public:
  GameClearCamera() {};
  ~GameClearCamera() {};

  void Init() override;

  void Update() override;

private:
};
