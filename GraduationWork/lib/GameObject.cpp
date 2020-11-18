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
	// 更新処理
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
	// 引数がnullptrなら終了
	if (_obj == nullptr) return;

	parent = _obj;
	_obj->SetChild(this);
}

std::list<GameObject*> GameObject::GetChild(std::string _tag) const
{
	std::list<GameObject*> list;

	// 対応した名前の子GameObject抽出
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
	// 既に子に存在したら終了
	for (auto child : children) {
		if (child == _obj)
			return false;
	}

	// 子のリストに追加
	children.push_back(_obj);
	_obj->parent = this;

	return true;
}

bool GameObject::RemoveChild(GameObject* _obj)
{
	// 対応した子GameObjectの破壊フラグを立てる
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

	// 対応したタグの子GameObjectの破壊フラグを立てる
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
	// 全ての子GameObjectの破壊フラグを立てる
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