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
    ifstream file("input");
    string line;

    Dir *curr, *prev, *root = new Dir();
    curr = root;
    curr->subDir[".."] = root;
    curr->name = "/";
    curr->size = 0;

    puts("digraph {\n"
         "    rankdir=LR\n"
         //"    layout=neato\n"
         "    overlap=false\n"
         //"    graph [splines=ortho]\n"
         //"    node [shape=plaintext]\n"
         "    \"///\" [label=\"/\"]\n");

    // skip first line going to root Dir
    getline(file, line);
    while (getline(file, line)) {
        string cmd = line.substr(0, 4);
        if (cmd == "$ cd") {
            // change current with new dir and save previous position
            string dirname = line.substr(5, line.size()-1);
            prev = curr;
            curr = curr->subDir[dirname];

            // save parent only in child dir

            if (dirname != "..") {
                curr->subDir[".."] = prev;
                curr->size = 0;
                printf("\"%s%s%s\" [label=\"%s\"]\n", curr->subDir[".."]->subDir[".."]->name.c_str(),
                                                      curr->subDir[".."]->name.c_str(),
                                                      curr->name.c_str(),
                                                      curr->name.c_str());
            } else
                curr->size += prev->size;
        }
        else if (cmd != "$ ls") {
            istringstream stream(line);
            int size = 0;
            string filename;
            stream >> filename;
            if (stringstream(filename) >> size) {
                curr->size += size;
                stream >> filename;
            } else {
                stream >> filename;
                curr->subDir[filename] = new Dir;
                curr->subDir[filename]->name = filename;
            }
            // combine grand-parent, parent and child name to avoid conflict
            printf("\"%s%s%s\" [label=\"%s\"]\n", curr->subDir[".."]->name.c_str(),
                                                  curr->name.c_str(),
                                                  filename.c_str(),
                                                  filename.c_str());
            printf("\"%s%s%s\" -> \"%s%s%s\"\n", curr->subDir[".."]->subDir[".."]->name.c_str(),
                                                 curr->subDir[".."]->name.c_str(),
                                                 curr->name.c_str(),
                                                 curr->subDir[".."]->name.c_str(),
                                                 curr->name.c_str(),
                                                 filename.c_str());

        }
    }
    // go back to root while adding sub dir size
    while (curr != root) {
        prev = curr;
        curr = curr->subDir[".."];
        curr->size += prev->size;
    }

    // traverse dirs
    int tot = 0;
    curr = root;
    stack<Dir *> dirs;
    for (auto &d : curr->subDir) {
        if (d.first != "..")
            dirs.push(d.second);
    }
    while (!dirs.empty()) {
        curr = dirs.top();
        dirs.pop();
        if (curr->size <= 100000)
            tot += curr->size;
        for (auto &d : curr->subDir) {
            if (d.first != "..")
                dirs.push(d.second);
        }
    }
    cout << "}";
}
