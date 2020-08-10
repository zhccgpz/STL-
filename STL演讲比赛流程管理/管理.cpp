#include <iostream>
#include "speechManager.h"
#include <ctime>
using namespace std;
int main()
{
	//随机种子
	srand((unsigned int)time(NULL));
	SpeechManager SM;
	//用户选择
	int choice = 0;
	while (true)
	{
		/*for (map<int, Speaker>::iterator it = SM.m_Speaker.begin(); it != SM.m_Speaker.end(); it++)
		{
			cout << "选手编号：" << it->first << "\t选手姓名：" << it->second.m_Name << "\t选手分数：" << it->second.m_Sore[0] << endl;
		}*/
		SM.show_Menu();
		cout << "请输入你的选择：" << endl;
		cin >> choice;
		
		switch (choice)
		{
		case 1://开始演讲比赛
			SM.start_Speech();
			break;
		case 2://查看往届记录信息
			SM.show_Record();
			break;
		case 3://清空比赛记录
			SM.clear_Record();
			break;
		case 0://退出比赛程序
			SM.exit_Sys();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}