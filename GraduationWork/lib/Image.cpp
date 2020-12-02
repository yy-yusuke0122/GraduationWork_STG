#include "Image.h"
#include "ImageRenderer.h"
#include "dxlib/DxLib.h"

std::unordered_map<std::string, Image::INFO> Image::loadInfo;
std::unordered_map<std::string, Image::INFO> Image::loadDivInfo;

bool Image::Load(const std::string& _path)
{
	if (!isDiv)
	{
		if (path == _path)return true;//パスが同じ場合即終了
	}

	//マップから検索

	INFO* p = nullptr;

	std::unordered_map<std::string, INFO>::iterator it = loadInfo.find(_path);
	if (it == loadInfo.end())
	{
		//未登録時、読み込んでから登録
		int h = LoadGraph(_path.c_str());

		if (h == -1)return false;//失敗したら終了

		p = &loadInfo[_path];//登録したINFOのアドレスを保持

		p->handles.emplace_back(h);

		if (GetUseASyncLoadFlag())
			AsyncLoad();
		else
			Initialize(p);
	}
	else
	{
		//登録済みの場合、カウントを増やしてアドレスを保持
		it->second.count += 1;
		p = &it->second;
	}

	Destroy();//元の画像を破棄

	imageInfo = p;
	path = _path;
	isDiv = false;

	return true;
}

bool Image::LoadDiv(const std::string& _path, unsigned _xdiv, unsigned _ydiv, unsigned _allnum)
{
	if (isDiv)
	{
		if (path == _path)return true;//パスが同じ場合即終了
	}

	//マップから検索

	INFO* p = nullptr;

	std::unordered_map<std::string, INFO>::iterator it = loadDivInfo.find(_path);
	if (it == loadDivInfo.end())
	{
		//未登録時、読み込んでから登録
		int x, y;
		GetImageSize_File(_path.c_str(), &x, &y);//ファイルから画像サイズ取得

		if (_allnum == 0u)_allnum = _xdiv * _ydiv;

		INFO info;
		info.sizeX = x / _xdiv;
		info.sizeY = y / _ydiv;
		info.handles.resize(_allnum);

		int result = LoadDivGraph(_path.c_str(), _allnum, _xdiv, _ydiv, info.sizeX, info.sizeY, &info.handles[0]);

		if (result == -1)return false;//失敗したら終了

		p = &loadDivInfo[_path];//登録したINFOのアドレスを保持

		if (GetUseASyncLoadFlag())
			AsyncLoad();
		else
			Initialize(p);

		*p = info;
	}
	else
	{
		//登録済みの場合、カウントを増やしてアドレスを保持
		it->second.count += 1;
		p = &it->second;
	}

	Destroy();//元の画像を破棄

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
		//今のところなし
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
	if (imageInfo == nullptr)return;//読み込んでいない

	//読み込んだ数が0以下で削除
	if (--imageInfo->count <= 0)
	{
		//読み込んだ画像削除
		for (size_t i = 0ull, size = imageInfo->handles.size(); i < size; ++i)
		{
			DeleteGraph(imageInfo->handles[i]);
		}

		//マップから消す
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
