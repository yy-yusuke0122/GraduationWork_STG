#include "CollideManager.h"
#include "CollideManager2D.h"
#include "CollideManager3D.h"

CollideManager* CollideManager::instance = nullptr;

CollideManager::CollideManager()
{
    manager2D = new CollideManager2D();
    manager3D = new CollideManager3D();
}

CollideManager::~CollideManager()
{
    delete manager2D;
    delete manager3D;
}

CollideManager* CollideManager::Get()
{
    if (instance == nullptr) {
        instance = new CollideManager();
    }

    return instance;
}

bool CollideManager::Destroy()
{
    if (instance == nullptr)
        return false;

    delete instance;
    return true;
}

void CollideManager::Start()
{
    manager2D->Init();
}

void CollideManager::Update()
{
    // “–‚½‚è”»’è‚ÌŠm”F
    manager2D->Update();
    manager3D->Update();
}

void CollideManager::RemoveAllCollider()
{
    manager2D->RemoveAll();
}

bool CollideManager::PushCollider2D(Collider2D* _col)
{
    // nullptr‚Å‚Í‚¶‚­
    if (_col == nullptr) return false;

    return manager2D->PushCollider(_col);
}

bool CollideManager::PushCollider3D(Collider3D* _col)
{
    // nullptr‚Å‚Í‚¶‚­
    if (_col == nullptr) return false;

    return manager3D->PushCollider(_col);
}

void CollideManager::RemoveCollider2D(Collider2D* _col)
{
    // nullptr‚Å‚Í‚¶‚­
    if (_col == nullptr) return;

    manager2D->RemoveCollider(_col);
}

void CollideManager::RemoveCollider3D(Collider3D* _col)
{
    // nullptr‚Å‚Í‚¶‚­
    if (_col == nullptr) return;

    manager3D->RemoveCollider(_col);
}
