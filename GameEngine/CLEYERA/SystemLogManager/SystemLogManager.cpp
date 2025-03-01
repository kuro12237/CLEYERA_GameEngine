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

SystemLogManager::~SystemLogManager() {
  if (logFile_.is_open()) {
    logFile_.close();
  }
