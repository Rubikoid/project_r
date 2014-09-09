// Inclides
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
// Struct witht info of player
typedef struct
{
	int in_btl; // Это есть в структуре, но нету в файле, осторожно. Взять save_o с собой!
	int p_reg;
	char p_name[100];
	int p_level;
	int p_x;
	int p_y;
	int xod;
	int hp;
	int mana;
	int kills;
	int atta;
	int def;
	int inv[10];
}pi;

typedef struct
{
	char name[100];
	int hp;
	int mana;
	int atta;
	int def;
}mon;

typedef struct
{
	char name[100];
	int id;
	int cost;
}item;

item items[] = 
{
	{"None",0,0},
	{"TestITM",1,500},
};

mon mo = {"NONAME",1,0,0,0};

pi pp = {0,0,"NONAME",0,99,99,0,1,1,0,5,0,{0,0,0,0,0,0,0,0,0,0}};

char cmd[500];

void save_to_file();
void read_from_file();
void reg();
int main_1_1();
int main_1_2();
int main_2();
void bvm();
void slap();
void inv();

int main_1_1 ()
{
	read_from_file();
	reg();
	char hi[][100] = 
	{
		"                    ",
		"Hi, my name Rubikoid",
		"I want to review my quest",
		".........................",
		"ENJOY!!",
	};
	for (int i=0;i<5;i++)
	{
		cout << hi[i] << endl;
	}
	int r = main_1_2();
	if (r==0) return 0;
}

int main_1_2 ()
{
	while (1==1)
	{
		//cout << "123" << endl;
		cin >> cmd;
		if (!strcmp(cmd,"up")|| !strcmp(cmd,"down") || !strcmp(cmd,"left") || !strcmp(cmd,"right") ) pp.xod++;
		if (pp.xod == 10)
		{
			pp.xod = 0;
			cout << "LEVEL UP!" << endl;
			pp.p_level++;
			pp.atta = pp.atta + 4;
			pp.def = pp.def +1;
			save_to_file();
		}
		int r = main_2();
		if (r==0) return 0;
		else 
		{
			int bttl = 0;
			if (bttl == 1) bvm();
		}
	}
}

void bvm()
{
	int mv = 5;
	char mn[][100]=
	{
		"",
		"You get very big monster!",
		"You get normal monster!",
		"You get small monster!",
		"You get small-normal monster!",
		"You get normal-big monster!",
		"You get VERY BIG MONSTER!!!",
	};
	if ( !pp.in_btl == 1 )
	{
		switch (mv)
		{
			case 5:
			{
				strcpy(mo.name,"Big Monstr");
				mo.hp = 100;
				mo.mana = 50;
				mo.atta = 15;
				mo.def = 5;
				pp.in_btl = 1;
				cout << mn[mv]<< endl;
			}
		}
	}
	if ((pp.atta - mo.def) <= 0 ) cout << "You are so looose for this monster, your's hits heal him, if you want to live, run_away!" << endl;
}



int main_2 ()// Команды
{
	if (!strcmp(cmd,"exit") && pp.in_btl == 0) 
	{
		save_to_file(); 
		return 0;
	}
	else if (!strcmp(cmd,"up") && pp.in_btl == 0)
	{
		pp.p_x++;
		cout << "You go up, your coordinate x = " << pp.p_x << endl;
	}
	else if (!strcmp(cmd,"down") && pp.in_btl == 0 )
	{
		pp.p_x--;
		cout << "You go down, your coordinate x = " << pp.p_x << endl;
	}
	else if (!strcmp(cmd,"left") && pp.in_btl == 0)
	{
		pp.p_y++;
		cout << "You go left, your coordinate y = " << pp.p_y << endl;
	}
	else if (!strcmp(cmd,"right") && pp.in_btl == 0)
	{
		pp.p_y--;
		cout << "You go right, your coordinate y = " << pp.p_y << endl;
	}
	else if (!strcmp(cmd,"heal")) 
	{
		int hp_p = pp.atta * 0.45;
		cout << "You healed for " << hp_p << ";" << endl;
		pp.hp = pp.hp + hp_p;
	}
	else if (!strcmp(cmd,"run_away")&& pp.in_btl == 1 )
	{
		pp.p_x = pp.p_x + 3;
		pp.p_y = pp.p_y + 2;
		pp.in_btl = 0;
		cout << "You ran away from the monster!" << endl;
	}
	else if (!strcmp(cmd,"inv")) inv();
	else if (!strcmp(cmd,"hit") && pp.in_btl == 1) slap();
	else if (!strcmp(cmd,"to_btl")) bvm(); 
	else if (!strcmp(cmd,"it")) cout << items[1].name << endl;
	else if (!strcmp(cmd,"load")) read_from_file();
	else if (!strcmp(cmd,"mostat") && pp.in_btl == 1) cout << "Monstr statistic:" << endl << "Name: " << mo.name << endl << "HP: " << mo.hp << endl << "MANA: " << mo.mana << endl << "Attack: "<< mo.atta << endl << "Def: " << mo.def << endl;
	else if (!strcmp(cmd,"coords")) cout << "Your coordinates. x = " << pp.p_x << " y = " << pp.p_y << endl;
	else if (!strcmp(cmd,"stat")) cout << "Your statistic:" << endl << "Name: " << pp.p_name << endl << "Level: " << pp.p_level << endl << "Coordinates: " << endl << "x: " << pp.p_x << endl << "y: " << pp.p_y << endl << "Your xods: " << pp.xod << endl << "HP: " << pp.hp << endl << "MANA: " << pp.mana << endl << "Kills: " << pp.kills << endl << "Attack: " << pp.atta << endl << "Def: " << pp.def << endl;
	else if (!strcmp(cmd,"help")) cout << "HELP" << endl << "Now this prigram have cmds:" << endl << "'up','down','left','right','coords','help','stat','save','exit' " << endl;
	//else if (!strcmp(cmd,""))
	else if (!strcmp(cmd,"save"))
	{
		save_to_file();
		cout << "Save Complete" << endl;
	}
	//else cout << "This program not have " << cmd << ", use 'help' for help" << endl;
}

