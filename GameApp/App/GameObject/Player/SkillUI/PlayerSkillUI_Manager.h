#pragma once
#include "CLEYERA.h"

#include "IPlayerSkillUI.h"
#include "BG/PlayerSkillUI_BG.h"
#include "Low/Normal/PlayerSkillUI_LowNormal.h"
#include "Low/Back/PlayerSkillUI_LowBack.h"
#include "High/Normal/PlayerSkillUI_HighNormal.h"
#include "High/Field/PlayerSkillUI_HighField.h"
#include "Special/Norml/PlayerSkillUI_SpecialNormal.h"
#include "Special/Power/PlayerSkillUI_SpecialPower.h"


class PlayerCore;


class PlayerSkillUI_Manager {

public:

	enum class SkillTypes {
		Low_Normal,
		Low_Back,
		High_Normal,
		High_Field,
		Special_Normal,
		Special_Power,
	};

	PlayerSkillUI_Manager() = default;
	~PlayerSkillUI_Manager() = default;

	void Init();
	void Update();
	void Draw2D();

	void SetPtr(std::weak_ptr<PlayerCore> corePtrm, SceneComponent * scenePtr) {
		p_playerCore_ = corePtrm;
		scene_ = scenePtr;
	}

	void SetActive(int uint, bool state) {
		skillUIs_[uint ]->SetActive(state);
	}

private:


private:


	std::weak_ptr<PlayerCore> p_playerCore_;
	SceneComponent * scene_ = nullptr;

	std::array<std::shared_ptr<PlayerSkillUI_BG>, 3> skillBg_;
	std::vector<std::shared_ptr<IPlayerSkillUI>> skillUIs_;

};