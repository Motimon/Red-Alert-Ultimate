#include<string>
#include<iostream>
#include<deque>
#include<algorithm>
#include <stdlib.h>
#define movingtime 5
using namespace std;
class Tank
{
public:
	string name;//坦克名字
	string starlevel;//星级
	int ID;//编号
	int price;//制造耗费的金币
	int producingtime;//制造耗费的时间
	int repairtime;//维修的时间
	int special_attack;//光棱攻击攻击力
	int normal_attack;//普通攻击攻击力
	int defense;//防御力数值
	int maxHp;//满血量
	double Hp;//血量
	bool survivalstate;//判断是否存活,'1'代表存活,'0'代表已报废
	bool transformation;//判断是否变形,'1'代表幻影坦克未处在变形状态及能被攻击的状态，'0'代表处于变形状态
	bool basestate;//判断是否出战,'1'代表在基地,'0'代表不在基地
	virtual void battle(int, int) {}//用来扣除血量
	virtual void starlevel_up() {}//用来提升星级；
	Tank(string Name, int Price, int Producingtime, int Repairtime, int Normal_attack, int Defense, int MaxHp, string Starlevel, double _Hp, bool Survivalstate, bool Basestate) :
		name(Name), price(Price), producingtime(Producingtime), repairtime(Repairtime), normal_attack(Normal_attack), defense(Defense), maxHp(MaxHp), starlevel("\0"), Hp(_Hp), survivalstate(Survivalstate), basestate(Basestate) {}
};
class Bear :public Tank
{
public:
	string name = "Bear";
	string starlevel = "\0";
	int ID;
	int price = 600;
	int producingtime = 1;
	int normal_attack = 30;
	int defense = 15;
	int maxHp = 100;
	double Hp = 100;
	bool survivalstate = 1;
	bool basestate = 1;
	void battle(int attack_strength, int defense_strength) {
		Tank::Hp -= attack_strength - defense_strength;
	}
	void starlevel_up() {
		Tank::starlevel += '*';
		Tank::normal_attack += 5;
		Tank::defense += 5;
	}
	Bear() :Tank("Bear", 600, 1, 0, 30, 15, 100, "\0", 100, 1, 1) {}
};
class Phantom :public Tank
{
public:
	string name = "Phantom";
	string starlevel = "\0";
	int ID;
	int price = 1000;
	int productingtime = 2;
	int normal_attack = 40;
	int defense = 15;
	int maxHp = 100;
	double Hp = 100;
	bool survivalstate = 1;
	bool transformation = 1;
	bool basestate = 1;
	void battle(int attack_strength, int defense_strength) {
		Tank::Hp -= attack_strength - defense_strength;
	}
	void starlevel_up() {
		Tank::starlevel += '*';
		Tank::normal_attack += 5;
		Tank::defense += 5;
	}
	Phantom() :Tank("Phantom", 1000, 2, 0, 40, 15, 100, "\0", 100, 1, 1) { Tank::transformation = 1; }
};
class Prism :public Tank
{
public:
	string name = "Prism";
	string starlevel = "\0";
	int ID;
	int price = 1200;
	int productingtime = 4;
	int special_attack = 50;
	int defense = 10;
	int maxHp = 100;
	double Hp = 100;
	bool survivalstate = 1;
	bool basestate = 1;
	void battle(int attack_strength, int defense_strength) {
		Tank::Hp -= attack_strength - defense_strength;
	}
	void starlevel_up() {
		Tank::starlevel += '*';
		Tank::defense += 5;
	}
	Prism() :Tank("Prism", 1200, 4, 0, 0, 10, 100, "\0", 100, 1, 1) { Tank::special_attack = 50; }
};
class Apocalypse :public Tank
{
public:
	string name = "Apocalypse";
	string starlevel = "\0";
	int ID;
	int price = 1750;
	int productingtime = 6;
	int normal_attack = 60;
	int defense = 20;
	int maxHp = 120;
	double Hp = 120;
	bool survivalstate = 1;
	bool basestate = 1;
	double damage_reduction = 0.8;
	void battle(int attack_strength, int defense_strength) {
		Tank::Hp -= (attack_strength - defense_strength) * 0.8;
	}
	void starlevel_up() {
		Tank::starlevel += '*';
		Tank::normal_attack += 5;
		Tank::defense += 5;
	}
	Apocalypse() :Tank("Apocalypse", 1750, 6, 0, 60, 20, 120, "\0", 120, 1, 1) {}
};
class Spy
{
public:
	int starlevel = 0;//星级
	int invasion_time;//入侵到对方基地所需时间
	Spy(int _starlevel) {
		starlevel = _starlevel;
		switch (starlevel) {
		case 1:invasion_time = 40; break;
		case 2:invasion_time = 20; break;
		case 3:invasion_time = 5; break;
		}
	}
};
typedef deque<Tank*>::iterator Iterator;//重命名迭代器名字
void producing(int& _totalmoney, int& _time, int _invadedtime, deque<Tank*>& tmp) {
	//'0'为灰熊,'1'为幻影,'2'为光棱,'3'为天启
	int i = 0;
	switch (i)
	{
	case 0:if (_totalmoney >= 600)
	{
		if (_time + 1 > _invadedtime)
		{
			_time = _invadedtime;
			break;
		}
		tmp.push_back(new Bear());
		_totalmoney -= 600;
		_time += 1;
	}
	case 1:if (_totalmoney >= 1000)
	{
		if (_time + 2 > _invadedtime)
		{
			_time = _invadedtime;
			break;
		}
		tmp.push_back(new Phantom());
		_totalmoney -= 1000;
		_time += 2;
	}
	case 2:if (_totalmoney > 1200)
	{
		if (_time + 4 > _invadedtime)
		{
			_time = _invadedtime;
			break;
		}
		tmp.push_back(new Prism());
		_totalmoney -= 1200;
		_time += 4;
	}
	case 3:if (_totalmoney >= 1750)
	{
		if (_time + 6 > _invadedtime)
		{
			_time = _invadedtime;
			break;
		}
		tmp.push_back(new Apocalypse());
		_totalmoney -= 1750;
		_time += 6;
	}
		  break;
	}
}//生产坦克
void fighting(Tank* tank1, Tank* tank2) {
	tank1->basestate = 0;//设为出战状态
	tank2->basestate = 0;
	if (tank1->name == "Bear" && tank2->name == "Bear")
	{
		tank1->battle(tank2->normal_attack, tank1->defense);
		tank2->battle(tank1->normal_attack, tank2->defense);
	}//Bear Vs Bear

	if ((tank1->name == "Bear" && tank2->name == "Phantom") || (tank2->name == "Bear" && tank1->name == "Phantom"))
	{
		if (tank1->transformation == 1 && tank1->name == "Phantom")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank1->transformation = 0;
		}
		else if (tank2->transformation == 1 && tank2->name == "Phantom")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank2->transformation = 0;
		}
		else if (tank2->transformation == 0 && tank1->name == "Bear")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->transformation = 1;
		}
		else if (tank1->transformation == 0 && tank2->name == "Bear")
		{
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank1->transformation = 1;
		}
	}//Bera Vs Phantom

	if ((tank1->name == "Bear" && tank2->name == "Prism") || (tank2->name == "Bear" && tank1->name == "Prism"))
	{
		if (tank1->name == "Bear")
		{
			tank1->battle(tank2->special_attack, 0);
			tank2->battle(tank1->normal_attack, tank2->defense);
		}
		if (tank2->name == "Bear")
		{
			tank2->battle(tank1->special_attack, 0);
			tank1->battle(tank2->normal_attack, tank1->defense);
		}
	}//Bear Vs Prism

	if ((tank1->name == "Bear" && tank2->name == "Apocalypse") || (tank1->name == "Apocalypse" && tank2->name == "Bear"))
	{
		if (tank1->name == "Bear")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->battle(tank1->normal_attack, tank2->defense);
		}
		if (tank2->name == "Bear")
		{
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank1->battle(tank2->normal_attack, tank1->defense);
		}
	}//Bear Vs Apocalypse

	if (tank1->name == "Phantom" && tank2->name == "Phantom")
	{
		if (tank1->transformation == 1 && tank2->transformation == 1)
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank1->transformation = 0;
			tank2->transformation = 0;
		}
		else if (tank1->transformation == 0 && tank2->transformation == 0)
		{
			tank1->transformation = 1;
			tank2->transformation = 1;
		}
	}//Phantom Vs Phantom

	if ((tank1->name == "Phantom" && tank2->name == "Prism") || (tank2->name == "Phantom" && tank1->name == "Prism"))
	{
		if (tank1->transformation == 1 && tank2->name == "Prism")
		{
			tank1->battle(tank2->special_attack, 0);
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank1->transformation = 0;
		}

		else if (tank2->transformation == 1 && tank1->name == "Prism")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->battle(tank1->special_attack, 0);
			tank2->transformation = 0;
		}
		else if (tank1->transformation == 0 && tank2->name == "Prism")
		{
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank1->transformation = 1;
		}
		else if (tank2->transformation == 0 && tank1->name == "Prism")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->transformation = 1;
		}
	}//Phantom Vs Prism

	if ((tank1->name == "Apocalypse" && tank2->name == "Phantom") || (tank2->name == "Apocalypse" && tank1->name == "Phantom"))
	{
		if (tank1->transformation == 1 && tank1->name == "Phantom")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank1->transformation = 0;
		}
		else if (tank2->transformation && tank2->name == "Phantom")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank2->transformation = 0;
		}
		else if (tank2->transformation == 0 && tank1->name == "Apocalypse")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->transformation = 1;
		}
		else if (tank1->transformation == 0 && tank2->name == "Apocalypse")
		{
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank1->transformation = 1;
		}
	}//Phantom Vs Apocalypse

	if (tank1->name == "Prism" && tank2->name == "Prism")
	{
		tank1->battle(tank2->special_attack, 0);
		tank2->battle(tank1->special_attack, 0);
	}//Prism Vs Prism

	if ((tank1->name == "Prism" && tank2->name == "Apocalypse") || (tank1->name == "Apocalypse" && tank2->name == "Prism"))
	{
		if (tank1->name == "Prism")
		{
			tank1->battle(tank2->normal_attack, tank1->defense);
			tank2->battle(tank1->special_attack, 0);
		}
		if (tank2->name == "Prism")
		{
			tank2->battle(tank1->normal_attack, tank2->defense);
			tank1->battle(tank2->special_attack, 0);
		}
	}//Prism Vs Apocalypse

	if ((tank1->name == "Apocalypse" && tank2->name == "Apocalypse"))
	{
		tank1->battle(tank2->normal_attack, tank1->defense);
		tank2->battle(tank1->normal_attack, tank2->defense);
	}//Apocalypse Vs Apocalypse
}//对战函数
void repair(Tank* tank, int& timecount) {
	tank->basestate = 1;
	if (timecount > 0 && tank->Hp < tank->maxHp)
		tank->Hp += (timecount - 5) * 4;//要减去自己返回基地所需的五个单位时间
	if (tank->Hp > tank->maxHp)
		tank->Hp = tank->maxHp;//防止一次性回复生命值回过头
	timecount = 0;//清空积累的维修时间
}//维修函数
void Repairtime(int p, int& Timecount, deque<Tank*>& tank) {
	if (p - 1 >= 0)
	{
		for (int k = 0; k < p; k++)
			tank[k]->repairtime += Timecount;
	}
}//给需要维修的坦克记录维修时间
Iterator get_iterator(deque<Tank*>& tmp) {
	for (Iterator k = tmp.begin(); k != tmp.end(); k++)
		if ((*k)->Hp <= 0)return k;
}//返回指向战败的坦克的指针的迭代器
int main()
{
	int time = 0;
	int totalmoney;//初始总金币
	int invadedtime;//敌方间谍入侵时间
	int starlevel_spy;//己方间谍星级
	string input;
	deque<Tank*> own;
	deque<Tank*> enemy;
	cin >> totalmoney;
	while (true)
	{
		cin >> input;
		if (input == "Bear") { enemy.push_back(new Bear()); continue; }
		if (input == "Phantom") { enemy.push_back(new Phantom()); continue; }
		if (input == "Prism") { enemy.push_back(new Prism()); continue; }
		if (input == "Apocalypse") { enemy.push_back(new Apocalypse()); continue; }
		else { invadedtime = atoi(input.c_str()); break; }
	}//产生敌方坦克
	cin >> starlevel_spy; Spy spy(starlevel_spy);
	if (true)
	{
		if ((totalmoney == 0 || invadedtime == 0) && enemy.empty())
		{
			cout << "Time:" << time << " Deadlock! It ended in a draw!";
			return 0;
		}//若己方无法生产坦克且敌方也无坦克

		if (totalmoney == 0 || invadedtime == 0)
		{
			cout << "Time:" << time << " You lost the war!";
			return 0;
		}//若己方初始金币为零或敌方间谍兵贵神速

		if (enemy.empty())
		{
			cout << "Time:" << time << " You won the war!";
			return 0;
		}//若敌方没有坦克，而己方有

	}//判断是否可以不战而胜/败
	while (time != invadedtime && totalmoney >= 600)
	{
		producing(totalmoney, time, invadedtime, own);
	}
	if (true)
	{
		if (totalmoney < 600 && time == invadedtime)
		{
			cout << "Time:" << time << " Money is empty, Invaded by enemy spies and production stalled,";
			for (Iterator i = own.begin(); i != own.end(); i++)
			{
				cout << ' ' << (*i)->name;
			}
			cout << '.';
		}//敌方间谍入侵和金币消耗殆尽同时发生
		if (totalmoney >= 600 && time == invadedtime)
		{
			cout << "Time:" << time << " Invaded by enemy spies and production stalled,";
			for (Iterator i = own.begin(); i != own.end(); i++)
			{
				cout << ' ' << (*i)->name;
			}
			cout << '.';
		}//金币未消耗殆尽但敌方间谍入侵
		if (totalmoney < 600 && time < invadedtime)
		{
			cout << "Time:" << time << " Money is empty and production stalled,";
			for (Iterator i = own.begin(); i != own.end(); i++)
			{
				cout << ' ' << (*i)->name;
			}
			cout << '.';
			time = invadedtime;
			cout << endl << "Time:" << time << " Invaded by enemy spies.";
		}//金币消耗殆尽敌方间谍未入侵
	}
	int invationTime = time + spy.invasion_time;
	int round = 1;//战斗开始
	int flag = 1;//让间谍入侵只进行一次；
	for (int i = 0, j = 0; !own.empty() && !enemy.empty();)
	{
		i %= own.size(); j %= enemy.size();//for循环中仅在循环体结束后才求解该表达式，所以放到这里来，避免出现分母为零的情况
		own[i]->transformation = 1;//每回合开始重置变形状态
		enemy[j]->transformation = 1;
		int timecount = 0;
		time += 5;
		if (i - 1 >= 0)own[i - 1]->basestate = 1;
		if (j - 1 >= 0)enemy[j - 1]->basestate = 1;//让上一回合胜利的坦克回到基地
		if (time > invationTime && time - 5 <= invationTime)
		{
			repair(own[i], own[i]->repairtime);
			repair(enemy[j], enemy[j]->repairtime);//出战前统一完成维修工作
			for (Iterator k = own.begin(); k != own.end(); k++)
			{
				if ((*k)->basestate)(*k)->starlevel_up();
			}
			cout << endl << "Time:" << invationTime + 0.5 << " Spy successfully steal enemy tank technology,";
			for (Iterator k = own.begin(); k != own.end(); k++)
			{
				if ((*k)->basestate)
					cout << ' ' << (*k)->name;
			}
			cout << " will be upgraded!";
			timecount -= 5;//减掉后两行那一句多加的
		}//防止时间在一回合结束后恰好在[invationTime-5,invationTime]之间
		timecount += 5;
		cout << endl << "Time:" << time << " Round " << round << " Start, " << own[i]->name << own[i]->starlevel << " vs " << enemy[j]->name << enemy[j]->starlevel << '.' << endl;
		while (own[i]->Hp > 0 && enemy[j]->Hp > 0)
		{
			repair(own[i], own[i]->repairtime);
			repair(enemy[j], enemy[j]->repairtime);//出战前统一完成维修工作
			fighting(own[i], enemy[j]);
			if (time == invationTime)
			{//己方间谍入侵时
				for (Iterator k = own.begin(); k != own.end(); k++)
				{
					if ((*k)->basestate)(*k)->starlevel_up();
				}
				cout << "Time:" << invationTime + 0.5 << " Spy successfully steal enemy tank technology,";
				for (Iterator k = own.begin(); k != own.end(); k++)
				{
					if ((*k)->basestate)
						cout << ' ' << (*k)->name;
				}
				cout << " will be upgraded!" << endl;
			}

			time++;
			timecount++;
		}
		cout << "Time:" << time << " Round " << round << " End, ";
		Repairtime(i, timecount, own);
		Repairtime(j, timecount, enemy);//记录需要维修坦克的维修时间
		if (true)
		{
			if (own[i]->Hp <= 0 && enemy[j]->Hp <= 0)
			{
				cout << "Deadlock!";
				own.erase(get_iterator(own));
				enemy.erase(get_iterator(enemy));
				if (i == own.size())i=0;
				if (j == enemy.size())j=0;//若将战败坦克从队列移出前下标恰好位于队列末尾，则移除后下标等于队列长度但其已越界
			}//平局
			else if (own[i]->Hp > 0 && enemy[j]->Hp <= 0)
			{
				cout << "You won the encounter!";
				enemy.erase(get_iterator(enemy));
				if (j - 1 >= 0)j %= enemy.size();//如果本回合敌方输了而前一回合赢了则需要更换下标，避免越界
				if (i + 1 < own.size())
				{
					i++;
				}//当队伍中存在坦克数>=2时才需要做下标递增，否则孤军奋战至最后一刻
			}//己方坦克胜利
			else if (own[i]->Hp <= 0 && enemy[j]->Hp > 0)
			{
				cout << "You lost the encounter!";
				own.erase(get_iterator(own));
				if (i - 1 >= 0)i %= own.size();
				if (j + 1 < enemy.size())
				{
					j++;
				}
			}//敌方坦克胜利
		}
		if (!own.empty())
		{
			int f = 0;//循环次数，限制其在容器容量长度内
			for (Iterator k = find(own.begin(), own.end(), own[i]); f < own.size(); f++, k++)
			{
				if (k == own.end())k = own.begin();
				if ((*k)->basestate)cout << ' ' << (*k)->name << (*k)->starlevel;
			}
			if(own.size()!=1)//如果战斗结束时己方还剩一辆坦克，则此时其不在基地，不需要输出"."
			cout << '.';
		}
		round++;
	}
	if (own.empty() && enemy.empty())
		cout << " It ended in a draw!";
	if (!own.empty() && enemy.empty())
		cout << " You won the war!";
	if (own.empty() && !enemy.empty())
		cout << " You lost the war!";
	return 0;
}
//20000 Prism Bear Bear Bear Apocalypse Apocalypse Phantom Phantom Bear 34 1





