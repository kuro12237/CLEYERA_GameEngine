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

  for (auto it = objectList_.begin(); it != objectList_.end();) {
    if (!(*it).expired()) {
      ++it;
    } else {
      it = objectList_.erase(it);
    }
  }

  std::unique_ptr<Util::Collider::Octree> octree = std::make_unique<Util::Collider::Octree>();
  octree->Init();
  std::map<int, std::vector<std::weak_ptr<CLEYERA::Component::ObjectComponent>>> map;
  std::list<std::weak_ptr<CLEYERA::Component::ObjectComponent>>
      stackList; // 上位空間のコリジョンをまとめたデータ
  int maxResolution = 5;
  // 空間の最大分割数

  int currentNum = 0; // 現在検証中のモートン序列番号

  	// 全体を更新
  for (auto obj : this->objectList_) {
    
      auto c = obj.lock()->GetCollder().lock();
      map[c->GetMortonNum()].push_back(obj); // mapに配置
  }

  while (true) {
    // 現在の空間に存在するコリジョンの数
    int size = static_cast<int>(map[currentNum].size());
    // 現在の空間内に登録されているオブジェクト同士を衝突
    for (int i = 0; i < size; i++) {
      for (int j = i + 1; j < size; j++) {

          //ここ
        auto obbA = map[currentNum][i].lock()->GetCollder().lock();
        auto obbB = map[currentNum][j].lock()->GetCollder().lock();

        auto typeA = dynamic_cast<Util::Collider::OBBCollider *>(obbA.get());
        auto typeB = dynamic_cast<Util::Collider::OBBCollider *>(obbB.get());

        // 判定
        if (Util::Collider::system::Func::OBBCheck(typeA->GetOBB(), typeB->GetOBB())) {

          obbA->HitCall(map[currentNum][j].lock());
          obbB->HitCall(map[currentNum][i].lock());
        }
      }
    }

    // -- 次の空間検索開始 -- //

    // 次の小空間が8分木分割数を超えていなければ移動
    if ((currentNum << 3) + 1 < maxResolution) {
      // スタックリストにこの空間のデータを追加
      for (int i = 0; i < size; i++) {
        stackList.push_back(map[currentNum][i]);
      }
      currentNum = (currentNum << 3) + 1;
      // 最初に戻る
      continue;
    }
    // そうでない場合は次のモートン番号に移動する
    else if (currentNum % 8 != 0) {
      currentNum++;
      // 最初に戻る
      continue;
    }

    // 下の空間に所属する小空間をすべて検証し終わった場合

    // １つ上の空間に戻る
    do {
      currentNum = (currentNum - 1) >> 3;
      // currentNumが実数値の場合 -> スタックからオブジェクトを外す
      if (currentNum >= 0) {
        size_t PopNum = map[currentNum].size();
        for (int i = 0; i < PopNum; i++) {
          stackList.pop_back();
        }
      }
      // 戻った空間がその空間の最後の数値の場合 -> もう一度戻る
    } while (currentNum % 8 == 0);

    // 次のモートン番号へ進む
    currentNum++;

    // 戻った空間が場外（-1）だった場合 -> ループ終了
    if (currentNum == 0) {
      break;
    }
  }

  // 各コライダーの更新
  for (auto it = objectList_.begin(); it != objectList_.end();) {
    if (!(*it).expired()) {
      (*it).lock()->GetCollder().lock()->MortonUpdate();
      (*it).lock()->GetCollder().lock()->Update();
      ++it;
    }
  }
}
