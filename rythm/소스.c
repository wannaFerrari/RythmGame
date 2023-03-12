#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <MMSystem.h>
#pragma comment (lib, "Winmm.lib")

// 색상 정의
#define BLACK	0
#define BLUE1	1 //진 파랑
#define GREEN1	2 //잔디 초록
#define CYAN1	3 // 탁한 청록
#define RED1	4 //탁한 빨강
#define MAGENTA1 5 //탁한 보라
#define YELLOW1	6 //누리끼리
#define GRAY1	7
#define GRAY2	8
#define BLUE2	9 //밝은파랑
#define GREEN2	10 
#define CYAN2	11
#define RED2	12
#define MAGENTA2 13
#define YELLOW2	14
#define WHITE	15

#define SPECIAL1 0xe0 // 특수키는 0xe0 + key 값으로 구성된다.
#define SPECIAL2 0x00 // keypad 경우 0x00 + key 로 구성된다.

#define UP  0x48 // Up key는 0xe0 + 0x48 두개의 값이 들어온다.
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d

//#define MAX 500;

struct {
	int x;
	int y;
	int note_line;
}sNote[2000];
struct {
	int x;
	int y;
	int note_line;
}testNote[2000];


void removeCursor(void) { // 커서를 안보이게 한다

	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void showCursor(void) { // 커서를 안보이게 한다

	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 100;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void cls(int bg_color, int text_color) // 화면 지우기
{
	char cmd[100];
	system("cls");
	sprintf(cmd, "COLOR %x%x", bg_color, text_color);
	system(cmd);
}

void gotoxy(int x, int y) //내가 원하는 위치로 커서 이동
{
	COORD pos; // Windows.h 에 정의
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void textcolor(int fg_color, int bg_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}



void main() {
	int x = 20, y = 2;
	int start = 0, last = 20;
	int j = 0;
	int sync = 17;
	int i = sync;
	double speed = 58;
	int line = 0;
	int l;
	int fa, fb, fc, fd, fe, ff, fg;//////이퀄라이저 Y축값 변수
	int fla, flb, flc, fld, fle, flf, flg;/////////////////for   변/////////////////////
	int faa, fbb, fcc, fdd, fee, fff, fgg;/////////////////문    수/////////////////////
	int equalizer = 40;   //이퀄라이저 사이클간 진행시간
	int music_color = 0;  //MUSIC단어 색변경 변수

	int conX = 40; //계속하려면 아무키 X값
	int erase; //계속하려면 아무키 문구 지우기위한 x값
	int display[200];
	int notePos = 0;//노트표시 순환 횟수, display접근에 필요
	int getBlank[500];//노트 처리시 사라지게만들기
	int getBlanki;
	int gb = 0;//getBlank 변수
	int bBuffer1 = 0;
	int bBuffer2 = 0;
	int bBuffer3 = 0;
	int bBuffer4 = 0;
	double loop_time = 95.8;
	int combo = 0;
	int bestCombo = 0;
	double speedin;
	int color_a = 0;
	int color_b = 0;
	int color_c = 0;
	int cross_colorA = 15;
	int cross_colorB = 15;
	int cross_colorC = 15;
	int color_Cycle = 0;
	int music_case = 1;
	int pre_case = 2;
	int selectPointer1;
	int selectPointer2;
	int excellent_count = 0;
	int great_count = 0;
	int miss_count = 0;
	int combo_color = 15;
	double user_speed;
	double duration = CLOCKS_PER_SEC;
	double time_avg = 0;
	int total_note;
	double exc_per;
	double gre_per;
	double mis_per;
	clock_t start_clock, now;
	unsigned char ch;

firstpage:
	PlaySound(TEXT("main.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	x = 20, y = 2;
	start = 0, last = 20;
	j = 0;
	//sync = 17;
	//i = sync;
	//speed = 82.5;
	line = 0;


	equalizer = 40;   //이퀄라이저 사이클간 진행시간
	music_color = 0;  //MUSIC단어 색변경 변수

	conX = 40; //계속하려면 아무키 X값
	erase; //계속하려면 아무키 문구 지우기위한 x값
	display[200];
	notePos = 0;//노트표시 순환 횟수, display접근에 필요
	getBlank[500];//노트 처리시 사라지게만들기
	getBlanki;
	gb = 0;//getBlank 변수
	bBuffer1 = 0;
	bBuffer2 = 0;
	bBuffer3 = 0;
	bBuffer4 = 0;

	combo = 0;
	bestCombo = 0;
	color_a = 0;
	color_b = 0;
	color_c = 0;
	cross_colorA = 15;
	cross_colorB = 15;
	cross_colorC = 15;
	color_Cycle = 0;

	excellent_count = 0;
	great_count = 0;
	miss_count = 0;
	combo_color = 15;
	ch = 0;


	cls(BLACK, WHITE);
	system("mode con cols=100 lines=25");



	for (getBlanki = 0; getBlanki < 500; getBlanki++) {
		getBlank[getBlanki] = 0;
	}


	gotoxy(40, 23);
	printf("계속하려면 아무키나 누르세요!");

	//이제부터 Q
	gotoxy(42, 2);

	textcolor(WHITE, WHITE);
	printf("    ");
	textcolor(RED2, WHITE);
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");
	printf("    ");

	gotoxy(42, 3);

	textcolor(RED2, WHITE);
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");

	gotoxy(42, 4);

	textcolor(YELLOW2, WHITE);
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");

	gotoxy(42, 5);

	textcolor(YELLOW2, WHITE);
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");

	gotoxy(42, 6);

	textcolor(GREEN2, WHITE);
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");
	printf("    ");
	textcolor(GREEN2, WHITE);
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");

	gotoxy(42, 7);

	textcolor(GREEN2, WHITE);
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");
	printf("    ");
	textcolor(GREEN2, WHITE);
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");

	gotoxy(42, 8);

	textcolor(GREEN1, WHITE);
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");
	printf("    ");
	textcolor(GREEN1, WHITE);
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");

	gotoxy(42, 9);

	textcolor(GREEN1, WHITE);
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");
	printf("    ");
	textcolor(GREEN1, WHITE);
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");

	gotoxy(42, 10);

	textcolor(BLUE2, WHITE);
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");
	printf("    ");
	textcolor(BLUE2, WHITE);
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");

	gotoxy(42, 11);

	textcolor(BLUE2, WHITE);
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	textcolor(BLUE2, WHITE);
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	textcolor(BLUE2, WHITE);
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");

	gotoxy(42, 12);

	textcolor(BLUE1, WHITE);
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	textcolor(BLUE1, WHITE);
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");

	gotoxy(42, 13);

	textcolor(BLUE1, WHITE);
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");
	textcolor(BLUE1, WHITE);
	printf("■■");
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");

	gotoxy(42, 14);

	textcolor(MAGENTA1, WHITE);
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");
	textcolor(MAGENTA1, WHITE);
	printf("■■");
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");

	gotoxy(42, 15);

	textcolor(MAGENTA1, WHITE);
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");

	gotoxy(42, 16);

	textcolor(GRAY1, WHITE);
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");

	gotoxy(42, 17);

	textcolor(WHITE, WHITE);
	printf("    ");
	textcolor(GRAY1, WHITE);
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	printf("■■");
	textcolor(GRAY2, WHITE);
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");

	gotoxy(42, 18);

	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");
	printf("    ");
	printf("    ");
	printf("    ");
	printf("    ");
	textcolor(GRAY2, WHITE);
	printf("■■");
	printf("■■");
	textcolor(WHITE, WHITE);
	printf("    ");

	gotoxy(42, 19);

	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");
	printf("    ");
	printf("    ");
	printf("    ");
	printf("    ");
	textcolor(GRAY2, WHITE);
	printf("■■");
	printf("■■");
	printf("■■");

	gotoxy(42, 20);
	textcolor(WHITE, WHITE);
	printf("    ");
	printf("    ");
	printf("    ");
	printf("    ");
	printf("    ");
	printf("    ");
	printf("    ");
	textcolor(GRAY2, WHITE);
	printf("■■");
	printf("■■");












	printf("\n");
	textcolor(WHITE, BLACK);
	gotoxy(30, 24);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////움직이는 개체////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	while (1) {
		if (kbhit() == 1) {
			ch = getch();
			for (int x = 0; x < 25; x++) {
				for (int z = 0; z < 100; z++) {
					gotoxy(z, x);
					textcolor(WHITE, WHITE);
					printf(" ");
					
				}
				Sleep(1);
			}
			for (int x = 0; x < 25; x++) {
				for (int z = 0; z < 100; z++) {
					gotoxy(z, x);
					textcolor(BLACK, BLACK);
					printf(" ");
					
				}
				Sleep(1);
			}
			break;
		}
		gotoxy(conX, 23);
		printf("계속하려면 아무키나 누르세요!");
		if (conX < 1)
			conX = 70;
		conX--;
		gotoxy(22, 20);
		textcolor(music_color, music_color);
		printf("   ");
		printf("   ");
		printf("   ");
		printf("   ");
		printf("   ");
		gotoxy(22, 19);
		printf("   ");
		gotoxy(22, 18);

		printf("   ");
		textcolor(music_color, music_color);
		printf("   ");
		printf("   ");
		printf("   ");
		printf("   ");
		gotoxy(22, 17);
		printf("   ");
		gotoxy(22, 16);
		printf("   ");
		printf("   ");
		printf("   ");
		printf("   ");
		printf("   ");
		//까지 M
		///////////////////////////////////////////////
		gotoxy(22, 14);
		printf("   ");
		printf("   ");
		printf("   ");
		printf("   ");
		printf("   ");
		gotoxy(22, 13);
		textcolor(BLACK, BLACK);
		printf("   ");
		printf("   ");
		printf("   ");
		printf("   ");
		textcolor(music_color, music_color);
		printf("   ");
		gotoxy(22, 12);
		printf("   ");
		printf("   ");
		printf("   ");
		printf("   ");
		printf("   ");
		//까지 U
		//////////////////////////////////////////////////////
		gotoxy(22, 10);
		printf("   ");
		printf("   ");
		printf("   ");
		textcolor(BLACK, BLACK);
		printf("   ");
		textcolor(music_color, music_color);
		printf("   ");
		gotoxy(22, 9);
		printf("   ");
		textcolor(BLACK, BLACK);
		printf("   ");
		textcolor(music_color, music_color);
		printf("   ");
		textcolor(BLACK, BLACK);
		printf("   ");
		textcolor(music_color, music_color);
		printf("   ");
		gotoxy(22, 8);
		printf("   ");
		textcolor(BLACK, BLACK);
		printf("   ");
		textcolor(music_color, music_color);
		printf("   ");
		printf("   ");
		printf("   ");
		//까지 S
		//////////////////////////////////////////////////////
		gotoxy(22, 6);
		printf("   ");
		printf("   ");
		printf("   ");
		printf("   ");
		printf("   ");
		//까지 I
		////////////////////////////////////////////////////
		gotoxy(22, 4);
		printf("   ");
		printf("   ");
		printf("   ");
		printf("   ");
		printf("   ");
		gotoxy(22, 3);
		printf("   ");
		textcolor(BLACK, BLACK);
		printf("   ");
		printf("   ");
		printf("   ");
		textcolor(music_color, music_color);
		printf("   ");
		gotoxy(22, 2);
		printf("   ");
		textcolor(BLACK, BLACK);
		printf("   ");
		printf("   ");
		printf("   ");
		textcolor(music_color, music_color);
		printf("   ");
		//까지 C
		///////////////////////////////////
		//
		///////////////////////////여기까지가 MUSIC
		///////////////////////////////////////////////////
		if (music_color > 15)
			music_color = 0;
		else 
			music_color++;

		/////////////////////////////////
		///////////////////////////////////
		//////////////////////////////
		////////이 아래가 이퀄라이저 표현부//////////////
		////////////////////////////////////
		///////////////////////////////////
		//////////////////////////////





		/////////////////////////////////
		////////////////사이클 1
		//////////////////////////////////
		textcolor(WHITE, BLACK);
		fla = fa =10;
		flb = fb = 8;
		flc = fc = 6;
		fld = fd = 8;
		fle = fe = 11;
		flf = ff = 14;
		flg = fg = 11;

		for (faa = 0; faa < 20 - fla; faa++) {
			gotoxy(2, fa);
			printf("■");
			gotoxy(96, fa);
			printf("■");
			fa++;
		}

		for (fbb = 0; fbb < 20 - flb; fbb++) {
			gotoxy(4, fb);
			printf("■");
			gotoxy(94, fb);
			printf("■");
			fb++;
		}

		for (fcc = 0; fcc < 20 - flc; fcc++) {
			gotoxy(6, fc);
			printf("■");
			gotoxy(92, fc);
			printf("■");
			fc++;
		}

		for (fcc = 0; fcc < 20 - fld; fcc++) {
			gotoxy(8, fd);
			printf("■");
			gotoxy(90, fd);
			printf("■");
			fd++;
		}

		for (fcc = 0; fcc < 20 - fle; fcc++) {
			gotoxy(10, fe);
			printf("■");
			gotoxy(88, fe);
			printf("■");
			fe++;
		}
		for (fcc = 0; fcc < 20 - flf; fcc++) {
			gotoxy(12, ff);
			printf("■");
			gotoxy(86, ff);
			printf("■");
			ff++;
		}
		for (fcc = 0; fcc < 20 - flg; fcc++) {
			gotoxy(14, fg);
			printf("■");
			gotoxy(84, fg);
			printf("■");
			fg++;
		}
		Sleep(equalizer);
		
		///////////////////////////////////
		////////////////////////////사이클 2에 없는 사이클1 부분 삭제
		/////////////////////////////////////////////////////
		gotoxy(6, 6);
		printf("  ");
		gotoxy(92, 6);
		printf("  ");
		gotoxy(6, 7);
		printf("  ");
		gotoxy(92, 7);
		printf("  ");
		gotoxy(8, 8);
		printf("  ");
		gotoxy(90, 8);
		printf("  ");
		gotoxy(8, 9);
		printf("  ");
		gotoxy(90, 9);
		printf("  ");
		gotoxy(8, 10);
		printf("  ");
		gotoxy(90, 10);
		printf("  ");
		gotoxy(10, 11);
		printf("  ");
		gotoxy(88, 11);
		printf("  ");
		gotoxy(10, 12);
		printf("  ");
		gotoxy(88, 12);
		printf("  ");
		gotoxy(10, 13);
		printf("  ");
		gotoxy(88, 13);
		printf("  ");
		



		/////////////////////////////////
		////////////////사이클2
		//////////////////////////////////
		fla = fa = 8;
		flb = fb = 6;
		flc = fc = 8;
		fld = fd = 11;
		fle = fe = 14;
		flf = ff = 11;
		flg = fg = 10;

		for (faa = 0; faa < 20 - fla; faa++) {
			gotoxy(2, fa);
			printf("■");
			gotoxy(96, fa);
			printf("■");
			fa++;
		}

		for (fbb = 0; fbb < 20 - flb; fbb++) {
			gotoxy(4, fb);
			printf("■");
			gotoxy(94, fb);
			printf("■");
			fb++;
		}

		for (fcc = 0; fcc < 20 - flc; fcc++) {
			gotoxy(6, fc);
			printf("■");
			gotoxy(92, fc);
			printf("■");
			fc++;
		}

		for (fcc = 0; fcc < 20 - fld; fcc++) {
			gotoxy(8, fd);
			printf("■");
			gotoxy(90, fd);
			printf("■");
			fd++;
		}

		for (fcc = 0; fcc < 20 - fle; fcc++) {
			gotoxy(10, fe);
			printf("■");
			gotoxy(88, fe);
			printf("■");
			fe++;
		}
		for (fcc = 0; fcc < 20 - flf; fcc++) {
			gotoxy(12, ff);
			printf("■");
			gotoxy(86, ff);
			printf("■");
			ff++;
		}
		for (fcc = 0; fcc < 20 - flg; fcc++) {
			gotoxy(14, fg);
			printf("■");
			gotoxy(84, fg);
			printf("■");
			fg++;
		}
		Sleep(equalizer);
		
		
		///////////////////////////////////////
		////////////사이클 3에 없는 사이클2 부분 삭제
		/////////////////////////////////////////////////
		gotoxy(4, 6);
		printf("  ");
		gotoxy(94, 6);
		printf("  ");
		gotoxy(4, 7);
		printf("  ");
		gotoxy(94, 7);
		printf("  ");
		gotoxy(6, 8);
		printf("  ");
		gotoxy(92, 8);
		printf("  ");
		gotoxy(6, 9);
		printf("  ");
		gotoxy(92, 9);
		printf("  ");
		gotoxy(6, 10);
		printf("  ");
		gotoxy(92, 10);
		printf("  ");
		gotoxy(8, 11);
		printf("  ");
		gotoxy(90, 11);
		printf("  ");
		gotoxy(8, 12);
		printf("  ");
		gotoxy(90, 12);
		printf("  ");
		gotoxy(8, 13);
		printf("  ");
		gotoxy(90, 13);
		printf("  ");
		
	
		/////////////////////////////////////
		////////////////////////사이클 3
		//////////////////////////////////////
		fla = fa = 6;
		flb = fb = 8;
		flc = fc = 11;
		fld = fd = 14;
		fle = fe = 11;
		flf = ff = 10;
		flg = fg = 8;

		for (faa = 0; faa < 20 - fla; faa++) {
			gotoxy(2, fa);
			printf("■");
			gotoxy(96, fa);
			printf("■");
			fa++;
		}

		for (fbb = 0; fbb < 20 - flb; fbb++) {
			gotoxy(4, fb);
			printf("■");
			gotoxy(94, fb);
			printf("■");
			fb++;
		}

		for (fcc = 0; fcc < 20 - flc; fcc++) {
			gotoxy(6, fc);
			printf("■");
			gotoxy(92, fc);
			printf("■");
			fc++;
		}

		for (fcc = 0; fcc < 20 - fld; fcc++) {
			gotoxy(8, fd);
			printf("■");
			gotoxy(90, fd);
			printf("■");
			fd++;
		}

		for (fcc = 0; fcc < 20 - fle; fcc++) {
			gotoxy(10, fe);
			printf("■");
			gotoxy(88, fe);
			printf("■");
			fe++;
		}
		for (fcc = 0; fcc < 20 - flf; fcc++) {
			gotoxy(12, ff);
			printf("■");
			gotoxy(86, ff);
			printf("■");
			ff++;
		}
		for (fcc = 0; fcc < 20 - flg; fcc++) {
			gotoxy(14, fg);
			printf("■");
			gotoxy(84, fg);
			printf("■");
			fg++;
		}


		/////////////////////////////////////////////////
		/////////////////////////////사이클4에 없는 사이클3 삭제
		//////////////////////////////////////////////////
		Sleep(equalizer);
		gotoxy(2, 6);
		printf("  ");
		gotoxy(96, 6);
		printf("  ");
		gotoxy(2, 7);
		printf("  ");
		gotoxy(96, 7);
		printf("  ");
		gotoxy(4, 8);
		printf("  ");
		gotoxy(94, 8);
		printf("  ");
		gotoxy(4, 9);
		printf("  ");
		gotoxy(94, 9);
		printf("  ");
		gotoxy(4, 10);
		printf("  ");
		gotoxy(94, 10);
		printf("  ");
		gotoxy(6, 11);
		printf("  ");
		gotoxy(92, 11);
		printf("  ");
		gotoxy(6, 12);
		printf("  ");
		gotoxy(92, 12);
		printf("  ");
		gotoxy(6, 13);
		printf("  ");
		gotoxy(92, 13);
		printf("  ");
		

		/////////////////////////////////////
		///////////////////////////사이클 4
		/////////////////////////////////////////////
		fla = fa = 8;
		flb = fb = 11;
		flc = fc = 14;
		fld = fd = 11;
		fle = fe = 10;
		flf = ff = 8;
		flg = fg = 6;

		for (faa = 0; faa < 20 - fla; faa++) {
			gotoxy(2, fa);
			printf("■");
			gotoxy(96, fa);
			printf("■");
			fa++;
		}

		for (fbb = 0; fbb < 20 - flb; fbb++) {
			gotoxy(4, fb);
			printf("■");
			gotoxy(94, fb);
			printf("■");
			fb++;
		}

		for (fcc = 0; fcc < 20 - flc; fcc++) {
			gotoxy(6, fc);
			printf("■");
			gotoxy(92, fc);
			printf("■");
			fc++;
		}

		for (fcc = 0; fcc < 20 - fld; fcc++) {
			gotoxy(8, fd);
			printf("■");
			gotoxy(90, fd);
			printf("■");
			fd++;
		}

		for (fcc = 0; fcc < 20 - fle; fcc++) {
			gotoxy(10, fe);
			printf("■");
			gotoxy(88, fe);
			printf("■");
			fe++;
		}
		for (fcc = 0; fcc < 20 - flf; fcc++) {
			gotoxy(12, ff);
			printf("■");
			gotoxy(86, ff);
			printf("■");
			ff++;
		}
		for (fcc = 0; fcc < 20 - flg; fcc++) {
			gotoxy(14, fg);
			printf("■");
			gotoxy(84, fg);
			printf("■");
			fg++;
		}
		Sleep(equalizer);

		///////////////////////////////////
		//////////////////////사이클5에없는 사이클4 삭제
		///////////////////////////////////////////
		gotoxy(2, 8);
		printf("  ");
		gotoxy(96, 8);
		printf("  ");
		gotoxy(2, 9);
		printf("  ");
		gotoxy(96, 9);
		printf("  ");
		gotoxy(2, 10);
		printf("  ");
		gotoxy(96, 10);
		printf("  ");
		gotoxy(4, 11);
		printf("  ");
		gotoxy(94, 11);
		printf("  ");
		gotoxy(4, 12);
		printf("  ");
		gotoxy(94, 12);
		printf("  ");
		gotoxy(4, 13);
		printf("  ");
		gotoxy(94, 13);
		printf("  ");
		gotoxy(14, 6);
		printf("  ");
		gotoxy(84, 6);
		printf("  ");
		gotoxy(14, 7);
		printf("  ");
		gotoxy(84, 7);
		printf("  ");
		

		///////////////////////////////////
		/////////////////사이클 5
		////////////////////////////////
		fla = fa = 11;
		flb = fb = 14;
		flc = fc = 11;
		fld = fd = 10;
		fle = fe = 8;
		flf = ff = 6;
		flg = fg = 8;
		
		for (faa = 0; faa < 20 - fla; faa++) {
			gotoxy(2, fa);
			printf("■");
			gotoxy(96, fa);
			printf("■");
			fa++;
		}

		for (fbb = 0; fbb < 20 - flb; fbb++) {
			gotoxy(4, fb);
			printf("■");
			gotoxy(94, fb);
			printf("■");
			fb++;
		}

		for (fcc = 0; fcc < 20 - flc; fcc++) {
			gotoxy(6, fc);
			printf("■");
			gotoxy(92, fc);
			printf("■");
			fc++;
		}

		for (fcc = 0; fcc < 20 - fld; fcc++) {
			gotoxy(8, fd);
			printf("■");
			gotoxy(90, fd);
			printf("■");
			fd++;
		}

		for (fcc = 0; fcc < 20 - fle; fcc++) {
			gotoxy(10, fe);
			printf("■");
			gotoxy(88, fe);
			printf("■");
			fe++;
		}
		for (fcc = 0; fcc < 20 - flf; fcc++) {
			gotoxy(12, ff);
			printf("■");
			gotoxy(86, ff);
			printf("■");
			ff++;
		}
		for (fcc = 0; fcc < 20 - flg; fcc++) {
			gotoxy(14, fg);
			printf("■");
			gotoxy(84, fg);
			printf("■");
			fg++;
		}
		Sleep(equalizer);

		///////////////////////////////
		////////////////////사이클6에 없는 사이클 5 삭제
		///////////////////////////////////////////////
		gotoxy(2, 11);
		printf("  ");
		gotoxy(96, 11);
		printf("  ");
		gotoxy(2, 12);
		printf("  ");
		gotoxy(96, 12);
		printf("  ");
		gotoxy(2, 13);
		printf("  ");
		gotoxy(96, 13);
		printf("  ");
		gotoxy(12, 6);
		printf("  ");
		gotoxy(86, 6);
		printf("  ");
		gotoxy(12, 7);
		printf("  ");
		gotoxy(86, 7);
		printf("  ");
		gotoxy(14, 8);
		printf("  ");
		gotoxy(84, 8);
		printf("  ");
		gotoxy(14, 9);
		printf("  ");
		gotoxy(84, 9);
		printf("  ");
		gotoxy(14, 10);
		printf("  ");
		gotoxy(84, 10);
		printf("  ");
		

		/////////////////////////////////////
		/////////////////////////사이클 6
		/////////////////////////////////////////
		fla = fa = 14;
		flb = fb = 11;
		flc = fc = 10;
		fld = fd = 8;
		fle = fe = 6;
		flf = ff = 8;
		flg = fg = 11;

		for (faa = 0; faa < 20 - fla; faa++) {
			gotoxy(2, fa);
			printf("■");
			gotoxy(96, fa);
			printf("■");
			fa++;
		}

		for (fbb = 0; fbb < 20 - flb; fbb++) {
			gotoxy(4, fb);
			printf("■");
			gotoxy(94, fb);
			printf("■");
			fb++;
		}

		for (fcc = 0; fcc < 20 - flc; fcc++) {
			gotoxy(6, fc);
			printf("■");
			gotoxy(92, fc);
			printf("■");
			fc++;
		}

		for (fcc = 0; fcc < 20 - fld; fcc++) {
			gotoxy(8, fd);
			printf("■");
			gotoxy(90, fd);
			printf("■");
			fd++;
		}

		for (fcc = 0; fcc < 20 - fle; fcc++) {
			gotoxy(10, fe);
			printf("■");
			gotoxy(88, fe);
			printf("■");
			fe++;
		}
		for (fcc = 0; fcc < 20 - flf; fcc++) {
			gotoxy(12, ff);
			printf("■");
			gotoxy(86, ff);
			printf("■");
			ff++;
		}
		for (fcc = 0; fcc < 20 - flg; fcc++) {
			gotoxy(14, fg);
			printf("■");
			gotoxy(84, fg);
			printf("■");
			fg++;
		}
		Sleep(equalizer);

		/////////////////////////////////
		/////////////////////////사이클 7에 없는 사이클 6 삭제
		//////////////////////////////////////////
		gotoxy(10, 6);
		printf("  ");
		gotoxy(88, 6);
		printf("  ");
		gotoxy(10, 7);
		printf("  ");
		gotoxy(88, 7);
		printf("  ");
		gotoxy(12,8);
		printf("  ");
		gotoxy(86, 8);
		printf("  ");
		gotoxy(12, 9);
		printf("  ");
		gotoxy(86, 9);
		printf("  ");
		gotoxy(12, 10);
		printf("  ");
		gotoxy(86, 10);
		printf("  ");
		gotoxy(14, 11);
		printf("  ");
		gotoxy(84, 11);
		printf("  ");
		gotoxy(14, 12);
		printf("  ");
		gotoxy(84, 12);
		printf("  ");
		gotoxy(14, 13);
		printf("  ");
		gotoxy(84, 13);
		printf("  ");
		

		///////////////////////////
		//////////////////사이클 7
		///////////////////////////////////
		fla = fa = 11;
		flb = fb = 10;
		flc = fc = 8;
		fld = fd = 6;
		fle = fe = 8;
		flf = ff = 11;
		flg = fg = 14;

		for (faa = 0; faa < 20 - fla; faa++) {
			gotoxy(2, fa);
			printf("■");
			gotoxy(96, fa);
			printf("■");
			fa++;
		}

		for (fbb = 0; fbb < 20 - flb; fbb++) {
			gotoxy(4, fb);
			printf("■");
			gotoxy(94, fb);
			printf("■");
			fb++;
		}

		for (fcc = 0; fcc < 20 - flc; fcc++) {
			gotoxy(6, fc);
			printf("■");
			gotoxy(92, fc);
			printf("■");
			fc++;
		}

		for (fcc = 0; fcc < 20 - fld; fcc++) {
			gotoxy(8, fd);
			printf("■");
			gotoxy(90, fd);
			printf("■");
			fd++;
		}

		for (fcc = 0; fcc < 20 - fle; fcc++) {
			gotoxy(10, fe);
			printf("■");
			gotoxy(88, fe);
			printf("■");
			fe++;
		}
		for (fcc = 0; fcc < 20 - flf; fcc++) {
			gotoxy(12, ff);
			printf("■");
			gotoxy(86, ff);
			printf("■");
			ff++;
		}
		for (fcc = 0; fcc < 20 - flg; fcc++) {
			gotoxy(14, fg);
			printf("■");
			gotoxy(84, fg);
			printf("■");
			fg++;
		}
		Sleep(equalizer);


		/////////////////////////////
		///////////////사이클 1에 없는 사이클 7 삭제
		////////////////////////////
		gotoxy(8, 6);
		printf("  ");
		gotoxy(90, 6);
		printf("  ");
		gotoxy(8, 7);
		printf("  ");
		gotoxy(90, 7);
		printf("  ");
		gotoxy(10, 8);
		printf("  ");
		gotoxy(88, 8);
		printf("  ");
		gotoxy(10, 9);
		printf("  ");
		gotoxy(88, 9);
		printf("  ");
		gotoxy(10, 10);
		printf("  ");
		gotoxy(88, 10);
		printf("  ");
		gotoxy(12, 11);
		printf("  ");
		gotoxy(86, 11);
		printf("  ");
		gotoxy(12, 12);
		printf("  ");
		gotoxy(86, 12);
		printf("  ");
		gotoxy(12, 13);
		printf("  ");
		gotoxy(86, 13);
		printf("  ");
		

		////////////////////////////////////
		////////////////////  "계속하려면 아무키나 누르세요!" 문구 자리 반복적으로 삭제
		//////////////////////////////////////////
		for (erase = 0; erase < 100; erase++) {
			gotoxy(erase, 23);
			printf(" ");
		}
		
		
		
	}
//ROD_prev:
	//PlaySound(TEXT("rageofdemon_prev.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
cls(BLACK, WHITE);
	gotoxy(30, 22);
	while (1) {//////////////////////////////////////////////////////////곡 선택 화면
	
		
		removeCursor();

	select:

		line = 0;
		start = 0; last = 20;
		i = sync;

		notePos = 0;//노트표시 순환 횟수, display접근에 필요
		getBlank[500];//노트 처리시 사라지게만들기
		getBlanki;
		gb = 0;//getBlank 변수
		bBuffer1 = 0;
		bBuffer2 = 0;
		bBuffer3 = 0;
		bBuffer4 = 0;
		
		combo = 0;
		bestCombo = 0;
		

		excellent_count = 0;
		great_count = 0;
		miss_count = 0;
		combo_color = 15;
		ch = 0;

		gotoxy(11, 0);
		printf("┌────────────────┐");
		gotoxy(11, 1);
		printf("│");
		gotoxy(45, 1);
		printf("│");
		gotoxy(11, 2);
		printf("└────────────────┘");
		gotoxy(13, 1);
		printf("(S) : 시작싱크설정 (현재 : %3.1lf)", speed);
		
		gotoxy(47, 0);
		printf("┌─────────┐");
		gotoxy(47, 1);
		printf("│");
		gotoxy(67, 1);
		printf("│");
		gotoxy(47, 2);
		printf("└─────────┘");
		gotoxy(49, 1);
		printf("(SPACE) : 게임시작");

		gotoxy(11, 22);
		printf("┌─────────┐");
		gotoxy(11, 23);
		printf("│");
		gotoxy(31, 23);
		printf("│");
		gotoxy(11, 24);
		printf("└─────────┘");
		gotoxy(13, 23);
		printf(" < Q > : 게임종료");
		
		
		gotoxy(33, 22);
		printf("┌─────────┐");
		gotoxy(33, 23);
		printf("│");
		gotoxy(53, 23);
		printf("│");
		gotoxy(33, 24);
		printf("└─────────┘");
		gotoxy(35, 23);
		printf(" < B > : 이전화면");


		
		gotoxy(69, 0);
		printf("┌──────────┐");
		gotoxy(69, 1);
		printf("│");
		gotoxy(91, 1);
		printf("│");
		gotoxy(69, 2);
		printf("└──────────┘");
		gotoxy(71, 1);
		printf("(↑ & ↓) : 곡 선택");



		gotoxy(11, 3);
		printf("┌────────────────┐");
		gotoxy(11, 4);
		printf("│");
		gotoxy(45, 4);
		printf("│");
		gotoxy(11, 5);
		printf("└────────────────┘");
		gotoxy(13, 4);
		printf("    ← , →로 지연 조절  (%3.1lf)",loop_time);






		////////////////
		////////////////
		//////////높은음자리
		gotoxy(1, 7);
		textcolor(WHITE, WHITE);
		printf("                                        ");//1줄
		gotoxy(1, 10);
		printf("                                        ");//2줄
		gotoxy(1, 13);
		printf("                                        ");//3줄
		gotoxy(1, 16);
		printf("                                        ");//4줄
		gotoxy(1, 19);
		printf("                                        ");//5줄
		gotoxy(3, 24);
		printf(" "); printf(" ");
		gotoxy(2, 23);
		printf(" "); printf(" ");
		gotoxy(5, 23);
		printf(" "); printf(" ");
		gotoxy(2, 22);
		printf(" "); printf(" "); printf(" "); printf(" "); printf(" ");
		gotoxy(3, 21);
		printf(" "); printf(" ");
		gotoxy(6, 21);
		printf(" ");
		gotoxy(6, 20);
		printf(" ");
		gotoxy(3, 18);
		printf(" "); printf(" "); printf(" "); printf(" ");
		gotoxy(2, 17);
		printf(" ");
		gotoxy(6, 17);
		printf(" "); printf(" ");
		gotoxy(2, 15);
		printf(" ");
		gotoxy(4, 15);
		printf(" ");
		gotoxy(6, 15);
		printf(" ");
		gotoxy(8, 15);
		printf(" ");
		gotoxy(2, 14);
		printf(" ");
		gotoxy(4, 14);
		printf(" "); printf(" "); printf(" ");
		gotoxy(8, 14);
		printf(" ");
		gotoxy(3, 12);
		printf(" ");
		gotoxy(5, 12);
		printf(" "); printf(" "); printf(" ");
		gotoxy(4, 11);
		printf(" "); printf(" ");
		gotoxy(5, 9);
		printf(" "); printf(" ");
		gotoxy(5, 8);
		printf(" ");
		gotoxy(7, 8);
		printf(" ");
		gotoxy(5, 6);
		printf(" ");
		gotoxy(7, 6);
		printf(" ");
		gotoxy(5, 5);
		printf(" ");
		gotoxy(7, 5);
		printf(" "); printf(" ");
		gotoxy(5, 4);
		printf(" ");
		gotoxy(8, 4);
		printf(" ");
		gotoxy(5, 3);
		printf(" ");
		gotoxy(7, 3);
		printf(" "); printf(" ");
		gotoxy(5, 2);
		printf(" "); printf(" "); printf(" ");
		gotoxy(6, 1);
		printf(" ");
		////////////////////////////////////
		///////////까지 높은음자리표
		////////////////////////////////////
		
		
		///음표 색 변경 사이클
		if (color_Cycle == 0) {//14 ,9, 2
			color_a = 14;
			color_b = 0;
			color_c = 0;
			cross_colorA = 14;
			cross_colorB = 15;
			cross_colorC = 15;
		}
		else if (color_Cycle == 1) {//14 ,9, 2
			color_a = 0;
			color_b = 9;
			color_c = 0;
			cross_colorA = 15;
			cross_colorB = 9;
			cross_colorC = 15;
		}
		else if (color_Cycle == 2) {//14 ,9, 2
			color_a = 0;
			color_b = 0;
			color_c = 10;
			cross_colorA = 15;
			cross_colorB = 15;
			cross_colorC = 10;
		}




		//////////////////////////////////
		///////////////////첫번째음표
		/////////////////////////////////
		gotoxy(12, 19);
		textcolor(cross_colorA, cross_colorA);
		printf(" "); printf(" "); printf(" ");
		gotoxy(12, 18);
		textcolor(color_a, color_a);
		printf(" "); printf(" "); printf(" ");
		gotoxy(12, 17);
		printf(" "); printf(" "); printf(" ");
		gotoxy(14, 16);
		textcolor(cross_colorA, cross_colorA);
		printf(" ");
		gotoxy(14, 15);
		textcolor(color_a, color_a);
		printf(" ");
		gotoxy(14, 14);
		printf(" ");
		gotoxy(14, 13);
		textcolor(cross_colorA, cross_colorA);
		printf(" ");
		gotoxy(14, 12);
		textcolor(color_a, color_a);
		printf(" ");
		gotoxy(17, 12);
		printf(" "); printf(" ");
		gotoxy(14, 11);
		printf(" "); printf(" "); printf(" "); printf(" ");
		gotoxy(14, 10);
		textcolor(cross_colorA, cross_colorA);
		printf(" "); printf(" "); printf(" ");
		gotoxy(14, 9);
		textcolor(color_a, color_a);
		printf(" ");
		/////////////////////////////////////
		//////////////////////////////첫번쨰음표 끝
		///////////////////////////////////////////

		///////////////////////////////////
		//////////////////////////두번째음표 시작
		////////////////////////////////////////
		gotoxy(19, 19);
		textcolor(color_b, color_b);
		printf(" "); printf(" "); printf(" ");
		gotoxy(19, 19);
		textcolor(cross_colorB, cross_colorB);
		printf(" "); printf(" "); printf(" ");
		gotoxy(19, 18);
		textcolor(color_b, color_b);
		printf(" "); printf(" "); printf(" ");
		gotoxy(25, 18);
		printf(" "); printf(" "); printf(" ");
		gotoxy(21, 17);
		printf(" ");
		gotoxy(25, 17);
		printf(" "); printf(" "); printf(" ");
		gotoxy(21, 16);
		textcolor(cross_colorB, cross_colorB);
		printf(" ");
		gotoxy(25, 16);
		printf(" "); printf(" "); printf(" ");
		gotoxy(21, 15);
		textcolor(color_b, color_b);
		printf(" ");
		gotoxy(27, 15);
		printf(" ");
		gotoxy(21, 14);
		printf(" ");
		gotoxy(27, 14);
		printf(" ");
		gotoxy(21, 13);
		textcolor(cross_colorB, cross_colorB);
		printf(" ");
		gotoxy(27, 13);
		printf(" ");
		gotoxy(21, 12);
		textcolor(color_b, color_b);
		printf(" ");
		gotoxy(27, 12);
		printf(" ");
		gotoxy(21, 11);
		printf(" "); printf(" "); printf(" ");
		gotoxy(27, 11);
		printf(" "); 
		gotoxy(21, 10);
		textcolor(cross_colorB, cross_colorB);
		printf(" "); printf(" "); printf(" "); printf(" "); printf(" ");
		gotoxy(27, 10);
		printf(" ");
		gotoxy(23, 9);
		textcolor(color_b, color_b);
		printf(" "); printf(" "); printf(" "); printf(" "); printf(" ");
		gotoxy(26, 8);
		printf(" "); printf(" ");
		/////////////////////////////
		/////////////////두번쨰음표 끝
		//////////////////////////////

		////////////////////////////////
		///////////////////세번쨰 음표
		//////////////////////////////
		gotoxy(32, 16);
		textcolor(cross_colorC, cross_colorC);
		printf(" "); printf(" "); printf(" ");
		gotoxy(32, 15);
		textcolor(color_c, color_c);
		printf(" "); printf(" "); printf(" ");
		gotoxy(32, 14);
		printf(" "); printf(" "); printf(" ");
		gotoxy(34, 13);
		textcolor(cross_colorC, cross_colorC);
		printf(" ");
		gotoxy(37, 13);
		printf(" "); printf(" ");
		gotoxy(34, 12);
		textcolor(color_c, color_c);
		printf(" "); printf(" "); printf(" "); printf(" ");
		gotoxy(34, 11);
		printf(" "); printf(" "); printf(" ");
		gotoxy(34, 10);
		textcolor(cross_colorC, cross_colorC);
		printf(" ");
		gotoxy(37, 10);
		printf(" "); printf(" ");
		gotoxy(34, 9);
		textcolor(color_c, color_c);
		printf(" "); printf(" "); printf(" "); printf(" ");
		gotoxy(34, 8);
		printf(" "); printf(" "); printf(" ");
		gotoxy(34, 7);
		textcolor(cross_colorC, cross_colorC);
		printf(" ");
		/////////////////////////////////////
		//////////////////세번째 음표 끝
		//////////////////////////////


		/////////////////////////////////////////
		////////////////////////선택 메뉴창
		/////////////////////////////////////
		if (music_case == 1) {
			if (pre_case == music_case)
				goto next;

			PlaySound(TEXT("black_swan_prev.wav"), NULL, SND_FILENAME | SND_ASYNC |SND_LOOP);
			selectPointer1 = 10;
			selectPointer2 = 10;
			textcolor(WHITE, BLACK);
			gotoxy(55, 12);
			printf(" ");
			gotoxy(87, 12);
			printf(" ");
			gotoxy(55, 18);
			printf("▷         작곡가 : Tak");
			gotoxy(87, 18);
			printf("◁");
			gotoxy(55, 19);
			printf("▷        음악 길이 : 1:53");
			gotoxy(87, 19);
			printf("◁");
			gotoxy(55, 20);
			printf("▷         난이도 : ");
			gotoxy(75, 20);
			textcolor(YELLOW2, BLACK);
			printf(" 보통");
			textcolor(WHITE, BLACK);
			gotoxy(87, 20);
			printf("◁");
		}
		else if (music_case == 2) {
			if (pre_case == music_case)
				goto next;
			PlaySound(TEXT("rageofdemon_prev.wav"), NULL, SND_FILENAME | SND_ASYNC |SND_LOOP );
			
			selectPointer1 = 12;
			selectPointer2 = 12;
			textcolor(WHITE, BLACK);
			gotoxy(55, 10);
			printf(" ");
			gotoxy(87, 10);
			printf(" ");
			gotoxy(55, 18);
			printf("▷         작곡가 : NIEN");
			gotoxy(87, 18);
			printf("◁");
			gotoxy(55, 19);
			printf("▷        음악 길이 : 1:47");
			gotoxy(87, 19);
			printf("◁");
			gotoxy(55, 20);
			printf("▷         난이도 : ");
			gotoxy(75, 20);
			textcolor(RED2, BLACK);
			printf("어려움");
			textcolor(WHITE, BLACK);
			gotoxy(87, 20);
			printf("◁");
		}
		next:
		textcolor(WHITE, BLACK);
		gotoxy(62, 5);
		printf("S E L E C T  M U S I C");
		gotoxy(55, selectPointer1);
		printf("▶");
		gotoxy(87, selectPointer1);
		printf("◀");
		gotoxy(52, 7);
		printf("┌──────────────────┐");
		gotoxy(52, 8);
		printf("│");
		gotoxy(90, 8);
		printf("│");
		gotoxy(52, 9);
		printf("│");
		gotoxy(90, 9);
		printf("│");
		gotoxy(52, 10);
		printf("│");
		gotoxy(67, 10);
		printf("Black Swan");
		gotoxy(65, 12);
		printf("Rage Of Demon");
		gotoxy(90, 10);
		printf("│");
		gotoxy(52, 11);
		printf("│");
		gotoxy(90, 11);
		printf("│");
		gotoxy(52, 12);
		printf("│");
		gotoxy(90, 12);
		printf("│");
		gotoxy(52, 13);
		printf("│");
		gotoxy(90, 13);
		printf("│");
		gotoxy(52, 14);
		printf("│");
		gotoxy(90, 14);
		printf("│");
		gotoxy(52, 15);
		printf("└──────────────────┘");
		gotoxy(52, 17);
		printf("┌──────────────────┐");
		gotoxy(52, 18);
		printf("│");
		gotoxy(90, 18);
		printf("│");
		gotoxy(52, 19);
		printf("│");
		gotoxy(90, 19);
		printf("│");
		gotoxy(52, 20);
		printf("│");
		gotoxy(90, 20);
		printf("│");
		gotoxy(52, 21);
		printf("└──────────────────┘");
		ch = 0;
		fflush(stdin);

		pre_case = music_case;
		if (kbhit() == 1) {
			ch = getch();
			if (ch == 0x20) {///   스페이스바 눌렀을때
				for (int x = 0; x < 25; x++) {
					for (int z = 0; z < 100; z++) {
						gotoxy(z, x);
						textcolor(WHITE, WHITE);
						printf(" ");

					}
					Sleep(1);
				}
				for (int x = 0; x < 25; x++) {
					for (int z = 0; z < 100; z++) {
						gotoxy(z, x);
						textcolor(BLACK, BLACK);
						printf(" ");

					}
					Sleep(1);
				}
				PlaySound(NULL, 0, 0);

				
				
				break;
			}
			else if (ch == 0x71) { //Q 눌렀을때
				for (int x = 0; x < 25; x++) {
					for (int z = 0; z < 100; z++) {
						gotoxy(z, x);
						textcolor(BLACK, BLACK);
						printf(" ");

					}
					Sleep(1);
				}
				goto exit;
			}
			else if (ch == 0x62) {// B눌렀을때
				for (int x = 0; x < 25; x++) {
					for (int z = 0; z < 100; z++) {
						gotoxy(z, x);
						textcolor(WHITE, WHITE);
						printf(" ");

					}
					Sleep(1);
				}
				for (int x = 0; x < 25; x++) {
					for (int z = 0; z < 100; z++) {
						gotoxy(z, x);
						textcolor(BLACK, BLACK);
						printf(" ");

					}
					Sleep(1);
				}
				if (pre_case == 1)
					pre_case = 2;
				else if (pre_case == 2)
					pre_case = 1;
				goto firstpage;
			}
			else if (ch == 0x73) {/// s 눌렀을때 -> 싱크 조절창
				//PlaySound(NULL, 0, 0);




				PlaySound(NULL, 0, 0);
				for (int x = 0; x < 25; x++) {
					for (int z = 0; z < 100; z++) {
						gotoxy(z, x);
						textcolor(WHITE, WHITE);
						printf(" ");

					}
					Sleep(1);
				}
				for (int x = 0; x < 25; x++) {
					for (int z = 0; z < 100; z++) {
						gotoxy(z, x);
						textcolor(BLACK, BLACK);
						printf(" ");

					}
					Sleep(1);
				}
				x = 20;
				FILE *testfile;
				testfile = fopen("testnote.txt", "r");
				
				for (j = 0; j < sync; j++) {
					testNote[j].note_line = 0;

				}
				while (!feof(testfile)) {
					fscanf(testfile, "%d", &testNote[i].note_line);

					i++;
					line++;
				}
				start = 0; last = 20;

				for (l = 0; l < line + 20; l++) {
					start_clock = clock();
					//now = clock();
					//duration = now - start_clock;
					for (j = last; j > start; j--) {
						//gotoxy(80, 2);
						//printf("%lf",speed);
						gotoxy(x, y);
						//sNote[j].x = last;
						
						if (testNote[j].note_line == 0) {
							display[j - notePos] = 0;
							printf("│      │      │      │      │\n");
						}
						else if (testNote[j].note_line == 1) {
							if ((j - notePos) == 2) {
								if (bBuffer1 == 2) {
									printf("│      │      │      │      │\n");
									bBuffer1--;
									display[2] = 0;
								}
								else if (bBuffer2 == 2) {
									printf("│      │      │      │      │\n");
									bBuffer2--;
									display[2] = 0;
								}
								else if (bBuffer3 == 2) {
									printf("│      │      │      │      │\n");
									bBuffer3--;
									display[2] = 0;
								}
								else if (bBuffer4 == 2) {
									printf("│      │      │      │      │\n");
									bBuffer4--;
									display[2] = 0;
								}
								else {
									display[j - notePos] = 1;
									printf("│");
									textcolor(CYAN2, WHITE);
									printf("■");
									textcolor(CYAN1, WHITE);
									printf("■");
									textcolor(CYAN2, WHITE);
									printf("■");
									textcolor(WHITE, BLACK);
									printf("│      │      │      │\n");
								}
							}
							else if ((j - notePos) == 1) {
								if (bBuffer1 == 1) {
									printf("│      │      │      │      │\n");
									bBuffer1--;
									display[1] = 0;
								}
								else if (bBuffer2 == 1) {
									printf("│      │      │      │      │\n");
									bBuffer2--;
									display[1] = 0;
								}
								else if (bBuffer3 == 1) {
									printf("│      │      │      │      │\n");
									bBuffer3--;
									display[1] = 0;
								}
								else if (bBuffer4 == 1) {
									printf("│      │      │      │      │\n");
									bBuffer4--;
									display[1] = 0;
								}
								else {
									display[j - notePos] = 1;
									printf("│");
									textcolor(CYAN2, WHITE);
									printf("■");
									textcolor(CYAN1, WHITE);
									printf("■");
									textcolor(CYAN2, WHITE);
									printf("■");
									textcolor(WHITE, BLACK);
									printf("│      │      │      │\n");
								}
							}
							else {
								display[j - notePos] = 1;
								printf("│");
								textcolor(CYAN2, WHITE);
								printf("■");
								textcolor(CYAN1, WHITE);
								printf("■");
								textcolor(CYAN2, WHITE);
								printf("■");
								textcolor(WHITE, BLACK);
								printf("│      │      │      │\n");
							}
						}
						else if (testNote[j].note_line == 2) {
							if ((j - notePos) == 2) {
								if (bBuffer1 == 2) {
									printf("│      │      │      │      │\n");
									bBuffer1--;
									display[2] = 0;
								}
								else if (bBuffer2 == 2) {
									printf("│      │      │      │      │\n");
									bBuffer2--;
									display[2] = 0;
								}
								else if (bBuffer3 == 2) {
									printf("│      │      │      │      │\n");
									bBuffer3--;
									display[2] = 0;
								}
								else if (bBuffer4 == 2) {
									printf("│      │      │      │      │\n");
									bBuffer4--;
									display[2] = 0;
								}
								else {
									display[j - notePos] = 2;
									printf("│      │");
									textcolor(CYAN2, WHITE);
									printf("■");
									textcolor(CYAN1, WHITE);
									printf("■");
									textcolor(CYAN2, WHITE);
									printf("■");
									textcolor(WHITE, BLACK);
									printf("│      │      │\n");
								}
							}
							else if ((j - notePos) == 1) {
								if (bBuffer1 == 1) {
									printf("│      │      │      │      │\n");
									bBuffer1--;
									display[1] = 0;
								}
								else if (bBuffer2 == 1) {
									printf("│      │      │      │      │\n");
									bBuffer2--;
									display[1] = 0;
								}
								else if (bBuffer3 == 1) {
									printf("│      │      │      │      │\n");
									bBuffer3--;
									display[1] = 0;
								}
								else if (bBuffer4 == 1) {
									printf("│      │      │      │      │\n");
									bBuffer4--;
									display[1] = 0;
								}
								else {
									display[j - notePos] = 2;
									printf("│      │");
									textcolor(CYAN2, WHITE);
									printf("■");
									textcolor(CYAN1, WHITE);
									printf("■");
									textcolor(CYAN2, WHITE);
									printf("■");
									textcolor(WHITE, BLACK);
									printf("│      │      │\n");
								}
							}
							else {
								display[j - notePos] = 2;
								printf("│      │");
								textcolor(CYAN2, WHITE);
								printf("■");
								textcolor(CYAN1, WHITE);
								printf("■");
								textcolor(CYAN2, WHITE);
								printf("■");
								textcolor(WHITE, BLACK);
								printf("│      │      │\n");
							}
						}
						else if (testNote[j].note_line == 3) {
							if ((j - notePos) == 2) {
								if (bBuffer1 == 2) {
									printf("│      │      │      │      │\n");
									bBuffer1--;
									display[2] = 0;
								}
								else if (bBuffer2 == 2) {
									printf("│      │      │      │      │\n");
									bBuffer2--;
									display[2] = 0;
								}
								else if (bBuffer3 == 2) {
									printf("│      │      │      │      │\n");
									bBuffer3--;
									display[2] = 0;
								}
								else if (bBuffer4 == 2) {
									printf("│      │      │      │      │\n");
									bBuffer4--;
									display[2] = 0;
								}
								else {
									display[j - notePos] = 3;
									printf("│      │      │");
									textcolor(CYAN2, WHITE);
									printf("■");
									textcolor(CYAN1, WHITE);
									printf("■");
									textcolor(CYAN2, WHITE);
									printf("■");
									textcolor(WHITE, BLACK);
									printf("│      │\n" );
								}
							}
							else if ((j - notePos) == 1) {
								if (bBuffer1 == 1) {
									printf("│      │      │      │      │\n");
									bBuffer1--;
									display[1] = 0;
								}
								else if (bBuffer2 == 1) {
									printf("│      │      │      │      │\n");
									bBuffer2--;
									display[1] = 0;
								}
								else if (bBuffer3 == 1) {
									printf("│      │      │      │      │\n");
									bBuffer3--;
									display[1] = 0;
								}
								else if (bBuffer4 == 1) {
									printf("│      │      │      │      │\n");
									bBuffer4--;
									display[1] = 0;
								}
								else {
									display[j - notePos] = 3;
									printf("│      │      │");
									textcolor(CYAN2, WHITE);
									printf("■");
									textcolor(CYAN1, WHITE);
									printf("■");
									textcolor(CYAN2, WHITE);
									printf("■");
									textcolor(WHITE, BLACK);
									printf("│      │\n");
								}
							}
							else {
								display[j - notePos] = 3;
								printf("│      │      │");
								textcolor(CYAN2, WHITE);
								printf("■");
								textcolor(CYAN1, WHITE);
								printf("■");
								textcolor(CYAN2, WHITE);
								printf("■");
								textcolor(WHITE, BLACK);
								printf("│      │\n");
							}

						}
						else if (testNote[j].note_line == 4) {
							if ((j - notePos) == 2) {
								if (bBuffer1 == 2) {
									printf("│      │      │      │      │\n");
									bBuffer1--;
									display[2] = 0;
								}
								else if (bBuffer2 == 2) {
									printf("│      │      │      │      │\n");
									bBuffer2--;
									display[2] = 0;
								}
								else if (bBuffer3 == 2) {
									printf("│      │      │      │      │\n");
									bBuffer3--;
									display[2] = 0;
								}
								else if (bBuffer4 == 2) {
									printf("│      │      │      │      │\n");
									bBuffer4--;
									display[2] = 0;
								}
								else {
									display[j - notePos] = 4;
									printf("│      │      │      │");
									textcolor(CYAN2, WHITE);
									printf("■");
									textcolor(CYAN1, WHITE);
									printf("■");
									textcolor(CYAN2, WHITE);
									printf("■");
									textcolor(WHITE, BLACK);
									printf("│\n");
								}
							}
							else if ((j - notePos) == 1) {
								if (bBuffer1 == 1) {
									printf("│      │      │      │      │\n");
									bBuffer1--;
									display[1] = 0;
								}
								else if (bBuffer2 == 1) {
									printf("│      │      │      │      │\n");
									bBuffer2--;
									display[1] = 0;
								}
								else if (bBuffer3 == 1) {
									printf("│      │      │      │      │\n");
									bBuffer3--;
									display[1] = 0;
								}
								else if (bBuffer4 == 1) {
									printf("│      │      │      │      │\n");
									bBuffer4--;
									display[1] = 0;
								}
								else {
									display[j - notePos] = 4;
									printf("│      │      │      │");
									textcolor(CYAN2, WHITE);
									printf("■");
									textcolor(CYAN1, WHITE);
									printf("■");
									textcolor(CYAN2, WHITE);
									printf("■");
									textcolor(WHITE, BLACK);
									printf("│\n");
								}
							}
							else {
								display[j - notePos] = 4;
								printf("│      │      │      │");
								textcolor(CYAN2, WHITE);
								printf("■");
								textcolor(CYAN1, WHITE);
								printf("■");
								textcolor(CYAN2, WHITE);
								printf("■");
								textcolor(WHITE, BLACK);
								printf("│\n");
							}
						}

						y++;
						gotoxy(20, 20);
						textcolor(RED2, BLACK);
						printf("├───────────────┤");
						textcolor(WHITE, BLACK);
						gotoxy(20, 22);
						printf("└───┴───┴───┴───┘");
					}
					gotoxy(20,12);
					printf("                                           ");
					gotoxy(20, 13);
					printf("          싱크 테스트 중입니다.               ");
					gotoxy(20, 14);
					printf("          잠시만 기다려주세요                 ");
					gotoxy(20, 15);
					printf("                                           ");


					if (kbhit() == 1) {
						ch = getch();
						if (ch == 0x71) {

							notePos = 0;//노트표시 순환 횟수, display접근에 필요
							getBlank[500];//노트 처리시 사라지게만들기
							getBlanki;
							gb = 0;//getBlank 변수
							bBuffer1 = 0;
							bBuffer2 = 0;
							bBuffer3 = 0;
							bBuffer4 = 0;
						
							combo = 0;
							bestCombo = 0;
							color_a = 0;
							color_b = 0;
							color_c = 0;
							cross_colorA = 15;
							cross_colorB = 15;
							cross_colorC = 15;
							color_Cycle = 0;
						
							excellent_count = 0;
							great_count = 0;
							miss_count = 0;
							combo_color = 15;
							ch = 0;
							PlaySound(NULL, 0, 0);

							for (int x = 0; x < 25; x++) {
								for (int z = 0; z < 100; z++) {
									gotoxy(z, x);
									printf(" ");
								}
							}
							cls(BLACK, WHITE);

							if (music_case == 1)
								pre_case = 2;
							else if (music_case == 2)
								pre_case = 1;
							goto select;
							break;
						}
						switch (ch) {



						case 0x66:

							if (display[1] == 1) {
								display[1] = 0;
								textcolor(YELLOW2, YELLOW2);
								gotoxy(63, 14);
								printf("                  ");
								textcolor(WHITE, BLACK);
								//gotoxy(6, 13);
								//printf("●GREAT●");
								combo++;
								great_count++;

							}
							else if (display[2] == 1) {
								display[2] = 0;
								gb = 1;
								getBlank[gb] = 1;
								textcolor(GREEN2, GREEN2);
								gotoxy(63, 11);
								printf("                  ");
								textcolor(WHITE, BLACK);
								//gotoxy(6, 13);
								//printf("★☆EXCELLENT☆★");
								combo++;
								excellent_count++;

							}
							else if (display[3] == 1) {
								display[3] = 0;
								gb = 5;
								getBlank[gb] = 1;
								textcolor(YELLOW2, YELLOW2);
								gotoxy(63, 14);
								printf("                  ");
								textcolor(WHITE, BLACK);
								//gotoxy(6, 13);
								//printf("●GREAT●");
								combo++;
								great_count++;
							}

							break;
						case 0x67:


							if (display[1] == 2) {
								display[1] = 0;
								textcolor(YELLOW2, YELLOW2);
								gotoxy(63, 14);
								printf("                  ");
								textcolor(WHITE, BLACK);
								//gotoxy(6, 13);
								//printf("●GREAT●");
								combo++;
								great_count++;
							}
							else if (display[2] == 2) {
								display[2] = 0;
								gb = 2;
								getBlank[gb] = 1;
								textcolor(GREEN2, GREEN2);
								gotoxy(63, 11);
								printf("                  ");
								textcolor(WHITE, BLACK);
								//gotoxy(6, 13);
								//printf("★☆PERFECT☆★");
								combo++;
								excellent_count++;
							}
							else if (display[3] == 2) {
								display[3] = 0;
								gb = 6;
								getBlank[gb] = 1;
								textcolor(YELLOW2, YELLOW2);
								gotoxy(63, 14);
								printf("                  ");
								textcolor(WHITE, BLACK);
								//gotoxy(6, 13);
								//printf("●GREAT●");
								combo++;
								great_count++;
							}
							break;
						case 0x68:

							if (display[1] == 3) {
								display[1] = 0;
								textcolor(YELLOW2, YELLOW2);
								gotoxy(63, 14);
								printf("                  ");
								textcolor(WHITE, BLACK);
								//gotoxy(6, 13);
								//printf("●GREAT●");
								combo++;
								great_count++;
							}
							else if (display[2] == 3) {
								display[2] = 0;
								gb = 3;
								getBlank[gb] = 1;
								textcolor(GREEN2, GREEN2);
								gotoxy(63, 11);
								printf("                  ");
								textcolor(WHITE, BLACK);
								//gotoxy(6, 13);
								//printf("★☆PERFECT☆★");
								combo++;
								excellent_count++;
							}
							else if (display[3] == 3) {
								display[3] = 0;
								gb = 7;
								getBlank[gb] = 1;
								textcolor(YELLOW2, YELLOW2);
								gotoxy(63, 14);
								printf("                  ");
								textcolor(WHITE, BLACK);
								//gotoxy(6, 13);
								//printf("●GREAT●");
								combo++;
								great_count++;
							}
							break;
						case 0x6A:
							if (display[1] == 4) {
								display[1] = 0;
								textcolor(YELLOW2, YELLOW2);
								gotoxy(63, 14);
								printf("                  ");
								textcolor(WHITE, BLACK);
								//gotoxy(6, 13);
								//printf("●GREAT●");
								combo++;
								great_count++;
							}
							else if (display[2] == 4) {
								display[2] = 0;
								gb = 4;
								getBlank[gb] = 1;
								textcolor(GREEN2, GREEN2);
								gotoxy(63, 11);
								printf("                  ");
								textcolor(WHITE, BLACK);
								//gotoxy(6, 13);
								//printf("★☆PERFECT☆★");
								combo++;
								excellent_count++;
							}
							else if (display[3] == 4) {
								display[3] = 0;
								gb = 8;
								getBlank[gb] = 1;
								textcolor(YELLOW2, YELLOW2);
								gotoxy(63, 14);
								printf("                  ");
								textcolor(WHITE, BLACK);
								//gotoxy(6, 13);
								//printf("●GREAT●");
								combo++;
								great_count++;
							}
							break;

							/*case 0x71:
							PlaySound(NULL, 0, 0);

							for (i = 0; i < 25; i++) {
							for (int z = 0; z < 100; z++) {
							gotoxy(z, i);
							printf(" ");
							}
							}
							cls(BLACK, WHITE);
							goto firstpage;

							break;
							*/
						case 0x72:
							speed = speed - 0.5;
							
							break;
						case 0x75:
							speed = speed + 0.5;
						
						}

					}

					if (getBlank[1] == 1) {
						bBuffer1 = 1;
						getBlank[1] = 0;
					}
					else if (getBlank[2] == 1) {
						bBuffer2 = 1;
						getBlank[2] = 0;
					}
					else if (getBlank[3] == 1) {
						bBuffer3 = 1;
						getBlank[3] = 0;
					}
					else if (getBlank[4] == 1) {
						bBuffer4 = 1;
						getBlank[4] = 0;
					}
					else if (getBlank[5] == 1) {
						bBuffer1 = 2;
						getBlank[5] = 0;
					}
					else if (getBlank[6] == 1) {
						bBuffer2 = 2;
						getBlank[6] = 0;
					}
					else if (getBlank[7] == 1) {
						bBuffer3 = 2;
						getBlank[7] = 0;
					}
					else if (getBlank[8] == 1) {
						bBuffer4 = 2;
						getBlank[8] = 0;
					}

					if (display[1] != 0) {
					
						textcolor(RED2, RED2);
						gotoxy(63, 17);
						printf("                  ");
						textcolor(WHITE, BLACK);
						miss_count++;
						if (bestCombo < combo)
							bestCombo = combo;
						combo = 0;
					}
					Sleep(speed);
					start++;
					last++;
					notePos++;
					gotoxy(x, y);
					y = 2;

					gotoxy(62, 11);
					textcolor(BLACK, BLACK);
					printf("     ");
					gotoxy(75, 11);
					printf("      ");

					gotoxy(62, 14);
					textcolor(BLACK, BLACK);
					printf("     ");
					gotoxy(75, 14);
					printf("      ");

					gotoxy(62, 17);
					textcolor(BLACK, BLACK);
					printf("       ");
					gotoxy(75, 17);
					printf("      ");

				
					gotoxy(61, 6);
					textcolor(combo_color, BLACK);
					printf("┌─────────┐");//combo 창
					gotoxy(61, 7);
					printf("│");
					gotoxy(81, 7);
					printf("│");
					gotoxy(61, 8);
					printf("└─────────┘");
					gotoxy(65, 7);
					printf("COMBO : %4d", combo);

					textcolor(GREEN2, BLACK);
					gotoxy(61, 10);
					printf("┌─────────┐");// excellent창
					gotoxy(61, 11);
					printf("│");
					gotoxy(81, 11);
					printf("│");
					gotoxy(61, 12);
					printf("└─────────┘");
					gotoxy(63, 11);
					printf("EXCELLENT : %4d", excellent_count);

					textcolor(YELLOW2, BLACK);
					gotoxy(61, 13);
					printf("┌─────────┐");// great 창
					gotoxy(61, 14);
					printf("│");
					gotoxy(81, 14);
					printf("│");
					gotoxy(61, 15);
					printf("└─────────┘");
					gotoxy(67, 14);
					printf("GREAT : %4d", great_count);

					textcolor(RED2, BLACK);
					gotoxy(61, 16);
					printf("┌─────────┐");//MISS 창
					gotoxy(61, 17);
					printf("│");
					gotoxy(81, 17);
					printf("│");
					gotoxy(61, 18);
					printf("└─────────┘");
					gotoxy(68, 17);
					printf("MISS : %4d", miss_count);

					textcolor(WHITE, BLACK);
					gotoxy(65, 7);
					printf("COMBO : %4d", combo);
					if (bestCombo < combo)
						bestCombo = combo;

					if (combo >= 0 && combo < 25)
						combo_color = 15;
					else if (combo >= 25 && combo < 50)
						combo_color = 8;
					else if (combo >= 50 && combo < 75)
						combo_color = 7;
					else if (combo >= 75 && combo < 100)
						combo_color = 11;
					else if (combo >= 100 && combo < 125)
						combo_color = 9;
					else if (combo >= 125 && combo < 150)
						combo_color = 13;


					textcolor(YELLOW2, MAGENTA1);
					gotoxy(0, 13);
					printf("┌───────┐");//최고 콤보창
					gotoxy(0, 14);
					printf("│");
					gotoxy(16, 14);
					printf("│");
					gotoxy(0, 15);
					printf("│");
					gotoxy(16, 15);
					printf("│");
					gotoxy(0, 16);
					printf("└───────┘");
					gotoxy(2, 14);
					printf("   BEST COMBO ");
					gotoxy(2, 15);
					printf("     %4d     ", bestCombo);
					textcolor(WHITE, BLACK);


					textcolor(YELLOW2, GRAY2);
					gotoxy(0, 9);
					printf("┌───────┐");// 조작법
					gotoxy(0, 10);
					printf("│");
					gotoxy(16, 10);
					printf("│");
					gotoxy(0, 11);
					printf("│");
					gotoxy(16, 11);
					printf("│");
					gotoxy(0, 12);
					printf("└───────┘");
					gotoxy(2, 10);
					printf("    <조작키>  ");
					gotoxy(2, 11);
					printf("    F,G,H,J   ");
					textcolor(WHITE, BLACK);

					now = clock();
					duration = now - start_clock;
					if (duration > loop_time) {
						speed = speed - 2;
					}
					else if (duration < loop_time) {
						speed = speed + 2;
					}
					/*if (l > 20) {
					time_avg = (time_avg + duration) / l;
					if (duration > time_avg)
					speed = speed - 0.5;
					else if (duration < time_avg)
					speed = speed + 0.5;
					}
					else if (l < 20)
					time_avg = time_avg+duration;*/
					gotoxy(61, 1);
					textcolor(WHITE, BLACK);
					printf("┌─────────┐");//싱크,지연정보 창
					gotoxy(61, 2);
					printf("│");
					gotoxy(81, 2);
					printf("│");
					gotoxy(61, 3);
					printf("│");
					gotoxy(81, 3);
					printf("│");
					gotoxy(61, 4);
					printf("└─────────┘");


					gotoxy(67, 2);
					printf("싱크 : %.1lf", speed);
					gotoxy(67, 3);
					printf("지연 : %3.1lf", duration);

					now = clock();
					duration = now - start_clock;
					if (duration > loop_time) {
						speed = speed - 2.0;
					}
					else if (duration < loop_time) {
						speed = speed + 2.0;
					}
					
					
					
				}
				gotoxy(20, 12);
				printf("                                           ");
				gotoxy(20, 13);
				printf("        싱크 테스트가 완료되었습니다.               ");
				gotoxy(20, 14);
				printf("          아무키나 눌러주세요                 ");
				gotoxy(20, 15);
				printf("                                           ");
				ch = getch();
				for (j = 0; j < sync + 40; j++)
					testNote[j].note_line = 0;
				line = 0;
				start = 0; last = 20;
				i = sync;
				if (pre_case == 1)
					pre_case = 2;
				else if (pre_case == 2)
					pre_case = 1;
				fclose(testfile);
				for (int x = 0; x < 25; x++) {
					for (int z = 0; z < 100; z++) {
						gotoxy(z, x);
						printf(" ");
					}
				}
		
				
			}
			else if (ch == SPECIAL1 || ch == SPECIAL2) {
				ch = getch();
				switch (ch) {
				case UP:
					if (music_case == 1) 
					{
						
						music_case = 2;
						/*gotoxy(57, 18);
						printf("                              ");
						gotoxy(57, 19);
						printf("                              ");
						gotoxy(57, 20);
						printf("                              ");*/
					}
					else if (music_case == 2)
					{
						
						music_case = 1;
					}
					break;
				case DOWN:
					if (music_case == 1)
					{
						
						music_case = 2;
						/*gotoxy(57, 18);
						printf("                              ");
						gotoxy(57, 19);
						printf("                              ");
						gotoxy(57, 20);
						printf("                              ");*/
					}
					else if (music_case == 2)
					{
						
						music_case = 1;
					}
					break;
				case LEFT:
					loop_time = loop_time - 0.2;
					break;
				case RIGHT:
					loop_time = loop_time + 0.2;
					break;
					
				}

			}
		}
		///////////////////////////////
		///////////////여기서부터, 선택되어있는 곡에 대한 동작지정
		////////////////////////////////////////
		
		if (color_Cycle == 2)
			color_Cycle = 0;
		else
			color_Cycle++;
		Sleep(200);
	}
	
	/*
	FILE *readfile = fopen("note.txt", "r");
	for (j = 0; j < sync; j++) {
		note[j] = 0;
		
	}
	while (!feof(readfile)) {
		fscanf(readfile, "%d",&note[i]);
		i++;
		line++;
	}*/
	line = 0;
	start = 0; last = 20;
	i = sync;
	
	notePos = 0;//노트표시 순환 횟수, display접근에 필요
	getBlank[500];//노트 처리시 사라지게만들기
	getBlanki=0;
	gb = 0;//getBlank 변수
	bBuffer1 = 0;
	bBuffer2 = 0;
	bBuffer3 = 0;
	bBuffer4 = 0;

	combo = 0;
	bestCombo = 0;
	color_a = 0;
	color_b = 0;
	color_c = 0;
	cross_colorA = 15;
	cross_colorB = 15;
	cross_colorC = 15;
	color_Cycle = 0;

	excellent_count = 0;
	great_count = 0;
	miss_count = 0;
	combo_color = 15;
	ch = 0;
	x = 20;
	//FILE *readfile = fopen("rageofdemon.txt", "r");
	FILE *readfile;
	if(music_case==1)readfile= fopen("black_swan2.txt", "r");
	else if (music_case == 2)readfile = fopen("rageofdemon.txt", "r");
	for (j = 0; j < sync; j++) {
		sNote[j].note_line = 0;

	}
	while (!feof(readfile)) {
		fscanf(readfile, "%d", &sNote[i].note_line);
		
		i++;
		line++;
	}
	/*for (d = 0; d < line+sync; d++){
		if (sNote[d].note_line = 0) {
			strcpy(display[d], "│      │      │      │      │\n");
		}

	}*/

	//line=strlen(note);
	cls(BLACK, WHITE);
	system("mode con cols=100 lines=25");
	gotoxy(x, y);
	Sleep(1000);
	
	

	//PlaySound("black_swan.wav", NULL, SND_ASYNC);
	if(music_case==1)
		PlaySound(TEXT("black_swan2.wav"), NULL, SND_FILENAME | SND_ASYNC );
	else if(music_case==2)
		PlaySound(TEXT("rageofdemon.wav"), NULL, SND_FILENAME | SND_ASYNC);
	//start_clock = clock();
	for (l = 0; l < line + 20; l++) {
		start_clock = clock();
		//now = clock();
		//duration = now - start_clock;
		for (j = last; j > start; j--) {
			//gotoxy(80, 2);
			//printf("%lf",speed);
			gotoxy(x, y);
			//sNote[j].x = last;
			sNote[j].y = j;
			if (sNote[j].note_line == 0) {
				display[j - notePos] = 0;
				printf("│      │      │      │      │\n");
			}
			else if (sNote[j].note_line == 1) {
				if ((j - notePos) == 2) {
					if (bBuffer1 == 2) {
						printf("│      │      │      │      │\n");
						bBuffer1--;
						display[2] = 0;
					}
					else if (bBuffer2 == 2) {
						printf("│      │      │      │      │\n");
						bBuffer2--;
						display[2] = 0;
					}
					else if (bBuffer3 == 2) {
						printf("│      │      │      │      │\n");
						bBuffer3--;
						display[2] = 0;
					}
					else if (bBuffer4 == 2) {
						printf("│      │      │      │      │\n");
						bBuffer4--;
						display[2] = 0;
					}
					else {
						display[j - notePos] = 1;
						printf("│");
						textcolor(CYAN2, WHITE);
						printf("■");
						textcolor(CYAN1, WHITE);
						printf("■");
						textcolor(CYAN2, WHITE);
						printf("■");
						textcolor(WHITE, BLACK);
						printf("│      │      │      │\n");
					}
				}
				else if ((j - notePos) == 1) {
					if (bBuffer1 == 1) {
						printf("│      │      │      │      │\n");
						bBuffer1--;
						display[1] = 0;
					}
					else if (bBuffer2 == 1) {
						printf("│      │      │      │      │\n");
						bBuffer2--;
						display[1] = 0;
					}
					else if (bBuffer3 == 1) {
						printf("│      │      │      │      │\n");
						bBuffer3--;
						display[1] = 0;
					}
					else if (bBuffer4 == 1) {
						printf("│      │      │      │      │\n");
						bBuffer4--;
						display[1] = 0;
					}
					else {
						display[j - notePos] = 1;
						printf("│");
						textcolor(CYAN2, WHITE);
						printf("■");
						textcolor(CYAN1, WHITE);
						printf("■");
						textcolor(CYAN2, WHITE);
						printf("■");
						textcolor(WHITE, BLACK);
						printf("│      │      │      │\n");
					}
				}
				else {
					display[j - notePos] = 1;
					printf("│");
					textcolor(CYAN2, WHITE);
					printf("■");
					textcolor(CYAN1, WHITE);
					printf("■");
					textcolor(CYAN2, WHITE);
					printf("■");
					textcolor(WHITE, BLACK);
					printf("│      │      │      │\n");
				}
			}
			else if (sNote[j].note_line == 2) {
				if ((j - notePos) == 2) {
					if (bBuffer1 == 2) {
						printf("│      │      │      │      │\n");
						bBuffer1--;
						display[2] = 0;
					}
					else if (bBuffer2 == 2) {
						printf("│      │      │      │      │\n");
						bBuffer2--;
						display[2] = 0;
					}
					else if (bBuffer3 == 2) {
						printf("│      │      │      │      │\n");
						bBuffer3--;
						display[2] = 0;
					}
					else if (bBuffer4 == 2) {
						printf("│      │      │      │      │\n");
						bBuffer4--;
						display[2] = 0;
					}
					else {
						display[j - notePos] = 2;
						printf("│      │");
						textcolor(CYAN2, WHITE);
						printf("■");
						textcolor(CYAN1, WHITE);
						printf("■");
						textcolor(CYAN2, WHITE);
						printf("■");
						textcolor(WHITE, BLACK);
						printf("│      │      │\n");
					}
				}
				else if ((j - notePos) == 1) {
					if (bBuffer1 == 1) {
						printf("│      │      │      │      │\n");
						bBuffer1--;
						display[1] = 0;
					}
					else if (bBuffer2 == 1) {
						printf("│      │      │      │      │\n");
						bBuffer2--;
						display[1] = 0;
					}
					else if (bBuffer3 == 1) {
						printf("│      │      │      │      │\n");
						bBuffer3--;
						display[1] = 0;
					}
					else if (bBuffer4 == 1) {
						printf("│      │      │      │      │\n");
						bBuffer4--;
						display[1] = 0;
					}
					else {
						display[j - notePos] = 2;
						printf("│      │");
						textcolor(CYAN2, WHITE);
						printf("■");
						textcolor(CYAN1, WHITE);
						printf("■");
						textcolor(CYAN2, WHITE);
						printf("■");
						textcolor(WHITE, BLACK);
						printf("│      │      │\n");
					}
				}
				else {
					display[j - notePos] = 2;
					printf("│      │");
					textcolor(CYAN2, WHITE);
					printf("■");
					textcolor(CYAN1, WHITE);
					printf("■");
					textcolor(CYAN2, WHITE);
					printf("■");
					textcolor(WHITE, BLACK);
					printf("│      │      │\n");
				}
			}
			else if (sNote[j].note_line == 3) {
				if ((j - notePos) == 2) {
					if (bBuffer1 == 2) {
						printf("│      │      │      │      │\n");
						bBuffer1--;
						display[2] = 0;
					}
					else if (bBuffer2 == 2) {
						printf("│      │      │      │      │\n");
						bBuffer2--;
						display[2] = 0;
					}
					else if (bBuffer3 == 2) {
						printf("│      │      │      │      │\n");
						bBuffer3--;
						display[2] = 0;
					}
					else if (bBuffer4 == 2) {
						printf("│      │      │      │      │\n");
						bBuffer4--;
						display[2] = 0;
					}
					else {
						display[j - notePos] = 3;
						printf("│      │      │");
						textcolor(CYAN2, WHITE);
						printf("■");
						textcolor(CYAN1, WHITE);
						printf("■");
						textcolor(CYAN2, WHITE);
						printf("■");
						textcolor(WHITE, BLACK);
						printf("│      │\n");
					}
				}
				else if ((j - notePos) == 1) {
					if (bBuffer1 == 1) {
						printf("│      │      │      │      │\n");
						bBuffer1--;
						display[1] = 0;
					}
					else if (bBuffer2 == 1) {
						printf("│      │      │      │      │\n");
						bBuffer2--;
						display[1] = 0;
					}
					else if (bBuffer3 == 1) {
						printf("│      │      │      │      │\n");
						bBuffer3--;
						display[1] = 0;
					}
					else if (bBuffer4 == 1) {
						printf("│      │      │      │      │\n");
						bBuffer4--;
						display[1] = 0;
					}
					else {
						display[j - notePos] = 3;
						printf("│      │      │");
						textcolor(CYAN2, WHITE);
						printf("■");
						textcolor(CYAN1, WHITE);
						printf("■");
						textcolor(CYAN2, WHITE);
						printf("■");
						textcolor(WHITE, BLACK);
						printf("│      │\n");
					}
				}
				else {
					display[j - notePos] = 3;
					printf("│      │      │");
					textcolor(CYAN2, WHITE);
					printf("■");
					textcolor(CYAN1, WHITE);
					printf("■");
					textcolor(CYAN2, WHITE);
					printf("■");
					textcolor(WHITE, BLACK);
					printf("│      │\n");
				}

			}
			else if (sNote[j].note_line == 4) {
				if ((j - notePos) == 2) {
					if (bBuffer1 == 2) {
						printf("│      │      │      │      │\n");
						bBuffer1--;
						display[2] = 0;
					}
					else if (bBuffer2 == 2) {
						printf("│      │      │      │      │\n");
						bBuffer2--;
						display[2] = 0;
					}
					else if (bBuffer3 == 2) {
						printf("│      │      │      │      │\n");
						bBuffer3--;
						display[2] = 0;
					}
					else if (bBuffer4 == 2) {
						printf("│      │      │      │      │\n");
						bBuffer4--;
						display[2] = 0;
					}
					else {
						display[j - notePos] = 4;
						printf("│      │      │      │");
						textcolor(CYAN2, WHITE);
						printf("■");
						textcolor(CYAN1, WHITE);
						printf("■");
						textcolor(CYAN2, WHITE);
						printf("■");
						textcolor(WHITE, BLACK);
						printf("│\n");
					}
				}
				else if ((j - notePos) == 1) {
					if (bBuffer1 == 1) {
						printf("│      │      │      │      │\n");
						bBuffer1--;
						display[1] = 0;
					}
					else if (bBuffer2 == 1) {
						printf("│      │      │      │      │\n");
						bBuffer2--;
						display[1] = 0;
					}
					else if (bBuffer3 == 1) {
						printf("│      │      │      │      │\n");
						bBuffer3--;
						display[1] = 0;
					}
					else if (bBuffer4 == 1) {
						printf("│      │      │      │      │\n");
						bBuffer4--;
						display[1] = 0;
					}
					else {
						display[j - notePos] = 4;
						printf("│      │      │      │");
						textcolor(CYAN2, WHITE);
						printf("■");
						textcolor(CYAN1, WHITE);
						printf("■");
						textcolor(CYAN2, WHITE);
						printf("■");
						textcolor(WHITE, BLACK);
						printf("│\n");
					}
				}
				else {
					display[j - notePos] = 4;
					printf("│      │      │      │");
					textcolor(CYAN2, WHITE);
					printf("■");
					textcolor(CYAN1, WHITE);
					printf("■");
					textcolor(CYAN2, WHITE);
					printf("■");
					textcolor(WHITE, BLACK);
					printf("│\n");
				}
			}

			y++;
			gotoxy(20, 20);
			textcolor(RED2, BLACK);
			printf("├───────────────┤");
			textcolor(WHITE, BLACK);
			gotoxy(20, 22);
			printf("└───┴───┴───┴───┘");
		}
		if (kbhit() == 1) {
			ch = getch();
			if (ch == 0x71) {//q누르면

				PlaySound(NULL, 0, 0);

				for (int x = 0; x < 25; x++) {
					for (int z = 0; z < 100; z++) {
						gotoxy(z, x);
						textcolor(WHITE, WHITE);
						printf(" ");

					}
					//Sleep(1);
				}
				for (int x = 0; x < 25; x++) {
					for (int z = 0; z < 100; z++) {
						gotoxy(z, x);
						textcolor(BLACK, BLACK);
						printf(" ");

					}
					//Sleep(1);
				}
				x = 20;
				start = 0; last = 20;
				cls(BLACK, WHITE);
				if (music_case == 1)
					pre_case = 2;
				else if (music_case == 2)
					pre_case = 1;
				goto firstpage;


				break;
			}
			switch (ch) {
			case 0x72://r
				loop_time += 0.2;
				break;
			case 0x75:
				loop_time -= 0.2;



			case 0x66://f

				if (display[1] == 1) {
					display[1] = 0;
					textcolor(YELLOW2, YELLOW2);
					gotoxy(63, 14);
					printf("                  ");
					textcolor(WHITE, BLACK);
					//gotoxy(6, 13);
					//printf("●GREAT●");
					combo++;
					great_count++;

				}
				else if (display[2] == 1) {
					display[2] = 0;
					gb = 1;
					getBlank[gb] = 1;
					textcolor(GREEN2, GREEN2);
					gotoxy(63, 11);
					printf("                  ");
					textcolor(WHITE, BLACK);
					//gotoxy(6, 13);
					//printf("★☆EXCELLENT☆★");
					combo++;
					excellent_count++;

				}
				else if (display[3] == 1) {
					display[3] = 0;
					gb = 5;
					getBlank[gb] = 1;
					textcolor(YELLOW2, YELLOW2);
					gotoxy(63, 14);
					printf("                  ");
					textcolor(WHITE, BLACK);
					//gotoxy(6, 13);
					//printf("●GREAT●");
					combo++;
					great_count++;
				}

				break;
			case 0x67://g


				if (display[1] == 2) {
					display[1] = 0;
					textcolor(YELLOW2, YELLOW2);
					gotoxy(63, 14);
					printf("                  ");
					textcolor(WHITE, BLACK);
					//gotoxy(6, 13);
					//printf("●GREAT●");
					combo++;
					great_count++;
				}
				else if (display[2] == 2) {
					display[2] = 0;
					gb = 2;
					getBlank[gb] = 1;
					textcolor(GREEN2, GREEN2);
					gotoxy(63, 11);
					printf("                  ");
					textcolor(WHITE, BLACK);
					//gotoxy(6, 13);
					//printf("★☆PERFECT☆★");
					combo++;
					excellent_count++;
				}
				else if (display[3] == 2) {
					display[3] = 0;
					gb = 6;
					getBlank[gb] = 1;
					textcolor(YELLOW2, YELLOW2);
					gotoxy(63, 14);
					printf("                  ");
					textcolor(WHITE, BLACK);
					//gotoxy(6, 13);
					//printf("●GREAT●");
					combo++;
					great_count++;
				}
				break;
			case 0x68://h

				if (display[1] == 3) {
					display[1] = 0;
					textcolor(YELLOW2, YELLOW2);
					gotoxy(63, 14);
					printf("                  ");
					textcolor(WHITE, BLACK);
					//gotoxy(6, 13);
					//printf("●GREAT●");
					combo++;
					great_count++;
				}
				else if (display[2] == 3) {
					display[2] = 0;
					gb = 3;
					getBlank[gb] = 1;
					textcolor(GREEN2, GREEN2);
					gotoxy(63, 11);
					printf("                  ");
					textcolor(WHITE, BLACK);
					//gotoxy(6, 13);
					//printf("★☆PERFECT☆★");
					combo++;
					excellent_count++;
				}
				else if (display[3] == 3) {
					display[3] = 0;
					gb = 7;
					getBlank[gb] = 1;
					textcolor(YELLOW2, YELLOW2);
					gotoxy(63, 14);
					printf("                  ");
					textcolor(WHITE, BLACK);
					//gotoxy(6, 13);
					//printf("●GREAT●");
					combo++;
					great_count++;
				}
				break;
			case 0x6A://j
				if (display[1] == 4) {
					display[1] = 0;
					textcolor(YELLOW2, YELLOW2);
					gotoxy(63, 14);
					printf("                  ");
					textcolor(WHITE, BLACK);
					//gotoxy(6, 13);
					//printf("●GREAT●");
					combo++;
					great_count++;
				}
				else if (display[2] == 4) {
					display[2] = 0;
					gb = 4;
					getBlank[gb] = 1;
					textcolor(GREEN2, GREEN2);
					gotoxy(63, 11);
					printf("                  ");
					textcolor(WHITE, BLACK);
					//gotoxy(6, 13);
					//printf("★☆PERFECT☆★");
					combo++;
					excellent_count++;
				}
				else if (display[3] == 4) {
					display[3] = 0;
					gb = 8;
					getBlank[gb] = 1;
					textcolor(YELLOW2, YELLOW2);
					gotoxy(63, 14);
					printf("                  ");
					textcolor(WHITE, BLACK);
					//gotoxy(6, 13);
					//printf("●GREAT●");
					combo++;
					great_count++;
				}
				break;

				/*case 0x71:
					PlaySound(NULL, 0, 0);

					for (i = 0; i < 25; i++) {
						for (int z = 0; z < 100; z++) {
							gotoxy(z, i);
							printf(" ");
						}
					}
					cls(BLACK, WHITE);
					goto firstpage;

					break;
					*/

			}

		}

		if (getBlank[1] == 1) {
			bBuffer1 = 1;
			getBlank[1] = 0;
		}
		else if (getBlank[2] == 1) {
			bBuffer2 = 1;
			getBlank[2] = 0;
		}
		else if (getBlank[3] == 1) {
			bBuffer3 = 1;
			getBlank[3] = 0;
		}
		else if (getBlank[4] == 1) {
			bBuffer4 = 1;
			getBlank[4] = 0;
		}
		else if (getBlank[5] == 1) {
			bBuffer1 = 2;
			getBlank[5] = 0;
		}
		else if (getBlank[6] == 1) {
			bBuffer2 = 2;
			getBlank[6] = 0;
		}
		else if (getBlank[7] == 1) {
			bBuffer3 = 2;
			getBlank[7] = 0;
		}
		else if (getBlank[8] == 1) {
			bBuffer4 = 2;
			getBlank[8] = 0;
		}

		if (display[1] != 0) {
			//gotoxy(6, 13);
			//printf("MISS!");
			textcolor(RED2, RED2);
			gotoxy(63, 17);
			printf("                  ");
			textcolor(WHITE, BLACK);
			miss_count++;
			if (bestCombo < combo)
				bestCombo = combo;
			combo = 0;
		}
		Sleep(speed);
		start++;
		last++;
		notePos++;
		gotoxy(x, y);
		y = 2;

		gotoxy(62, 11);
		textcolor(BLACK, BLACK);
		printf("     ");
		gotoxy(75, 11);
		printf("      ");

		gotoxy(62, 14);
		textcolor(BLACK, BLACK);
		printf("     ");
		gotoxy(75, 14);
		printf("      ");

		gotoxy(62, 17);
		textcolor(BLACK, BLACK);
		printf("       ");
		gotoxy(75, 17);
		printf("      ");


		gotoxy(61, 6);
		textcolor(combo_color, BLACK);
		printf("┌─────────┐");//combo 창
		gotoxy(61, 7);
		printf("│");
		gotoxy(81, 7);
		printf("│");
		gotoxy(61, 8);
		printf("└─────────┘");
		gotoxy(65, 7);
		printf("COMBO : %4d", combo);

		textcolor(GREEN2, BLACK);
		gotoxy(61, 10);
		printf("┌─────────┐");// excellent창
		gotoxy(61, 11);
		printf("│");
		gotoxy(81, 11);
		printf("│");
		gotoxy(61, 12);
		printf("└─────────┘");
		gotoxy(63, 11);
		printf("EXCELLENT : %4d", excellent_count);

		textcolor(YELLOW2, BLACK);
		gotoxy(61, 13);
		printf("┌─────────┐");// great 창
		gotoxy(61, 14);
		printf("│");
		gotoxy(81, 14);
		printf("│");
		gotoxy(61, 15);
		printf("└─────────┘");
		gotoxy(67, 14);
		printf("GREAT : %4d", great_count);

		textcolor(RED2, BLACK);
		gotoxy(61, 16);
		printf("┌─────────┐");//MISS 창
		gotoxy(61, 17);
		printf("│");
		gotoxy(81, 17);
		printf("│");
		gotoxy(61, 18);
		printf("└─────────┘");
		gotoxy(68, 17);
		printf("MISS : %4d", miss_count);

		textcolor(WHITE, BLACK);
		gotoxy(61, 19);
		printf("┌─────────┐");//MISS 창
		gotoxy(61, 20);
		printf("│");
		gotoxy(81, 20);
		printf("│");
		gotoxy(61, 21);
		printf("└─────────┘");
		gotoxy(63, 20);
		printf("< Q > : 선택메뉴로");


		textcolor(WHITE, BLACK);
		gotoxy(65, 7);
		printf("COMBO : %4d", combo);
		if (bestCombo < combo)
			bestCombo = combo;

		if (combo >= 0 && combo < 25)
			combo_color = 15;
		else if (combo >= 25 && combo < 50)
			combo_color = 8;
		else if (combo >= 50 && combo < 75)
			combo_color = 7;
		else if (combo >= 75 && combo < 100)
			combo_color = 11;
		else if (combo >= 100 && combo < 125)
			combo_color = 9;
		else if (combo >= 125 && combo < 150)
			combo_color = 13;



		textcolor(YELLOW2, MAGENTA1);
		gotoxy(0, 13);
		printf("┌───────┐");//최고 콤보창
		gotoxy(0, 14);
		printf("│");
		gotoxy(16, 14);
		printf("│");
		gotoxy(0, 15);
		printf("│");
		gotoxy(16, 15);
		printf("│");
		gotoxy(0, 16);
		printf("└───────┘");
		gotoxy(2, 14);
		printf("   BEST COMBO ");
		gotoxy(2, 15);
		printf("     %4d     ", bestCombo);
		textcolor(WHITE, BLACK);


		textcolor(YELLOW2, GRAY2);
		gotoxy(0, 9);
		printf("┌───────┐");// 조작법
		gotoxy(0, 10);
		printf("│");
		gotoxy(16, 10);
		printf("│");
		gotoxy(0, 11);
		printf("│");
		gotoxy(16, 11);
		printf("│");
		gotoxy(0, 12);
		printf("└───────┘");
		gotoxy(2, 10);
		printf("    <조작키>  ");
		gotoxy(2, 11);
		printf("    F,G,H,J   ");
		textcolor(WHITE, BLACK);

		now = clock();
		duration = now - start_clock;
		if (duration > loop_time) {
			speed = speed - 2.5;
		}
		else if (duration < loop_time) {
			speed = speed + 2.5;
		}

		gotoxy(61, 1);
		textcolor(WHITE, BLACK);
		printf("┌─────────┐");//싱크,지연정보 창
		gotoxy(61, 2);
		printf("│");
		gotoxy(81, 2);
		printf("│");
		gotoxy(61, 3);
		printf("│");
		gotoxy(81, 3);
		printf("│");
		gotoxy(61, 4);
		printf("└─────────┘");


		gotoxy(67, 2);
		printf("싱크 : %.1lf", speed);
		gotoxy(67, 3);
		printf("지연 : %3.1lf", duration);
	}

		total_note = excellent_count + great_count + miss_count;
		exc_per = excellent_count / (double)total_note;
		gre_per = great_count / (double)total_note;
		mis_per = miss_count / (double)total_note;
		Sleep(400);
	
	PlaySound(TEXT("result.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	if (exc_per >= 0.65) {
		for (int x = 0; x < 25; x++) {
			for (int z = 0; z < 100; z++) {
				gotoxy(z, x);
				textcolor(WHITE, WHITE);
				printf(" ");

			}
			Sleep(1);
		}
		for (int x = 0; x < 25; x++) {
			for (int z = 0; z < 100; z++) {
				gotoxy(z, x);
				textcolor(BLACK, BLACK);
				printf(" ");

			}
			Sleep(1);
		}
		

		textcolor(WHITE, BLACK);
		gotoxy(14, 5);
		printf("★─────────★");
		gotoxy(14, 6);
		printf("│                  │");
		gotoxy(14, 7);
		printf("│                  │");
		gotoxy(14, 8);
		printf("│                  │");
		gotoxy(14, 9);
		printf("│                  │");
		gotoxy(14, 10);
		printf("│                  │");
		gotoxy(14, 11);
		printf("│                  │");
		gotoxy(14, 12);
		printf("│                  │");
		gotoxy(14, 13);
		printf("│                  │");
		gotoxy(14, 14);
		printf("│                  │");
		gotoxy(14, 15);
		printf("★─────────★");


		textcolor(MAGENTA2, BLACK);
		gotoxy(19, 7);
		printf("■■■■■■");
		gotoxy(19, 8);
		printf("■");
		gotoxy(19, 9);
		printf("■");
		gotoxy(19, 10);
		printf("■■■■■■");
		gotoxy(29, 11);
		printf("■");
		gotoxy(29, 12);
		printf("■");
		gotoxy(19, 13);
		printf("■■■■■■");


		gotoxy(50, 7);
		if (music_case == 1) {
			printf("곡 이름 : Black Swan");
			pre_case = 2;
		}
		else if (music_case == 2) {
			printf("곡 이름 : Rage Of Demon");
			pre_case = 1;
		}


		textcolor(WHITE, BLACK);
		gotoxy(47, 7);
		printf("▷");
		gotoxy(47, 9);
		printf("▷");
		gotoxy(47, 11);
		printf("▷");
		gotoxy(47, 13);
		printf("▷");


		textcolor(GREEN2, BLACK);
		gotoxy(50, 9);
		printf("EXCELLENT : %3d (%2.1lf%%)", excellent_count, exc_per * 100);

		textcolor(YELLOW2, BLACK);
		gotoxy(50, 11);
		printf("GREAT : %3d (%2.1lf%%)", great_count, gre_per * 100);

		textcolor(RED2, BLACK);
		gotoxy(50, 13);
		printf("MISS : %3d (%2.1lf%%)", miss_count, mis_per * 100);

		textcolor(RED2, BLACK);
		gotoxy(14, 19);
		printf("┌──────────────┐");
		gotoxy(14, 20);
		printf("│");
		gotoxy(44, 20);
		printf("│");
		gotoxy(14, 21);
		printf("└──────────────┘");
		
		gotoxy(16, 20);
		printf("< Q > 를 눌러 게임 종료하기");

		
		textcolor(GREEN2, BLACK);
		gotoxy(51, 19);
		printf("┌──────────────────┐");
		gotoxy(51, 20);
		printf("│");
		gotoxy(89, 20);
		printf("│");
		gotoxy(51, 21);
		printf("└──────────────────┘");
		gotoxy(53, 20);
		printf("< S > 를 눌러 곡 선택 화면으로 가기");


		textcolor(MAGENTA2, BLACK);
		gotoxy(29, 1);
		printf("┌──────────────────┐");
		gotoxy(29, 2);
		printf("│");
		gotoxy(67, 2);
		printf("│");
		gotoxy(29, 3);
		printf("└──────────────────┘");
		gotoxy(35, 2);
		printf("▷▶▷▶ PLAY RESULT ◀◁◀◁ ");

	}
	else if (exc_per<0.65&&exc_per >= 0.45) {
		for (int x = 0; x < 25; x++) {
			for (int z = 0; z < 100; z++) {
				gotoxy(z, x);
				textcolor(WHITE, WHITE);
				printf(" ");

			}
			Sleep(1);
		}
		for (int x = 0; x < 25; x++) {
			for (int z = 0; z < 100; z++) {
				gotoxy(z, x);
				textcolor(BLACK, BLACK);
				printf(" ");

			}
			Sleep(1);
		}
		/*textcolor(GRAY1, GRAY1);
		for (result_alpha1 = 0; result_alpha1 < 30; result_alpha1++)
		{
		for (result_alpha2 = 0; result_alpha2 < 20; result_alpha2++)
		{
		gotoxy(result_alpha1+10, result_alpha2+3);
		printf(" ");
		}
		}*/


		textcolor(WHITE, BLACK);
		gotoxy(14, 5);
		printf("★─────────★");
		gotoxy(14, 6);
		printf("│                  │");
		gotoxy(14, 7);
		printf("│                  │");
		gotoxy(14, 8);
		printf("│                  │");
		gotoxy(14, 9);
		printf("│                  │");
		gotoxy(14, 10);
		printf("│                  │");
		gotoxy(14, 11);
		printf("│                  │");
		gotoxy(14, 12);
		printf("│                  │");
		gotoxy(14, 13);
		printf("│                  │");
		gotoxy(14, 14);
		printf("│                  │");
		gotoxy(14, 15);
		printf("★─────────★");


		textcolor(YELLOW2, BLACK);
		gotoxy(19, 7);
		printf("■■■■■");
		gotoxy(19, 8);
		printf("■        ■");
		gotoxy(19, 9);
		printf("■        ■");
		gotoxy(19, 10);
		printf("■■■■■");
		gotoxy(19, 11);
		printf("■        ■");
		gotoxy(19, 12);
		printf("■        ■");
		gotoxy(19, 13);
		printf("■■■■■");


		gotoxy(50, 7);
		if (music_case == 1) {
			printf("곡 이름 : Black Swan");
			pre_case = 2;
		}
		else if (music_case == 2) {
			printf("곡 이름 : Rage Of Demon");
			pre_case = 1;
		}


		textcolor(WHITE, BLACK);
		gotoxy(47, 7);
		printf("▷");
		gotoxy(47, 9);
		printf("▷");
		gotoxy(47, 11);
		printf("▷");
		gotoxy(47, 13);
		printf("▷");


		textcolor(GREEN2, BLACK);
		gotoxy(50, 9);
		printf("EXCELLENT : %3d (%2.1lf%%)", excellent_count, exc_per * 100);

		textcolor(YELLOW2, BLACK);
		gotoxy(50, 11);
		printf("GREAT : %3d (%2.1lf%%)", great_count, gre_per * 100);

		textcolor(RED2, BLACK);
		gotoxy(50, 13);
		printf("MISS : %3d (%2.1lf%%)", miss_count, mis_per * 100);

		textcolor(RED2, BLACK);
		gotoxy(14, 19);
		printf("┌──────────────┐");
		gotoxy(14, 20);
		printf("│");
		gotoxy(44, 20);
		printf("│");
		gotoxy(14, 21);
		printf("└──────────────┘");

		gotoxy(16, 20);
		printf("< Q > 를 눌러 게임 종료하기");

		textcolor(GREEN2, BLACK);
		gotoxy(51, 19);
		printf("┌──────────────────┐");
		gotoxy(51, 20);
		printf("│");
		gotoxy(89, 20);
		printf("│");
		gotoxy(51, 21);
		printf("└──────────────────┘");
		gotoxy(53, 20);
		printf("< S > 를 눌러 곡 선택 화면으로 가기");



		textcolor(MAGENTA2, BLACK);
		gotoxy(29, 1);
		printf("┌──────────────────┐");
		gotoxy(29, 2);
		printf("│");
		gotoxy(67, 2);
		printf("│");
		gotoxy(29, 3);
		printf("└──────────────────┘");
		gotoxy(35, 2);
		printf("▷▶▷▶ PLAY RESULT ◀◁◀◁ ");

	}
	else if (exc_per<0.50) {
		for (int x = 0; x < 25; x++) {
			for (int z = 0; z < 100; z++) {
				gotoxy(z, x);
				textcolor(WHITE, WHITE);
				printf(" ");

			}
			Sleep(1);
		}
		for (int x = 0; x < 25; x++) {
			for (int z = 0; z < 100; z++) {
				gotoxy(z, x);
				textcolor(BLACK, BLACK);
				printf(" ");

			}
			Sleep(1);
		}
		/*textcolor(GRAY1, GRAY1);
		for (result_alpha1 = 0; result_alpha1 < 30; result_alpha1++)
		{
		for (result_alpha2 = 0; result_alpha2 < 20; result_alpha2++)
		{
		gotoxy(result_alpha1+10, result_alpha2+3);
		printf(" ");
		}
		}*/


		textcolor(WHITE, BLACK);
		gotoxy(14, 5);
		printf("★─────────★");
		gotoxy(14, 6);
		printf("│                  │");
		gotoxy(14, 7);
		printf("│                  │");
		gotoxy(14, 8);
		printf("│                  │");
		gotoxy(14, 9);
		printf("│                  │");
		gotoxy(14, 10);
		printf("│                  │");
		gotoxy(14, 11);
		printf("│                  │");
		gotoxy(14, 12);
		printf("│                  │");
		gotoxy(14, 13);
		printf("│                  │");
		gotoxy(14, 14);
		printf("│                  │");
		gotoxy(14, 15);
		printf("★─────────★");


		textcolor(GRAY2, BLACK);
		gotoxy(19, 7);
		printf("  ■■■■");
		gotoxy(19, 8);
		printf("■        ■");
		gotoxy(19, 9);
		printf("■        ");
		gotoxy(19, 10);
		printf("■");
		gotoxy(19, 11);
		printf("■        ");
		gotoxy(19, 12);
		printf("■        ■");
		gotoxy(19, 13);
		printf("  ■■■■");


		gotoxy(50, 7);
		if (music_case == 1) {
			printf("곡 이름 : Black Swan");
			pre_case = 2;
		}
		else if (music_case == 2) {
			printf("곡 이름 : Rage Of Demon");
			pre_case = 1;
		}


		textcolor(WHITE, BLACK);
		gotoxy(47, 7);
		printf("▷");
		gotoxy(47, 9);
		printf("▷");
		gotoxy(47, 11);
		printf("▷");
		gotoxy(47, 13);
		printf("▷");


		textcolor(GREEN2, BLACK);
		gotoxy(50, 9);
		printf("EXCELLENT : %3d (%2.1lf%%)", excellent_count, exc_per * 100);

		textcolor(YELLOW2, BLACK);
		gotoxy(50, 11);
		printf("GREAT : %3d (%2.1lf%%)", great_count, gre_per * 100);

		textcolor(RED2, BLACK);
		gotoxy(50, 13);
		printf("MISS : %3d (%2.1lf%%)", miss_count, mis_per * 100);

		textcolor(RED2, BLACK);
		gotoxy(14, 19);
		printf("┌──────────────┐");
		gotoxy(14, 20);
		printf("│");
		gotoxy(44, 20);
		printf("│");
		gotoxy(14, 21);
		printf("└──────────────┘");

		gotoxy(16, 20);
		printf("< Q > 를 눌러 게임 종료하기");

		textcolor(GREEN2, BLACK);
		gotoxy(51, 19);
		printf("┌──────────────────┐");
		gotoxy(51, 20);
		printf("│");
		gotoxy(89, 20);
		printf("│");
		gotoxy(51, 21);
		printf("└──────────────────┘");
		gotoxy(53, 20);
		printf("< S > 를 눌러 곡 선택 화면으로 가기");



		textcolor(MAGENTA2, BLACK);
		gotoxy(29, 1);
		printf("┌──────────────────┐");
		gotoxy(29, 2);
		printf("│");
		gotoxy(67, 2);
		printf("│");
		gotoxy(29, 3);
		printf("└──────────────────┘");
		gotoxy(35, 2);
		printf("▷▶▷▶ PLAY RESULT ◀◁◀◁ ");

	}
	while (1) {
		ch = getch();
		if (ch == 0x73) {//s키
			for (int x = 0; x < 25; x++) {
				for (int z = 0; z < 100; z++) {
					gotoxy(z, x);
					textcolor(WHITE, WHITE);
					printf(" ");

				}
				Sleep(1);
			}
			for (int x = 0; x < 25; x++) {
				for (int z = 0; z < 100; z++) {
					gotoxy(z, x);
					textcolor(BLACK, BLACK);
					printf(" ");

				}
				Sleep(1);
			}
			goto select;
		}
			
		else if (ch == 0x71)
			break;
	}
exit:
	for (int x = 0; x < 25; x++) {
		for (int z = 0; z < 100; z++) {
			gotoxy(z, x);
			printf(" ");
		}
	}
	textcolor(WHITE, BLACK);
	gotoxy(45, 12);
	printf("종료됩니다...");
	gotoxy(37, 15);
	
}