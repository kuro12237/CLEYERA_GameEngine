#include "SystemLogManager.h"

using namespace CLEYERA::LogManager;

SystemLogManager::SystemLogManager() {

  logFile_.open(this->fileName_, std::ios::app);

  if (logFile_.is_open()) {
    logFile_ << "Create " + fileName_ << std::endl;
  }
}

void SystemLogManager::OnObjectCreated(const std::string &objectType) {

  if (logFile_.is_open()) {
    logFile_ << "[LOG] Created: " << objectType << std::endl;
  }
}

std::wstring SystemLogManager::ConvertString(const std::string &str) {
  if (str.empty()) {
    return std::wstring();
  }

  auto sizeNeeded =
      MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char *>(&str[0]),
                          static_cast<int>(str.size()), NULL, 0);
  if (sizeNeeded == 0) {
    return std::wstring();
  }
  std::wstring result(sizeNeeded, 0);
  MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char *>(&str[0]),
                      static_cast<int>(str.size()), &result[0], sizeNeeded);
  return result;
}

std::string SystemLogManager::ConvertString(const std::wstring &str)
{
  if (str.empty()) {
    return std::string();
  }

  auto sizeNeeded =
      WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.size()),
                          NULL, 0, NULL, NULL);
  if (sizeNeeded == 0) {
    return std::string();
  }
  std::string result(sizeNeeded, 0);
  WideCharToMultiByte(CP_UTF8, 0, str.data(), static_cast<int>(str.size()),
                      result.data(), sizeNeeded, NULL, NULL);
  return result;
}

void SystemLogManager::Log(const std::string &message)
{
  OutputDebugStringA(message.c_str());

}

SystemLogManager::~SystemLogManager() {
  if (logFile_.is_open()) {
    logFile_.close();
  }
}