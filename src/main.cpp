#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <conio.h>

using namespace std;

//Структура инфы о предмете
struct item
{
	string name;
	int cost;
};

//Структура инфы о враге
struct enemy
{
	string name;
	int hp;
	int mana;
	int attack;
	int def;
};

// Структура инфы о игроке
struct player_struct
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
	vector<int> inv;
	enemy cEnemy; // Current enemy
};

vector<item> items_list(0);
vector<enemy> enemy_list(0);

player_struct player = {0,0,"",0,-1,-1,0,1,1,0,5,0,vector<int>(1)};

void save();
void read();
void reg();
int game();
void cmdWork(string cmd);
void bvm();
void slap();
void inv();
void move(int dir);

int game()
{
	read();
	reg();
	string cmd = "";
	do
	{
		cmd = "";
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
			save();
		}
		cmdWork(cmd);
	}
	while (cmd != "exit");
	return 0;
}




void cmdWork(string cmd)// Команды
{
	if(cmd=="save") { save(); }
	else if(cmd=="load") { read(); }
	else if(cmd=="inv") { inv(); }
	else if(cmd=="coord") { cout << "Your coordinates. x = " << player.x << " y = " << player.y << endl; }
	else if(cmd=="stat") cout << "Your statistic:" << endl << "Name: " << player.name << endl << "Level: " << player.level << endl << "Coordinates: " << endl << "x: " << player.x << endl << "y: " << player.y << endl << "Your experience: " << player.xp << endl << "HP: " << player.hp << endl << "MANA: " << player.mana << endl << "Kills: " << player.kills << endl << "Attack: " << player.attack << endl << "Def: " << player.def << endl;
	else if(cmd=="hit" && player.in_btl==1) slap();
	else if(cmd=="heal" && player.in_btl==0)
	{
			cout << "You healed for " << player.attack * 0.45 << ";" << endl;
			player.hp += player.attack * 0.45;
	}
	else if(cmd=="run_away" && player.in_btl == 1)
	{
			player.x += 3; // TODO::Add random
			player.y += 2;
			player.in_btl = 0;
			cout << "You ran away from the monster!" << endl;
			
	}
	else if(cmd=="enemy_stat" && player.in_btl==1) cout << "Monstr statistic:" << endl << "Name: " << player.cEnemy.name << endl << "HP: " << player.cEnemy.hp << endl << "MANA: " << player.cEnemy.mana << endl << "Attack: "<< player.cEnemy.attack << endl << "Def: " << player.cEnemy.def << endl;
	else if(cmd=="to_btl") bvm();
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
				player.cEnemy.name = "Big Monstr";
				player.cEnemy.hp = 100;
				player.cEnemy.mana = 50;
				player.cEnemy.attack = 15;
				player.cEnemy.def = 5;
				player.in_btl = 1;
				cout << mn[mv]<< endl;
			}
		}
	}
	// if ((player.attack - player.cEnemy.def) <= 0 ) cout << "You are so looose for this monster, your's hits heal him, if you want to live, run_away!" << endl; - ??
}

void slap()
{
	player.cEnemy.hp -=(player.attack - player.cEnemy.def);
	cout << "You atack monstr and hit him for " << player.attack - player.cEnemy.def << " damage" << endl;
	player.hp -= (player.cEnemy.attack - player.def);
	cout << "Monstr atack you and hit you for " << player.cEnemy.attack - player.def << " damage" << endl;
	if (player.cEnemy.hp <= 0 )
	{
		cout << "You win monstr!" << endl;
		player.in_btl = 0;
		player.cEnemy.hp = 1;
	}
	if (player.hp <= 0)
	{
		cout << "You die, level -1, attack -1, x=0,y=0" << endl;
		player.level--;
		player.attack--;
		player.x=0;
		player.y=0;
		player.in_btl = 0;
	}
}

void inv()
{
	int inv = 0;
	cout << "WIP" << endl;

}

void save()
{
	ofstream out("save");
	out << player.reg << endl;
	out << player.name << endl;
	out << player.level << endl;
	out << player.x << endl;
	out << player.y << endl;
	out << player.xp << endl;
	out << player.hp << endl;
	out << player.mana << endl;
	out << player.kills << endl;
	out << player.attack << endl;
	out << player.def << endl;
	out.close();
}

void read()
{
	ifstream in("save");
	in >> player.reg;
	in >> player.name;
	in >> player.level;
	in >> player.x;
	in >> player.y;
	in >> player.xp;
	in >> player.hp;
	in >> player.mana;
	in >> player.kills;
	in >> player.attack;
	in >> player.def;
	in.close();
	if (!player.reg == 0 ) cout << "Your name:" << player.name << endl << "Your level: " << player.level << endl;

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
		save();
		cout << "Your name: " << player.name << endl << "Your level: " << player.level << endl;
	}
}

int main()
{
	while(game()!=0) { }
	save();
	cout << "Thanks for playing!"<< endl;
	return 0;
}