#pragma once


class IMaterial {
public:
  virtual ~IMaterial() = default;
  virtual void Bind(const size_t &index) = 0;
};