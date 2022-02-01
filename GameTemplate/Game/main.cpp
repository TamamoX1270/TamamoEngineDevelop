#include "stdafx.h"
#include "system/system.h"
#include "Game.h"

/// <summary>
/// ���C�g�\����
/// </summary>
struct Light
{
	// �f�B���N�V�������C�g�p�̃����o
	Vector3 dirDirection;   // ���C�g�̕���
	float pad0;
	Vector3 dirColor;       // ���C�g�̃J���[
	float pad1;

	// step-1 ���C�g�\���̂Ƀ|�C���g���C�g�p�̃����o�ϐ���ǉ�����
	Vector3 ptPosition;		//�ʒu�B
	float pad2;					//�p�f�B���O�B
	Vector3 ptColor;			//�J���[�B
	float ptRange;				//�e���͈́B

	Vector3 eyePos;         // ���_�̈ʒu
	float pad3;
	Vector3 ambientLight;   // �A���r�G���g���C�g
};


// K2EngineLow�̃O���[�o���A�N�Z�X�|�C���g�B
K2EngineLow* g_k2EngineLow = nullptr;

/// <summary>
/// ���C���֐�
/// </summary>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// �Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));
	
	// k2EngineLow�̏������B
	g_k2EngineLow = new K2EngineLow();
	g_k2EngineLow->Init(g_hWnd, FRAME_BUFFER_W, FRAME_BUFFER_H);
	g_camera3D->SetPosition({ 0.0f, 100.0f, 200.0f });
	g_camera3D->SetTarget({ 0.0f, 50.0f, 0.0f });

	NewGO<Game>(0);

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		// �t���[���̊J�n���ɌĂяo���K�v�����鏈�������s
		g_k2EngineLow->BeginFrame();

		// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V�������Ăяo���B
		g_k2EngineLow->ExecuteUpdate();

		// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̕`�揈�����Ăяo���B
		g_k2EngineLow->ExecuteRender();

		// �f�o�b�O�`�揈�������s����B
		g_k2EngineLow->DebubDrawWorld();

		// �t���[���̏I�����ɌĂяo���K�v�����鏈�������s�B
		g_k2EngineLow->EndFrame();

	}

	delete g_k2EngineLow;

	return 0;
}