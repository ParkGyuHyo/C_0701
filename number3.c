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
	printf("100�� �Ѿ�� ����\n\n");
	printf("��ǻ�Ϳ� ����ڰ� �����ư���\n");
	printf("���ڸ� �Է��ϵ� 1~10������\n");
	printf("�ߺ����� �ʴ� ���ڸ� �Է��Ͽ�\n\n");
	printf("���ʷ� 100�� �ѱ�� ���ڰ� �˴ϴ�.\n\n");
	printf("��ǻ�Ͱ� ���� �����մϴ�.\n");
	printf("�ƹ�Ű�� ������ �����մϴ�.");
	getch();
}

void game_control() {
	int max=100; // �ִ� �հ� ������ 100�� ( max���� �ʰ��ϴ� �ڰ� �� ) 
	int com_array[10] = {0}, user_array[10] = {0}, number; // com, user array = 0���� �ʱ�ȭ 
	int i, sum=0, win;
	
	// 10ȸ �ݺ� 
	for (i=0; i<10; i++) {
		system("cls"); // ȭ���� ���� 
		number = computer_number(i, com_array); // ��ǻ�ͳѹ� �Լ� ȣ�� (���� Ƚ���� ��ǻ�Ͱ� �Է��� ������ �迭�� ����) 
		sum+=number; // ���Ϲ��� ���� sum�� ����. 
		number_display(i, com_array, user_array, sum); // �Է�, �հ� ���� ��� 
		
		// ��ǻ�� �Է� ������ max ������ �ʰ����� ���
		if (max<sum) {
			win = 1; // ��ǻ��:1 �����:2 // ��ǻ�� �� 
			break; // �ݺ��� ���� 
		}
		
		//����ڵ� ��ǻ�Ϳ� ������ ������ �ݺ� 
		number = user_number(i, user_array);
		sum+=number;
		number_display(i, com_array, user_array, sum);
		if (max<sum) {
			win = 2;
			break;
		}
		
		press_any_key(); // ���� �ֱ����� �ƹ�Ű�� ������� ���� �ܰ�� �Ѿ�� �Լ� 
	}
	
	conclusion(win); // �ݺ��� ���� ��� ���� ��� 
}

// ��ǻ�� ���� �Է� �κ� 
int computer_number(int i, int com_array[]) {
	int j, number;
	
	again:; // ���ƿ� ���� 
	number = rand() % 10 + 1; // ���� ���� ( 1 ~ 10 ) 
	
	// ���� ���� ȸ��-1��ŭ �ݺ� 
	for (j=0; j<i; j++) {

		// ���� �ԷµǾ� �ִ� �迭�� ������ ���� ��� 
		if (com_array[j] == number) {
			goto again; // ���ƿ� ���� again: �κ����� �̵� 
		}
	}

	com_array[i] = number; // �ߺ��Ǵ� ���ڰ� ���� ��� ���� ȸ���� �ε����� ������ ���� 

	return com_array[i]; // ���� ���� 
}

// ����� �κ� 
int user_number(int i, int user_array[]) {
	int j, number;
	
	again:; // Ŀ�� �̵� 
	
	gotoxy(1, 7);
	
	printf("����� ���� �Է��� Enter>");
	scanf("%d", &number); // ����ڿ��� ������ �Է� ���� 
	
	// ���� ȸ��-1 ��ŭ �ݺ� 
	for (j=0; j<i; j++) {
		
		// ���� ����ڰ� �Է��ߴ� ��ȣ�� ���� �Է��� ��ȣ�� ���� ��� 
		if (user_array[j] == number) {
			gotoxy(1, 8); // Ŀ�� �̵� 
			printf("�ߺ��� ���ڸ� �Է��߽��ϴ�. \n");

			goto again; // again:���� ���ư� 
		}
	}

	user_array[i] = number; // ���� ȸ���ε����� ����ڰ� �Է��� ���ڸ� ���� 

	return user_array[i]; // ����ڰ� �Է��� ���ڸ� ���� 
}

// �Էµ� ��, �հ� ��� �κ� 
void number_display(int i, int com_array[], int user_array[], int sum) {
	int j;

	gotoxy(1, 2); // Ŀ�� �̵� 
	printf("��ǻ�� ���� : ");
	
	// ���� �Էµ� ȸ�� ��ŭ �ݺ� 
	for(j=0; j<=i; j++) {
		printf("%2d ", com_array[j]); // ��ǻ���� �Էµ� ������ ��� 
	}

	gotoxy(1, 3); // Ŀ�� �̵� 
	printf("����� ���� : ");
	
	// ���� �Էµ� ȸ�� ��ŭ �ݺ� 
	for(j=0; j<=i; j++) {
		
		// ���� �Էµ� ������ �� 0�� ������ ��� 
		if (user_array[j] == 0) {
			continue; // ���� �ݺ����� �Ѿ 
		} else {
			printf("%2d ", user_array[j]); // ������� �Էµ� �� ���� ��� 
		}
	}
	
	gotoxy(1, 5);
	printf("���� �հ� : %3d\n", sum);
}

void conclusion(int win) {
	if (win == 1) {
		printf("��ǻ�Ͱ� �̰���ϴ�. \n");
	} else {
		printf("����ڰ� �̰���ϴ�. \n");
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
	printf("�ƹ�Ű�� �����ÿ�..");
	getch();
}
