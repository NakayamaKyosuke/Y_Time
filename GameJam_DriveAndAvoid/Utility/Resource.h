#pragma once

//�Ǎ��A�`��֘A�̃v���O����
class Resource
{
private:
	static int number_imaga[3];	//�����̉摜
public:
	static void Initialize();
	static int LoadAndCheck(const char* _data);	 //�摜�A�����̓Ǎ����G���[�`�F�b�N
	static void LoadAndCheck(const char* _data,int AllNum, int XNum, int YNum, int XSize, int YSize, int* HandleArray); //�����摜�̓Ǎ����G���[�`�F�b�N
	static void DrawNumber(int draw_num, int color);	//������`�悷��icolor�̎�ނ� 0=�� 1=�� 2=���j
};