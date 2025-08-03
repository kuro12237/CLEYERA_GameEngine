#pragma once
#include "CLEYERA.h"

class TitleCamera : public CLEYERA::Component::CameraCompornent {
public:
  TitleCamera() {};
  ~TitleCamera() {};

  void Init() override;

  void Update() override;

private:
};
