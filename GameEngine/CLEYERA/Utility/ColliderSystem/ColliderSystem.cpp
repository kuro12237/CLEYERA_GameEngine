#include "ColliderSystem.h"
#include "Compornent/ObjectCompornent.h"

void CLEYERA::Manager::ColliderSystem::ImGuiUpdate() {

  if (ImGui::Button("LineDraw")) {

    if (isLineDraw_) {

      for (auto itr = objectList_.begin(); itr != objectList_.end(); ++itr) {
        if (itr->expired()) {
          continue;
        }
        const auto &collider = itr->lock()->GetCollder().lock();

        RenderManager::GetInstance()->PushLine3d(collider->GetLine());
      }
      isLineDraw_ = false;
    } else {
      for (auto itr = objectList_.begin(); itr != objectList_.end(); ++itr) {
        if (itr->expired()) {
          continue;
        }
        const auto &collider = itr->lock()->GetCollder().lock();
        RenderManager::GetInstance()->PopLine3d(collider->GetLine());
      }
      isLineDraw_ = true;
    }
  }
}

void CLEYERA::Manager::ColliderSystem::Update() {
  // 無効なオブジェクトを削除
  for (auto it = objectList_.begin(); it != objectList_.end();) {
    if (it->expired()) {
      it = objectList_.erase(it);
    } else {
      ++it;
    }
  }

  // Octree初期化（未使用なら削除可）
  std::unique_ptr<Util::Collider::Octree> octree = std::make_unique<Util::Collider::Octree>();
  octree->Init();

  // モートン番号ごとにオブジェクトを分類
  std::map<int, std::vector<std::weak_ptr<CLEYERA::Component::ObjectComponent>>> mortonMap;
  for (const auto &obj : objectList_) {
    auto collider = obj.lock()->GetCollder().lock();
    if (collider) {
      mortonMap[collider->GetMortonNum()].push_back(obj);
    }
  }

  int maxResolution = 5;
  int currentNum = 0;
  std::list<std::weak_ptr<CLEYERA::Component::ObjectComponent>> stackList;

  // 空間ごとの衝突判定
  while (true) {
    auto &group = mortonMap[currentNum];
    int size = static_cast<int>(group.size());

    for (int i = 0; i < size; ++i) {
      auto obbA = group[i].lock();
      if (!obbA)
        continue;

      auto colA = obbA->GetCollder().lock();
      auto typeA = dynamic_cast<Util::Collider::AABBCollider *>(colA.get());
      if (!typeA)
        continue;

      for (int j = i + 1; j < size; ++j) {
        auto obbB = group[j].lock();
        if (!obbB)
          continue;
        auto colB = obbB->GetCollder().lock();
        auto typeB = dynamic_cast<Util::Collider::AABBCollider *>(colB.get());
        if (!typeB)
          continue;

        if (Util::Collider::system::Func::AABBCheck(typeA->GetAABB(),typeB->GetAABB())) {
          colA->HitCall(group[j].lock());
          colB->HitCall(group[i].lock());
        }
      }
    }

    // 空間分割の進行
    if ((currentNum << 3) + 1 < maxResolution) {
      for (auto &obj : group)
        stackList.push_back(obj);
      currentNum = (currentNum << 3) + 1;
      continue;
    } else if (currentNum % 8 != 0) {
      ++currentNum;
      continue;
    }

    // 上位空間に戻る
    do {
      currentNum = (currentNum - 1) >> 3;
      if (currentNum >= 0) {
        size_t popNum = mortonMap[currentNum].size();
        for (size_t i = 0; i < popNum; ++i) {
          if (!stackList.empty())
            stackList.pop_back();
        }
      }
    } while (currentNum % 8 == 0);

    ++currentNum;
    if (currentNum == 0)
      break;
  }

  // 各コライダーの更新
  for (const auto &obj : objectList_) {
    auto collider = obj.lock()->GetCollder().lock();
    if (collider) {
      collider->MortonUpdate();
      collider->Update();
    }
  }
}
