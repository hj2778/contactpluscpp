#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Contact {
public:
	string name;
	string phone;
};

class ContactManager {
private:
	vector<Contact> list;
	string filename = "contacts.txt";
	
public:
	// 【开机自动读档】
	ContactManager() {
		ifstream inFile(filename);
		Contact temp;
		while (inFile >> temp.name >> temp.phone) {
			list.push_back(temp);
		}
		inFile.close();
		cout << "已成功读取存档，当前有 " << list.size() << " 个联系人。\n";
	}
	
	// 【关机自动存档】
	~ContactManager() {
		ofstream outFile(filename);
		for (int i = 0; i < list.size(); i++) {
			outFile << list[i].name << " " << list[i].phone << endl;
		}
		outFile.close();
		cout << "数据已自动保存，安全退出！\n";
	}
	
	void addContact() {
		Contact c;
		cout << "请输入姓名: "; cin >> c.name;
		cout << "请输入电话: "; cin >> c.phone;
		list.push_back(c);
	}
	
	void showContacts() {
		for (int i = 0; i < list.size(); i++) {
			cout << list[i].name << " - " << list[i].phone << endl;
		}
	}
	
	void run() {
		int choice;
		do {
			cout << "\n1. 添加 2. 查看 3. 退出\n请选择: ";
			cin >> choice;
			if (choice == 1) addContact();
			else if (choice == 2) showContacts();
		} while (choice != 3);
	}
};

int main() {
	ContactManager app; // 构造：自动读档
	app.run();          // 运行菜单
	
	return 0;           // 结束前：自动调用析构，保存数据
}
