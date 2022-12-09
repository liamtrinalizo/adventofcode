#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

struct Dir {
    int size;
    string name;
    map<string, Dir *> subDir;
};

int main() {
    ifstream file("input_test");
    string line;

    Dir *curr, *root = new Dir();
    curr = root;
    curr->subDir[".."] = root;

    // skip first line going to root Dir
    getline(file, line);
    while (getline(file, line)) {
        string cmd = line.substr(0, 4);
        if (cmd == "$ cd") {
            string dirname = line.substr(5, line.size()-1);

            Dir *parent = curr;
            cout << dirname << " " << curr->size << "\n";
            curr = curr->subDir[dirname];
            curr->size = 0;

            // save parent only in child dir
            if (dirname != "..")
                curr->subDir[".."] = parent;

            cout.flush();
        }
        else if (cmd != "$ ls") {
            istringstream stream(line);
            int size = 0;
            string filename;
            stream >> filename;
            if (stringstream(filename) >> size)
                curr->size += size;
            else {
                stream >> filename;
                curr->subDir[filename] = new Dir;
                curr->subDir[filename]->name = filename;
            }
            // TODO add calculated dir size to container size
        }
    }

    // traverse dirs
    curr = root;
    stack<Dir *> dirs;
    for (auto &d : curr->subDir) {
        if (d.first != "..")
            dirs.push(d.second);
    }
    while (!dirs.empty()) {
        curr = dirs.top();
        dirs.pop();
        cout << dirs.size() << "\n";
        cout << curr->name << "\n";
        for (auto &d : curr->subDir) {
            if (d.first != "..")
                dirs.push(d.second);
        }
    }
}
