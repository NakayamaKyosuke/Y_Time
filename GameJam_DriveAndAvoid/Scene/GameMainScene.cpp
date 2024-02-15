#include"GameMainScene.h"
#include"../Object/RankingData.h"
#include "../Utility/inputControl.h"
#include"../Utility/Resource.h"
#include"DxLib.h"
#include<math.h>
#include"../Object/Oil.h"
#include "../Object/Cone.h"

GameMainScene::GameMainScene() : high_score(0), back_ground(NULL),
barrier_image(NULL), obstruct_image(NULL), mileage(0), player(nullptr), enemy(nullptr), item(nullptr),movie_play_once(false)
{
	for (int i = 0; i < 3; i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}
}

GameMainScene::~GameMainScene()
{

}

//����������
void GameMainScene::Initialize()
{
	//�����_�l��ǂݍ���
	ReadHighScore();

	//�摜�̓ǂݍ���	
	back_ground = LoadGraph("Resource/images/back.bmp");
	barrier_image= LoadGraph("Resource/images/barrier.png");
	obstruct_image = LoadGraph("Resource/images/flash.jpg");
	oilsounds = LoadSoundMem("Resource/sound/se_blood03.mp3");
	hit_SE = LoadSoundMem("Resource/sound/gatigire.mp3");
	BGM = LoadSoundMem("Resource/sound/GameMainBGM.mp3");
	back_ground = Resource::LoadAndCheck("Resource/images/GameMain_Back.jpg");
	barrier_image= Resource::LoadAndCheck("Resource/images/barrier.png");
	obstruct_image = Resource::LoadAndCheck("Resource/images/flash.jpg");
	oilsounds = Resource::LoadAndCheck("Resource/sound/se_blood03.mp3");
	hit_SE = Resource::LoadAndCheck("Resource/sound/gatigire.mp3");
	Resource::LoadAndCheck("Resource/images/cars2.png", 3, 3, 1, 63, 120, enemy_image);

	//�I�u�W�F�N�g�̐���
	player = new Player;
	enemy = new Enemy * [10];
	cone = new Cone;
	item = new Item * [10];

	//�I�u�W�F�N�g�̏�����
	player->Initialize();
	
	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}

	for (int i = 0; i < 10; i++)
	{
		item[i] = nullptr;
	}

	PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);
}

