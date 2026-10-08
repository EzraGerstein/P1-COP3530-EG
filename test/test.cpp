// //Ezra Gerstein
// //76844003
//
// #include <catch2/catch_test_macros.hpp>
// #include <iostream>
// #include <algorithm>
// #include <random>
//
// #include "AVLTree.h"
//
// using namespace std;
//
// TEST_CASE("AVL - Test 5 Unsuccessful Commands", "[avl][validation]") {
//     AVLTree tree;
//
//     REQUIRE(tree.insert("Bi11y", "12345678") == false);
//     REQUIRE(tree.insert("Johnson", "123456789") == false);
//     REQUIRE(tree.insert("Billy", "1234567a") == false);
//     REQUIRE(tree.insert("Bob", "1234567 ") == false);
//     REQUIRE(tree.insert("Billy", "1234567?") == false);
//
//     REQUIRE(tree.insert("Jeff", "11223345") == true);
//     REQUIRE(tree.insert("Jefferson", "11223345") == false);
//     REQUIRE(tree.remove("87654321") == false);
//     REQUIRE(tree.remove("987654321") == false);
//     REQUIRE(tree.insert("   ", "12345678") == false);
//     REQUIRE(tree.insert("   Bob", "11223344") == true);
// }
//
// TEST_CASE("AVL - Test Edge Cases", "[avl][edge]") {
//     AVLTree tree;
//
//     REQUIRE(tree.remove("12345678") == false);
//     REQUIRE(tree.removeInorder(0) == false);
//     REQUIRE(tree.levelCount() == 0);
//     REQUIRE(tree.searchID("12345678").empty());
//     REQUIRE(tree.searchName("Nobody").empty());
//
//     tree.insert("Alice", "12345678");
//     REQUIRE(tree.removeInorder(-1) == false);
//     REQUIRE(tree.removeInorder(5) == false);
//     REQUIRE(tree.remove("99999999") == false);
// }
//
// TEST_CASE("AVL - Test All Four Rotations", "[avl][rotations]") {
//     SECTION("Left-Left Case Use Right Rotation") {
//         AVLTree tree;
//         tree.insert("Eight", "80000000");
//         tree.insert("Five",  "50000000");
//         tree.insert("One",   "10000000");
//
//         vector<string> expected = {"One", "Five", "Eight"};
//         REQUIRE(tree.inorder() == expected);
//         REQUIRE(tree.levelCount() == 2);
//     }
//
//     SECTION("Right-Right Case Use Left Rotation") {
//         AVLTree tree;
//         tree.insert("Three", "30000000");
//         tree.insert("Four",  "40000000");
//         tree.insert("Seven", "70000000");
//
//         vector<string> expected = {"Three", "Four", "Seven"};
//         REQUIRE(tree.inorder() == expected);
//         REQUIRE(tree.levelCount() == 2);
//     }
//
//     SECTION("Left-Right Case Use Left-Right Rotation") {
//         AVLTree tree;
//         tree.insert("Four",  "40000000");
//         tree.insert("One",   "10000000");
//         tree.insert("Three", "30000000");
//
//         vector<string> expected = {"One", "Three", "Four"};
//         REQUIRE(tree.inorder() == expected);
//         REQUIRE(tree.levelCount() == 2);
//     }
//
//     SECTION("Right-Left Case Use Right-Left Rotation") {
//         AVLTree tree;
//         tree.insert("Seven", "70000000");
//         tree.insert("Nine",  "90000000");
//         tree.insert("Eight", "80000000");
//
//         vector<string> expected = {"Seven", "Eight", "Nine"};
//         REQUIRE(tree.inorder() == expected);
//         REQUIRE(tree.levelCount() == 2);
//     }
// }
//
// TEST_CASE("AVL - Test Three Deletion Cases", "[avl][deletion]") {
//     AVLTree tree;
//     tree.insert("Five",  "50000000");
//     tree.insert("Three", "30000000");
//     tree.insert("Seven","70000000");
//     tree.insert("Two", "20000000");
//     tree.insert("Four",  "40000000");
//     tree.insert("Six",  "60000000");
//     tree.insert("Eight", "80000000");
//
//     SECTION("Delete Node with 0 Children") {
//         REQUIRE(tree.remove("20000000") == true);
//         vector<string> expected = {"Three", "Four", "Five", "Six", "Seven", "Eight"};
//         REQUIRE(tree.inorder() == expected);
//     }
//
//     SECTION("Delete Node with 1 Child") {
//         tree.remove("20000000");
//         REQUIRE(tree.remove("30000000") == true);
//         vector<string> expected = {"Four", "Five", "Six", "Seven", "Eight"};
//         REQUIRE(tree.inorder() == expected);
//     }
//
//     SECTION("Delete Node with 2 Children") {
//         REQUIRE(tree.remove("50000000") == true);
//         vector<string> expected = {"Two", "Three", "Four", "Six", "Seven", "Eight"};
//         REQUIRE(tree.inorder() == expected);
//     }
// }
//
// TEST_CASE("AVL - Insert 100, Remove 10", "[avl][large]") {
//     AVLTree tree;
//     vector<int> expectedOutput;
//
//     while (expectedOutput.size() < 100) {
//         int randomID = 10000000 + (rand() % 90000000);
//         if (count(expectedOutput.begin(), expectedOutput.end(), randomID) == 0) {
//             expectedOutput.push_back(randomID);
//             REQUIRE(tree.insert("Student", to_string(randomID)));
//         }
//     }
//
//     for (int i = 0; i < 10; ++i) {
//         REQUIRE(tree.remove(to_string(expectedOutput[i])));
//     }
//
//     vector<int> remainingExpected(expectedOutput.begin() + 10, expectedOutput.end());
//     sort(remainingExpected.begin(), remainingExpected.end());
//
//     REQUIRE(tree.inorderIDs() == remainingExpected);
// }