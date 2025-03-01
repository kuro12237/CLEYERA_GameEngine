#pragma once
#include "ISystemObserver.h"

namespace CLEYERA::LogManager {

class SystemLogManager : public CLEYERA::LogManager::ISystemObserver {
public:
  SystemLogManager();
  ~SystemLogManager();

  /// <summary>
  /// 
  /// </summary>
  /// <param name="objectType"></param>
  void OnObjectCreated(const std::string &objectType) override;

  static std::wstring ConvertString(const std::string &str);
  static std::string ConvertString(const std::wstring &str);
  

  void Log(const std::string &message);


private:
  std::string fileName_ = "BuildLog.txt";
  std::ofstream logFile_;
};

} // namespace CLEYERA::LogManager