#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject() :
	parent(nullptr), scene(nullptr), tag("")
{
	transform = new Transform();
	transform->gameObject = this;
	compList.clear();
	children.clear();
}

GameObject::~GameObject()
{
	delete transform;
	for (auto it = compList.begin(); it != compList.end();) {
		delete (*it);
		it = compList.erase(it);
	}
}

void GameObject::Update()
{	
	// �X�V����
	for (auto comp : compList) {
		if (comp->IsActive()) {
			comp->Update();
		}
	}
}

GameObject* GameObject::GetParent() const
{
	return parent;
}

void GameObject::SetParent(GameObject* _obj)
{
	// ������nullptr�Ȃ�I��
	if (_obj == nullptr) return;

	parent = _obj;
	_obj->SetChild(this);
}

std::list<GameObject*> GameObject::GetChild(std::string _tag) const
{
	std::list<GameObject*> list;

	// �Ή��������O�̎qGameObject���o
	for (auto child : children) {
		if (child->tag == _tag) {
			list.push_back(child);
		}
	}
	return list;
}

std::list<GameObject*> GameObject::GetChildren() const
{
	return children;
}

bool GameObject::SetChild(GameObject* _obj)
{
	// ���Ɏq�ɑ��݂�����I��
	for (auto child : children) {
		if (child == _obj)
			return false;
	}

	// �q�̃��X�g�ɒǉ�
	children.push_back(_obj);
	_obj->parent = this;

	return true;
}

bool GameObject::RemoveChild(GameObject* _obj)
{
	// �Ή������qGameObject�̔j��t���O�𗧂Ă�
	for (auto child : children) {
		if (child == _obj) {
			child->Destroy();
			return true;
		}
	}
	return false;
}

bool GameObject::RemoveChild(std::string _tag)
{
	bool ret = false;

	// �Ή������^�O�̎qGameObject�̔j��t���O�𗧂Ă�
	for (auto child : children) {
		if (child->tag == _tag) {
			child->Destroy();
			ret = true;
		}
	}
	return ret;
}

void GameObject::RemoveChildren()
{
	// �S�Ă̎qGameObject�̔j��t���O�𗧂Ă�
	for (auto child : children) {
		child->Destroy();
	}
}

std::list<Component*> GameObject::GetComponentAll()
{
	return compList;
}

void GameObject::RemoveComponentAll()
{
	for (auto it = compList.begin(); it != compList.end();) {
		delete (*it);
		it = compList.erase(it);
	}
}

void GameObject::DestroyComponents()
{
	for (auto it = compList.begin(); it != compList.end();) {
		if ((*it)->IsDestroy()) {
			delete (*it);
			it = compList.erase(it);
		}
		else {
			++it;
		}
	}
}

Scene* GameObject::GetScene() const
{
	return scene;
}

void GameObject::SetActive(bool _active)
{
	active = _active;

	for (auto child : children) {
		child->SetActive(_active);
	}
}

GameObject* GameObject::func(GameObject* _p)
{
	scene->AddGameObject(_p);

	_p->scene = scene;

	return _p;
}