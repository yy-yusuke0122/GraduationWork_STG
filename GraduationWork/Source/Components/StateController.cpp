//#include "StateController.h"
//
//StateController::StateController() :
//	currentState("")
//{
//	boolList.clear();
//	transDirList.clear();
//	states.clear();
//}
//
//StateController::~StateController()
//{
//	for (std::list<TransBool*>::iterator it = boolList.begin(); it != boolList.end();) {
//		delete (*it);
//		it = boolList.erase(it);
//	}
//
//	for (std::list<TransDirection*>::iterator it = transDirList.begin(); it != transDirList.end();) {
//		delete (*it);
//		it = transDirList.erase(it);
//	}
//}
//
//void StateController::Update()
//{
//	// 初期ステータスが設定されていない場合無視する
//	if (currentState == "") return;
//
//	// 遷移する必要があれば遷移する
//	TransDirection* dir = nullptr;
//	if (IsTranslate(dir)) {
//		currentState = dir->dirState;
//	}
//}
//
//void StateController::SetDefaultState(const std::string& _stateName)
//{
//	if (isExistState(_stateName)) {
//		currentState = _stateName;
//	}
//}
//
//void StateController::CreateNewState(const std::string& _stateName)
//{
//	// 既に存在するステータスなら無視する
//	for (std::list<std::string>::iterator it = states.begin(); it != states.end(); ++it) {
//		if ((*it) == _stateName) {
//			return;
//		}
//	}
//
//	// 新しくステータスを追加
//	states.push_back(_stateName);
//}
//
//void StateController::CreateNewTransDir(const std::string& _sourceState, const std::string& _dirState)
//{
//	bool end = false;
//
//	// 遷移前と遷移後が同じなら無視する
//	end = _sourceState == _dirState;
//	if (end) return;
//
//	// 存在しないステータスなら無視する
//	end = !(isExistState(_sourceState) && isExistState(_dirState));
//	if (end) return;
//
//	// 既に存在する遷移の流れなら無視する
//	end = isExistTransDir(_sourceState, _dirState);
//	if (end) return;
//
//	// 新しく遷移の流れを追加
//	TransDirection* dir = new TransDirection(_sourceState, _dirState);
//	transDirList.push_back(dir);
//}
//
//void StateController::CreateNewTransBool(const std::string& _name)
//{
//	// 既に存在する遷移条件なら無視する
//	if (isExistTransBool(_name))
//		return;
//
//	// 新しく遷移条件を生成する
//	TransBool* newBool = new TransBool(_name);
//	boolList.push_back(newBool);
//}
//
//void StateController::SetTransInfo(const std::string& _sourceState, const std::string& _dirState, const std::string& _boolName, bool _enable)
//{
//	TransDirection* dir = nullptr;
//
//	// 対応する遷移の流れを取得
//	for (std::list<TransDirection*>::iterator it = transDirList.begin(); it != transDirList.end(); ++it) {
//		bool isSameSource = (*it)->sourceState == _sourceState;
//		bool isSameDir = (*it)->dirState == _dirState;
//		if (isSameSource && isSameDir) {
//			dir = (*it);
//			break;
//		}
//	}
//
//	// 取得失敗で無視する
//	if (dir == nullptr) 
//		return;
//
//	// 既に設定している遷移条件なら無視する
//	if (dir->info.IsExistInfo(_boolName))
//		return;
//
//	// 対応する遷移条件を追加
//	for (std::list<TransBool*>::iterator it = boolList.begin(); it != boolList.end(); ++it) {
//		if ((*it)->name == _boolName) {
//			dir->info.transBool.emplace_back((*it));
//			dir->info.transState.emplace_back(_enable);
//			return;
//		}
//	}
//}
//
//bool StateController::GetBool(const std::string& _boolName)
//{
//	for (std::list<TransBool*>::iterator it = boolList.begin(); it != boolList.end(); ++it) {
//		if ((*it)->name == _boolName) {
//			return (*it)->enable;
//		}
//	}
//	return false;
//}
//
//bool StateController::SetBool(const std::string& _boolName, bool _bool)
//{
//	for (std::list<TransBool*>::iterator it = boolList.begin(); it != boolList.end(); ++it) {
//		if ((*it)->name == _boolName) {
//			(*it)->enable = _bool;
//			return true;
//		}
//	}
//	return false;
//}
//
//bool StateController::isExistState(const std::string& _name)
//{
//	for (std::list<std::string>::iterator it = states.begin(); it != states.end(); ++it) {
//		if ((*it) == _name) {
//			return true;
//		}
//	}
//
//	return false;
//}
//
//bool StateController::isExistTransDir(const std::string& _sourceState, const std::string& _dirState)
//{
//	for (std::list<TransDirection*>::iterator it = transDirList.begin(); it != transDirList.end(); ++it) {
//		bool isSameSource = (*it)->sourceState == _sourceState;
//		bool isSameDir = (*it)->dirState == _dirState;
//		if (isSameSource && isSameDir) {
//			return true;
//		}
//	}
//
//	return false;
//}
//
//bool StateController::isExistTransBool(const std::string& _name)
//{
//	for (std::list<TransBool*>::iterator it = boolList.begin(); it != boolList.end(); ++it) {
//		if ((*it)->name == _name) {
//			return true;
//		}
//	}
//
//	return false;
//}
//
//bool StateController::IsTranslate(TransDirection*& _dir)
//{
//	// 現在のステータスからの遷移の流れを全て抽出
//		std::list<TransDirection*> checkDir;
//	for (auto it : transDirList) {
//		if (it->sourceState == currentState) {
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
//bool StateController::TransDirInfo::IsTranslate()
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
//bool StateController::TransDirInfo::IsExistInfo(const std::string& _boolName)
//{
//	for (int i = 0; i < transBool.size(); ++i) {
//		if (transBool.at(i)->name == _boolName) {
//			return true;
//		}
//	}
//
//	return false;
//}
//
//bool StateController::TransDirection::IsTranslate()
//{
//	return info.IsTranslate();
//}
