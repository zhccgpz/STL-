#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "speaker.h"
using namespace std;
class SpeechManager
{
public:
	//构造
	SpeechManager();

	//析构函数
	~SpeechManager();
	//初始化容器
	void init_Speech();
	//创建选手
	void createSpeaker();
	//显示菜单
	void show_Menu();
	//开始比赛
	void start_Speech();
	//抽签
	void speech_Draw();
	//比赛
	void speech_Contest();
	//显示晋级选手
	void show_Winner();
	//保存记录
	void save_Record();
	//读取记录
	void load_Record();
	//显示记录
	void show_Record();
	//清空记录
	void clear_Record();
	//退出系统
	void exit_Sys();
	//成员属性
	vector<int>v1;//保存第1轮选手编号容器
	vector<int>v2;//保存第2轮选手编号容器
	vector<int>vVictory;//保存胜出前3选手编号容器
	map<int, Speaker> m_Speaker;//保存编号以及对应的具体选手容器
	int speech_Rounds;//比赛轮数
	bool fileIsEmpty;//判断文件是否为空
	map<int, vector<string>> m_Record;//往届比赛记录

};
