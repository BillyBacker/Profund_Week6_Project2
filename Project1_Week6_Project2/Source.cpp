#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include<stdio.h>
#include<vector>
#include<cstdlib>

std::vector<int> MaxPos = { 50,20 };

void setCursor(int, int);
void printField(void);

void setCursor(int x, int y) {
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

struct Ball {
	std::vector<int> Pos;
	int Direction[2];
	int texture;

	const bool IsBumpX(int x) {
		return this->Pos[0] == x;
	}
	const bool IsBumpY(int y) {
		return this->Pos[1] == y;
	}
	std::vector<int> getPos() {
		return this->Pos;
	}
	void go() {
		if (this->Pos[0] < MaxPos[0] && this->Pos[0] > 0) {
			this->Pos[0] += Direction[0];
		}
		else {
			this->Direction[0] /= -1;
			this->Pos[0] += this->Direction[0];
		}
		if (this->Pos[1] < MaxPos[1] && this->Pos[1] > 0) {
			this->Pos[1] += this->Direction[1];
		}
		else {
			this->Direction[1] /= -1;
			this->Pos[1] += this->Direction[1];
		}
	}
	void printfPos() {
		std::vector<int> Buffer = this->getPos();
		setCursor(0, 0);
		printf("%d %d", this->Pos[0], this->Pos[1]);
		this->Pos = Buffer;
	}
	void draw() {
		setCursor(this->Pos[0], this->Pos[1]);
		if (this->Pos[0] > 0 && this->Pos[1] > 0 && this->Pos[0] < MaxPos[0] && this->Pos[1] < MaxPos[1]) {
			printf("%c", this->texture);
		}
		setCursor(this->Pos[0] - this->Direction[0], this->Pos[1] - this->Direction[1]);
		if (this->Pos[0] - this->Direction[0] > 0 && this->Pos[1] - this->Direction[1] > 0 && this->Pos[0] - this->Direction[0] < MaxPos[0] && this->Pos[1] - this->Direction[1] < MaxPos[1]) {
			printf(" ");
		}
		go();
	}
};

struct Field {
	std::vector<Ball*> Map;

	void AddBall() {
		Ball* p = new Ball;
		p->Pos = { rand()%MaxPos[0], rand() % MaxPos[1] };
		p->Direction[0] = rand() % 4 + 1;
		p->Direction[1] = rand() % 4 + 1;
		p->texture = 'O';
		Map.push_back(p);
	}
	void Update() {
		for (int i = 0; i < Map.size(); i++) {
			Map[i]->draw();
		}
	}
};

void setcursorvisible(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void printField() {
	setCursor(0, 0);
	for (int i = 0; i < MaxPos[1]; i++) {
		for (int j = 0; j < MaxPos[0]; j++) {
			printf(" ");
		}
		printf(" |\n");
	}
	for (int j = 0; j <= MaxPos[0]; j++) {
		printf("-");
	}
}
int main() {
	Field Map;
	int num;
	setcursorvisible(false);
	printf("Enter number of Balls : ");
	scanf("%d", &num);
	setCursor(0,0);
	printf("\t\t\t\t\t\t\t\t\t");
	printField();
	for (int i = 0; i < num; i++) {
		Map.AddBall();
	}
	while (true) {
		Map.Update();
		Sleep(20);
	}
	return 0;
}
