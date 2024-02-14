#pragma once

#include "SceneBase.h"
#include "../Object/Player.h"
#include "../Object/Enemy.h"
#include "../Object/Item.h"

#include "../Object/Oil.h"
#include "../Object/Cone.h"
//����m�F�p
class GameMainScene : public SceneBase
{
private:
	int high_score; //�n�C�X�R�A
	int back_ground; //�w�i�摜
	int barrier_image; //�o���A�摜
	int obstruct_image;		//��ʑj�Q�̉摜
	int mileage; //���s����
	int enemy_image[3]; //�G�摜
	int enemy_count[3]; //�ʂ�߂����G�J�E���g
	Player* player; //�v���C���[
	Enemy** enemy; //�G
	Cone* cone;

	Item** item;   //�A�C�e���i���P�b�g�G���W���A��ʑj�Q�j
	int oilsounds;
	int hit_SE;

	Oil* oil;//�I�C��
public:
	GameMainScene();
	virtual~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
	
private:
	//�n�C�X�R�A�ǂݍ��ݏ���
	void ReadHighScore();
	//�����蔻��
	bool IsHitCheak(Player* p, Enemy* e);
	//
	bool IsHitCheak(Player* p, Oil* o);
	bool IsHitCheak(Player* p, Item* i);
	bool IsHitCheak(Player* p, Cone* c);
};