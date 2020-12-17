#include "Animator2D.h"
#include "Anim2D.h"
#include "ImageRenderer.h"
#include "Time.h"
#include "Function.h"

Animator2D::Animator2D() :
	renderer(nullptr), state(nullptr), currentAnim(nullptr), currentState("")
{
	animations.clear();
}

Animator2D::~Animator2D()
{
	for(std::map<std::string, Anim2D*>::iterator it = animations.begin(); it != animations.end();){
		delete it->second;
		it = animations.erase(it);
	}
}

void Animator2D::Start()
{
	// イメージレンダラーの取得・追加
	renderer = GetComponent<ImageRenderer>();
	if (renderer == nullptr)
		renderer = AddComponent<ImageRenderer>();
}

void Animator2D::Update()
{
	if (state != nullptr && currentState != "") {
		state->Update();

		if (currentState != state->GetState()) {
			ChangeStateAnim();
		}
		if (currentAnim != nullptr) {
			currentAnim->Update();
		}
	}
}

bool Animator2D::SetStateMachine(StateMachine* _stateMachine)
{
	if (state != nullptr)
		return false;

	state = _stateMachine;
	state->Start();

	// 現在のステータスを設定
	currentState = state->GetState();

	// ステータス名をからmapを初期化
	std::list<std::string> states = state->GetStateAll();
	for (std::list<std::string>::iterator it = states.begin(); it != states.end(); ++it) {
		animations.emplace((*it), nullptr);
	}

	return true;
}

std::string Animator2D::GetState() const
{
	return state->GetState();
}

bool Animator2D::GetBool(const std::string& _boolName)
{
	return state->GetBool(_boolName);
}

bool Animator2D::SetBool(const std::string& _boolName, bool _bool)
{
	return state->SetBool(_boolName, _bool);
}

Anim2D* Animator2D::SetAnim(const std::string& _stateName, const std::string& _filePass, unsigned int _xdiv, unsigned int _ydiv, unsigned int _allnum, float _playSpeed, unsigned int _start, unsigned int _end, bool _isLoop)
{
	Anim2D* anim = new Anim2D(renderer);
	Anim2D** setArea = FindStateAnim(_stateName);
	bool isExistState = state->isExistState(_stateName);
	bool settingYet = *setArea == nullptr;
	bool okaySetting = 
		anim->SetUsedImage(_filePass, _xdiv, _ydiv, _allnum)
		&& anim->SetPlaySpeed(_playSpeed) 
		&& anim->SetPlayNum(_start, _end);

	if (isExistState && settingYet && okaySetting) {
		anim->loopFlag = _isLoop;
		if (setArea != nullptr) {
			*setArea = anim;
		}
		if (currentState == _stateName) {
			currentAnim = anim;
			currentAnim->Start();
		}
		return anim;
	}
	else {
		delete anim;
		return nullptr;
	}
}

Anim2D* Animator2D::GetAnim(const std::string& _animName)
{
	return *FindStateAnim(_animName);
}

Anim2D** Animator2D::FindStateAnim(const std::string& _name)
{
	std::map<std::string, Anim2D*>::iterator it = animations.find(_name);
	if (it == animations.end())
		return nullptr;

	return &((*it).second);
}

void Animator2D::ChangeStateAnim()
{
	currentState = state->GetState();

	currentAnim = animations.find(currentState)->second;

	if (currentAnim != nullptr) {
		currentAnim->Start();
	}
}

Anim2D* Animator2D::GetCurrentAnim()
{
	return currentAnim;
}