//�X�V����
eSceneType GameMainScene::Update()
{

	//�v���C���[�̍X�V
	player->Update();

	//�ړ������̍X�V
	mileage += (int)player->GetSpeed() + 5;

	//�G��������
	if (mileage / 20 % 100 == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			if (enemy[i] == nullptr)
			{
				int type = GetRand(3) % 3;
				enemy[i] = new Enemy(type, enemy_image[type]);
				enemy[i]->Initialize();
				break;
			}
		}
	}
	//�G��������
	if (mileage / 20 % 250 == 0)
	{
		//�A�C�e������
		for (int i = 0; i < 10; i++)
		{
			if (item[i] == nullptr)
			{
				item[i] = new Item();
				item[i]->Initialize();
				break;
			}
		}
	}
	//�I�C����������
	if (mileage / 10 % 200 == 0)
	{
		//�I�C������
		for (int i = 0; i < 10; i++)
		{
			if (oil == nullptr)
			{
				oil = new Oil();
				oil->Initialize();
				break;
			}
		}
	}

	if (mileage / 20 % 100 == 0) {
		cone = new Cone;
		cone->Initialize();
	}

	//�G�̍X�V�Ɠ����蔻��`�F�b�N
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Update(player->GetSpeed());

			//��ʊO�ɍs������A�G���폜���ăX�R�A���Z
			if (enemy[i]->GetLocation().y >= 640.0f)
			{
				enemy_count[enemy[i]->GetType()]++;
				enemy[i]->Finalize();
				delete enemy[i];
				enemy[i] = nullptr;
				break;
			}

			//�����蔻��̊m�F
			if (IsHitCheak(player, enemy[i]) && enemy[i]->GetDeathFlg() == false)
			{
				//�v���C���[���u�[�X�g���Ȃ�A�G�ɓ������������_
				if (player->GetBoostFlg() == true)
				{
					enemy_count[enemy[i]->GetType()]++;
					enemy[i]->SetDeathFlg(true);
				}
				else
				{
					PlaySoundMem(hit_SE, DX_PLAYTYPE_BACK);
					player->SetActive(false);
					player->DecreaseHp(-50.0f);
					enemy[i]->Finalize();
					delete enemy[i];
					enemy[i] = nullptr;
				}
			}
		}
	}

	//�A�C�e���̍X�V�Ɠ����蔻��`�F�b�N
	for (int i = 0; i < 10; i++)
	{
		if (item[i] != nullptr)
		{
			item[i]->Update(player->GetSpeed());

			//��ʊO�ɍs������A�G���폜���ăX�R�A���Z
			if (item[i]->GetLocation().y >= 640.0f)
			{
				item[i]->Finalize();
				delete item[i];
				item[i] = nullptr;
				continue;
			}

			//�����蔻��̊m�F
			if (IsHitCheak(player, item[i]))
			{
				if (item[i]->GetType() == 2) {
					if (player->GetHp() <= 500) {
						player->SetItemPower(item[i]);
						player->DecreaseHp(50.0f);
						item[i]->Finalize();
						delete item[i];
						item[i] = nullptr;
						continue;
					}
					else {
						player->SetItemPower(item[i]);
						item[i]->Finalize();
						delete item[i];
						item[i] = nullptr;
						continue;
					}
				}
				if (item[i]->GetType() == 3) {
					if (player->GetFuel() <= 20000) {
						player->SetItemPower(item[i]);
						player->IncreaseFuel(2000.0f);
						item[i]->Finalize();
						delete item[i];
						item[i] = nullptr;
						continue;
					}
					else {
						player->SetItemPower(item[i]);
						item[i]->Finalize();
						delete item[i];
						item[i] = nullptr;
						continue;
					}
				}
				else {
					player->SetItemPower(item[i]);
					item[i]->Finalize();
					delete item[i];
					item[i] = nullptr;
					continue;
				}
			}
		}
	}

	

	//�I�C���̍X�V�Ɠ����蔻��`�F�b�N
	for (int i = 0; i < 10; i++)
	{
		if (oil != nullptr)
		{
			oil->Update(player->GetSpeed());
			//��ʊO�ɍs������A�I�C�����폜����
			if (oil->GetLocation().y >= 640.0f)
			{
				oil->Finalize();
				delete oil;
				oil = nullptr;
				break;
			}
			//�����蔻��̊m�F
			if (IsHitCheak(player, oil))
			{
				PlaySoundMem(oilsounds, DX_PLAYTYPE_BACK);
				player->SetActive(false);
				oil->Finalize();
				delete oil;
				oil = nullptr;
			}
		}
	}

	

	//�R�[���̍X�V�Ɠ����蔻��`�F�b�N
	for (int i = 0; i < 10; i++)
	{
		if (cone != nullptr)
		{
			cone->Update(player->GetSpeed());

			//��ʊO�ɍs������A�R�[�����폜
			if (cone->GetLocation().y >= 640.0f)
			{
				delete cone;
				cone = nullptr;
				break;
			}

			//�����蔻��̊m�F
			if (IsHitCheak(player, cone))
			{
				player->SetActive(false);
				player->DecreaseHp(-25.0f);
				delete cone;
				cone = nullptr;
			}
		}
	}
	//�v���C���[�̔R�����̗͂�0�����Ȃ�A���U���g�Ɋ҈ڂ���
	if (player->GetFuel() < 0.0f || player->GetHp() < 0.0f)
	{
		//��񂾂�����Đ�
		if (movie_play_once == false)
		{
			PlayMovie("RPReplay_Final1707791741.avi", 1, DX_MOVIEPLAYTYPE_BCANCEL);
			movie_play_once = true;
		}
		if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
		{
			return eSceneType::E_RESULT;
		}
	}
		StopSoundMem(BGM);
		return eSceneType::E_RESULT;
	}

		return GetNowScene();

	}

