#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <iterator>
#include <algorithm>
#include <fstream>


class Student {
public:
    std::string name;
    std::string fac;
    int pass;
    std::string date;
    std::string room;

    Student(const std::string& name, const std::string& fac, const int& pass, const std::string& date, const std::string& room): name(name), fac(fac), pass(pass), date(date), room(room) {}

    void showInfo(Student* student) {
	    std::cout << "Name: " << student->name << "\n";
	    std::cout << "Facility: " << student->fac << "\n";
	    std::cout << "ID pass: " << student->pass << "\n";
	    std::cout << "Birthday: " << student->date << "\n";
	    std::cout << "Room number: " << student->room << "\n";
    }
};

template<typename T>
struct Node {
        Student* student;
        T data;
        Node* left;
        Node* right;
        int height;

     	Node(Student* student, const T& data): student(student),data(data), left(nullptr), right(nullptr), height(1) {}
    };


template<typename T>
class AVLTree {
private:
    
    Node<T>* root;
    
    int height(Node<T>* node) const {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }
    
    int balanceFactor(Node<T>* node) const {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }
    
    void fixHeight(Node<T>* node) {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
    
    Node<T>* rotateRight(Node<T>* node) {
        Node<T>* leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;
        fixHeight(node);
        fixHeight(leftChild);
        return leftChild;
    }
    
    Node<T>* rotateLeft(Node<T>* node) {
        Node<T>* rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;
        fixHeight(node);
        fixHeight(rightChild);
        return rightChild;
    }
    
    Node<T>* balance(Node<T>* node) {
        fixHeight(node);
        if (balanceFactor(node) == 2) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        } else if (balanceFactor(node) == -2) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        return node;
    }
    
    Node<T>* insert(Node<T>* node, const T& data, Student* student) {
        if (node == nullptr) {
            return new Node(student, data);
        }
        if (data < node->data) {
            node->left = insert(node->left, data, student);
        } else {
            node->right = insert(node->right, data, student);
        }
        return balance(node);
    }
    
    Node<T>* findMin(Node<T>* node) const {
        if (node->left == nullptr) {
            return node;
        }
        return findMin(node->left);
    }
    
    Node<T>* removeMin(Node<T>* node) {
        if (node->left == nullptr) {
            return node->right;
        }
        node->left = removeMin(node->left);
        return balance(node);
    }
    
    Node<T>* remove(Node<T>* node, const T& data) {
        if (node == nullptr) {
            return nullptr;
        }
        if (data < node->data) {
            node->left = remove(node->left, data);
        } else if (data > node->data) {
            node->right = remove(node->right, data);
        } else {
            Node<T>* leftChild = node->left;
            Node<T>* rightChild = node->right;
            delete node;
            if (rightChild == nullptr) {
                return leftChild;
            }
            Node<T>* minNode = findMin(rightChild);
            minNode->right = removeMin(rightChild);
            minNode->left = leftChild;
            return balance(minNode);
        }
        return balance(node);
    }
    void printTree(Node<T>* root) {
            if (root == nullptr) return;

            printTree(root->left);
            std::cout << root->data << "  ";
            printTree(root->right);
    }
    Node<T>* contains(Node<T>* node, const T& value) const {
           if (!node)
                   return nullptr;
           if (value < node->data) {
                   return contains(node->left, value);
	   }else if (value > node->data) {
                   return contains(node->right, value);
	   }else {
                   return node;
	   }
    }
    

public:
    AVLTree(): root(nullptr) {}
    
    void insert(const T& data, Student* student) {
	    root = insert(root, data, student);
	
    }
    void remove(const T& data, Student* student) {
	    root = remove(root, data, student);
	
    }
    Node<T>* contains(const T& value) const {
	    return contains(root, value);
    }

    void printTree() {
	printTree(root);
    }

};




