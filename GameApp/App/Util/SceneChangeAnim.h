#pragma once
#include "CLEYERA.h"
#include "Compornent/SpriteComponent.h"

class SceneChangeAnim : public SpriteComponent {
public:
  SceneChangeAnim() {};
  ~SceneChangeAnim() {};

  void Init() override;

  void Update() override;

  bool IsEnd() { return isEnd_; };

  void Start() { isStart = true; };


private:
  float easeInCubic(float x) { return x * x * x; }

  bool isEnd_ = false;
  bool isStart = false;

  bool gameStart_ = true;
  bool gameStartEnd_ = false;

  float color_a_ = 1.0f;

  float time_ = 0.0f;
};