//#include <iostream>
//#include <string>
//using namespace std;
//#define Tank_Num_Max  100//表示双方基地最多生产的坦克数目
//long double Time = 0;//游戏进行时间
//int Spy_Grade = 0;//间谍星级
//int Invade_Time = 0;//入侵时间
//
//void Time_Out() {//时间输出函数
//	cout << "Time:" << Time << " ";
//}
//
//class Tank {//基类坦克
//public:
//	string Name;
//	int ATK;//普通攻击
//	int DEF;//防御
//	int HP;//血量
//	int TI;//生产时间
//	int PR;//价格
//	int Jud_Ser;//是否需要维修判断位
//	int Ret_Time;//返回基地时间
//	int HP_Max;//最大血量值
//	int Str_Time;//出发时间
//	Tank() :ATK(0), DEF(0), HP(0), TI(0), PR(0), Name("Tank"), Jud_Ser(0), Ret_Time(0), HP_Max(0), Str_Time(0) {}//初始化函数
//	Tank(int A, int D, int H, int T, int P, string N, int J, int R, int H_M, int S) :ATK(A), DEF(D), HP(H), TI(T), PR(P), Name(N), Jud_Ser(J), Ret_Time(R), HP_Max(H_M), Str_Time(S) {}
//	void Start(void) {//从基地出发函数
//		Jud_Ser = 0;
//		Str_Time = (int)Time;
//	}
//	void Back(void) {//返回基地函数(有判断条件)
//		Jud_Ser = 1;
//		Ret_Time = (int)Time + 5;//返回需要5个时间，此时Time为结束战斗时间
//	}
//	virtual void Skill(int Harm) {}//每个坦克的技能（传入该坦克收到的伤害），其实该函数是为幻影和天启坦克准备的
//	virtual void Attack(Tank* s1) {}//攻击函数
//};
//
//class Bear :public Tank {//灰熊
//public:
//	Bear() :Tank(30, 15, 100, 1, 600, "Bear", 0, 0, 100, 0) {}//初始化
//	void Attack(Tank* s1) {
//		s1->HP -= (ATK - s1->DEF);
//		s1->Skill(ATK - s1->DEF);
//	}
//	void Skill(int Harm) {}//无特殊技能
//};
//
//class Phantom :public Tank {//幻影
//public:
//	int Tran;//变形判断位，初始化为1，即第一次受到伤害
//	Phantom() :Tank(40, 15, 100, 2, 1000, "Phantom", 0, 0, 100, 0), Tran(1) {}
//	void Attack(Tank* s1) {
//		s1->HP -= (ATK - s1->DEF);
//		s1->Skill(ATK - s1->DEF);
//	}
//	void Skill(int Harm) {//在同一回合内，受到伤害后，下一次将免伤
//		if (Harm == 0) {//判断是否受到伤害
//			Tran = 1;//在同一回合内，如果第一次没受到伤害，那么以后也不会受到伤害，故置1即可
//		}
//		else {
//			if (Tran % 2 == 0) {
//				HP += Harm;
//			}
//			Tran++;
//		}
//	}
//};
//
//class Prism :public Tank {//光棱
//public:
//	int Lig_ATK;//光棱攻击的攻击力
//	Prism() :Tank(0, 10, 100, 4, 1200, "Prism", 0, 0, 100, 0), Lig_ATK(50) {}
//	void Attack(Tank* s1) {
//		s1->HP -= Lig_ATK;//无视防御
//		s1->Skill(Lig_ATK);
//	}
//	void Skill(int Harm) {}//无特殊技能
//};
//
//class Apocalypse :public Tank {//天启
//public:
//	double Avoid;
//	Apocalypse() :Tank(60, 20, 120, 6, 1750, "Apocalypse", 0, 0, 120, 0), Avoid(0.2) {}
//	void Attack(Tank* s1) {
//		s1->HP -= (ATK - s1->DEF);
//		s1->Skill(ATK - s1->DEF);
//	}
//	void Skill(int Harm) {//具有免伤技能
//		HP += (int)(Harm * Avoid);
//	}
//};
//
//class Site {//基类基地
//public:
//	int Gold;//金币数
//	Tank* List[Tank_Num_Max];//战斗顺序，生产的坦克放入当中
//	int List_Num;//战斗顺序表中的坦克数目
//	Tank* Combat;//正在战斗的坦克
//	Tank* Winner[Tank_Num_Max];//胜利归来的坦克(需要维修)
//	int Winner_Num;//胜利归来在基地里的坦克数目
//	Site() {//初始化函数
//		Gold = 0;
//		List_Num = 0;
//		Winner_Num = 0;
//		Combat = NULL;
//		for (int i = 0; i < Tank_Num_Max; i++) {
//			List[i] = NULL;
//			Winner[i] = NULL;
//		}
//	}
//	void Service() {//基地的维修坦克函数
//		for (int i = 0; i < Winner_Num; i++) {
//			if (Winner[i]) {//判断是否是空指针NULL
//				if (Winner[i]->Jud_Ser && Time > Winner[i]->Ret_Time) {//需要同时满足维修判断标志位为1和当前时间大于该坦克返回基地时间
//					Winner[i]->HP += 4;
//					if (Winner[i]->HP > Winner[i]->HP_Max) {//判断当前生命值是否大于最大HP
//						Winner[i]->HP = Winner[i]->HP_Max;//血量直接赋值为最大值
//						Winner[i]->Jud_Ser = 0;//将维修判断标志位置0
//					}
//				}
//			}
//		}
//	}
//
//};
//
//class My_Site :public Site {//我方基地
//public:
//	Tank* PD_List_Tank[4];//坦克生产顺序表
//	My_Site() :Site() {//给入生产顺序
//		PD_List_Tank[0] = new Bear(); PD_List_Tank[1] = new Phantom();
//		PD_List_Tank[2] = new Prism(); PD_List_Tank[3] = new Apocalypse();
//	}
//	void MY_PD();//我方基地生产函数
//};
//
//class Your_Site :public Site {//敌方基地
//public:
//	Your_Site() :Site() {}//构造函数
//	void YO_PD(const string s);//敌方基地生产函数
//};
//
//void My_Site::MY_PD() {//我方生产函数
//	int i = 0;
//	int Spy_Jud = 0;//判断生产结束原因（是否因间谍入侵导致）
//	for (i = 0; Gold >= PD_List_Tank[0]->PR && Time < Invade_Time; ++i %= 4) {
//		if (Gold >= PD_List_Tank[i]->PR) {
//			if ((Time + PD_List_Tank[i]->TI) > Invade_Time) {//如果时间超过间谍入侵时间则停止
//				Spy_Jud = 1;
//				break;
//			}
//			Gold -= PD_List_Tank[i]->PR;
//			Time += PD_List_Tank[i]->TI;
//			switch (i) {
//			case 0:List[List_Num] = new Bear();
//				break;
//			case 1:List[List_Num] = new Phantom();
//				break;
//			case 2:List[List_Num] = new Prism();
//				break;
//			case 3:List[List_Num] = new Apocalypse();
//				break;
//			}
//			List_Num++;
//		}
//	}
//	if (Gold < PD_List_Tank[0]->PR && (Spy_Jud || Time >= Invade_Time)) {//如果当前金币数不足以生产任何坦克并且是由于间谍入侵导致
//		Time = Invade_Time;//此时时间等于间谍入侵时间					 //（有个隐含条件，如果刚好生产完最后一辆坦克时结束，且时间
//		Time_Out();														 //刚好等于间谍入侵时间时，Spy_Jud不能生效，故需要进行时间判断
//		cout << "Money is empty, Invaded by enemy spies and production stalled, ";
//	}
//	else if (Spy_Jud || Time >= Invade_Time) {//如果只是因为间谍入侵导致
//		Time = Invade_Time;//此时时间等于间谍入侵时间
//		Time_Out();
//		cout << "Invaded by enemy spies and production stalled, ";
//	}
//	else if (Gold < PD_List_Tank[0]->PR) {//如果只是因为金币不够导致
//		Time_Out();
//		cout << "Money is empty and production stalled, ";
//	}
//	for (i = 0; i < List_Num; i++) {//输出当前已经生产的坦克
//		if (i == 0) {
//			cout << List[i]->Name;
//		}
//		else {
//			cout << " " << List[i]->Name;
//		}
//	}
//	cout << "." << endl;
//	if (Time < Invade_Time) {//判断时间是否到达间谍入侵时间，前面只有只是因为金币不够导致无法生产情况下未将时间修改，并且也只有该情况需要输出“Invaded by enemy spies.”
//		Time = Invade_Time;//此时时间等于间谍入侵时间
//		Time_Out();
//		cout << "Invaded by enemy spies." << endl;
//	}
//}
//
//bool Jud_Spy_0ut = true;//间谍输出函数是否执行的判断变量
//My_Site MY;//我方实际基地
//Your_Site Your;//地方实际基地
//int Round = 0;//回合数字
//
//void Spy_Out(Site& M) {//我方间谍的输出函数
//	cout << "Time:" << (Time + 0.5) << " ";
//	if (M.List_Num == 0) {//判断当前基地是否有坦克
//		cout << "Spy successfullysteal enemy tank technology." << endl;
//	}
//	else {
//		cout << "Spy successfully steal enemy tank technology, ";
//		for (int i = 0; i < M.List_Num; i++) {
//			if (M.List[i]->Ret_Time <= (Time + 0.5) || M.List[i]->Str_Time >= (Time + 0.5) || M.List[i]->Str_Time == 0) {//在出发之前或者回来之后，由于出发时间初始化是0，故在基地未出发的坦克出发时间为零
//				cout << M.List[i]->Name << " ";
//				M.List[i]->Name += "*";
//				M.List[i]->ATK += 5;
//				M.List[i]->DEF += 5;
//			}
//		}
//		cout << "will be upgraded!" << endl;
//	}
//	Jud_Spy_0ut = false;//用来判断是否需要进入该函数，节省时间
//}
//
//void My_Spy_Act() {//间谍判断输出函数，如果判断位为0则不需要进入函数if内部
//	if (Jud_Spy_0ut) {
//		if (Spy_Grade == 3) {
//			if (Time == (5.0 + Invade_Time)) {
//				Spy_Out(MY);
//			}
//		}
//		else if (Spy_Grade == 2) {
//			if (Time == (20.0 + Invade_Time)) {
//				Spy_Out(MY);
//			}
//		}
//		else if (Spy_Grade == 1) {
//			if (Time == (40.0 + Invade_Time)) {
//				Spy_Out(MY);
//			}
//		}
//	}
//}
//
//void Road() {//坦克出发（或返回）的前进（或返回）时间函数
//	for (int i = 0; i < 5; i++) {//需要五个单位时间
//		My_Spy_Act();//我方间谍的判断函数
//		MY.Service();//我方基地的维修函数
//		Your.Service();//敌方基地的维修函数
//		Time++;
//	}
//}
//
//void Road_Fight() {//战斗过程的时间处理
//	My_Spy_Act();//我方间谍的判断函数
//	MY.Service();//我方基地的维修函数
//	Your.Service();//敌方基地的维修函数
//	Time++;
//}
//
//void Your_Site::YO_PD(const string s) {//敌方基地的生产函数
//	if (s == "Bear") {
//		List[List_Num] = new Bear();
//		List_Num++;
//	}
//	else if (s == "Phantom") {
//		List[List_Num] = new Phantom();
//		List_Num++;
//	}
//	else if (s == "Prism") {
//		List[List_Num] = new Prism();
//		List_Num++;
//	}
//	else if (s == "Apocalypse") {
//		List[List_Num] = new Apocalypse();
//		List_Num++;
//	}
//}
//
//bool Jud_S_N(const string s) {//判断输入字符串死否是数字
//	if (s[0] <= 57 && s[0] >= 48) {
//		return false;
//	}
//	else {
//		return true;
//	}
//}
//
//void Game_Init() {//初始化游戏
//	cin >> MY.Gold;//输入价钱
//	string temp;//用来
//	while (cin >> temp && Jud_S_N(temp)) {//输入敌方基地的坦克和顺序
//		Your.YO_PD(temp);
//	}
//	Invade_Time = std::stoi(temp);//字符串转数字函数，输入入侵时间
//	cin >> Spy_Grade;//用来输入间谍星级
//	if (MY.Gold >= MY.PD_List_Tank[0]->PR && Your.List[0] != NULL && Invade_Time >= 1) {//双方都有坦克情况
//		MY.MY_PD();
//	}
//	else {//一方没有坦克情况，则不需要战斗了，可以直接得出战斗结果，进入该过程，我方绝对没有进行坦克生产，故MY.List[0] == NULL绝对成立
//		Time_Out();
//		if (Your.List[0] != NULL && (MY.Gold < MY.PD_List_Tank[0]->PR || Invade_Time == 0)) {//失败条件
//			cout << "You lost the war!" << endl;
//		}
//		if (Your.List[0] == NULL && (MY.Gold >= MY.PD_List_Tank[0]->PR && (Invade_Time > 0))) {//获胜条件
//			cout << "You won the war!" << endl;
//		}
//		if (Your.List[0] == NULL && (MY.Gold < MY.PD_List_Tank[0]->PR || Invade_Time == 0)) {//和局条件
//			cout << "It ended in a draw!" << endl;
//		}
//	}
//}
//
//bool Jud_Insert_Winner(Site& M) {//判断是否需要将获胜的坦克插入Winner数组里，判断地址
//	for (int i = 0; i < M.Winner_Num; i++) {
//		if (M.Combat == M.Winner[i]) {
//			return false;
//		}
//	}
//	return true;
//}
//
//
//void Clear_List(Site& M) {//败者使用，将战斗失败的坦克delete掉,并且判断WInner数组里是否有，并删除
//	for (int i = 0; i < M.Winner_Num; i++) {
//		if (M.Combat == M.Winner[i]) {
//			delete M.Combat;
//			for (int j = i; j < M.Winner_Num - 1; j++) {
//				M.Winner[j] = M.Winner[j + 1];
//			}
//			M.Winner[M.Winner_Num - 1] = NULL;
//			M.Combat = NULL;
//			M.Winner_Num--;
//		}
//	}
//	if (M.Combat) {
//		delete M.Combat;
//		M.Combat = NULL;
//	}
//}
//
//void Ready_List(Site& Y) {//战斗前使用，将List重新排序，并删除(并不是将其detele，将List的坦克前移一位，第一位赋给Combat)
//	Y.Combat = Y.List[0];
//	Y.List[0] = NULL;
//	int i = 0;
//	for (i = 0; i < Y.List_Num - 1; i++) {
//		Y.List[i] = Y.List[i + 1];
//	}
//	Y.List[i] = NULL;
//	Y.List_Num--;
//}
//
//void Sort_List(Site& Y) {//赢者使用，调换顺序
//	if (Jud_Insert_Winner(Y)) {//判断获胜的坦克是否已经插入Winner数组
//		Y.Winner[Y.Winner_Num] = Y.Combat;//战胜的坦克插入战胜的坦克的数组里
//		Y.Winner_Num++;
//	}
//	Y.List[Y.List_Num] = Y.Combat;//战胜的坦克插入战斗顺序链尾
//	Y.List_Num++;
//}
//
//void Clear_Place(Site& M, Site& Y) {//为下一回合做准备(正在战斗的坦克切换，获胜的坦克返回基地维修(有个返回的前提条件)并且插到队尾，失败的坦克直接delete掉，并将基地的List_Num减一，然后重新排列一下出场顺序。
//	if (M.Combat && Y.Combat) {//判断是否有空指针
//		if (M.Combat->HP > 0 && Y.Combat->HP <= 0) {//赢了
//			Clear_List(Y);
//			Sort_List(M);
//		}
//		else if (M.Combat->HP <= 0 && Y.Combat->HP > 0) {//输了
//			Clear_List(M);
//			Sort_List(Y);
//		}
//		else {//平局
//			Clear_List(M);
//			Clear_List(Y);
//		}
//	}
//}
//
//void Phantom_Round_Init(Site& M) {//幻影坦克技能的回合初始化
//	if (M.Combat->Name == "Phantom" || M.Combat->Name == "Phantom*") {
//		M.Combat->Skill(0);
//	}
//}
//
//void Depart_Tank(Site& M, Site& Y) {//坦克的出发函数
//	Y.Combat = Y.List[0];
//	M.Combat = M.List[0];
//	Ready_List(M);
//	Ready_List(Y);
//	if (Y.Combat && M.Combat) {//判断是否有空指针
//		M.Combat->Start();
//		Y.Combat->Start();
//		Phantom_Round_Init(M);
//		Phantom_Round_Init(Y);
//	}
//}
//
//void Round_Start(Site& M, Site& Y) {//回合开始函数
//	Depart_Tank(M, Y);
//	Road();
//	Time_Out();
//	if (Y.Combat && M.Combat) {//判断是否有空指针
//		Round++;
//		cout << "Round " << Round << " Start, " << M.Combat->Name << " " << "vs " << Y.Combat->Name << "." << endl;
//	}
//}
//
//void Jud_Result() {//判断双方基地最终成败结果函数
//	if (MY.List[0] == NULL && Your.List[0] != NULL) {
//		cout << " You lost the war!";
//	}
//	else if (MY.List[0] != NULL && Your.List[0] == NULL) {
//		cout << " You won the war!";
//	}
//	else if (MY.List[0] == NULL && Your.List[0] == NULL) {
//		cout << " It ended in a draw!";
//	}
//	cout << endl;
//}
//
//void My_Tank(Site& M) {//输出我余下的坦克（每回合结束后使用）
//	for (int i = 0; i < M.List_Num; i++) {
//		cout << " " << M.List[i]->Name;
//	}
//	if (M.List_Num != 0) {
//		cout << ".";
//	}
//}
//
//void Round_End(Site& M, Site& Y) {//回合结束并按指定输出(需要处理坦克换代)
//	Time_Out();
//	cout << "Round " << Round << " End, ";
//	if (M.Combat && Y.Combat) {
//		if (M.Combat->HP > 0 && Y.Combat->HP <= 0) {//赢了
//			M.Combat->Back();
//			cout << "You won the encounter!";
//			My_Tank(M);
//		}
//		else if (M.Combat->HP <= 0 && Y.Combat->HP > 0) {//输了
//			Y.Combat->Back();
//			cout << "You lost the encounter!";
//			My_Tank(M);
//		}
//		else {//平局
//			cout << "Deadlock!";
//			My_Tank(M);
//		}
//	}
//}
//
//void Fight_Course(Site& M, Site& Y) {//战斗中
//	if (M.Combat && Y.Combat) {//双方战斗前提条件非空指针
//		while (M.Combat->HP > 0 && Y.Combat->HP > 0) {//其次每次战斗前两者必须都活着
//			M.Combat->Attack(Y.Combat);
//			Y.Combat->Attack(M.Combat);
//			Road_Fight();//战斗时间处理函数
//		}
//	}
//}
//
//int main() {
//	Game_Init();//游戏初始化
//	while (MY.List[0] && Your.List[0]) {//判断双方是否有坦克
//		Round_Start(MY, Your);//回合开始
//		Fight_Course(MY, Your);//战斗中
//		Round_End(MY, Your);//回合结束
//		Clear_Place(MY, Your);//打扫战场
//		Jud_Result();//判断双方基地最终成败结果函数
//	}
//	return 0;
//}