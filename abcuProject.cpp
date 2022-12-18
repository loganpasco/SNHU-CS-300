//============================================================================
// Name        : ABCU Project2 .cpp
// Author      : Pasco Logan  
// Version     : 1.0
// Copyright   : Copyright @ 2017 SNHU CODE WAS USED IN THIS PROJECT  
// Description : This program is designed to import data from a file and output a course list 
//               in alphabetical order, as well as a specific course and any requirements.
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> 
#include <time.h>
#include <fstream>
#include <sstream>
#include <vector>


//#include "CSVparser.hpp"

using namespace std;

struct Course
{
    string courseId; // identifier
    string title;
    string preReq1;
    string preReq2;
    vector<string> preReqs;
};

// Structure for tree node
struct Node
{
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node()
    {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course t_course)
    {
        left = nullptr;
        right = nullptr;
        course = t_course;
    }
};

// Binary Search Tree 

/**
 * Define a class implement a binary search tree
 */

class BinarySearchTree
{

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Course course);
    Course Search(string courseId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
}


BinarySearchTree::~BinarySearchTree()
{
    // delete each node iteratively from the root
}

// Traverse the tree in order

void BinarySearchTree::InOrder()
{
    // inOrder function and pass root
    this->inOrder(root);
}

void BinarySearchTree::Insert(Course course)
{

    if (root == nullptr)
    {
        root = new Node(course);
    }
    else
        
    {
        this->addNode(root, course); // add Node root and course
    }
}

 // Search for a course
Course BinarySearchTree::Search(string courseId)
{
    
    Node* current = root; // set current node equal to root

     // Loop downhill continuously until bottom is reached or a matching courseId is discovered.
    while (current != nullptr)
    {
        // If current node matches, return it
        if (current->course.courseId.compare(courseId) == 0)
        {
            return current->course;
        }
        // If course is smaller, traverse left subtree
        if (courseId.compare(current->course.courseId) < 0)
        {
            current = current->left;
        }
        // else larger so traverse right
        else
        {
            current = current->right;
        }
    }

    Course course;
    return course;
}


void BinarySearchTree::addNode(Node* node, Course course)
{
    // if node is greater then add to left
    if (node->course.courseId.compare(course.courseId) > 0)
    {
       
        if (node->left == nullptr)// if no left node
        {
            node->left = new Node(course);// this node becomes left
        }
        // else recurse down the left node
        else
        {
            this->addNode(node->left, course);
        }
    }
    else
    {
       
        if (node->right == nullptr) // if no right node
        {
            node->right = new Node(course);// this node becomes right
        }
        // else recurse down the right node
        else
        {
            this->addNode(node->right, course);
        }
    }
}

void BinarySearchTree::inOrder(Node* node)
{
   

    if (node != nullptr)// if node is not equal to null ptr
    {

        inOrder(node->left); // Traverse left side first

        cout << node->course.courseId << ", " << node->course.title << endl;

        inOrder(node->right); // Traverse right side after each level's been checked
    }
}


// Static methods used for testing

void displayCourse(Course& course)
{
    cout << course.courseId << ", " << course.title << endl;

    if (!(course.preReq2 == " "))
    {

        cout << "Required Prerequisites: " << course.preReq1 << ", " << course.preReq2;
    }
    else
    {
        cout << "Required Prerequisites: " << course.preReq1;
    }
}


void loadCourses(string csvPath, BinarySearchTree* bst)
{
    Course course;

    cout << "Loading file " << csvPath << endl;

    ifstream file;
    string line;

    try
    {
        file.open(csvPath);
        if (file.is_open())
        {
            while (file.good())
            {
                cout << line << endl;

                while (getline(file, line))
                {
                    stringstream ss(line);

                    string courseID;
                    string title;
                    string preReq1;
                    string preReq2;

                    getline(ss, courseID, ',');
                    getline(ss, title, ',');
                    getline(ss, preReq1, ',');
                    getline(ss, preReq2, ',');

                    course.courseId = courseID;
                    course.title = title;
                    course.preReq1 = preReq1;
                    course.preReq2 = preReq2;

                    course.preReqs.push_back(preReq1);
                    course.preReqs.push_back(preReq2);

                    bst->Insert(course);
                    ss.clear();
                }
            }
        }
    }
    catch (exception& e)
    {
        cerr << e.what() << endl;
    }
}

int main(int argc, char* argv[])
{

    // process command line arguments
    string csvPath, courseKey;
    Course course;

    switch (argc)
    {
    case 2:
        csvPath = argv[1]; // courseKey = course.courseId;
       
        break;
    case 3:
        csvPath = argv[1];// courseKey = course.courseId;
       
        break;
    default:
        csvPath = "abcuClasses.txt";
        
    }

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();

    int choice = 0;
    while (choice != 9)
    {
        if (!(choice <= 3) && (choice > 0))
        {
            cout << endl;
            cout << choice << " is not a valid option.";
            cout << endl;
        }

        cout << endl;
        cout << "==============================" << endl;
        cout << "Welcome to the course planner." << endl;
        cout << "==============================" << endl;
        cout << endl;
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {

        case 1:
            loadCourses(csvPath, bst);
            break;

        case 2:

            if (bst == NULL)
            {
                cout << "Data not loaded.";
            }
            else
                cout << "This is an example of a schedule:\n"
                << endl;
            bst->InOrder(); //Print course ID sequentially.
            break;

        case 3:
            cout << "What course information would you like? ";
            cin >> courseKey;
            cout << "\n";

            for (int i = 0; i < courseKey.length(); i++){ //Loop to make all user inputs upper case 
                courseKey[i] = toupper(courseKey[i]);
            }

            transform(courseKey.begin(), courseKey.end(), courseKey.begin(), ::toupper);

            course = bst->Search(courseKey);

            if (!course.courseId.empty())
            {
                displayCourse(course);
            }
            else
            {
                cout << "Course " << courseKey << " not found." << endl;
            }
            break;
        }
    }

    cout << "Thank you for using the course Planner!" << endl;

    return 0;
}