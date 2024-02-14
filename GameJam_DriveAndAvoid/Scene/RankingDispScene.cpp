#include"RankingDispScene.h"
#include"../Utility/inputControl.h"
#include"DxLib.h"

RankingDispScene::RankingDispScene() : background_image(NULL), ranking(nullptr)
{

}

RankingDispScene::~RankingDispScene()
{

}

//����������
void RankingDispScene::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("Resource/images/ranking.png");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("Resource/images/ranking.png");
	}

	//�����L���O�����擾
	ranking = new RankingData;
	ranking->Initialize();
}

//�X�V����
eSceneType RankingDispScene::Update()
{
	//B�{�^���������ꂽ��A�^�C�g���ɖ߂�
	if (InputControl::GetButtonUp(XINPUT_BUTTON_A))
	{
		return eSceneType::E_TITLE;
	}
	return GetNowScene();
}

//�`�揈��
void RankingDispScene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);
	//�����̑傫���ύX
	SetFontSize(40);
	//�擾���������L���O�f�[�^��`�悷��
	for (int i = 0; i < 5; i++)
	{
		DrawFormatString(0, 160 + i * 59, 0xff00ff, "%2d %-15s %6d",
		ranking->GetRank(i), ranking->GetName(i), ranking->GetScore(i));
	}
	SetFontSize(16);
	DrawString(150, 450, "---- A�{�^���������ă^�C�g���֖߂� ----", 0x000000, 0);
}

//�I��������
void RankingDispScene::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);

	//���I�������̉��
	ranking->Finalize();
	delete ranking;
}

//���݂̃V�[�������擾
eSceneType RankingDispScene::GetNowScene() const
{
	return eSceneType::E_RANKING_DISP;
}