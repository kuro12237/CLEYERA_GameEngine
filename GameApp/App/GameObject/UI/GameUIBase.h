#pragma once
#include "CLEYERA.h"

class GameUIBase : public SpriteComponent {
public:
  GameUIBase() {};
  ~GameUIBase() {};

  virtual void Init() = 0;
  virtual void Update() = 0;

private:
};