int main() {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    
    std::vector<int> allIds(1000000);
    for (int i = 0; i < 1000000; i++) {
        allIds[i] = i + 1;
    }
    //std::shuffle(allIds.begin(), allIds.end(), rng);

    std::ifstream firstNameFile("es.txt");
    std::vector<std::string> firstNames;
    std::string firstName;
    while (std::getline(firstNameFile, firstName)) {
        firstNames.push_back(firstName);
    }
    firstNameFile.close();
    
    std::ifstream surnameFile("ru.txt");
    std::vector<std::string> surnames;
    std::string surname;
    while (std::getline(surnameFile, surname)) {
        surnames.push_back(surname);
    }
    surnameFile.close();
    

    int minYear = 1960;
    int maxYear = 2006;
    int minMonth = 1;
    int maxMonth = 12;
    int minDay = 1;
    int maxDay = 31;

    std::vector<std::string> birthDates;
    std::uniform_int_distribution<> yearDist(minYear, maxYear);
    std::uniform_int_distribution<> monthDist(minMonth, maxMonth);
    std::uniform_int_distribution<> dayDist(minDay, maxDay);
    for (int i = 0; i < 10000; i++) {
        int year = yearDist(rng);
        int month = monthDist(rng);
        int day = dayDist(rng);
        std::string birthDate = std::to_string(year) + "-" + (month < 10 ? "0" : "") + std::to_string(month) + "-" + (day < 10 ? "0" : "") + std::to_string(day);
        birthDates.push_back(birthDate);
    }
    
    std::vector<std::string> courses = {"Computer Science", "Mathematics", "Physics", "Biology", "Chemistry"};
    std::vector<std::string> faculties = {"Faculty of Science", "Faculty of Arts", "Faculty of Engineering", "Faculty of Medicine"};
    std::vector<std::string> universities = {"Harvard University", "Stanford University", "Massachusetts Institute of Technology", "California Institute of Technology", "University of Cambridge", "University of Oxford", "ETH Zurich", "University of Tokyo", "SPbU", "MSU", "HSE", "MIPT"};

    std::vector<std::string> infoVec;
    for (int i = 0; i < 50000; i++) {
        std::uniform_int_distribution<> courseDist(0, courses.size()-1);
        std::uniform_int_distribution<> facultyDist(0, faculties.size()-1);
        std::uniform_int_distribution<> universityDist(0, universities.size()-1);
        std::string course = courses[courseDist(rng)];
        std::string faculty = faculties[facultyDist(rng)];
        std::string university = universities[universityDist(rng)];
        
        std::string info = course + " at the " + faculty + " of " + university;
        
        infoVec.push_back(info);
    }

    std::vector<std::string> roomVec;
    for (int i = 0; i < 50000; i++) {
        std::uniform_int_distribution<> dist(1, 23);
        std::uniform_int_distribution<> dist2(101, 1499);
        int number1 = dist(rng);
        int number2 = dist2(rng);

        std::string numberStr = std::to_string(number1) + "/" + std::to_string(number2);
        roomVec.push_back(numberStr);
    }

    AVLTree<int> avl_int;
    AVLTree<std::string> avl_string;
    std::vector<Student*> studentVec;
    for (int i=0; i<100;++i) {
        std::string name = firstNames[i] + " " + surnames[i];
        std::string fac = infoVec[rand() % 50000];
        int pass = allIds[i];
        std::string date = birthDates[rand() % 10000];
	std::string room = roomVec[rand() % 50000];
	Student* student = new Student(name, fac, pass, date, room);
        studentVec.push_back(student);
        avl_int.insert(pass, student);
        avl_string.insert(name, student);
    }
   int number;
   while (number != 3) {
	std::cout << "If u want to exit just enter 3" << "\n";   
   	std::cout << "Search id(1)/name(2)" << "\n"; 
   	std::cin >> number;
   	if (number == 1) {
	   	std::cout << "Enter id" << "\n";
	   	int id;
	   	std::cin >> id;
	   	Node<int>* node = avl_int.contains(id);
	   	if (node != nullptr) {
		   	node->student->showInfo(node->student);
	   	}
   	}else if (number == 2) {
	   	std::cout << "Enter name" << "\n";
		std::string name;
		std::getline(std::cin >> std::ws, name);	
	   	Node<std::string>* node = avl_string.contains(name);
		if (node != nullptr) {
			node->student->showInfo(node->student);
		}
   	}
   }	
}
