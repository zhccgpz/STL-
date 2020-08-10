#include "speechManager.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>

//���캯��
SpeechManager::SpeechManager()
{
	this->init_Speech();
	this->createSpeaker();
	this->load_Record();

}

//��������
SpeechManager::~SpeechManager()
{

}
void SpeechManager::init_Speech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Record.clear();
	this->speech_Rounds = 1;
}
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];
		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.m_Sore[j] = 0;
		}
		//����ѡ�ֱ�Ų��ҷ�������
		this->v1.push_back(i + 10001);
		//������Լ���Ӧ��ѡ�ִ������
		this->m_Speaker.insert(make_pair(i + 10001, sp));

	}
}
void SpeechManager::show_Menu()
{
	cout << "***********************************" << endl;
	cout << "******** ��ӭ�μ��ݽ����� *********" << endl;
	cout << "******** 1.��ʼ�ݽ����� ***********" << endl;
	cout << "******** 2.�鿴�����¼ ***********" << endl;
	cout << "******** 3.��ձ�����¼ ***********" << endl;
	cout << "******** 0.�˳��������� ***********" << endl;
	cout << "***********************************" << endl;


}

void SpeechManager::start_Speech()
{
	//��һ�ֿ�ʼ����
	//1����ǩ
	this->speech_Draw();
	//2������
	this->speech_Contest();
	//3����ʾ�������
	this->show_Winner();
	//�ڶ��ֿ�ʼ����
	this->speech_Rounds++;
	//1����ǩ
	this->speech_Draw();
	//2������
	this->speech_Contest();
	//3����ʾ�������
	this->show_Winner();
	//4������������ļ���
	this->save_Record();
	this->init_Speech();
	this->createSpeaker();
	this->load_Record();

	cout << "���������Ļ����" << endl;
	system("pause");
	system("cls");


}
//��ǩ
void SpeechManager::speech_Draw()
{
	cout << "<<��" << this->speech_Rounds << "��>>ѡ�����ڳ�ǩ!!" << endl;
	cout << "--------------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->speech_Rounds == 1)
	{
		//��һ�ֱ���
		random_shuffle(this->v1.begin(), this->v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//��һ�ֱ���
		random_shuffle(this->v2.begin(), this->v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}

	cout << "--------------------------------" << endl;
	system("pause");

}
//����
void SpeechManager::speech_Contest()
{
	cout << "<<��" << this->speech_Rounds << "��>>������ʽ��ʼ!!" << endl;
	vector<int> v_Src;//����ѡ������
	//׼����ʱ���������С��ɼ�
	multimap<double, int, greater<double>> groupScore;
	int num = 0;//��¼��Ա���� ����һ��
	if (this->speech_Rounds == 1)
	{
		v_Src = this->v1;
	}
	else
	{
		v_Src = this->v2;
	}
	//��������ѡ�ֽ��б���
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		//��ί���
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();//ȥ����߷�
		d.pop_back();//ȥ����ͷ�
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		//cout << "��ţ�" << *it << "\t������" << this->m_Speaker[*it].m_Name << "\t�÷֣�" << avg << endl;
		//��ƽ���ַ���map����
		this->m_Speaker[*it].m_Sore[this->speech_Rounds - 1] = avg;
		//��������ݷ�����ʱ������
		groupScore.insert(make_pair(avg, *it));	
		num++;
		//ÿ����ȡ��ǰ����
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "��ţ�" << it->second << "������" << this->m_Speaker[it->second].m_Name 
					 << "�÷֣�" << this->m_Speaker[it->second].m_Sore[this->speech_Rounds-1] << endl;
			}
			cout << endl;
			//����ǰ����
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&&count<3; it++,count++)
			{
				if (this->speech_Rounds == 1)
				{
					this->v2.push_back((*it).second);
				}
				else
				{
					this->vVictory.push_back(it->second);
				
				}
			}
			groupScore.clear();
		}


	}
	cout << "----------------��" << this->speech_Rounds << "�ֱ������-------------" << endl;
	system("pause");
}
//��ʾ����ѡ��
void SpeechManager::show_Winner()
{
	cout << "<<��" << this->speech_Rounds << "��>>����ѡ������" << endl;
	vector<int> v_Src;//��������ѡ������
	if (this->speech_Rounds == 1)
	{
		v_Src = this->v2;
	}
	else
	{
		v_Src = this->vVictory;
	}
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << *it << "\t������" << this->m_Speaker[*it].m_Name
			<< "\t�÷֣�" << this->m_Speaker[*it].m_Sore[this->speech_Rounds - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
}
//�����¼
void SpeechManager::save_Record()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	//��ÿ��ѡ������д���ļ�
	for (vector<int>::iterator it = this->vVictory.begin(); it != this->vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Sore[1] << ",";
	}
	ofs << endl;
	//�ر�
	ofs.close();
	cout << "��¼�Ѿ�������ˣ���" << endl;
	//�м�¼�ˣ��ļ���Ϊ��
	this->fileIsEmpty = false;
}
//��ȡ��¼
void SpeechManager::load_Record()
{
	ifstream ifs("speech.csv", ios::in);//���ļ�
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "�ļ������ڣ���" << endl;
		ifs.close();
		return;
	}
	//�ļ����
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ���Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch);//���жϵ��ַ�������
	string data;
	int year = 1;
	while (ifs >> data)
	{
		//cout << data << endl;
		//10002, 86.675, 10009, 81.3, 10007, 78.55,
		vector<string> v;//���6��string�ַ���
		int pos = -1;//���ҵ�","λ�õı���
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			//cout << pos << endl;
			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);
			//cout << endl;
			start = pos+1;

		}
		//cout << v.size() << endl;
		
		this->m_Record.insert(make_pair(year,v));
		year++;
	}
	ifs.close();
	/*for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
	{
		cout << "��" << it->first << "���ݽ�����" << endl;
	}*/
}
//��ʾ��¼
void SpeechManager::show_Record()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ������ڻ���Ϊ�գ���" << endl;
	}
	
	for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
	{
		cout << "��" << it->first << "���ݽ�����" <<
			"\n�ھ���ţ�" << it->second[0] << "\t����" << it->second[1]
			<< "\n�Ǿ���ţ�" << it->second[2] << "\t����" << it->second[3]
			<< "\n������ţ�" << it->second[4] << "\t����" << it->second[5] << endl;
	}
	system("pause");
	system("cls");
}
//��ռ�¼
void SpeechManager::clear_Record()
{
	cout << "�Ƿ�����ļ���" << endl;
	cout << "1����" << endl;
	cout << "2����" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		this->init_Speech();
		this->createSpeaker();
		this->load_Record();
	}
	system("pause");
	system("cls");

}
void SpeechManager::exit_Sys()
{
	cout << "��ӭ�´�ʹ��ϵͳ" << endl;
	system("pause");
	exit(0);
}
