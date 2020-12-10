#include "Animator2D.h"
#include "ImageRenderer.h"
#include "Time.h"
#include "Function.h"

//Animator2D::Animator2D() :
//	controller(nullptr), imageRenderer(nullptr), currentAnim(nullptr), currentAnimName(""), nextAnimName(""), animCount(0.0f), drawNum(0)
//{
//	animList.clear();
//}

Animator2D::Animator2D()
{
}

Animator2D::~Animator2D()
{
}

void Animator2D::Start()
{
}

void Animator2D::Update()
{
	//if (controller == nullptr)
	//	return;

	//if (imageRenderer == nullptr) {
	//	imageRenderer = GetComponent<ImageRenderer>();
	//	if (imageRenderer == nullptr)
	//		return;
	//}

	//// アニメーション切り替え
	//TransAnimation();

	//// 再生中のアニメーションが無ければ終了
	//if (currentAnim == nullptr)
	//	return;

	//// アニメーション処理
	//animCount += currentAnim->speed * Time::DeltaTime();
	//if (animCount >= 1.0f) {
	//	animCount = 0.0f;
	//	if (++drawNum > currentAnim->end) {
	//		drawNum = currentAnim->start;
	//	}
	//	imageRenderer->SetImageNumber(drawNum);
	//}
}

//bool Animator2D::AddAnim(unsigned int _start, unsigned int _end, std::string _animName, float _animSpeed, bool _isLoop)
//{
//	// 既に追加されていれば終了
//	if (GetAnim(_animName) != nullptr)
//		return false;
//
//	// アニメーションを生成し、追加する
//	Anim2D* newAnim = new Anim2D(_start, _end, _animName, _animSpeed, _isLoop);
//	animList.push_back(newAnim);
//
//	return true;
//}
//
//bool Animator2D::DeleteAnim(std::string _animName)
//{
//	for (auto it = animList.begin(); it != animList.end();) {
//		if ((*it)->name == _animName) {
//			delete (*it);
//			it = animList.erase(it);
//			return true;
//		}
//		else {
//			++it;
//		}
//	}
//
//	return false;
//}
//
//bool Animator2D::SetStartAnim(std::string _animName)
//{
//	// 既に追加されていれば終了
//	if (GetAnim(_animName) == nullptr)
//		return false;
//
//	nextAnimName = _animName;
//	return true;
//}
//
//Anim2D* Animator2D::GetAnim(std::string _animName)
//{
//	for (auto anim : animList) {
//		if (anim->name == _animName) {
//			return anim;
//		}
//	}
//
//	return nullptr;
//}
//
//Anim2D* Animator2D::GetCurrentAnim()
//{
//	return currentAnim;
//}
//
//int Animator2D::GetDrawNum() const
//{
//	return drawNum;
//}
//
//bool Animator2D::SetDrawNum(unsigned int _num)
//{
//	if (IsInSideValue(_num, currentAnim->start, currentAnim->end + 1)) {
//		drawNum = _num;
//		return true;
//	}
//
//	return false;
//}
//
//bool Animator2D::GetBool(std::string _boolName)
//{
//	for (auto it : boolList) {
//		if (it->boolName == _boolName) {
//			return it->enable;
//		}
//	}
//	return false;
//}
//
//void Animator2D::SetBool(std::string _boolName, bool _bool)
//{
//	for (auto it : boolList) {
//		if (it->boolName == _boolName) {
//			it->enable = _bool;
//		}
//	}
//}
//
//bool Animator2D::CreateBool(std::string _boolName)
//{
//	// 同じ名称のAnimBoolを見つけたら終了させる
//	for (auto it : boolList) {
//		if (it->boolName == _boolName)
//			return false;
//	}
//
//	// 新しい遷移用Boolを生成
//	TransBool* newBool = new TransBool(_boolName);
//	boolList.emplace_back(newBool);
//
//	return true;
//}
//
//bool Animator2D::CreateTransDirection(std::string _sourceName, std::string _dirName)
//{
//	// 同じTransDirectionを見つけたら終了させる
//	for (auto it : transDirList) {
//		if (it->sourceName == _sourceName &&
//			it->dirName == _dirName)
//			return false;
//	}
//
//	// 新しいTransDirectionを生成
//	TransDirection* newDir = new TransDirection(_sourceName, _dirName);
//	transDirList.emplace_back(newDir);
//
//	return true;
//}
//
//bool Animator2D::AddTransDirInfo(std::string _sourceName, std::string _dirName, std::string _boolName, bool _enable)
//{
//	// 対応するTransDirectionを抽出
//	TransDirection* dir = nullptr;
//	for (auto it : transDirList) {
//		if (it->sourceName == _sourceName &&
//			it->dirName == _dirName) {
//			dir = it;
//			break;
//		}
//	}
//	if (dir == nullptr) return false;	// 抽出失敗で終了
//
//	// 既に使われているboolが見つかったら、追加せず終了
//	for (auto it : dir->info.transBool) {
//		if (it->boolName == _boolName)
//			return false;
//	}
//
//	// 新しい遷移条件を追加
//	for (auto it : boolList) {	// boolリストから対応したboolを追加
//		if (it->boolName == _boolName) {
//			dir->info.transBool.emplace_back(it);
//			break;
//		}
//	}
//	dir->info.transState.emplace_back(_enable);
//
//	return true;
//}
//
//void Animator2D::TransAnimation()
//{
//	if (controller-> != nextAnimName) {
//		for (auto anim : animList) {
//			if (anim->name == nextAnimName) {
//				currentAnim = anim;
//				drawNum = currentAnim->start;
//				currentAnimName = nextAnimName;
//				animCount = 0.0f;
//				imageRenderer->SetImageNumber(drawNum);
//			}
//		}
//	}
//}
//
//bool Animator2D::IsTranslate(TransDirection*& _dir)
//{
//	// 現在のアニメーションの名前と一致するSourceNameのTransDirを全て抽出
//	std::list<TransDirection*> checkDir;
//	for (auto it : transDirList) {
//		if (it->sourceName == currentAnimName) {
//			checkDir.emplace_back(it);
//		}
//	}
//	if (checkDir.size() == 0) return false;	// 見つからなければ終了
//
//	// 抽出したTransDirの中から、遷移条件を満たしているものを１つ抽出
//	TransDirection* transDir = nullptr;
//	for (auto it : checkDir) {
//		if (it->IsTranslate()) {
//			transDir = it;
//			break;
//		}
//	}
//	if (transDir == nullptr) return false;	// 見つからなければ終了
//
//	// 抽出したTransDirを代入
//	_dir = transDir;
//	return true;
//}
//
//bool Animator2D::TransDirInfo::IsTranslate()
//{
//	int size = static_cast<int>(transBool.size());
//	for (int i = 0; i < size; ++i) {
//		// 遷移条件と一致していないboolがあれば遷移しない
//		if (transBool.at(i)->enable != transState.at(i))
//			return false;
//	}
//	return true;
//}
//
//bool Animator2D::TransDirection::IsTranslate()
//{
//	return info.IsTranslate();
//}
