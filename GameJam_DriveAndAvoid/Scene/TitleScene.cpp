#include"TitleScene.h"
#include"../Utility/inputControl.h"
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

TitleScene::TitleScene() : wait(0),timer(0),background_image(NULL), menu_image(NULL), menu_image_num{0}, cursor_image(NULL), menu_cursor(0)
{

}

TitleScene::~TitleScene()
{

}

//����������
void TitleScene::Initialize()
{
	wait = 20;
	//�摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/Title.bmp");
	menu_image = LoadGraph("Resource/images/menu.bmp");
	cursor_image = LoadGraph("Resource/images/cone.bmp");
	if (LoadDivGraph("Resource/images/menu.bmp", 4, 1, 4, 195, 40, menu_image_num) == -1)
	{
		throw("Resource/images/menu.bmp�̓Ǎ��Ɏ��s���܂����B\n");
	}

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmp������܂���\n");
	}
	if (menu_image == -1)
	{
		throw("Resource/images/menu.bmp������܂���\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmp������܂���\n");
	}
}

//�X�V����
eSceneType TitleScene::Update()
{
	//���ԑ���
	timer++;
	//��莞�ԓ��͂��󂯕t���Ȃ�(����͖h�~)
	if (--wait <= 0)
	{
		wait = 0;
		//�J�[�\�����ړ�
		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
		{
			menu_cursor++;
			//��ԉ��ɓ��B������A��ԏ�ɂ���
			if (menu_cursor > 3)
			{
				menu_cursor = 0;
			}
		}

		//�J�[�\����ړ�
		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
		{
			menu_cursor--;
			//��ԏ�ɓ��B������A��ԉ��ɂ���
			if (menu_cursor < 0)
			{
				menu_cursor = 3;
			}
		}

		//�J�[�\������i���肵����ʂɑJ�ڂ���j
		if (InputControl::GetButtonUp(XINPUT_BUTTON_B))
		{
			switch (menu_cursor)
			{
			case 0:
				return eSceneType::E_MAIN;
			case 1:
				return eSceneType::E_RANKING_DISP;
			case 2:
				return eSceneType::E_HELP;
			case 3:
				return eSceneType::E_END;
			}
		}

	}
	//���݂̃V�[���^�C�v��Ԃ�
	return GetNowScene();
}

//�`�揈��
void TitleScene::Draw() const
{
	//�^�C�g���摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	//���j���[�摜�̕`��
	for (int i = 0; i < 4; i++)
	{
		if (i == menu_cursor && InputControl::GetButton(XINPUT_BUTTON_B) == false)
		{
			DrawRotaGraph(230, 220 + i * 40, 1.2, 0, menu_image_num[i], TRUE);
		}
		else
		{
			DrawRotaGraph(230, 220 + i * 40, 1.0, 0, menu_image_num[i], TRUE);
		}
	}

	//�J�[�\���摜�̕`��
	DrawRotaGraph(90+2*cosf(2*(timer/5)+M_PI/3), 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);
}

//�I��������
void TitleScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}

//���݂̃V�[�������擾
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}