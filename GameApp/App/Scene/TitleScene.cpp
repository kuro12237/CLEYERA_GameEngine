#include "TitleScene.h"

void TitleScene::Init() {

  loader_ = std::make_unique<SceneLoader>();
  loader_->LoadSceneData("TitleSceneData");
  // 初期化
  for (auto manager : managerCompornents_) {
    manager.lock()->Init();
    // マネージャーのGameObjListをSceneにも登録(weak)
    for (auto obj : manager.lock()->GetObjList()) {

      // 絶対に登録
      objectComponents_.push_back(obj);
      objectList_.push_back(obj.lock()->GetGameObject());

      // 重力適用
      gravityManager_->PushData(obj);
      // 地形当たり判定適用
      terrain_->PushData(obj);
    }
    manager.lock()->GetObjList().clear();
  }

  // エディタのデータを各オブジェクトにセット
  enviromentObjs_ = loader_->SettingData(objectComponents_);

  for (auto obj : enviromentObjs_) {
    objectComponents_.push_back(obj);
  }

  loader_.reset();

  // 地形モデルの設定
  uint32_t modelHandlet =
      modelManager_->LoadModel("Resources/Model/Terrain/", "terrain");
  terrain_->ChengeData(modelHandlet);

}

void TitleScene::Update([[maybe_unused]] GameManager *g) {


  for (auto manager : managerCompornents_) {

    auto mgr = manager.lock();

    for (auto objs : mgr->GetObjList()) {
      auto it = objs.lock();
      if (!it)
        return;

      if (it) {
        objectComponents_.push_back(it);
      }
    }

    // ObjList をクリア（元の manager 側から削除）
    mgr->GetObjList().clear();
    mgr->Update();
    mgr->CollectAllObjects(objectComponents_);
  }

  // コンポーネントがからの場合削除
  for (auto it = objectComponents_.begin(); it != objectComponents_.end();) {
    if (it->expired()) {
      it = objectComponents_.erase(it);
    } else {
      ++it;
    }
  }

  std::list<std::string> objNames;

  for (auto obj : objectComponents_) {

    if (!obj.lock()) {
      continue;
    }

    for (std::string name : objNames) {

      if (name == obj.lock()->GetName()) {
        // 同じものが複数回呼び出されてる
        assert(0);
      }
    }

    obj.lock()->Update();

    objNames.push_back(obj.lock()->GetName());
  }
}

void TitleScene::Draw2d() {}
