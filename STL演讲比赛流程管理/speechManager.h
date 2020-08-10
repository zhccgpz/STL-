#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "speaker.h"
using namespace std;
class SpeechManager
{
public:
	//����
	SpeechManager();

	//��������
	~SpeechManager();
	//��ʼ������
	void init_Speech();
	//����ѡ��
	void createSpeaker();
	//��ʾ�˵�
	void show_Menu();
	//��ʼ����
	void start_Speech();
	//��ǩ
	void speech_Draw();
	//����
	void speech_Contest();
	//��ʾ����ѡ��
	void show_Winner();
	//�����¼
	void save_Record();
	//��ȡ��¼
	void load_Record();
	//��ʾ��¼
	void show_Record();
	//��ռ�¼
	void clear_Record();
	//�˳�ϵͳ
	void exit_Sys();
	//��Ա����
	vector<int>v1;//�����1��ѡ�ֱ������
	vector<int>v2;//�����2��ѡ�ֱ������
	vector<int>vVictory;//����ʤ��ǰ3ѡ�ֱ������
	map<int, Speaker> m_Speaker;//�������Լ���Ӧ�ľ���ѡ������
	int speech_Rounds;//��������
	bool fileIsEmpty;//�ж��ļ��Ƿ�Ϊ��
	map<int, vector<string>> m_Record;//���������¼

};
