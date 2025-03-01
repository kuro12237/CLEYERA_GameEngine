#pragma once
#include "ISystemObserver.h"

namespace CLEYERA::LogManager {

// === ロガークラス (オブザーバー) ===
class SystemLogManager : public CLEYERA::LogManager::ISystemObserver {
public:
  SystemLogManager();
  ~SystemLogManager();

  /// <summary>
  /// 作った通知の書き込み
  /// </summary>
  /// <param name="objectType"></param>
  void OnObjectCreated(const std::string &objectType) override;

private:
  std::string fileName_ = "BuildLog.txt";
  std::ofstream logFile_;
};

} // namespace CLEYERA::LogManager