// Sean Flynn
// 12/10/23
// SNHU CS-300 - Project 2
// Courses Manager Program


#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>


using namespace std;

// Course structure
struct Course {
	string courseId;
	string courseName;
	vector<string> preReqs;
};

// Node Structure
struct Node {
	Course course;
	Node *left;
	Node *right;
	
	// Constructor
	Node() : left(nullptr), right(nullptr) {
	}
	
	// Constructor - course
	Node(Course t_course) :
		Node() {
			course = t_course;
		}
};

// CLASS - Binary Search Tree
class BinarySearchTree {
	private:
		Node* root;
		
		void addNode(Node* node, Course course);
		void inOrder(Node* node);
	
	public:
		BinarySearchTree();
		void inOrder();
		void insert(Course course);
		Course search(string t_key);
};

// Constructor
BinarySearchTree::BinarySearchTree() {
	root = nullptr;
}

// In order printing
void BinarySearchTree::inOrder() {
	inOrder(root);
}

// Recursive function for in order printing
void BinarySearchTree::inOrder(Node* node) {
	if (node->left != nullptr) {
    	inOrder(node->left);
	}
  
  cout << node->course.courseId << ", " << node->course.courseName;
  for (int i = 0; i < node->course.preReqs.size(); i++) {
  	cout << ", " << node->course.preReqs.at(i);
  }
  cout << endl;
  
  if (node->right != nullptr) {
    inOrder(node->right);
  }
}

// Search for a course
Course BinarySearchTree::search(string t_key) {
	// Search for a node
	// Start at root node 
	Node* currentNode = root;
	Course searchCourse;

	// Loop left or right depending until the value is found
	while (currentNode != nullptr) {
		
		if (currentNode->course.courseId == t_key) {
			searchCourse = currentNode->course;
			break;
		}
    // Not found, determine travel direction
		else if (currentNode->course.courseId > t_key) {
			currentNode = currentNode->left;
		}
		else {
			currentNode = currentNode->right;
		}
  }
  return searchCourse;
}

// Starting function to build the tree
void BinarySearchTree::insert(Course course) {
  if (root == nullptr) {
    root = new Node(course);
    return;
  }
  else {
    addNode(root, course);
  }
}

// Recursive function to build the tree
void BinarySearchTree::addNode(Node* node, Course course) {
  // Logic to insert nodes into the BST
  
  // Check left node first - if null then make node, otherwise recure
  if (node->course.courseId >= course.courseId) {
    if (node->left == nullptr) {
      node->left = new Node(course);
    }
    else {
      addNode(node->left, course);
    }
  }
  // Else check right node - if null then make node, otherwise recurse
  else {
    if (node->right == nullptr) {
      node->right = new Node(course);
    }
    else {
      addNode(node->right, course);
    }
  }
}


// -- Function Declartions --
void loadCourse(string csvPath, BinarySearchTree* bts);
vector<string> parseCsv(string line);


// -- Function Definitions --
// Function to load the course information
void loadCourse(string csvPath, BinarySearchTree* bst) {
	ifstream file(csvPath);
	string line;
	
	// Read the file by line, crack the lines into tokens, assign the tokens to course
	while (getline(file, line)) {
		Course course;
		vector<string> tokens = parseCsv(line);
		
		// Assign name and Id
		course.courseId   = tokens[0];
		course.courseName = tokens[1];
		
		// Assign remaining tokens to prereqs
		for (int i = 2; i < tokens.size(); i++) {
			course.preReqs.push_back(tokens[i]);
		}
		
		// FIXME - add token to bst
		bst->insert(course);
	}
	
}

// Function to split the csv lines into tokens
vector<string> parseCsv(string line) {
	vector<string> tokens;
	
	istringstream crack(line);
	string token;
	
	while (getline(crack, token, ',')) {
		tokens.push_back(token);
	}
	
	return tokens;
} 

// -- Main --
int main(int argc, char* argv[]){
	// Define the binary search tree
	BinarySearchTree* bst;
	bst = new BinarySearchTree();
	
	
	int userChoice = 0;
	// Menu
	while (userChoice != 4) {
		cout << "-- Menu --" << endl;
		cout << "1: Load course data" << endl;
		cout << "2: Print ordered courses" << endl;
		cout << "3: Course Search" << endl;
		cout << "4: Exit" << endl;
		cin >> userChoice;
		
		switch (userChoice) {
		case 1: {
			// Load in the course data
			string csvFile = "";
			string defaultCsv = "courseInfo.csv";
			cout << "Enter the name of the csv file or enter 1 to use default. " << endl;
			cin >> csvFile;
			
			// Use either user file or default
			if (csvFile == "1") {
				loadCourse(defaultCsv, bst);
			}
			else {
				loadCourse(csvFile, bst);
			}
			break;
		}
		case 2: {
			// Print the courses
			bst->inOrder();
			break;
		}
		case 3: {
			// Search for a course
			string key;
			cout << "Please enter course ID: " << endl;
			cin >> key;
			
			Course course = bst->search(key);
			// If the course if found print it's information
			if (!course.courseId.empty()) {
				cout << course.courseId << ", " << course.courseName;
				for (int i = 0; i < course.preReqs.size(); i++) {
					cout << ", " << course.preReqs.at(i);
				}
				cout << endl;
			}
			else {
				cout << "Course not found." <<  endl;
			}
			
			break;
		}
		case 4: {
			// Exit the program
			cout << "Exiting";
			break;
		}
		}
	}
}