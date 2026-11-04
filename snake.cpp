#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
using namespace std;

class PlayerRecord {
private:
	string name;
	int score;
public:
	PlayerRecord(string n, int s) {
		name = n;
		score = s;
	}
	int getScore() {
		return score;
	}
};

// 排序规则
bool cmp(PlayerRecord a, PlayerRecord b) {
	return a.getScore() > b.getScore();
} // 【修复1】这里必须有右括号

const int WIDTH = 20;
const int HEIGHT = 15;
struct Point { int x, y; };

// 把所有东西塞进 GameManager 类里
class GameManager {
private:
	int HighestScore;
	vector<PlayerRecord> records;
	int currentScore; // 【修复3】专门存这一局的得分，供析构函数使用
	
public:
	GameManager() {
		currentScore = 0; // 初始化
		cout << "===游戏启动===" << endl << "正在读取历史数据" << endl;
		ifstream inFile("rank.txt");
		if (!inFile) {
			HighestScore = 0;
			return;
		} // 【修复2】加上大括号，防止提前 return
		int tempScore;
		string tempName;
		while (inFile >> tempName >> tempScore) {
			records.push_back(PlayerRecord(tempName, tempScore));
		}
		if (!records.empty()) {
			sort(records.begin(), records.end(), cmp);
			HighestScore = records[0].getScore();
		} else {
			HighestScore = 0;
		}
		inFile.close();
	}
	
	~GameManager() {
		cout << "===游戏关闭===" << endl << "正在保存历史数据" << endl;
		// 如果这局得分大于0，就存档
		if(currentScore > 0) {
			ofstream appendFile("rank.txt", ios::app); 
			// 【修复3和4】把这次的得分存入文件
			appendFile << "玩家 " << currentScore << "分" << endl; 
			appendFile.close();
		}
	}
	
	// 【修复5】把 playGame 收编为成员函数，这样它就能用 currentScore 了
	void playGame() {
		vector<Point> snake;
		snake.push_back({WIDTH / 2, HEIGHT / 2});
		Point food = {rand() % WIDTH, rand() % HEIGHT};
		int dirX = 1, dirY = 0;
		currentScore = 0;
		bool gameOver = false;
		int time=150;
		while (!gameOver) {
			if (_kbhit()) {
				char key = _getch();
				if (key == 'w' && dirY != 1) { dirX = 0; dirY = -1; }
				if (key == 's' && dirY != -1) { dirX = 0; dirY = 1; }
				if (key == 'a' && dirX != 1) { dirX = -1; dirY = 0; }
				if (key == 'd' && dirX != -1) { dirX = 1; dirY = 0; }
			}
			Point newHead = {snake[0].x + dirX, snake[0].y + dirY};
			if (newHead.x < 0 || newHead.x >= WIDTH || newHead.y < 0 || newHead.y >= HEIGHT) {
				gameOver = true; break;
			}
			for (int i = 0; i < snake.size(); i++) {
				if (newHead.x == snake[i].x && newHead.y == snake[i].y) {
					gameOver = true; break;
				}
			}
			if (gameOver) break;
			
			snake.insert(snake.begin(), newHead);
			bool flag=false;
			if (newHead.x == food.x && newHead.y == food.y) {
				currentScore++;
				if(currentScore%10==0&&time>50){
					time-=20;
				}
				food = {rand() % WIDTH, rand() % HEIGHT};
			} else {
				snake.pop_back();
			}
			
			system("cls");
			cout << "Score: " << currentScore << " (Speed: " << time << "ms)" << endl;
			
			// 1. 打印最顶部的边框
			cout << "+";
			for (int j = 0; j < WIDTH; j++) cout << "-";
			cout << "+" << endl;
			
			// 2. 打印中间的每一行
			for (int i = 0; i < HEIGHT; i++) {
				cout << "|"; // 打印左侧边框
				
				for (int j = 0; j < WIDTH; j++) {
					if (i == snake[0].y && j == snake[0].x) cout << "O"; // 蛇头
					else if (i == food.y && j == food.x) cout << "*";    // 食物
					else {
						bool isBody = false;
						for (int k = 1; k < snake.size(); k++) {
							if (i == snake[k].y && j == snake[k].x) {
								cout << "o"; // 蛇身
								isBody = true;
								break;
							}
						}
						if (!isBody) cout << " "; // 空地
					}
				}
				
				cout << "|" << endl; // 打印右侧边框并换行
			}
			
			// 3. 打印最底部的边框
			cout << "+";
			for (int j = 0; j < WIDTH; j++) cout << "-";
			cout << "+" << endl;
			Sleep(time);
		}
		system("cls");
		cout << "Game Over! Final Score: " << currentScore << endl;
		// 【修复4】不要往 records 里 push int，直接存文件，或者在游戏结束把数据塞进 records
		records.push_back(PlayerRecord("你", currentScore));
		system("pause"); // 暂停一下，让玩家看清分数
	}
	
	// 【修复5】把排行榜也收编
	void showRank() {
		if (!records.empty()) {
			sort(records.begin(), records.end(), cmp);
		}
		cout << "=== 历史排行榜 ===" << endl;
		// 【修复6】修复越界和漏分号问题，i 要小于 size()
		for(int i = 0; i < records.size(); i++) {
			cout << i + 1 << ". " << records[i].getScore() << " 分" << endl;
		}
		system("pause");
	}
	
	void start() {
		int choice;
		while(true) {
			system("cls");
			cout << "1. 开始新游戏" << endl;
			cout << "2. 查看排行榜" << endl;
			cout << "3. 退出" << endl;
			cin >> choice;
			if (choice == 1) playGame();
			else if (choice == 2) showRank();
			else if (choice == 3) break;
		}
	}
};

int main() {
	GameManager app; 
	app.start(); // 直接在 start 里面包含菜单循环
	return 0;
}
