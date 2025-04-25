#include "playerCore.h"



/// <summary>
/// 初期化処理
/// </summary>
void PlayerCore::Init()
{
	// クラス名
	ObjectComponent::name_ = VAR_NAME(PlayerCore);

	// Modelの設定
	std::pair<std::string, std::string> str = {
		"Resources/Model/Player/Core", "Core" };
	uint32_t handle = ObjectComponent::modelManager_->LoadModel(str.first, str.second);
	ObjectComponent::gameObject_->ChangeModel(handle);

	// コライダー作成
	ObjectComponent::CreateCollider(ColliderType::OBB);

}


/// <summary>
/// 更新処理
/// </summary>
void PlayerCore::Update()
{
	TransformUpdate();
}
