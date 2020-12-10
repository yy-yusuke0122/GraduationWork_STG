#include <Windows.h>
#include "UrLib.h"
#include "DrawManager.h"
#include "CollideManager.h"
#include "MapChipManager.h"

int Screen::x = 800;
int Screen::y = 600;

float Meter::oneMeter = 1.f;

#ifdef _DEBUG

#include <list>
#include <unordered_map>
#include <map>
#include <string>

namespace//TODO
{
    struct hogehoge
    {
        void test() { i = 0; }
        int i;
    };

    void all_calc()
    {
        clsDx();

        std::list<hogehoge> l;
        std::map<std::string, hogehoge> m;
        std::unordered_map<std::string, hogehoge> u;

        for (int i = 0; i < 100000; ++i)l.push_back(hogehoge());
        for (int i = 0; i < 100000; ++i)m.insert(std::make_pair("hoge" + i, hogehoge()));
        for (int i = 0; i < 100000; ++i)u.insert(std::make_pair("hoge" + i, hogehoge()));

        //list計測
        unsigned long long c = GetNowSysPerformanceCount();

        for (std::list<hogehoge>::iterator it = l.begin(), end = l.end(); it != end; ++it)it->test();

        printfDx("list : %d\n", GetNowSysPerformanceCount() - c);

        //map計測
        c = GetNowSysPerformanceCount();

        for (std::map<std::string, hogehoge>::iterator it = m.begin(), end = m.end(); it != end; ++it)it->second.test();

        printfDx(" map : %d\n", GetNowSysPerformanceCount() - c);

        //unordered_map計測
        c = GetNowSysPerformanceCount();

        for (std::unordered_map<std::string, hogehoge>::iterator it = u.begin(), end = u.end(); it != end; ++it)it->second.test();

        printfDx("hash : %d\n", GetNowSysPerformanceCount() - c);

    }

    void debug() {}
}

#endif // !_DEBUG

int UrLib::Init(int ScreenSizeX, int ScreenSizeY, int ColorBitDepth, int WindowMode, bool IsShadowCalc)
{
    int ret = 0;

    Screen::x = ScreenSizeX;
    Screen::y = ScreenSizeY;
    
//    ret += SetEnableXAudioFlag(TRUE);//TODO：エラーがでます、DxLibが更新されたら解除しましょう

    ret += SetAlwaysRunFlag(TRUE);

    ret += SetUsePixelLighting(TRUE);

    ret += Set3DSoundOneMetre(Meter::oneMeter);
    
    ret += ChangeWindowMode(WindowMode);

    ret += SetGraphMode(Screen::x, Screen::y, ColorBitDepth);

    ret += DxLib_Init();
    
    ret += SetDrawScreen(DX_SCREEN_BACK);	//裏画面を描画対象へ

    ret += SetLightEnable(FALSE);

    SceneManager::Start();

    Input::Start();

    Time::Init();

    SetSysCommandOffFlag(TRUE);

    CreateDirectory("Save", NULL);

    Loader::Load();

    return ret;
}

void UrLib::Update()
{
    int ret = 0;

    while (ret += ProcessMessage(), ret == 0) {
        ret += clsDx();
        Input::Update();                    // 入力更新
        Time::Update();                     // 経過時間更新
        SceneManager::Update();             // シーンの更新処理
        CollideManager::Get()->Update();    // 衝突判定
        MapChipManager::Update();           // マップチップ当たり判定
        ret += UrLib::Draw();               // 描画処理

#ifdef _DEBUG

        debug();

#endif // !_DEBUG

        ret += ScreenFlip();		        // 裏画面と表画面の入替
        ret += ClearDrawScreen();	        // 裏画面の描画を全て消去

        if (SceneManager::IsEnd())ret = -1;//終了チェック
    }
}

int UrLib::Draw()
{
    int ret = 0;

#if defined _DEBUG || DEBUG

    printfDx("Loading:%d\n", Loader::IsLoading());

    printfDx("ファイル非同期:%d\n", SceneManager::GetAsyncLoadAllCount());

#endif // !
    Scroll::Update();

    DrawManager::Draw();
    return ret;
}

int UrLib::End()
{
    int ret = 0;
    SceneManager::Destroy();
    CollideManager::Destroy();
    DrawManager::Destroy();
    Input::End();
    Saver::Wait();
    Loader::Wait();
    Debug::Release();
    return ret;
}