void slap()
{
	//int 
	mo.hp = mo.hp - (pp.atta - mo.def);
	cout << "You atack monstr and hit him for " << pp.atta - mo.def << " damage" << endl;
	pp.hp = pp.hp - (mo.atta - pp.def);
	cout << "Monstr atack you and hit you for " << mo.atta - pp.def << " damage" << endl;
	if (mo.hp <= 0 )
	{
		cout << "You win monstr!" << endl;
		pp.in_btl = 0;
		mo.hp = 1;
	}
	if (pp.hp <= 0)
	{
		cout << "You die, level -1, attack -1, x=0,y=0" << endl;
		pp.p_level--;
		pp.atta--;
		pp.p_x=0;
		pp.p_y=0;
		pp.in_btl = 0;
	}
}

void inv()
{
	int inv = 0;
	cout << "What's inv you want (1-10)?" << endl;
	cin >> inv;
	inv--;
	if ((inv <= 9) && (inv >=0)) 
	{
		int itm_id = pp.inv[inv];
		switch (inv)
		{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				cout << "Inv" << endl << "Inv num: " << inv << endl << "Item name: " << items[itm_id].name << endl;
				break;
			default:
				cout << "No, only numbers 1-10!" << endl;
		}
	}
	else cout << "No, only numbers 1-10!" << endl;
}

void save_to_file()
{
	ofstream out("save");
	out << pp.p_reg << endl;
	out << pp.p_name << endl;
	out << pp.p_level << endl;
	out << pp.p_x << endl;
	out << pp.p_y << endl;
	out << pp.xod << endl;
	out << pp.hp << endl;
	out << pp.mana << endl;
	out << pp.kills << endl;
	out << pp.atta << endl;
	out << pp.def << endl;
	for (int i=0; i<10;i++) 
	{
		out << pp.inv[i] << endl;
		cout << "ITEM:" << i << "  SAVED" << endl;
	}
	//out << pp.inv[10] << endl;
	out.close();
}

void read_from_file()
{
	ifstream in("save"); // save - НАЗВАНИЕ ФАЙЛА С СОХРАНЕНИЕМ, А НЕ НАЗВАНИЕ ПОТОКА!!
	in >> pp.p_reg;
	in >> pp.p_name;
	in >> pp.p_level;
	in >> pp.p_x;
	in >> pp.p_y;
	in >> pp.xod;
	in >> pp.hp;
	in >> pp.mana;
	in >> pp.kills;
	in >> pp.atta;
	in >> pp.def;
	for (int i=0; i<10;i++)
	{
		in >> pp.inv[i];		
		cout << "ITEM:" << i << "  LOADED" << endl;
	}
	//in >> pp.inv[10];
	in.close();
	if (!pp.p_reg == 0 ) cout << "Your name:" << pp.p_name << endl << "Your level: " << pp.p_level << endl;

}

void reg()
{
	if ( pp.p_reg == 0 )
	{
		cout << "Please, write your name:";
		cin >> pp.p_name;
		cout << endl << "Please, write your level(age)[Write only numbers!, inache budet ploxo]:";
		int perem;
		cin >> perem;
		//int perem_2 = (int)perem[0];
		pp.p_level = perem;
		cout << endl << "You successfully registred"<<endl;
		pp.p_reg = 1;
		pp.p_x = 0;
		pp.p_y = 0;
		save_to_file();
		cout << "Your name: " << pp.p_name << endl << "Your level: " << pp.p_level << endl;
	}
	else
	{
		cout << "You registred. Hi! "<< endl;
	}
}

int main()
{
	int r = main_1_1 ();
	if (r==0)
	{
		save_to_file();
		cout << "Thanks for playing, go back!"<< endl;
		return 0;
	}
	else 
	{
		r = main_1_1 ();
	}
}
