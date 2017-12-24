#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define up 72
#define down 80
#define left 75
#define right 77
#define Enter 13
#define mark 127

char mines[18][32], filled[17][31], temp, chr, pa='y',prev,p_t=1,chk;
int max_i, max_j, mine, vic, p_i,p_j,keep_play;

//set prev
int mark_prev(int i, int j) {
	if (p_t == 1) {
		p_i = 1;
		p_j = 1;
		prev = filled[1][1];
		filled[1][1] = mark;
		p_t++;
		return 0;
	}
	else {
		filled[p_i][p_j] = prev;
		prev = filled[i][j];
		filled[i][j] = mark;
		return 1;
	}
}

//reset filleds
void reset_game() {
	int i, j;
	for (i = 0; i <= 18; i++) {
		for (j = 0; j <= 32; j++) {
			mines[i][j] = ' ';
			if ((i<=17)&&(j<=31))
			if (i == 0)
				if (j == 0)	filled[i][j] = '\\';
				else filled[i][j] = j + 48;
			else if ((j == 0) && (i > 0)) filled[i][j] = i + 48;
			else filled[i][j] = '#';
		//	if ((i == 1) && (j == 1)) filled[i][j] = mark;
		}
	}
}

//printnig mines
void printing_mines() {
	int i, j;
	printf("\n");
	for (i = 1; i <= max_i; i++) {
		for (j = 1; j <= max_j; j++)
			printf("%c", mines[i][j]);
		printf("\n");
	}
	printf("\n");
}

//printnig filled
void printing_filled() {
	int i, j;
	system("cls");
//	printing_mines();
	printf("mines= %d.\n\n", mine);
	for (i = 0; i <= max_i; i++) {
		for (j = 0; j <= max_j; j++)
			if ((i == 0) && (j == 0)) printf(" \\|"); else
				if (i == 0) printf("%2d|", filled[i][j] - 48);
				else if (j == 0)	printf("%2d|", filled[i][j] - 48);
				else printf("%2c ", filled[i][j]);
				printf("\n");
	}
}

// set the difficult level of the game
void diff() {
	char x;
	int flg;
	do {
		flg = 1;
		
		printf("insert E for easy, 9X9 - 10 mines.\n");
		printf("insert M for medium, 16X16 - 30 mines.\n");
		printf("insert H for hard, 16X32 - 99 mines : ");
		
		x = getchar();
		temp = getchar();
		switch (x) {
			case 'e':
			case 'E':
				mine = vic = 10; max_i = max_j = 9; break;
			case 'm':
			case 'M':
				mine = vic = 30; max_i = max_j = 16; break;
			case 'h':
			case 'H':
				mine = vic = 99; max_i = 16; max_j = 30; break;
			default:
				system("cls");
				printf("wrong choise try again!!!\n"); flg = 0;
		}
	} while (flg==0);
} 

// set the mines
void set_mines() {
	int r_i, r_j, t;
	for (t = 0; t < mine; t++) {
		r_i = (rand() % max_i);
		r_j =(rand() % max_j);
		if ((mines[r_i][r_j] == ' ')&&(r_i>0)&&(r_j>0)) mines[r_i][r_j] = '*';
		else t--;
	}
}

//set the number around the mines
void set_num() {
	int i, j,count;
	for (i=1;i<=max_i;i++)
		for (j = 1; j <= max_j; j++) {
			count = 0;
			if (mines[i][j] != '*') {
				if (mines[i - 1][j - 1] == '*') count++;
				if (mines[i - 1][j] == '*') count++;
				if (mines[i - 1][j + 1] == '*') count++;
				if (mines[i][j - 1] == '*') count++;
				if (mines[i][j + 1] == '*') count++;
				if (mines[i + 1][j - 1] == '*') count++;
				if (mines[i + 1][j] == '*') count++;
				if (mines[i + 1][j + 1] == '*') count++;
				mines[i][j] = count + 48;
			}
		}
}

