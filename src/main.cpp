#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;
// Структура инфы о игроке
typedef struct
{
	int in_btl;
	int reg;
	string name;
	int level;
	int x;
	int y;
	int xp;
	int hp;
	int mana;
	int kills;
	int attack;
	int def;
	vector<int> inv(1);
}player_struct;
//Структура инфы о враге
typedef struct
{
	string name;
	int hp;
	int mana;
	int atta;
	int def;
}enemy;
//Структура инфы о предмете
typedef struct
{
	string name;
	int cost;
}item;

vector<item> items_list(0);

player_struct player = {0,0,"",0,-1,-1,0,1,1,0,5,0,null};

void save();
void read();
void reg();
int game();
int main_2();
void bvm();
void slap();
void inv();
void move();

int game()
{
	read_from_file();
	reg();
	do
	{
		string cmd = "";
		int key=-1;
		key = getch();
		// Говнокод по причине кроссплатформенности.
		// Под виндой можно сделать хорошо, но потом маяться под линукс я очень не хочу, так что вот так. Если кому не нравится - примите извинения.
		if(key == 224)
		{
			key = getch();
			switch(key)
			{
				case 72:{ move(0); break;}
				case 80:{ move(1); break;}
				case 75:{ move(2); break;}
				case 77:{ move(3); break;}
				default:{break;}
			}
		}
		else if(key == 13) continue;
		else
		{
			cmd+=(char)key;
			cout << (char)key;
			while(key != 13)
			{
				key = getche();
				if(key != 13) cmd+=(char)key;
			}
			cout << endl;
		}

		if (player.xp == (25*player.level))
		{
			player.xp = 0; 
			cout << "Level UP!" << endl;
			player.level++;
			player.attack += 4;
			player.def +=1;
			save_to_file();
		}
		cmdWork(string cmd);
	}
	while (cmd!="exit")
	return 0;
}




int cmdWork(string cmd)// Команды
{
	/*
		case "":
		{
			
			break;
		}
		case "": {  break;}
		case "":
		{
			if(player.in_btl==)
			{
				
			}
			break;
		}
	
	*/
	switch(cmd)
	{
		case "save": { save_to_file(); break;}
		case "load": { read_from_file(); break;}
		case "inv": { inv(); break;}
		case "coord": { cout << "Your coordinates. x = " << player.x << " y = " << player.y << endl; break;}
		case "stat":
		{
			cout << "Your statistic:" << endl << "Name: " << player.name << endl << "Level: " << player.level << endl << "Coordinates: " << endl << "x: " << player.x << endl << "y: " << player.y << endl << "Your experience: " << player.xp << endl << "HP: " << player.hp << endl << "MANA: " << player.mana << endl << "Kills: " << player.kills << endl << "Attack: " << player.attack << endl << "Def: " << player.def << endl;
			break;
		}
		case "hit":
		{
			if(player.in_btl==1){ slap(); }
			break;
		}
		case "heal":
		{
			if(player.in_btl==0)
			{
				int hp_p = pp.atta * 0.45;
				cout << "You healed for " << hp_p << ";" << endl;
				pp.hp = pp.hp + hp_p;
			}
			break;
		}
		case "run_away":
		{
			if(player.in_btl == 1)
			{
				pp.p_x = pp.p_x + 3; // TODO::Add random
				pp.p_y = pp.p_y + 2;
				pp.in_btl = 0;
				cout << "You ran away from the monster!" << endl;
			}
			break;
		}
		case "enemy_stat":
		{
			if(player.in_btl==)
			{
				cout << "Monstr statistic:" << endl << "Name: " << mo.name << endl << "HP: " << mo.hp << endl << "MANA: " << mo.mana << endl << "Attack: "<< mo.atta << endl << "Def: " << mo.def << endl;
			}
			break;
		}
		case "to_btl": { bvm(); break;}
		default:{break;}
	}
	// else if (!strcmp(cmd,"it")) cout << items[1].name << endl; - ??
	//else if (!strcmp(cmd,"help")) cout << "HELP" << endl << "Now this prigram have cmds:" << endl << "'up','down','left','right','coords','help','stat','save','exit' " << endl;
}

void move(int dir)
{
	switch(dir)
	{
		case 0: //up
		{
			player.x++;
			cout << "You go up, your coordinate x = " << player.x << endl;
			break;
		}
		case 1: //down
		{
			player.x--;
			cout << "You go up, your coordinate x = " << player.x << endl;
			break;
		}
		case 2: //left
		{
			player.y--;
			cout << "You go up, your coordinate y = " << player.y << endl;
			break;
		}
		case 3: //right
		{
			player.y++;
			cout << "You go up, your coordinate y = " << player.y << endl;
			break;
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
	if ( !player.in_btl == 1 )
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
				player.in_btl = 1;
				cout << mn[mv]<< endl;
			}
		}
	}
	// if ((pp.atta - mo.def) <= 0 ) cout << "You are so looose for this monster, your's hits heal him, if you want to live, run_away!" << endl; - ??
}

void slap()
{
	mo.hp -=(player.attack - mo.def);
	cout << "You atack monstr and hit him for " << player.attack - mo.def << " damage" << endl;
	player.hp -= (mo.atta - player.def);
	cout << "Monstr atack you and hit you for " << mo.atta - player.def << " damage" << endl;
	if (mo.hp <= 0 )
	{
		cout << "You win monstr!" << endl;
		player.in_btl = 0;
		mo.hp = 1;
	}
	if (pp.hp <= 0)
	{
		cout << "You die, level -1, attack -1, x=0,y=0" << endl;
		player.level--;
		player.attack--;
		player.p_x=0;
		player.p_y=0;
		player.in_btl = 0;
	}
}

void inv()
{
	int inv = 0;
	cout << "WIP" << endl;

}

void save_to_file()
{
	ofstream out("save");
	out << pp.reg << endl;
	out << pp.name << endl;
	out << pp.level << endl;
	out << pp.x << endl;
	out << pp.y << endl;
	out << pp.xp << endl;
	out << pp.hp << endl;
	out << pp.mana << endl;
	out << pp.kills << endl;
	out << pp.attack << endl;
	out << pp.def << endl;
	out.close();
}

void read_from_file()
{
	ifstream in("save");
	in >> pp.reg;
	in >> pp.name;
	in >> pp.level;
	in >> pp.x;
	in >> pp.y;
	in >> pp.xp;
	in >> pp.hp;
	in >> pp.mana;
	in >> pp.kills;
	in >> pp.attack;
	in >> pp.def;
	in.close();
	if (!pp.reg == 0 ) cout << "Your name:" << pp.name << endl << "Your level: " << pp.level << endl;

}

void reg()
{
	if ( player.reg == 0 )
	{;
		cout << "Name:";
		cin >> player.name;
		cout << endl << "You successfully registred"<<endl;
		player.reg = 1;
		player.x = 0;
		player.y = 0;
		player.level = 1;
		save_to_file();
		cout << "Your name: " << player.name << endl << "Your level: " << player.level << endl;
	}
}

int main()
{
	while(game()!=0) { }
	save_to_file();
	cout << "Thanks for playing!"<< endl;
	return 0;
}