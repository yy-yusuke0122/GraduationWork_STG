#include "Mesh.h"
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

Mesh::Mesh() :
	diffuse(defColor), specular(defColor), ambient(defColor), emissive(defColor), alpha(1.f)
{
}

void Mesh::Set()
{
	ClampColor(diffuse);
	ClampColor(specular);
	ClampColor(emissive);
	ClampColor(ambient);
	Clamp(alpha, 0.f, 1.f);

	Clamp(blendParam, 0, 255);

	MV1SetMeshDifColorScale(info->handle, no, diffuse);
	MV1SetMeshSpcColorScale(info->handle, no, specular);
	MV1SetMeshEmiColorScale(info->handle, no, emissive);
	MV1SetMeshAmbColorScale(info->handle, no, ambient);
	MV1SetMeshOpacityRate(info->handle, no, alpha);

	MV1SetMeshDrawBlendMode(info->handle, no, blendMode);
	MV1SetMeshDrawBlendParam(info->handle, no, blendParam);
}

bool Mesh::IsSemiTrans() const
{
	return info->meshes[no].isSemiTrans;
}

Material* Mesh::GetMaterial() const
{
	return renderer->GetMaterial(info->meshes[no].materialNo);
}

bool Mesh::SetBlendMode(int _mode)
{
	switch (blendMode)
	{
	case Mesh::NONE:
	case Mesh::ALPHA:
	case Mesh::ADD:
	case Mesh::SUB:
	case Mesh::MUL:
	case Mesh::INVSRC:break;
	default:return false;
	}

	blendMode = _mode;
	return true;
}
