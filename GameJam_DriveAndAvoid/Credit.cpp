#include"Credit.h"
#include"Utility/inputControl.h"
#include"DxLib.h"

CreditScene::CreditScene() : background_image(NULL)
{

}

CreditScene::~CreditScene()
{

}

//����������
void CreditScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/credit.jpg");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/credit.jpg������܂���\n");
	}
}

//�X�V����
eSceneType CreditScene::Update()
{
	//B�{�^���������ꂽ��A�^�C�g���ɖ߂�
	if (InputControl::GetButtonUp(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

//�`�揈��
void CreditScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	//�Q�[������
	SetFontSize(60);
	SetFontThickness(9);
	ChangeFont("�l�r ����");
	DrawString(170, 0, "�N���W�b�g", 0x000000, 0);
	SetFontSize(50);
	DrawString(200, 110, "���ʉ����{", 0x000000, 0);
	DrawString(130, 170, "�|�P�b�g�T�E���h", 0x000000, 0);
	DrawString(200, 230, "���炷�Ƃ�", 0x000000, 0);
	DrawString(230, 280, "photoAC", 0x000000, 0);
	DrawString(170, 330, "�C�O�n���ʉ�", 0x000000, 0);
	SetFontSize(16);
	DrawString(150, 450, "---- B�{�^���������ă^�C�g���֖߂� ----", 0x000000, 0);
}

//�I��������
void CreditScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
}

//���݂̃V�[�������擾
eSceneType CreditScene::GetNowScene() const
{
	return eSceneType::E_CREDIT;
}