#include "ScreenOut.h"

void ScreenOut::OnCollisionExit2D(Collider2D* _collider)
{
	if (_collider->gameObject->tag == "ScreenCollider")
	{
		gameObject->Destroy();
	}
}
