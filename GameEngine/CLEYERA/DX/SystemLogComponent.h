#pragma once
#include "../SystemLogManager/ISystemObserver.h"

/// <summary>
/// DIrectXのコンポーネント
/// </summary>
class DXComponent {
public:
  DXComponent() = default;
  ~DXComponent() = default;

  virtual bool Create() = 0;

private:
protected:

  std::string name_ = "";

  std::vector<CLEYERA::LogManager::ISystemObserver> obsrvers_;
};
