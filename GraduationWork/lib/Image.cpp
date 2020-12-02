#include "Image.h"
#include "ImageRenderer.h"
#include "dxlib/DxLib.h"

std::unordered_map<std::string, Image::INFO> Image::loadInfo;
std::unordered_map<std::string, Image::INFO> Image::loadDivInfo;

bool Image::Load(const std::string& _path)
{
	if (!isDiv)
	{
		if (path == _path)return true;//�p�X�������ꍇ���I��
	}

	//�}�b�v���猟��

	INFO* p = nullptr;

	std::unordered_map<std::string, INFO>::iterator it = loadInfo.find(_path);
	if (it == loadInfo.end())
	{
		//���o�^���A�ǂݍ���ł���o�^
		int h = LoadGraph(_path.c_str());

		if (h == -1)return false;//���s������I��

		p = &loadInfo[_path];//�o�^����INFO�̃A�h���X��ێ�

		p->handles.emplace_back(h);

		if (GetUseASyncLoadFlag())
			AsyncLoad();
		else
			Initialize(p);
	}
	else
	{
		//�o�^�ς݂̏ꍇ�A�J�E���g�𑝂₵�ăA�h���X��ێ�
		it->second.count += 1;
		p = &it->second;
	}

	Destroy();//���̉摜��j��

	imageInfo = p;
	path = _path;
	isDiv = false;

	return true;
}

bool Image::LoadDiv(const std::string& _path, unsigned _xdiv, unsigned _ydiv, unsigned _allnum)
{
	if (isDiv)
	{
		if (path == _path)return true;//�p�X�������ꍇ���I��
	}

	//�}�b�v���猟��

	INFO* p = nullptr;

	std::unordered_map<std::string, INFO>::iterator it = loadDivInfo.find(_path);
	if (it == loadDivInfo.end())
	{
		//���o�^���A�ǂݍ���ł���o�^
		int x, y;
		GetImageSize_File(_path.c_str(), &x, &y);//�t�@�C������摜�T�C�Y�擾

		if (_allnum == 0u)_allnum = _xdiv * _ydiv;

		INFO info;
		info.sizeX = x / _xdiv;
		info.sizeY = y / _ydiv;
		info.handles.resize(_allnum);

		int result = LoadDivGraph(_path.c_str(), _allnum, _xdiv, _ydiv, info.sizeX, info.sizeY, &info.handles[0]);

		if (result == -1)return false;//���s������I��

		p = &loadDivInfo[_path];//�o�^����INFO�̃A�h���X��ێ�

		if (GetUseASyncLoadFlag())
			AsyncLoad();
		else
			Initialize(p);

		*p = info;
	}
	else
	{
		//�o�^�ς݂̏ꍇ�A�J�E���g�𑝂₵�ăA�h���X��ێ�
		it->second.count += 1;
		p = &it->second;
	}

	Destroy();//���̉摜��j��

	path = _path;
	imageInfo = p;
	isDiv = true;

	return true;
}

void Image::Destroy()
{
	if (isDiv)	Destroy(loadDivInfo);
	else		Destroy(loadInfo);
}

void Image::Initialize(INFO* _p)
{
	if (isDiv)
	{
		//���̂Ƃ���Ȃ�
	}
	else
	{
		GetGraphSize(_p->handles[0], &_p->sizeX, &_p->sizeY);
	}
}

void Image::DestroyParam()
{
	if (imageInfo == nullptr)return;

	if (isDiv)	loadDivInfo.erase(path);
	else loadInfo.erase(path);

	imageInfo = nullptr;
	path.clear();
}

void Image::Destroy(std::unordered_map<std::string, Image::INFO>& _info)
{
	if (imageInfo == nullptr)return;//�ǂݍ���ł��Ȃ�

	//�ǂݍ��񂾐���0�ȉ��ō폜
	if (--imageInfo->count <= 0)
	{
		//�ǂݍ��񂾉摜�폜
		for (size_t i = 0ull, size = imageInfo->handles.size(); i < size; ++i)
		{
			DeleteGraph(imageInfo->handles[i]);
		}

		//�}�b�v�������
		_info.erase(path);
	}

	imageInfo = nullptr;
	path.clear();

}

void Image::AsyncLoad()
{
	renderer->AddRendererToScene();
	renderer->isRendererEnable = false;
}
