#pragma once
#include "CLEYERA.h"

/// <summary>
/// PlayerHP管理
/// </summary>
class HealthComponent : public CLEYERA::Component::JsonCompornent {
public:
  HealthComponent() {};
  ~HealthComponent() {};

  void Init();

  void ImGuiUpdate();

  void Update();

  void CalcHp(int32_t attackPower);

  void SetName(const std::string name) { name_ = name; }

  bool GetIsDead() { return isDead_; }

  /// <summary>
  /// 体力の取得
  /// </summary>
  /// <returns></returns>
  const int32_t &GetHp() const { return hp_; }

  /// <summary>
  /// 最大HPの設定
  /// </summary>
  /// <param name="maxHp"></param>
  void SetMaxHP(const int32_t & maxHp) {
	  this->maxHp_ = maxHp;
  }

  /// <summary>
  /// 最大の体力の値を取得
  /// </summary>
  /// <returns></returns>
  inline int32_t GetMaxHp()const {
	  return maxHp_;
  }


  void SetHP(const int32_t & hp) {
	  hp_ = hp;
  }

private:
  bool isDead_ = false;

  //最大の体力
  int32_t maxHp_ = 0;

  //現在の体力
  int32_t hp_ = 0;

  float interval_ = 0.0f;
  float intarvalMax_ = 0.5f;

  std::string directory_ = "Hp";
  std::string name_ = "";
};
