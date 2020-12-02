#include <Windows.h>
#include "UrLib.h"
#include "DrawManager.h"
#include "CollideManager.h"

int Screen::x = 800;
int Screen::y = 600;

float Meter::oneMeter = 1.f;

int UrLib::Init(int ScreenSizeX, int ScreenSizeY, int ColorBitDepth, int WindowMode, bool IsShadowCalc)
{
    int ret = 0;

    Screen::x = ScreenSizeX;
    Screen::y = ScreenSizeY;
    
//    ret += SetEnableXAudioFlag(TRUE);//TODO�F�G���[���ł܂��ADxLib���X�V���ꂽ��������܂��傤

    ret += SetAlwaysRunFlag(TRUE);

    ret += SetUsePixelLighting(TRUE);

    ret += Set3DSoundOneMetre(Meter::oneMeter);
    
    ret += ChangeWindowMode(WindowMode);

    ret += SetGraphMode(Screen::x, Screen::y, ColorBitDepth);

    ret += DxLib_Init();
    
    ret += SetDrawScreen(DX_SCREEN_BACK);	//����ʂ�`��Ώۂ�

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
        Input::Update();                    // ���͍X�V
        Time::Update();                     // �o�ߎ��ԍX�V
        SceneManager::Update();      // �V�[���̍X�V����
        CollideManager::Get()->Update();    // �Փ˔���
        ret += UrLib::Draw();               // �`�揈��
        ret += ScreenFlip();		        // ����ʂƕ\��ʂ̓���
        ret += ClearDrawScreen();	        // ����ʂ̕`���S�ď���
        if (SceneManager::IsEnd())ret = -1;//�I���`�F�b�N
    }
}

int UrLib::Draw()
{
    int ret = 0;

#if defined _DEBUG || DEBUG

    printfDx("Loading:%d\n", Loader::IsLoading());

    printfDx("�t�@�C���񓯊�:%d\n", SceneManager::GetAsyncLoadAllCount());

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
