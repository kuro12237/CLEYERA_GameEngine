#pragma once
#include "../SystemLogManager/ISystemObserver.h"

/// <summary>
/// 
/// </summary>
class DXComponent {
public:
  DXComponent() = default;
  ~DXComponent() = default;

  virtual void Create() = 0;

private:
protected:

  std::string name_ = "";

  std::vector<CLEYERA::LogManager::ISystemObserver> obsrvers_;
};
