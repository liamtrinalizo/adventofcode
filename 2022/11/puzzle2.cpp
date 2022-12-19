#include <algorithm>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum OP {
    add,
    multiply
};

struct Operation {
    OP type;
    int val;
    bool old;
};

struct Monkey {
    vector<int> items;
    struct Operation op; // multiply or add
    int divisibleBy;
    int send_to[2];
    int inspecCnt;
};

int main() {
    ifstream file("input");
    string line;
    string tmp;
    char c;
    int i;
    vector<Monkey *> monkeys;

    while (getline(file, line)) {
        // monkey line
        Monkey *monkey = new Monkey;
        monkeys.push_back(monkey);
        monkey->inspecCnt = 0;

        // read items
        getline(file, line);
        line = line.substr(strlen("  Starting items: "));
        istringstream stream(line);
        stream >> tmp;
        while (stringstream(tmp) >> i) {
            monkey->items.push_back(i);
            if (stream.eof())
                break;
            stream.get(c);
            stream >> tmp;
        }

        // read operation
        getline(file, line);
        line = line.substr(strlen("  Operation: new = old "));
        stream = istringstream(line);
        stream.get(c);
        monkey->op.type  = (c == '+' ? add : multiply);
        stream >> tmp;
        if (tmp == "old")
            monkey->op.old = true;
        else {
            monkey->op.old = false;
            stringstream(tmp) >> monkey->op.val;
        }

        // read test
        getline(file, line);
        line = line.substr(strlen("  Test: divisible by "));
        stream = istringstream(line);
        stream >> monkey->divisibleBy;

        // read true
        getline(file, line);
        line = line.substr(strlen("    If true: throw to monkey "));
        stream = istringstream(line);
        stream >> monkey->send_to[0];

        // read false
        getline(file, line);
        line = line.substr(strlen("    If false: throw to monkey "));
        stream = istringstream(line);
        stream >> monkey->send_to[1];

        // read empty line
        getline(file, line);
    }

    for (int i = 0; i < 20; i++) {
        for (Monkey *monkey : monkeys) {
            for (int item : monkey->items) {
                monkey->inspecCnt++;
                //cout << "    old " << item << endl;
                if (monkey->op.old)
                    item = (monkey->op.type == add ? item + item : item * item);
                else
                    item = (monkey->op.type == add ? item + monkey->op.val : item * monkey->op.val);
                //cout << "    new " << item << endl;

                item /= 3;
                if (item % monkey->divisibleBy == 0) {
                    //    cout << "    send to 0" << endl;
                    monkeys[monkey->send_to[0]]->items.push_back(item);
                } else {
                    //    cout << "    send to 1" << endl;
                    monkeys[monkey->send_to[1]]->items.push_back(item);
                }

            }
            monkey->items.clear();
        }
    }
    //for (Monkey *m : monkeys) {
    //    cout << "monkey " << m->inspecCnt << endl;
    //}
    auto it = max_element(monkeys.begin(), monkeys.end(),
                          [](Monkey *a, Monkey *b) {return a->inspecCnt < b->inspecCnt;});
    int max = (*it)->inspecCnt;
    monkeys.erase(it);
    it = max_element(monkeys.begin(), monkeys.end(),
                     [](Monkey *a, Monkey *b) {return a->inspecCnt < b->inspecCnt;});
    cout << "monkey business " << max * (*it)->inspecCnt;
}
