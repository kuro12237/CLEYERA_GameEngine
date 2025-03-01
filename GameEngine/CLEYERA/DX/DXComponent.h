#pragma once
#include "../SystemLogManager/ISystemObserver.h"

/// <summary>
///
/// </summary>
class DXComponent {
public:
  DXComponent(const std::string &name) : name_(name) {};
  ~DXComponent() = default;

  virtual void Create() = 0;

  void AddObserver(
      const std::weak_ptr<CLEYERA::LogManager::ISystemObserver> &observer) {
    obsrvers_.push_back(observer);
  }

  void NotifyObserversCreateComp() {
    for (auto observer : obsrvers_) {
      observer.lock()->OnObjectCreated(name_);
    }
  }

private:
protected:
  std::string name_ = "";

  std::vector<std::weak_ptr<CLEYERA::LogManager::ISystemObserver>> obsrvers_;
};
