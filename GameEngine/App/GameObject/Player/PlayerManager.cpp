#include "PlayerManager.h"

void PlayerManager::Init() {

   name_ = VAR_NAME(PlayerManager);

   // カメラ
   camera_ = std::make_shared<PlayerCamera>();
   this->cameraCompornents_.push_back(camera_);

   // コア
   core_ = std::make_shared<PlayerCore>();
   this->objComponents_.push_back(core_);


   // 弾管理クラス
   bulletManager_ = std::make_shared<PlayerBulletManager>();
   bulletManager_->Init();

   handler_ = std::make_unique<PlayerCommandHandler>();
   handler_->SetPlayer(core_);
   handler_->SetPlayer(bulletManager_);
   handler_->Init();

   // 初期化
   this->ListInit();
   // コライダーシステムに登録
   colliderSystem_->PushCollider(core_);

   // ペアレント
   camera_->SetTarget(core_->GetTranslate());

   testLua_ = std::make_unique<LuaScript>();
   testLua_->LoadScript("LuaScript/Dev", "Dev.lua");
}

void PlayerManager::Update() {

   handler_->Handler();

   handler_->Exec();

   // 更新処理
   this->ListUpdate();

   bulletManager_->Update();


   ImGui::Begin("TestLua");
   int hp = testLua_->GetVariable<int>("Data.hp");
   float attack = testLua_->GetVariable<float>("Data.attack");
   std::string state = testLua_->GetVariable<std::string>("Data.state");
   
   int num = testLua_->GetVariable<int>("Data.num");
   std::optional<std::string> func = testLua_->CallFunction<std::string>("GetStageFileName", num);
   
   ImGui::Text("hp = %d", hp);
   
   ImGui::Text("attack = %f", attack);
   ImGui::Text("state = %s", state.c_str());
   ImGui::Text("num = %d", num);
   ImGui::Text("string = %s", func.value().c_str());
   
   ImGui::End();
   
   testLua_->MonitorScript();
}
