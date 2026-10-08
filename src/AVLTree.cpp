#include "AVLTree.h"

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    clearHelper(root);
}

// Helps delete Student pointers
void AVLTree::clearHelper(Student* sdnt) {
    if (!sdnt) return;
    clearHelper(sdnt->left);
    clearHelper(sdnt->right);
    delete sdnt;
}

// Uses regex to check for a valid ID
bool AVLTree::isValidID(const std::string &ufid) {
    const std::regex validID("^[0-9]{8}$");
    return std::regex_match(ufid, validID);
}

// Uses regex to check for a valid Name
bool AVLTree::isValidName(const std::string &name) {
    const std::regex validName("^(?=.*[a-zA-Z])[a-zA-Z ]+$");
    return std::regex_match(name, validName);
}

// Getter for height property
int AVLTree::getHeight(const Student* sdnt) {
    if (!sdnt) return 0;
    return sdnt->height;
}

// Getter for balance value
int AVLTree::getBalanceFactor(const Student* sdnt) {
    if (!sdnt) return 0;
    return getHeight(sdnt->left) - getHeight(sdnt->right);
}

// Helper for rebalancing the tree
AVLTree::Student* AVLTree::rotateRight(Student* sdnt) {
    Student* newRoot = sdnt->left;
    Student* temp = newRoot->right;

    newRoot->right = sdnt;
    sdnt->left = temp;

    sdnt->height = 1 + std::max(getHeight(sdnt->left), getHeight(sdnt->right));
    newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));

    return newRoot;
}

// Helper for rebalancing the tree
AVLTree::Student* AVLTree::rotateLeft(Student* sdnt) {
    Student* newRoot = sdnt->right;
    Student* temp = newRoot->left;

    newRoot->left = sdnt;
    sdnt->right = temp;

    sdnt->height = 1 + std::max(getHeight(sdnt->left), getHeight(sdnt->right));
    newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));

    return newRoot;
}

// Uses rotateRight and rotateLeft to check all four types of rotations
AVLTree::Student* AVLTree::rebalance(Student* sdnt) {
    int balance = getBalanceFactor(sdnt);
    if (balance > 1) {
        if (getBalanceFactor(sdnt->left) <= 0) {
            sdnt->left = rotateLeft(sdnt->left);
        }
        return rotateRight(sdnt);
    }
    if (balance < -1) {
        if (getBalanceFactor(sdnt->right) >= 0) {
            sdnt->right = rotateRight(sdnt->right);
        }
        return rotateLeft(sdnt);
    }
    return sdnt;
}

// Helper to search tree by IDs
AVLTree::Student* AVLTree::searchIDHelper(Student* sdnt, const std::string &ufid) {
    if (!sdnt || sdnt->gatorID == ufid) {
        return sdnt;
    }
    if (ufid < sdnt->gatorID) {
        return searchIDHelper(sdnt->left, ufid);
    }
    return searchIDHelper(sdnt->right, ufid);
}

// Returns name of the associated Student with a matching ID
std::string AVLTree::searchID(const std::string &ufid) {
    if (!isValidID(ufid)) return "";
    const Student* target = searchIDHelper(root, ufid);
    if (target) {
        return target->gatorName;
    }
    return "";
}

// Helper to search tree by Names
void AVLTree::searchNameHelper(Student* sdnt, const std::string &name, std::vector<std::string> &results) {
    if (!sdnt) return;
    if (sdnt->gatorName == name) {
        results.push_back(sdnt->gatorID);
    }
    searchNameHelper(sdnt->left, name, results);
    searchNameHelper(sdnt->right, name, results);
}

// Returns a vector of all Students with the same name
std::vector<std::string> AVLTree::searchName(const std::string &name) {
    std::vector<std::string> results;
    if (!isValidName(name)) return results;
    searchNameHelper(root, name, results);
    return results;
}

// Helper to insert new Students
AVLTree::Student* AVLTree::insertHelper(Student* sdnt, const std::string &ufid, const std::string &name, bool &success) {
    if (!sdnt) {
        success = true;
        return new Student(ufid, name);
    }

    if (ufid < sdnt->gatorID) {
        sdnt->left = insertHelper(sdnt->left, ufid, name, success);
    } else if (ufid > sdnt->gatorID) {
        sdnt->right = insertHelper(sdnt->right, ufid, name, success);
    } else {
        success = false;
        return sdnt;
    }

    sdnt->height = 1 + std::max(getHeight(sdnt->left), getHeight(sdnt->right));
    return rebalance(sdnt);
}

