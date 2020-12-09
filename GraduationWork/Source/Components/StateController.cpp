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
//	// �����X�e�[�^�X���ݒ肳��Ă��Ȃ��ꍇ��������
//	if (currentState == "") return;
//
//	// �J�ڂ���K�v������ΑJ�ڂ���
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
//	// ���ɑ��݂���X�e�[�^�X�Ȃ疳������
//	for (std::list<std::string>::iterator it = states.begin(); it != states.end(); ++it) {
//		if ((*it) == _stateName) {
//			return;
//		}
//	}
//
//	// �V�����X�e�[�^�X��ǉ�
//	states.push_back(_stateName);
//}
//
//void StateController::CreateNewTransDir(const std::string& _sourceState, const std::string& _dirState)
//{
//	bool end = false;
//
//	// �J�ڑO�ƑJ�ڌオ�����Ȃ疳������
//	end = _sourceState == _dirState;
//	if (end) return;
//
//	// ���݂��Ȃ��X�e�[�^�X�Ȃ疳������
//	end = !(isExistState(_sourceState) && isExistState(_dirState));
//	if (end) return;
//
//	// ���ɑ��݂���J�ڂ̗���Ȃ疳������
//	end = isExistTransDir(_sourceState, _dirState);
//	if (end) return;
//
//	// �V�����J�ڂ̗����ǉ�
//	TransDirection* dir = new TransDirection(_sourceState, _dirState);
//	transDirList.push_back(dir);
//}
//
//void StateController::CreateNewTransBool(const std::string& _name)
//{
//	// ���ɑ��݂���J�ڏ����Ȃ疳������
//	if (isExistTransBool(_name))
//		return;
//
//	// �V�����J�ڏ����𐶐�����
//	TransBool* newBool = new TransBool(_name);
//	boolList.push_back(newBool);
//}
//
//void StateController::SetTransInfo(const std::string& _sourceState, const std::string& _dirState, const std::string& _boolName, bool _enable)
//{
//	TransDirection* dir = nullptr;
//
//	// �Ή�����J�ڂ̗�����擾
//	for (std::list<TransDirection*>::iterator it = transDirList.begin(); it != transDirList.end(); ++it) {
//		bool isSameSource = (*it)->sourceState == _sourceState;
//		bool isSameDir = (*it)->dirState == _dirState;
//		if (isSameSource && isSameDir) {
//			dir = (*it);
//			break;
//		}
//	}
//
//	// �擾���s�Ŗ�������
//	if (dir == nullptr) 
//		return;
//
//	// ���ɐݒ肵�Ă���J�ڏ����Ȃ疳������
//	if (dir->info.IsExistInfo(_boolName))
//		return;
//
//	// �Ή�����J�ڏ�����ǉ�
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
//	// ���݂̃X�e�[�^�X����̑J�ڂ̗����S�Ē��o
//		std::list<TransDirection*> checkDir;
//	for (auto it : transDirList) {
//		if (it->sourceState == currentState) {
//			checkDir.emplace_back(it);
//		}
//	}
//	if (checkDir.size() == 0) return false;	// ������Ȃ���ΏI��
//
//	// ���o����TransDir�̒�����A�J�ڏ����𖞂����Ă�����̂��P���o
//	TransDirection* transDir = nullptr;
//	for (auto it : checkDir) {
//		if (it->IsTranslate()) {
//			transDir = it;
//			break;
//		}
//	}
//	if (transDir == nullptr) return false;	// ������Ȃ���ΏI��
//
//	// ���o����TransDir����
//	_dir = transDir;
//	return true;
//}
//
//bool StateController::TransDirInfo::IsTranslate()
//{
//	int size = static_cast<int>(transBool.size());
//	for (int i = 0; i < size; ++i) {
//		// �J�ڏ����ƈ�v���Ă��Ȃ�bool������ΑJ�ڂ��Ȃ�
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
