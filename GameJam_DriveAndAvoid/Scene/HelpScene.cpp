#include"HelpScene.h"
#include"../Utility/inputControl.h"
#include"DxLib.h"
#include"../Utility/Resource.h"

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
	background_image = Resource::LoadAndCheck("Resource/images/help.png");

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
	DrawString(130, 460, "A�{�^���������ă^�C�g���֖߂�",0xff0000, 0);
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