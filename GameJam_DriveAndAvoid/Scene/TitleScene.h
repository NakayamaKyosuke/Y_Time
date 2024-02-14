#pragma once

#include"SceneBase.h"

#define MENU_NUM 5		//���j���[���ڐ�

class TitleScene : public SceneBase
{
private:

private:
	int timer;			//���t���[���o�߂���������
	int wait;			//���͉\�܂ł̎��Ԃ𑪂�
	int background_image; //�w�i�摜
	int titlemenu_image; //�w�i�摜
	int menupole_image; //�w�i�摜
	int cursor_sound;	//�J�[�\���ړ���
	int enter_sound;	//�J�[�\���ړ���
	int menu_image_num[MENU_NUM]; //���j���[�摜
	int cursor_image; //�J�[�\���摜
	int menu_cursor; //���j���[�J�[�\���ԍ�

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

};