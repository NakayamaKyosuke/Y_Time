#include"HelpScene.h"
#include"../Utility/inputControl.h"
#include"DxLib.h"

HelpScene::HelpScene() : background_image(NULL)
{

}

HelpScene::~HelpScene()
{

}

//����������
void HelpScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/help.png");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/help.bmp������܂���\n");
	}
}

//�X�V����
eSceneType HelpScene::Update()
{
	//A�{�^���������ꂽ��A�^�C�g���ɖ߂�
	if (InputControl::GetButtonUp(XINPUT_BUTTON_A))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

//�`�揈��
void HelpScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	//�Q�[������
	SetFontSize(16);
	DrawString(150, 450, "---- B�{�^���������ă^�C�g���֖߂� ----",0xffffff, 0);
}

//�I��������
void HelpScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
}

//���݂̃V�[�������擾
eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}