#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"

bool Game::Start()
{
	//�v���C���[�I�u�W�F�N�g���쐬����B
	m_player = NewGO<Player>(0, "player");
	//�w�i�I�u�W�F�N�g���쐬����B
	m_backGround = NewGO<BackGround>(0, "background");

	return true;
}
void Game::Update()
{

	//(*��֥)/ʰ�
	// ���X�e�B�b�N(�L�[�{�[�h�FWASD)�ŕ��s�ړ��B
	m_pointligpos.x += g_pad[0]->GetLStickXF();
	m_pointligpos.z += g_pad[0]->GetLStickYF();
	m_pointligpos.y = 50.0f;

	g_directionLig.SetPointPos(m_pointligpos);
	//�f�B���N�V�������C�g�̓���������ƃJ���[���Z�b�g�ł����Ⴂ�܂�
	//g_directionLig.SetLigDirection({ 1.0f,-1.0f,-1.0f });
	//g_directionLig.SetLigColor({0.5f,0.5f,0.5f});
}
void Game::Render(RenderContext& rc)
{
}