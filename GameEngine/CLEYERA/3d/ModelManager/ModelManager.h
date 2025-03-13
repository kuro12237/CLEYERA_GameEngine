#pragma once

#include "../../pch/Pch.h"

namespace CLEYERA {

namespace Manager {

/// <summary>
/// モデル管理クラス
/// </summary>
class ModelManager {
 public:

   /// <summary>
   /// モデル読み込み
   /// </summary>
   /// <param name="ファイル"></param>
   /// <param name="ファイルの名前(objつけない)"></param>
   /// <returns></returns>
   [[nodiscard]]
   uint32_t LoadModel(const std::string &directory, const std::string fileName);

 private:
#pragma region Singlton
   ModelManager() = default;
   ~ModelManager() = default;
   ModelManager(const ModelManager &) = delete;
   ModelManager &operator=(const ModelManager &) = delete;
#pragma endregion

};

} // namespace Manager

} // namespace CLEYERA