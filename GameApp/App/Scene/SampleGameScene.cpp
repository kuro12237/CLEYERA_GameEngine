#include "SampleGameScene.h"

void SampleGameScene::Init() {
  curl_global_init(CURL_GLOBAL_ALL);
  [[maybe_unused]]CURL *curl = curl_easy_init();

  coins_.resize(4);

  for (size_t i = 0; i < 4; i++) {

    coins_[i] = std::make_shared<Coin>();
    spriteComponents_.push_back(coins_[i]);
  }

  for (auto s : spriteComponents_) {

    s.lock()->Init();
  }

  auto texM = CLEYERA::Manager::TexManager::GetInstance();
  // 表
  uint32_t texHandle = texM->LoadPngTex("front");
  coins_[0]->SetName("front");
  coins_[0]->SetUpTex(texHandle);
  coins_[0]->SetIsEnemy(true);
  coins_[0]->SetSRT({0.1f, 0.1f, 0.1f}, {}, {800.0f, 128.0f, 0.0f});
  // 裏
  texHandle = texM->LoadPngTex("back");
  coins_[1]->SetName("back");
  coins_[1]->SetUpTex(texHandle);
  coins_[1]->SetIsEnemy(true);
  coins_[1]->SetSRT({0.1f, 0.1f, 0.1f}, {}, {480.0f, 128.0f, 0.0f});

  // 表
  texHandle = texM->LoadPngTex("front");
  coins_[2]->SetName("front_Player");
  coins_[2]->SetUpTex(texHandle);
  coins_[2]->SetSRT({0.1f, 0.1f, 0.1f}, {}, {800.0f, 512.0f, 0.0f});
  // 裏
  texHandle = texM->LoadPngTex("back");
  coins_[3]->SetName("back_Player");
  coins_[3]->SetUpTex(texHandle);

  coins_[3]->SetSRT({0.1f, 0.1f, 0.1f}, {}, {480.0f, 512.0f, 0.0f});
  getScoreFuture_ = GetAllScoresAsync();
}

void SampleGameScene::Update([[maybe_unused]] GameManager *g) {
  auto input = CLEYERA::Manager::InputManager::GetInstance();
  auto texM = CLEYERA::Manager::TexManager::GetInstance();
  int32_t selectPlayerNum = 0;
  if (!isSelect_) {

    if (input->PushKey(DIK_1) || input->PushKey(DIK_2)) {
      isSelect_ = true;
      if (input->PushKey(DIK_1)) {
        coins_[2]->SetHandle(texM->LoadPngTex("front_Red"));
        selectPlayerNum = 2;
      } else if (input->PushKey(DIK_2)) {
        coins_[3]->SetHandle(texM->LoadPngTex("back_Red"));
        selectPlayerNum = 3;
      }
    }
  }

  if (isSelect_) {

    if (!isEnemyAttack_) {

      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dist(0, 1);
      int random = dist(gen);

      if (0 == random) {
        coins_[random]->SetHandle(texM->LoadPngTex("front_Red"));
      }
      if (1 == random) {
        coins_[random]->SetHandle(texM->LoadPngTex("back_Red"));
      }
      // win
      if ((selectPlayerNum - 2) == random) {
        scores_++;
      } else {
        gameReset_ = true;
      }
      isEnemyAttack_ = true;
    }
    if (!gameReset_) {

      // next
      if (input->PushKey(DIK_SPACE)) {
        isReset_ = true;
      }
    }
  }

  if (isReset_) {
    // 表
    uint32_t texHandle = texM->LoadPngTex("front");
    coins_[0]->SetUpTex(texHandle);

    // 裏
    texHandle = texM->LoadPngTex("back");
    coins_[1]->SetUpTex(texHandle);

    // 表
    texHandle = texM->LoadPngTex("front");
    coins_[2]->SetUpTex(texHandle);
    // 裏
    texHandle = texM->LoadPngTex("back");
    coins_[3]->SetUpTex(texHandle);
    isSelect_ = false;
    isReset_ = false;
    isEnemyAttack_ = false;
  }



  ImGui::Begin("BESample");

  ImGui::Text("Rank");

  //ここに表示

  if (getScoreFuture_.valid() && getScoreFuture_.wait_for(std::chrono::seconds(
                                     0)) == std::future_status::ready) {

    std::string jsonResponse = getScoreFuture_.get();

    try {
      nlohmann::json json = nlohmann::json::parse(jsonResponse);

      // スコアだけを格納
      std::vector<int> allScores;

      for (auto &entry : json) {
        allScores.push_back(entry["score"].get<int>());
      }

      // 高い順にソート
      std::sort(allScores.begin(), allScores.end(), std::greater<>());

      // 上位5件を表示（必要に応じて調整）
      int maxDisplay = std::min(5, static_cast<int>(allScores.size()));
      rankText_ = "";
      for (int i = 0; i < maxDisplay; ++i) {
        // 例えば順位とスコアをテキストにまとめる場合
      
        rankText_ +=
            std::to_string(i + 1) + ":: " + std::to_string(allScores[i]) + "\n";

        // ImGuiで表示したい場合はコメントアウトを外す
        // ImGui::Text("%d:: %d", i + 1, allScores[i]);
      }

    } catch (...) {
      ImGui::Text("エラー: JSON解析失敗");
    }
  }

  
  ImGui::Text("%s", rankText_.c_str());

  ImGui::Separator();
  ImGui::Text("%d", scores_*1000);

  if (isSelect_ && !gameReset_) {

    ImGui::Text("next");
  }

  if (gameReset_) {
    ImGui::Text("GameSet");
  }
  ImGui::End();

  if (gameReset_) {

    if (input->PushKey(DIK_R)) {

      PostScoreAsync(scores_*1000);
      g->ChangeScene(std::make_unique<SampleGameScene>());
      return;
    }
  }

  // sprite更新
  std::list<std::string> spNames;
  for (auto s : spriteComponents_) {

#ifdef _DEBUG

    if (s.lock()->GetName() != "") {
      for (std::string name : spNames) {
        if (name == s.lock()->GetName()) {
          // 同じものが複数回呼び出されてる
          assert(0);
        }
      }
    }
#endif // _DEBUG
    s.lock()->Update();
    spNames.push_back(s.lock()->GetName());
  }
}

void SampleGameScene::Draw2d() {

  for (size_t i = 0; i < 4; i++) {

    coins_[i]->Draw();
  }
}
