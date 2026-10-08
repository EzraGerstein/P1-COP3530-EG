#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <regex>
#include <algorithm>

class AVLTree {
    struct Student {
        std::string gatorID;
        std::string gatorName;
        int height;
        Student *left;
        Student *right;

        Student(std::string id, std::string name)
            : gatorID(std::move(id)), gatorName(std::move(name)), height(1), left(nullptr), right(nullptr) {}
    };

    Student *root = nullptr;

    bool isValidID(const std::string &ufid) ;
    bool isValidName(const std::string &name) ;
    int getHeight(const Student *sdnt) ;
    int getBalanceFactor(const Student *sdnt) ;

    Student* rotateRight(Student *sdnt);
    Student* rotateLeft(Student *sdnt);
    Student* rebalance(Student *sdnt);

    Student* insertHelper(Student *sdnt, const std::string &ufid, const std::string &name, bool &success);
    Student* removeHelper(Student *sdnt, const std::string &ufid, bool &success);

    Student* searchIDHelper(Student *sdnt, const std::string &ufid);

    void searchNameHelper(Student *sdnt, const std::string &name, std::vector<std::string> &results);

    void inorderNameHelper(const Student *sdnt, std::vector<std::string> &vec);
    void inorderIDHelper(const Student *sdnt, std::vector<int> &vec);
    void preorderHelper(const Student *sdnt, std::vector<std::string> &vec);
    void postorderHelper(const Student *sdnt, std::vector<std::string> &vec);
    void getInorderStudents(Student *sdnt, std::vector<Student *> &students);
    void clearHelper(Student *sdnt);

public:
    AVLTree();
    ~AVLTree();

    bool insert(const std::string &name, const std::string &ufid);
    bool remove(const std::string &ufid);
    bool removeInorder(int n);
    std::string searchID(const std::string &ufid);
    std::vector<std::string> searchName(const std::string &name);

    std::vector<std::string> inorder();
    std::vector<std::string> preorder();
    std::vector<std::string> postorder();
    std::vector<int> inorderIDs();
    int levelCount();
};