//�`�揈��
void GameMainScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, mileage % 480 - 480, back_ground, TRUE);
	DrawGraph(0, mileage % 480, back_ground, TRUE);

	//�G�̕`��
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}

	//�I�C���̕`��
	/*for (int i = 0; i < 10; i++)
	{
		if (oil[i] != nullptr)
		{
			oil[i]->Draw();
		}
	}*/

	//�A�C�e���̕`��
	for (int i = 0; i < 10; i++)
	{
		if (item[i] != nullptr)
		{
			item[i]->Draw();
		}

	}

	if (oil != nullptr)
	{
		oil->Draw();
	}

	if (cone != nullptr) {
		cone->Draw();
	}


	//�v���C���[�̕`��
	player->Draw();

	//UI�̕`��
	DrawBox(500, 0, 640, 480, GetColor(153, 0, 0), TRUE);
	SetFontSize(16);
	DrawFormatString(510, 20, GetColor(0, 0, 0), "�n�C�X�R�A");
	DrawFormatString(510, 40, GetColor(255, 255, 255), "%08d", high_score);
	DrawFormatString(500, 80, GetColor(0, 0, 0), "��������&�󂵂���");
	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraph(523 + (i * 50), 120, 0.3, 0, enemy_image[i], TRUE, FALSE);
		DrawFormatString(510 + (i * 50), 140, GetColor(255, 255, 255), "%03d", enemy_count[i]);
	}
	DrawFormatString(510, 200, GetColor(0, 0, 0), "���s����");
	DrawFormatString(555, 220, GetColor(255,255,255), "%08d",mileage/10);
	DrawFormatString(510, 240, GetColor(0, 0, 0), "�X�s�[�h");
	DrawFormatString(555, 260, GetColor(255,255,255), "%08.1f",player->GetSpeed());
	DrawFormatString(510, 300, GetColor(0, 0, 0), "�c��o���A��");
	//�o���A�����̕`��
	for (int i = 0; i < player->GetBarrierCount(); i++)
	{
		DrawRotaGraph(520 + i * 25, 340, 0.2f, 0, barrier_image, TRUE,FALSE);
	}

	//�R���Q�[�W�̕`��
	float fx = 510.0f;
	float fy = 390.0f;
	DrawFormatString(fx, fy, GetColor(0, 0, 0), "FUEL METER");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetFuel() * 100 / 20000), fy + 40.0f, GetColor(0, 102, 204), TRUE);
	DrawBoxAA(fx, fy = 20.0f, fx + 100.f, fy + 40.0f, GetColor(0, 0, 0), FALSE);

	//�̗̓Q�[�W�̕`��
	float hx = 510.0f;
	float hy = 430.0f;
	DrawFormatString(hx, hy, GetColor(0, 0, 0), "PLAYER HP");
	DrawBoxAA(hx, hy + 20.0f, hx + (player->GetHp() * 100 / 500), hy + 40.0f, GetColor(255, 0, 0), TRUE);
	DrawBoxAA(hx, hy = 20.0f, hx + 100.f, hy + 40.0f, GetColor(0, 0, 0), FALSE);

	//��ʑj�Q�A�C�e���̗L�����Ԃɉ����đj�Q�摜��`��
	if (player->GetObstructTime() < 255)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, player->GetObstructTime());
		DrawGraphF(0, 0, obstruct_image, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	else
	{
		DrawGraphF(0, 0, obstruct_image, TRUE);
	}
}

//�I��������
void GameMainScene::Finalize()
{
	//�X�R�A���v�Z����
	int score = (mileage / 10 * 10);
	for (int i = 0; i < 3; i++)
	{
		score += (i + 1) * 50 * enemy_count[i];
	}
	//���U���g�f�[�^�̏�������
	FILE* fp = nullptr;
	//�t�@�C���I�[�v��
	errno_t result = fopen_s(&fp, "Resource/dat/result_data.csv", "w");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("Resource/dat/result_data.csv���J���܂���\n");
	}


	//�X�R�A��ۑ�
	fprintf(fp, "%d,\n",score);

	//���������Ɠ��_��ۑ�
	for (int i = 0; i < 3; i++)
	{
		fprintf(fp, "%d\n", enemy_count[i]);
	}

	//�t�@�C���N���[�Y
	fclose(fp);

	//���I�m�ۂ����I�u�W�F�N�g���폜����
	player->Finalize();
	delete player;
	delete oil;

	delete cone;

	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Finalize();
			delete enemy[i];
			enemy[i] = nullptr;
		}
	}
	delete[] enemy;

}

//���݂̃V�[�������擾
eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}

//�n�C�X�R�A�̓ǂݍ���
void GameMainScene::ReadHighScore()
{
	RankingData data;
	data.Initialize();

	high_score = data.GetScore(0);

	data.Finalize();
}

//�����蔻�菈���i�v���C���[�ƓG�j
bool GameMainScene::IsHitCheak(Player* p, Enemy* e)
{
	//�v���C���[���o���A�𒣂��Ă�����A�����蔻��𖳎�����
	if (p->IsBarrier())
	{
		return false;
	}

	//�ʒu���̍������擾
	Vector2D diff_location = p->GetLocation() - e->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}

//�����蔻�菈���i�v���C���[�ƃA�C�e���j
bool GameMainScene::IsHitCheak(Player* p, Item* i)
{
	//�ʒu���̍������擾
	Vector2D diff_location = p->GetLocation() - i->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize() + i->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}

//�����蔻�菈���i�v���C���[�ƃI�C���j
bool GameMainScene::IsHitCheak(Player* p, Oil* o)
{
	

	//�ʒu���̍������擾
	Vector2D diff_location = p->GetLocation() - o->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize() + o->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}


bool GameMainScene::IsHitCheak(Player* p, Cone* c)
{
	//�v���C���[���o���A�𒣂��Ă�����A�����蔻��𖳎�����
	if (p->IsBarrier())
	{
		return false;
	}

	//�ʒu���̍������擾
	Vector2D diff_location = p->GetLocation() - c->GetLocation();

	//�����蔻��T�C�Y�̑傫�����擾
	Vector2D box_ex = p->GetBoxSize() + c->GetBoxSize();

	//�R���W�����f�[�^���ʒu���̍������������Ȃ�A�q�b�g����Ƃ���
	return((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) < box_ex.y));
}