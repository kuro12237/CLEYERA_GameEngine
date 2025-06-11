#include "ColliderSystem.h"
#include "Compornent/ObjectCompornent.h"

using namespace CLEYERA::Util::Collider::system::Func;

void CLEYERA::Manager::ColliderSystem::ImGuiUpdate() {

  if (ImGui::Button("LineDraw")) {

    if (isLineDraw_) {

      for (auto itr = objectList_->begin(); itr != objectList_->end(); ++itr) {
        if (itr->expired()) {
          continue;
        }
        const auto &collider = itr->lock()->GetCollder().lock();

        RenderManager::GetInstance()->PushLine3d(collider->GetLine());
      }
      isLineDraw_ = false;
    } else {
      for (auto itr = objectList_->begin(); itr != objectList_->end(); ++itr) {
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

  // Octree初期化（未使用なら削除可）
  std::unique_ptr<Util::Collider::Octree> octree = std::make_unique<Util::Collider::Octree>();
  octree->Init();

  // モートン番号ごとにオブジェクトを分類
  std::map<int, std::vector<std::weak_ptr<CLEYERA::Component::ObjectComponent>>> mortonMap;
  for (const auto &obj : *objectList_) {
    auto it = obj.lock();

    if (!it) {
      continue;
    }

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
      auto aabb2 = group[i].lock();
      if (!aabb2)
        continue;

      auto colA = aabb2->GetCollder().lock();
      auto typeA = dynamic_cast<Util::Collider::AABBCollider *>(colA.get());
      if (!typeA)
        continue;

      for (int j = i + 1; j < size; ++j) {
        auto aabb1 = group[j].lock();
        if (!aabb1)
          continue;
        auto colB = aabb1->GetCollder().lock();
        auto typeB = dynamic_cast<Util::Collider::AABBCollider *>(colB.get());
        if (!typeB)
          continue;

        if (Util::Collider::system::Func::AABBCheck(typeA->GetAABB(), typeB->GetAABB())) {
          Math::Vector::Vec3 push = AABBComputePushOutVector(typeA->GetAABB(), typeB->GetAABB());
          typeA->GetAABB_().SetPush(push);
          typeB->GetAABB_().SetPush(push);

          colA->HitCall(aabb1);
          colB->HitCall(aabb2);
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
  for (const auto &obj : *objectList_) {
    auto it = obj.lock();

    if (!it) {
      continue;
    }

    auto collider = it->GetCollder().lock();
    if (collider) {
      collider->MortonUpdate();
      collider->Update();
    }
  }
}
