#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "AVLTree.h"

using namespace std;

void printVector(const vector<string> &vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i + 1 < vec.size()) {
            cout << ", ";
        }
    }
    cout << "\n";
}

int main() {
    AVLTree tree;
    string line;

    if (!getline(cin, line)) return 0;
    stringstream numStream(line);
    int numCommands = 0;
    if (!(numStream >> numCommands)) return 0;

    for (int i = 0; i < numCommands; ++i) {
        if (!std::getline(cin, line)) break;
        if (line.empty()) continue;

        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "insert") {
            size_t firstQuote = line.find('\"');
            size_t lastQuote = line.rfind('\"');

            if (firstQuote != string::npos && lastQuote != string::npos && firstQuote < lastQuote) {
                string name = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);
                string id = line.substr(lastQuote + 1);

                stringstream idStream(id);
                string ufid;
                idStream >> ufid;

                if (tree.insert(name, ufid)) {
                    cout << "successful\n";
                } else {
                    cout << "unsuccessful\n";
                }
            } else {
                cout << "unsuccessful\n";
            }
        } else if (command == "remove") {
            string ufid;
            if (ss >> ufid) {
                if (tree.remove(ufid)) {
                    cout << "successful\n";
                } else {
                    cout << "unsuccessful\n";
                }
            } else {
                cout << "unsuccessful\n";
            }
        } else if (command == "search") {
            size_t firstQuote = line.find('\"');
            size_t lastQuote = line.rfind('\"');

            if (firstQuote != string::npos && lastQuote != string::npos && firstQuote < lastQuote) {
                string name = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);
                vector<string> ids = tree.searchName(name);
                if (ids.empty()) {
                    cout << "unsuccessful\n";
                } else {
                    for (const string &id : ids) {
                        cout << id << "\n";
                    }
                }
            } else {
                string ufid;
                if (ss >> ufid) {
                    string name = tree.searchID(ufid);
                    if (name.empty()) {
                        std::cout << "unsuccessful\n";
                    } else {
                        cout << name << "\n";
                    }
                } else {
                    cout << "unsuccessful\n";
                }
            }
        } else if (command == "printInorder") {
            printVector(tree.inorder());
        } else if (command == "printPreorder") {
            printVector(tree.preorder());
        } else if (command == "printPostorder") {
            printVector(tree.postorder());
        } else if (command == "printLevelCount") {
            cout << tree.levelCount() << "\n";
        } else if (command == "removeInorder") {
            int n;
            if (ss >> n) {
                if (tree.removeInorder(n)) {
                    cout << "successful\n";
                } else {
                    cout << "unsuccessful\n";
                }
            } else {
                cout << "unsuccessful\n";
            }
        } else {
            cout << "unsuccessful\n";
        }
    }
    return 0;
}