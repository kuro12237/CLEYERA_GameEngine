#pragma once
#include"../../pch/Pch.h"

class ShaderManager
{
 public:
   ShaderManager() {};
   ~ShaderManager() {};

   static std::vector<char> CompileShader(const std::filesystem::path &hlslFilename);


 private:
};