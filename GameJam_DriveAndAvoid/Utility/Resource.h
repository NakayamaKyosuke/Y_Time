#pragma once

//�Ǎ��A�`��֘A�̃v���O����
class Resource
{
public:
	static int LoadAndCheck(const char* _data);	 //�摜�A�����̓Ǎ����G���[�`�F�b�N
	static void LoadAndCheck(const char* _data,int AllNum, int XNum, int YNum, int XSize, int YSize, int* HandleArray); //�����摜�̓Ǎ����G���[�`�F�b�N
};