// open according to the player
void open_cell() {
	int flg=0,i,j;
	system("cls");
	switch (chr) {
		case '#':
			if (mines[p_i][p_j] == '*') vic++;
			if (filled[p_i][p_j] == '*') mine++;
			filled[p_i][p_j] = prev ='#';
			break;
		case '?':
			filled[p_i][p_j] = prev = '?';
			break;
		case '*':
			mine--;
			if (mines[p_i][p_j] == '*') { vic--; mines[p_i][p_j] = '@'; }
			filled[p_i][p_j] = prev = '*';
			break;
		case 'o':
		case 'O':
			if (mines[p_i][p_j] == '*') { vic = -1; break; }
			else if (mines[p_i][p_j] != '0') { filled[p_i][p_j] = prev = mines[p_i][p_j]; mines[p_i][p_j] = '~'; }
			else  {
					if (mines[p_i - 1][p_j - 1] == '0') { flg = 1; mines[p_i - 1][p_j - 1] = '!'; }
					if (mines[p_i - 1][p_j] == '0') { flg = 1; mines[p_i - 1][p_j] = '!'; }
					if (mines[p_i - 1][p_j + 1] == '0') { flg = 1; mines[p_i - 1][p_j + 1] = '!'; }
					if (mines[p_i][p_j - 1] == '0') { flg = 1; mines[p_i][p_j - 1] = '!'; }
					if (mines[p_i][p_j + 1] == '0') { flg = 1; mines[p_i][p_j + 1] = '!'; }
					if (mines[p_i + 1][p_j - 1] == '0') { flg = 1; mines[p_i + 1][p_j - 1] = '!'; }
					if (mines[p_i + 1][p_j] == '0') { flg = 1; mines[p_i + 1][p_j] = '!'; }
					if (mines[p_i + 1][p_j + 1] == '0') { flg = 1; mines[p_i + 1][p_j + 1] = '!'; }
					mines[p_i][p_j] = '~'; filled[p_i][p_j] =prev = ' ';
				}
			do{
				flg=0;
				for (i = 1; i <= max_i; i++) {
					for (j = 1; j <= max_j; j++) {
						if (mines[i][j] == '!') {
							if (mines[i - 1][j - 1] == '0') { flg = 1; mines[i - 1][j - 1] = '!'; }
							if (mines[i - 1][j] == '0') { flg = 1; mines[i - 1][j] = '!'; }
							if (mines[i - 1][j + 1] == '0') { flg = 1; mines[i - 1][j + 1] = '!'; }
							if (mines[i][j - 1] == '0') { flg = 1; mines[i][j - 1] = '!'; }
							if (mines[i][j + 1] == '0') { flg = 1; mines[i][j + 1] = '!'; }
							if (mines[i + 1][j - 1] == '0') { flg = 1; mines[i + 1][j - 1] = '!'; }
							if (mines[i + 1][j] == '0') { flg = 1; mines[i + 1][j] = '!'; }
							if (mines[i + 1][j + 1] == '0') { flg = 1; mines[i + 1][j + 1] = '!'; }
							mines[i][j] = '~';
							filled[i][j] =  prev = ' ';
						}
					}
				}
			} while (flg);   
	}
}

//test
void show_option() {
	int flg = 0, chk;
	printing_filled();
	
		switch (prev) 
		{
		case '#':
			flg = 1;
			printf("insert O to open,\n");
			printf("insert * to mark as mine,\n");
			printf("insert ? to flag,\n");
			break;
		case '*':
			flg = 2;
			printf("insert O to open,\n");
			printf("insert # to reset,\n");
			printf("insert ? to flag,\n");
			break;
		case '?':
			flg = 3;
			printf("insert O to open,\n");
			printf("insert * to mark as mine,\n");
			printf("insert # to reset,\n");
			break;
		default:
			flg = 4;
			printf("this cell is allready open!!!\n");
			printf("choose another,\n");
			chk = 0;
			return;
		}

		scanf("%c", &chr);
		temp = getchar();
		if ((flg == 1) && (chr != 'o') && (chr != 'O') && (chr != '*') && (chr != '?'))
		{
			printf("wrong input try again!\n"); chk = 0;
		}
		if ((flg == 2) && (chr != 'o') && (chr != 'O') && (chr != '#') && (chr != '?'))
		{
			printf("wrong input try again!\n"); chk = 0;
		}
		if ((flg == 3) && (chr != 'o') && (chr != 'O') && (chr != '#') && (chr != '*'))
		{
			printf("wrong input try again!\n"); chk = 0;
		}

}

//select cell with the arrows
void use_arrow() {
	char arrow=1;
	
	while (arrow != Enter) 
	{
		printf("choose cell, using the arrows - then press 'enter':\n");
		arrow = getch();
		if ((arrow == 0) || (arrow == -32)) 
		{
			arrow = getch();
			switch (arrow) {
				case up:
					if (p_i > 1)
						if(mark_prev(p_i - 1, p_j)) p_i--;
					break;
				case down:
					if (p_i < max_i)
						if(mark_prev(p_i + 1, p_j)) p_i++;
					break;
				case left:
					if (p_j > 1)
						if(mark_prev(p_i, p_j-1)) p_j--;
					break;
				case right:
					if (p_j < max_j)
						if(mark_prev(p_i, p_j + 1)) p_j++;
					break;
			}
		}
		if ((arrow == Enter) && (prev != '#') && (prev != '*') && (prev != '?')) { arrow = 1; }
		printing_filled();

	}

}

void main() {
	while ((pa == 'y')||(pa=='Y'))
	{
		p_i = p_j = 1;
		keep_play = 1;
		system("cls");
		srand(time(NULL));
		reset_game();
		diff();
		set_mines();
		set_num();
		while (vic > 0) 
		{
			system("cls");
			if ((mine == 0) && (vic > 0)) printf("some marked mines are not corrcet!!!\nfind them!!!\n\n");
			printing_filled();
			chk = 1;
			use_arrow();
			show_option();
			open_cell();
		}
		if (vic == 0) 
		{
			system("cls");
			printf("you won!!!!\n");
			printf("to play again press Y\nto exit press any other key: ");
			pa = getchar();
			temp = getchar();
		}
		else 
		{
			system("cls");
			printf("you lost!!!!\n");
			printf("to play again press Y\nto exit press any other key: ");
			pa = getchar();
			temp = getchar();
		}
	}
}