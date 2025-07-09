#pragma once
#include "../Scene/IScene.h"

class IuiState {
public:
  IuiState() {};
  virtual~IuiState() {};

  virtual void Init() {};

  virtual void Update() {};

  virtual void Draw2d() {};

  void SetScene(SceneComponent *s) { scene_ = s; }


private:

protected:
  SceneComponent *scene_ = nullptr;
};
