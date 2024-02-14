#include"TitleScene.h"
#include"../Utility/inputControl.h"
#include"../Utility/ResourceChecker.h"
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

TitleScene::TitleScene() : wait(0),timer(0), titlemenu_image(NULL), menu_image_num{0}, cursor_image(NULL), menu_cursor(0), cursor_sound(0), enter_sound(0)
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
	background_image = Resource::LoadAndCheck("Resource/images/title/D&D_Title.jpg");
	titlemenu_image = LoadGraph("Resource/images/title/D&D_TitleMenu.jpg");
	menupole_image = LoadGraph("Resource/images/title/D&D_MenuPole.jpg");
	cursor_image = LoadGraph("Resource/images/cone.bmp");

	cursor_sound = LoadSoundMem("Resource/sound/�J�[�\���ړ�8.mp3");
	enter_sound = LoadSoundMem("Resource/sound/����.mp3");

	//�G���[�`�F�b�N
	if (LoadDivGraph("Resource/images/title/D&D_Menu2.jpg", MENU_NUM, 1, MENU_NUM, 185, 40, menu_image_num) == -1)
	{
		throw("Resource/images/title/D&D_Menu2.jpg�̓Ǎ��Ɏ��s���܂����B\n");
	}
	if (titlemenu_image == -1)
	{
		throw("Resource/images/title/D&D_TitleMenu.jpg������܂���\n");
	}
	if (menupole_image == -1)
	{
		throw("Resource/images/title/D&D_MenuPole.jpg������܂���\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.png������܂���\n");
	}
	if (cursor_sound == -1)
	{
		throw("Resource/sound/�J�[�\���ړ�8.mp3������܂���\n");
	}
	if (enter_sound == -1)
	{
		throw("Resource/sound/����.mp3������܂���\n");
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
			PlaySoundMem(cursor_sound, DX_PLAYTYPE_BACK);
			menu_cursor++;
			//��ԉ��ɓ��B������A��ԏ�ɂ���
			if (menu_cursor > MENU_NUM-1)
			{
				menu_cursor = 0;
			}
		}

		//�J�[�\����ړ�
		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
		{
			PlaySoundMem(cursor_sound, DX_PLAYTYPE_BACK);
			menu_cursor--;
			//��ԏ�ɓ��B������A��ԉ��ɂ���
			if (menu_cursor < 0)
			{
				menu_cursor = MENU_NUM-1;
			}
		}

		//�J�[�\������̉�������ɖ炷
		if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
		{
			PlaySoundMem(enter_sound, DX_PLAYTYPE_BACK);
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
				return eSceneType::E_CREDIT;
			case 4:
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
	DrawGraph(180, 255, menupole_image, TRUE);
	DrawGraph(60, 175, titlemenu_image, FALSE);

	//���j���[�摜�̕`��
	for (int i = 0; i < MENU_NUM; i++)
	{
		if (i == menu_cursor && InputControl::GetButton(XINPUT_BUTTON_B) == false)
		{
			DrawRotaGraph(230, 220 + i * 40, 1.2, 0, menu_image_num[i], FALSE);
		}
		else
		{
			DrawRotaGraph(230, 220 + i * 40, 1.0, 0, menu_image_num[i], FALSE);
		}
	}

	//�J�[�\���摜�̕`��
	DrawRotaGraph(100+2*cosf(2*(timer/5)+M_PI/3), 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);
}

//�I��������
void TitleScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
	DeleteGraph(titlemenu_image);
	DeleteGraph(menupole_image);
	DeleteGraph(cursor_image);
	
}

//���݂̃V�[�������擾
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}