#include <iostream>
#include "speechManager.h"
#include <ctime>
using namespace std;
int main()
{
	//�������
	srand((unsigned int)time(NULL));
	SpeechManager SM;
	//�û�ѡ��
	int choice = 0;
	while (true)
	{
		/*for (map<int, Speaker>::iterator it = SM.m_Speaker.begin(); it != SM.m_Speaker.end(); it++)
		{
			cout << "ѡ�ֱ�ţ�" << it->first << "\tѡ��������" << it->second.m_Name << "\tѡ�ַ�����" << it->second.m_Sore[0] << endl;
		}*/
		SM.show_Menu();
		cout << "���������ѡ��" << endl;
		cin >> choice;
		
		switch (choice)
		{
		case 1://��ʼ�ݽ�����
			SM.start_Speech();
			break;
		case 2://�鿴�����¼��Ϣ
			SM.show_Record();
			break;
		case 3://��ձ�����¼
			SM.clear_Record();
			break;
		case 0://�˳���������
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