// Attempts to insert a new Student with provided data and returns if successful
bool AVLTree::insert(const std::string& name, const std::string& ufid) {
    if (!isValidName(name) || !isValidID(ufid)) return false;

    bool success = false;
    root = insertHelper(root, ufid, name, success);
    return success;
}

// Helper to remove a student based on the ID
AVLTree::Student* AVLTree::removeHelper(Student* sdnt, const std::string &ufid, bool &success) {
    if (!sdnt) {
        success = false;
        return nullptr;
    }

    if (ufid < sdnt->gatorID) {
        sdnt->left = removeHelper(sdnt->left, ufid, success);
    } else if (ufid > sdnt->gatorID) {
        sdnt->right = removeHelper(sdnt->right, ufid, success);
    } else {
        success = true;

        if (!sdnt->left && !sdnt->right) {
            delete sdnt;
            return nullptr;
        }
        if (!sdnt->left) {
            Student* temp = sdnt->right;
            delete sdnt;
            return temp;
        }
        if (!sdnt->right) {
            Student* temp = sdnt->left;
            delete sdnt;
            return temp;
        }
        Student* succ = sdnt->right;
        while (succ->left) {
            succ = succ->left;
        }
        sdnt->gatorID = succ->gatorID;
        sdnt->gatorName = succ->gatorName;

        sdnt->right = removeHelper(sdnt->right, succ->gatorID, success);
    }

    sdnt->height = 1 + std::max(getHeight(sdnt->left), getHeight(sdnt->right));
    return rebalance(sdnt);
}

// Attempts to remove a new Student with provided data and returns if successful
bool AVLTree::remove(const std::string &ufid) {
    if (!isValidID(ufid) || !root) return false;
    bool success = false;
    root = removeHelper(root, ufid, success);
    return success;
}

// Helper to collect names for an inorder traversal
void AVLTree::inorderNameHelper(const Student* sdnt, std::vector<std::string> &vec) {
    if (!sdnt) return;
    inorderNameHelper(sdnt->left, vec);
    vec.push_back(sdnt->gatorName);
    inorderNameHelper(sdnt->right, vec);
}

// Helper to collect IDs for an inorder traversal
void AVLTree::inorderIDHelper(const Student* sdnt, std::vector<int> &vec) {
    if (!sdnt) return;
    inorderIDHelper(sdnt->left, vec);
    vec.push_back(std::stoi(sdnt->gatorID));
    inorderIDHelper(sdnt->right, vec);
}

// Helper to collect names for a preorder traversal
void AVLTree::preorderHelper(const Student* sdnt, std::vector<std::string> &vec) {
    if (!sdnt) return;
    vec.push_back(sdnt->gatorName);
    preorderHelper(sdnt->left, vec);
    preorderHelper(sdnt->right, vec);
}

// Helper to collect names for a postorder traversal
void AVLTree::postorderHelper(const Student* sdnt, std::vector<std::string> &vec) {
    if (!sdnt) return;
    postorderHelper(sdnt->left, vec);
    postorderHelper(sdnt->right, vec);
    vec.push_back(sdnt->gatorName);
}

// Populates vector with students via inorder traversal
void AVLTree::getInorderStudents(Student* sdnt, std::vector<Student*> &students) {
    if (!sdnt) return;
    getInorderStudents(sdnt->left, students);
    students.push_back(sdnt);
    getInorderStudents(sdnt->right, students);
}

// Removes the Nth student from the tree based on a inorder traversal vector of students
bool AVLTree::removeInorder(const int n) {
    if (n < 0) return false;

    std::vector<Student*> students;
    getInorderStudents(root, students);

    if (static_cast<size_t>(n) >= students.size()) return false;

    std::string target = students[n]->gatorID;
    return remove(target);
}

// Returns a vector of names via an inorder traversal
std::vector<std::string> AVLTree::inorder() {
    std::vector<std::string> names;
    inorderNameHelper(root, names);
    return names;
}

// Returns a vector of names via a preorder traversal
std::vector<std::string> AVLTree::preorder() {
    std::vector<std::string> names;
    preorderHelper(root, names);
    return names;
}

// Returns a vector of names via a postorder traversal
std::vector<std::string> AVLTree::postorder() {
    std::vector<std::string> names;
    postorderHelper(root, names);
    return names;
}

// Returns a vector of int IDs via an iorder traversal
std::vector<int> AVLTree::inorderIDs() {
    std::vector<int> ids;
    inorderIDHelper(root, ids);
    return ids;
}

// Yeah, this one wasn't necessary, but I made it anyway
int AVLTree::levelCount() {
    return getHeight(root);
}