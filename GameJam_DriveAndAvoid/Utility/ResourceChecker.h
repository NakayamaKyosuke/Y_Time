#pragma once

class Resource
{
public:
	//�摜�A�����̓Ǎ����G���[�`�F�b�N
	static int LoadAndCheck(const char* _data);
	static int LoadAndCheck(const char* _data,int AllNum, int XNum, int YNum, int   XSize, int   YSize, int* HandleArray);
};
