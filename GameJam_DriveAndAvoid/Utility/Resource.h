#pragma once
#include"Vector2D.h"

#define NUMBER_IMAGE_NUM 3	//�����̉摜��

static const char* number_image_data[NUMBER_IMAGE_NUM] =
{
	"Resource/images/D&D_Number.png",
	"Resource/images/D&D_Number_Red.png",
	"Resource/images/D&D_Number_White.png"
};

//�Ǎ��A�`��֘A�̃v���O����
class Resource
{
private:
	static int number_image[NUMBER_IMAGE_NUM][10];	//�����̉摜
public:
	static void Initialize();
	static int LoadAndCheck(const char* _data);	 //�摜�A�����̓Ǎ����G���[�`�F�b�N
	static void LoadAndCheck(const char* _data,int AllNum, int XNum, int YNum, int XSize, int YSize, int* HandleArray); //�����摜�̓Ǎ����G���[�`�F�b�N
	static void DrawNumber(Vector2D location,int draw_num, int size, float font_size, int color);	//������`�悷��(location:�`��ʒu, draw_num:�`�悷�鐔��, size:������(�E�l��), font_size:�t�H���g�̃T�C�Y, color:0=�� 1=�� 2=��)
};
