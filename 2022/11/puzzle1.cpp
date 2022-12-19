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
    vector<long long> items;
    struct Operation op; // multiply or add
    int divisibleBy;
    int send_to[2];
    int inspecCnt;
};

int main() {
    ifstream file("input_test");
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
        cout << endl;

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

    for (int i = 0; i < 10000; i++) {
        for (Monkey *monkey : monkeys) {
            for (long long item : monkey->items) {
                monkey->inspecCnt++;
                if (monkey->op.old)
                    item = (monkey->op.type == add ? item + item : item * item);
                else
                    item = (monkey->op.type == add ? item + monkey->op.val : item * monkey->op.val);

                cout << item << endl;
                if (item % monkey->divisibleBy == 0) {
                    monkeys[monkey->send_to[0]]->items.push_back(item);
                } else {
                    monkeys[monkey->send_to[1]]->items.push_back(item);
                }

            }
            monkey->items.clear();
        }
        if ( (i+1) % 1000 == 0) {
            cout << i+1 << endl;
            for (Monkey *m : monkeys) {
                cout << "monkey " << m->inspecCnt << endl;
            }
        }
    }
    auto it = max_element(monkeys.begin(), monkeys.end(),
                          [](Monkey *a, Monkey *b) {return a->inspecCnt < b->inspecCnt;});
    int max = (*it)->inspecCnt;
    monkeys.erase(it);
    it = max_element(monkeys.begin(), monkeys.end(),
                     [](Monkey *a, Monkey *b) {return a->inspecCnt < b->inspecCnt;});
    cout << "monkey business " << max * (*it)->inspecCnt;
}
