#include <iostream>
#include <string>
#include "Set.h"

using namespace std;

int main(void) {
	Set<int> s1;
	size_t depth = 0;
	string cmd;
	int x;

	while (true) {
		cout << "cmd : ";
		getline(cin, cmd);
		string number;
		string command;

		for (int i = 0; i < cmd.length(); i++) {
			if (isdigit(cmd[i])) {
				number += cmd[i];
			}
			else if (isspace(cmd[i]))
				continue;
			else {
				command += cmd[i];
			}
		}

		if (strcmp("insert", command.c_str()) == 0) {
			x = stoi(number);
			s1.insert(x);
			cout << "--------- After Insert ---------" << endl;
			s1.show_contents(&s1, depth);
			cout << "--------------------------------" << endl;
			cout << "\n";
		}
		else if (strcmp("erase", command.c_str()) == 0) {
			x = stoi(number);
			s1.erase(x);
			cout << "--------- After Erase ---------" << endl;
			s1.show_contents(&s1, depth);
			cout << "--------------------------------" << endl;
			cout << "\n";
		}
		else if (strcmp("count", command.c_str()) == 0) {
			x = stoi(number);
			s1.count(x);
			cout << "count : " << s1.count(x) << endl;
			cout << "\n";
		}
		else if (strcmp("quit", cmd.c_str()) == 0)
			break;
	}
}


