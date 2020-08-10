#include "speechManager.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>

//构造函数
SpeechManager::SpeechManager()
{
	this->init_Speech();
	this->createSpeaker();
	this->load_Record();

}

//析构函数
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
		string name = "选手";
		name += nameSeed[i];
		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.m_Sore[j] = 0;
		}
		//创建选手编号并且放入容器
		this->v1.push_back(i + 10001);
		//将编号以及对应的选手存放容器
		this->m_Speaker.insert(make_pair(i + 10001, sp));

	}
}
void SpeechManager::show_Menu()
{
	cout << "***********************************" << endl;
	cout << "******** 欢迎参加演讲比赛 *********" << endl;
	cout << "******** 1.开始演讲比赛 ***********" << endl;
	cout << "******** 2.查看往届记录 ***********" << endl;
	cout << "******** 3.清空比赛记录 ***********" << endl;
	cout << "******** 0.退出比赛程序 ***********" << endl;
	cout << "***********************************" << endl;


}

void SpeechManager::start_Speech()
{
	//第一轮开始比赛
	//1、抽签
	this->speech_Draw();
	//2、比赛
	this->speech_Contest();
	//3、显示晋级结果
	this->show_Winner();
	//第二轮开始比赛
	this->speech_Rounds++;
	//1、抽签
	this->speech_Draw();
	//2、比赛
	this->speech_Contest();
	//3、显示晋级结果
	this->show_Winner();
	//4、保存分数到文件中
	this->save_Record();
	this->init_Speech();
	this->createSpeaker();
	this->load_Record();

	cout << "本届比赛落幕！！" << endl;
	system("pause");
	system("cls");


}
//抽签
void SpeechManager::speech_Draw()
{
	cout << "<<第" << this->speech_Rounds << "轮>>选手正在抽签!!" << endl;
	cout << "--------------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (this->speech_Rounds == 1)
	{
		//第一轮比赛
		random_shuffle(this->v1.begin(), this->v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//第一轮比赛
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
//比赛
void SpeechManager::speech_Contest()
{
	cout << "<<第" << this->speech_Rounds << "轮>>比赛正式开始!!" << endl;
	vector<int> v_Src;//比赛选手容器
	//准备临时容器，存放小组成绩
	multimap<double, int, greater<double>> groupScore;
	int num = 0;//记录人员个数 六人一组
	if (this->speech_Rounds == 1)
	{
		v_Src = this->v1;
	}
	else
	{
		v_Src = this->v2;
	}
	//遍历所有选手进行比赛
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		//评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();//去除最高分
		d.pop_back();//去除最低分
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		//cout << "编号：" << *it << "\t姓名：" << this->m_Speaker[*it].m_Name << "\t得分：" << avg << endl;
		//将平均分放入map容器
		this->m_Speaker[*it].m_Sore[this->speech_Rounds - 1] = avg;
		//将打分数据放入临时容器中
		groupScore.insert(make_pair(avg, *it));	
		num++;
		//每六人取出前三名
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second << "姓名：" << this->m_Speaker[it->second].m_Name 
					 << "得分：" << this->m_Speaker[it->second].m_Sore[this->speech_Rounds-1] << endl;
			}
			cout << endl;
			//拿走前三名
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
	cout << "----------------第" << this->speech_Rounds << "轮比赛完毕-------------" << endl;
	system("pause");
}
//显示晋级选手
void SpeechManager::show_Winner()
{
	cout << "<<第" << this->speech_Rounds << "轮>>晋级选手如下" << endl;
	vector<int> v_Src;//比赛晋级选手容器
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
		cout << "选手编号：" << *it << "\t姓名：" << this->m_Speaker[*it].m_Name
			<< "\t得分：" << this->m_Speaker[*it].m_Sore[this->speech_Rounds - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
}
//保存记录
void SpeechManager::save_Record()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	//将每个选手数据写入文件
	for (vector<int>::iterator it = this->vVictory.begin(); it != this->vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Sore[1] << ",";
	}
	ofs << endl;
	//关闭
	ofs.close();
	cout << "记录已经保存好了！！" << endl;
	//有记录了，文件不为空
	this->fileIsEmpty = false;
}
//读取记录
void SpeechManager::load_Record()
{
	ifstream ifs("speech.csv", ios::in);//读文件
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "文件不存在！！" << endl;
		ifs.close();
		return;
	}
	//文件清空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch);//将判断的字符补回来
	string data;
	int year = 1;
	while (ifs >> data)
	{
		//cout << data << endl;
		//10002, 86.675, 10009, 81.3, 10007, 78.55,
		vector<string> v;//存放6个string字符串
		int pos = -1;//查找到","位置的变量
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
		cout << "第" << it->first << "届演讲比赛" << endl;
	}*/
}
//显示记录
void SpeechManager::show_Record()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在或者为空！！" << endl;
	}
	
	for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
	{
		cout << "第" << it->first << "届演讲比赛" <<
			"\n冠军编号：" << it->second[0] << "\t分数" << it->second[1]
			<< "\n亚军编号：" << it->second[2] << "\t分数" << it->second[3]
			<< "\n季军编号：" << it->second[4] << "\t分数" << it->second[5] << endl;
	}
	system("pause");
	system("cls");
}
//清空记录
void SpeechManager::clear_Record()
{
	cout << "是否清空文件：" << endl;
	cout << "1、是" << endl;
	cout << "2、否" << endl;
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
	cout << "欢迎下次使用系统" << endl;
	system("pause");
	exit(0);
}
