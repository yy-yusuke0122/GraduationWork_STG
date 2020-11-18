#include "Bone.h"
#include "MeshRendererInfo.h"
#include "MeshRenderer.h"
#include "Function.h"

namespace
{
	constexpr COLOR_F defColor{ 1.f, 1.f, 1.f, 1.f };

	void ClampColor(COLOR_F& _color)
	{
		Clamp(_color.r, 0.f, 1.f);
		Clamp(_color.g, 0.f, 1.f);
		Clamp(_color.b, 0.f, 1.f);
		Clamp(_color.a, 0.f, 1.f);
	}
}

Bone::Bone() :
	diffuse(defColor), specular(defColor), ambient(defColor), emissive(defColor), alpha(1.f)
{
}

void Bone::Set()
{
	ClampColor(diffuse);
	ClampColor(specular);
	ClampColor(emissive);
	ClampColor(ambient);
	Clamp(alpha, 0.f, 1.f);

	MV1SetFrameVisible(info->handle, no, (isDisp) ? TRUE : FALSE);

	MV1SetFrameDifColorScale(info->handle, no, diffuse);
	MV1SetFrameSpcColorScale(info->handle, no, specular);
	MV1SetFrameAmbColorScale(info->handle, no, ambient);
	MV1SetFrameEmiColorScale(info->handle, no, emissive);
	MV1SetFrameOpacityRate(info->handle, no, alpha);
}

std::string Bone::GetName() const
{
	return info->bones[no].name;
}

Bone* Bone::GetParent()
{
	int i = info->bones[no].parent;
	
	if (i == -1)
		return nullptr;

	return renderer->GetBone(i);
}

unsigned Bone::GetChildCount() const
{
	return static_cast<unsigned>(info->bones[no].children.size());
}

Bone* Bone::GetChild(unsigned _count)
{
	if (_count < GetChildCount())
		return renderer->GetBone(info->bones[no].children[_count]);
	return nullptr;
}

Bone* Bone::GetChild(const std::string& _name)
{
	for (unsigned i = 0u, size = GetChildCount(); i < size; ++i)
	{
		Bone* p = GetChild(i);
		if (_name == p->GetName())
			return p;
	}
	return nullptr;
}

bool Bone::IsSemiTrans() const
{
	return info->bones[no].isSemiTrans;
}

VECTOR3 Bone::GetWorldPosition() const
{
	return MV1GetFramePosition(info->handle, no);
}

MATRIX Bone::GetWorldMatrix() const
{
	return MV1GetFrameLocalWorldMatrix(info->handle, no);
}

unsigned Bone::GetMeshCount() const
{
	return static_cast<unsigned>(info->bones[no].meshes.size());
}

Mesh* Bone::GetMesh(unsigned _count)
{
	if (_count < GetMeshCount())
		return &meshes[_count];
	return nullptr;
}
