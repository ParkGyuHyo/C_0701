#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>

void intro_game();
void game_control();
int computer_number(int i, int com_array[]);
int user_number(int i, int user_array[]);
void number_display(int i, int com_array[], int user_array[], int sum);
void conclusion(int win);
void gotoxy(int x, int y);
void press_any_key();

int main() {
	srand(time(NULL));
	intro_game();
	game_control();
	
	return 0;
}

void intro_game() {
	system("cls");
	printf("100을 넘어라 게임\n\n");
	printf("컴퓨터와 사용자가 번갈아가며\n");
	printf("숫자를 입력하되 1~10사이의\n");
	printf("중복되지 않는 숫자를 입력하여\n\n");
	printf("최초로 100을 넘기면 승자가 됩니다.\n\n");
	printf("컴퓨터가 먼저 시작합니다.\n");
	printf("아무키나 누르면 시작합니다.");
	getch();
}

void game_control() {
	int max=100; // 최대 합계 점수는 100점 ( max점을 초과하는 자가 승 ) 
	int com_array[10] = {0}, user_array[10] = {0}, number; // com, user array = 0으로 초기화 
	int i, sum=0, win;
	
	// 10회 반복 
	for (i=0; i<10; i++) {
		system("cls"); // 화면을 지움 
		number = computer_number(i, com_array); // 컴퓨터넘버 함수 호출 (현재 횟수와 컴퓨터가 입력한 수들의 배열을 전송) 
		sum+=number; // 리턴받은 수를 sum에 더함. 
		number_display(i, com_array, user_array, sum); // 입력, 합계 숫자 출력 
		
		// 컴퓨터 입력 시점에 max 점수를 초과했을 경우
		if (max<sum) {
			win = 1; // 컴퓨터:1 사용자:2 // 컴퓨터 승 
			break; // 반복문 종료 
		}
		
		//사용자도 컴퓨터와 동일한 원리로 반복 
		number = user_number(i, user_array);
		sum+=number;
		number_display(i, com_array, user_array, sum);
		if (max<sum) {
			win = 2;
			break;
		}
		
		press_any_key(); // 텀을 주기위한 아무키나 누를경우 다음 단계로 넘어가는 함수 
	}
	
	conclusion(win); // 반복이 끝날 경우 승자 출력 
}

// 컴퓨터 숫자 입력 부분 
int computer_number(int i, int com_array[]) {
	int j, number;
	
	again:; // 돌아올 지점 
	number = rand() % 10 + 1; // 난수 생성 ( 1 ~ 10 ) 
	
	// 현재 게임 회차-1만큼 반복 
	for (j=0; j<i; j++) {

		// 만일 입력되어 있는 배열과 난수가 같을 경우 
		if (com_array[j] == number) {
			goto again; // 돌아올 지점 again: 부분으로 이동 
		}
	}

	com_array[i] = number; // 중복되는 숫자가 없는 경우 현재 회차의 인덱스에 난수를 저장 

	return com_array[i]; // 난수 리턴 
}

// 사용자 부분 
int user_number(int i, int user_array[]) {
	int j, number;
	
	again:; // 커서 이동 
	
	gotoxy(1, 7);
	
	printf("사용자 숫자 입력후 Enter>");
	scanf("%d", &number); // 사용자에게 정수를 입력 받음 
	
	// 현재 회차-1 만큼 반복 
	for (j=0; j<i; j++) {
		
		// 만일 사용자가 입력했던 번호와 현재 입력한 번호가 같을 경우 
		if (user_array[j] == number) {
			gotoxy(1, 8); // 커서 이동 
			printf("중복된 숫자를 입력했습니다. \n");

			goto again; // again:으로 돌아감 
		}
	}

	user_array[i] = number; // 현재 회차인덱스에 사용자가 입력한 숫자를 저장 

	return user_array[i]; // 사용자가 입력한 숫자를 리턴 
}

// 입력된 수, 합계 출력 부분 
void number_display(int i, int com_array[], int user_array[], int sum) {
	int j;

	gotoxy(1, 2); // 커서 이동 
	printf("컴퓨터 숫자 : ");
	
	// 현재 입력된 회차 만큼 반복 
	for(j=0; j<=i; j++) {
		printf("%2d ", com_array[j]); // 컴퓨터의 입력된 수들을 출력 
	}

	gotoxy(1, 3); // 커서 이동 
	printf("사용자 숫자 : ");
	
	// 현재 입력된 회차 만큼 반복 
	for(j=0; j<=i; j++) {
		
		// 만약 입력된 데이터 중 0이 존재할 경우 
		if (user_array[j] == 0) {
			continue; // 다음 반복으로 넘어감 
		} else {
			printf("%2d ", user_array[j]); // 사용자의 입력된 수 들을 출력 
		}
	}
	
	gotoxy(1, 5);
	printf("현재 합계 : %3d\n", sum);
}

void conclusion(int win) {
	if (win == 1) {
		printf("컴퓨터가 이겼습니다. \n");
	} else {
		printf("사용자가 이겼습니다. \n");
	}
}

void gotoxy(int x, int y) {
    COORD c;

    c.X=x;        
    c.Y=y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);    
}

void press_any_key() {
	gotoxy(1, 10);
	printf("아무키나 누르시오..");
	getch();
}
