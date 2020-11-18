#include "BoxCollider2D.h"
#include "UrLib.h"
#include "CircleCollider2D.h"

BoxCollider2D::BoxCollider2D() :
	rotation(0.0f)
{
	box.hl.x = 0.5f;
	box.hl.y = 0.5f;
}

BoxCollider2D::~BoxCollider2D()
{
}

void BoxCollider2D::Disp()
{
	AABB2D dispBox = box;
	dispBox.p = GetWorldPosition();
	float rad = ToRadian(rotation);
	DrawRotaBox(dispBox, rad, GetColor(255, 255, 255), FALSE);
	printfDx("rotation = %f\n", rotation);
}

bool BoxCollider2D::IsCollide(Collider2D* _collider)
{
	CircleCollider2D* col_c = dynamic_cast<CircleCollider2D*>(_collider);
	BoxCollider2D* col_b = dynamic_cast<BoxCollider2D*>(_collider);
	if (col_c != nullptr) {	// �Ώۂ�CircleCollider�̎�
		return IsCollideCircle(col_c);
	}
	else if (col_b != nullptr) { // �Ώۂ�BoxCollider�̎�
		return IsCollideBox(col_b);
	}
	return false;
}

Point2D BoxCollider2D::GetWorldPosition()
{
	Point p = transform->position + box.p;
	return Point2D(p.x, p.y);
}

Point2D BoxCollider2D::LeftTop()
{
	MATRIX matZ = MGetRotZ(ToRadian(rotation));
	VECTOR2 lt = box.LeftTop();
	Point p = VTransform(VGet(lt.x, lt.y, 0.0f), matZ);
	Point2D p2(p.x, p.y);
	p2 = p2 + GetWorldPosition();
	return p2;
}

Point2D BoxCollider2D::LeftBottom()
{
	MATRIX matZ = MGetRotZ(ToRadian(rotation));
	VECTOR2 lb = box.LeftBottom();
	Point p = VTransform(VGet(lb.x, lb.y, 0.0f), matZ);
	Point2D p2(p.x, p.y);
	p2 = p2 + GetWorldPosition();
	return p2;
}

Point2D BoxCollider2D::RightTop()
{
	MATRIX matZ = MGetRotZ(ToRadian(rotation));
	VECTOR2 rt = box.RightTop();
	Point p = VTransform(VGet(rt.x, rt.y, 0.0f), matZ);
	Point2D p2(p.x, p.y);
	p2 = p2 + GetWorldPosition();
	return p2;
}

Point2D BoxCollider2D::RightBottom()
{
	MATRIX matZ = MGetRotZ(ToRadian(rotation));
	VECTOR2 rb = box.RightBottom();
	Point p = VTransform(VGet(rb.x, rb.y, 0.0f), matZ);
	Point2D p2(p.x, p.y);
	p2 = p2 + GetWorldPosition();
	return p2;
}

bool BoxCollider2D::IsCollideCircle(CircleCollider2D* _collider)
{
	// ��`�O�x�̎��̍��W�ɉ~�̊p�x�𒼂�
	Point2D circle = _collider->GetWorldPosition();
	float radian = ToRadian(rotation);
	Point2D rect = GetWorldPosition();
	Point2D c;

	c.x = static_cast<float>(cos(radian) * ((double)circle.x - (double)rect.x) - sin(radian) * ((double)circle.y - (double)rect.y) + rect.x);
	c.y = static_cast<float>(sin(radian) * ((double)circle.x - (double)rect.x) + cos(radian) * ((double)circle.y - (double)rect.y) + rect.y);

	// �~�̒��S�_�����`�̂P�ԋ߂����_�̍��W
	Point2D p;

	// �Z�a�̒��_���W
	Point2D lt(box.LeftTop() + rect);
	Point2D rb(box.RightBottom() + rect);

	// �P�ԋ߂�x���W�����߂�
	if (c.x < rect.x)
		p.x = lt.x;
	else if (c.x > rect.x)
		p.x = rb.x;
	else
		p.x = c.x;

	// �P�ԋ߂�y���W�����߂�
	if (c.y < rect.y)
		p.y = lt.y;
	else if (c.y > rect.y)
		p.y = rb.y;
	else
		p.y = c.y;

	// ��ԋ߂��p�ۂƂ̏Փ˔���
	float radius = _collider->circle.r;
	float distance = (c - p).Length();
	if (distance < radius)
		return true; // �Փ�

	// �~�̒��S�_�ƒ����`�̂����蔻��
	bool a = c.x > lt.x && c.x < rb.x && c.y > lt.y - radius && c.y < rb.y + radius;
	bool b = c.x > lt.x - radius && c.x < rb.x + radius && c.y > lt.y && c.y < rb.y;
	if (a || b)  return true;
	else return false;
}

bool BoxCollider2D::IsCollideBox(BoxCollider2D* _collider)
{
	// �����̒��_
	Point2D myP[4];
	myP[0] = LeftTop();
	myP[1] = RightTop();
	myP[2] = RightBottom();
	myP[3] = LeftBottom();
	// ����̒��_
	Point2D pairP[4];
	pairP[0] = _collider->LeftTop();
	pairP[1] = _collider->RightTop();
	pairP[2] = _collider->RightBottom();
	pairP[3] = _collider->LeftBottom();

	// �������\������S�ӂ̃x�N�g��
	VECTOR2 myVec[4];
	myVec[0] = myP[1] - myP[0];
	myVec[1] = myP[2] - myP[1];
	myVec[2] = myP[3] - myP[2];
	myVec[3] = myP[0] - myP[3];
	// �������\������S�ӂ̃x�N�g��
	VECTOR2 pairVec[4];
	pairVec[0] = pairP[1] - pairP[0];
	pairVec[1] = pairP[2] - pairP[1];
	pairVec[2] = pairP[3] - pairP[2];
	pairVec[3] = pairP[0] - pairP[3];

	// �����蔻��m�F
	for (int i = 0; i < 4; ++i) { // �S���_�`�F�b�N
		bool isHit = true;
		VECTOR2 v[4];
		v[0] = pairP[i] - myP[0];
		v[1] = pairP[i] - myP[1];
		v[2] = pairP[i] - myP[2];
		v[3] = pairP[i] - myP[3];
		for (int j = 0; j < 4; ++j) {
			float dot = myVec[j].Cross(v[j]);
			if (dot < 0.0f) {
				isHit = false;
				break;
			}
		}
		if (isHit) return true;
	}
	for (int i = 0; i < 4; ++i) { // �S���_�`�F�b�N
		bool isHit = true;
		VECTOR2 v[4];
		v[0] = myP[i] - pairP[0];
		v[1] = myP[i] - pairP[1];
		v[2] = myP[i] - pairP[2];
		v[3] = myP[i] - pairP[3];
		for (int j = 0; j < 4; ++j) {
			float dot = pairVec[j].Cross(v[j]);
			if (dot < 0.0f) {
				isHit = false;
				break;
			}
		}
		if (isHit) return true;
	}

	return false;
}
