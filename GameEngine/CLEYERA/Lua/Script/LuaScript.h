#pragma once

#include "pch/Pch.h"
#include <lua.hpp>


/* 個々のスクリプトを管理するクラス */
class LuaScript {

 public:
	
   using ReloadCallback = std::function<void()>;

   /// <summary>
   /// コンストラクタ
   /// </summary>
   LuaScript();

   /// <summary>
   /// デストラクタ
   /// </summary>
   ~LuaScript() = default;

   /// <summary>
   /// スクリプトの読み込み
   /// </summary>
   bool LoadScript(const std::string &file);

   /// <summary>
   /// スクリプトの再評価
   /// </summary>
   bool Reload(const std::string &file);

   /// <summary>
   /// リロード時のコールバックの登録
   /// </summary>
   void SetReloadCallBack();

   /// <summary>
   /// Lua側の変数を取得
   /// </summary>
   /// <typeparam name="T"> 取得変数の型 </typeparam>
   /// <param name="varName"> Lua側にある変数名 </param>
   template <typename T> T GetVaruable(const std::string &varName);

   /// <summary>
   /// Lua側の関数を実行
   /// </summary>
   /// <param name="funcName"> Lua側にある関数名 </param>
   /// <param name="...args"> 引数 </param>
   template <typename... Args> bool ExeFunction(const std::string &funcName, Args... args);

   
 private:

   std::unique_ptr<lua_State, decltype(&lua_close)> L_;
   ReloadCallback reloadCallback_ = nullptr; // コールバック関数

};



/// <summary>
/// コンストラクタ
/// </summary>
inline LuaScript::LuaScript() : L_(luaL_newstate(), &lua_close) 
{
   luaL_openlibs(L_.get()); // Luaライブラリを開く
}


/// <summary>
/// スクリプトの読み込み
/// </summary>
inline bool LuaScript::LoadScript([[maybe_unused]] const std::string &file) { return false; }


/// <summary>
/// スクリプトの再評価
/// </summary>
inline bool LuaScript::Reload([[maybe_unused]] const std::string &file) { return false; }


/// <summary>
/// リロード時のコールバックの登録
/// </summary>
inline void LuaScript::SetReloadCallBack() {}


/// <summary>
/// Lua側の変数を取得
/// </summary>
/// <typeparam name="T"> 取得変数の型 </typeparam>
/// <param name="varName"> Lua側にある変数名 </param>
template <typename T> inline T LuaScript::GetVaruable(const std::string &varName) { return T(); }


/// <summary>
/// Lua側の関数を実行
/// </summary>
/// <param name="funcName"> Lua側にある関数名 </param>
/// <param name="...args"> 引数 </param>
template <typename... Args> inline bool LuaScript::ExeFunction(const std::string &funcName, Args... args) { return false; }
