#include "../lib/UrLib.h"
#include "Scenes/TitleScene.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (UrLib::Init(800, 600, 32, TRUE) < 0)		// UR���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	//TODO
	//SceneManager::Get()->isAsyncLoad = true;
	//Loader::isAsync = true;
	//Saver::isAsync = true;

	SceneManager::Get()->LoadScene<TitleScene>();

	//���C������
	UrLib::Update();

	UrLib::End();			// UR���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}
