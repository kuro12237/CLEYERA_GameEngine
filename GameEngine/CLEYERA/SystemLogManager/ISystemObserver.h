#pragma once
#include"../pch/Pch.h"

namespace CLEYERA::LogManager
{

/// <summary>
/// システムの監視インターフェース
/// </summary>
class ISystemObserver {
public:
  ISystemObserver() = default;
  virtual ~ISystemObserver() = default;

  virtual void OnObjectCreated(const std::string &objectType) = 0;

private:
};


} // namespace CLEYERA