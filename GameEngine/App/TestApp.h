#pragma once
#include"../CLEYERA/CLEYERA.h"

class TestApp {
 public:
   TestApp() {};
   ~TestApp() {};

   void Init();

 private:

	 CLEYERA::LogManager::SystemLogManager system;

};
