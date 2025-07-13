#pragma once
#include "CLEYERA.h"

class Coin : public SpriteComponent {
public:
  using Vec3 = Math::Vector::Vec3;
  Coin() {};
  ~Coin() {};

  void Init() override;

  void Update() override;

  void SetUpTex(uint32_t texHandle) { this->handle_ = texHandle; }

  void SetSRT(Vec3 s, Vec3 r, Vec3 t) {
    scale_ = s, rotate_ = r, translate_ = t;
  }

  void SetIsEnemy(bool f) { isEnemy_ = f; }

  void SetIsSelect(bool &f) { isSelect_ = &f; };
  void SetHandle(uint32_t h) { handle_ = h; }

private:

    bool isEnemy_ = false;
  bool *isSelect_ = nullptr;
};
