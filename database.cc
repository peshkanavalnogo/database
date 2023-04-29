#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>


template<typename T>
class AVLTree {
private:
    struct Node {
        int index;
        T data;
        Node* left;
        Node* right;
        int height;
        
        Node(const T& data, const int& index): data(data), index(index), left(nullptr), right(nullptr), height(1) {}
    };
    
    Node* root;
    
    int height(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }
    
    int balanceFactor(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }
    
    void fixHeight(Node* node) {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
    
    Node* rotateRight(Node* node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;
        fixHeight(node);
        fixHeight(leftChild);
        return leftChild;
    }
    
    Node* rotateLeft(Node* node) {
        Node* rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;
        fixHeight(node);
        fixHeight(rightChild);
        return rightChild;
    }
    
    Node* balance(Node* node) {
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
    
    Node* insert(Node* node, const T& data, const int index) {
        if (node == nullptr) {
            return new Node(data, index);
        }
        if (data < node->data) {
            node->left = insert(node->left, data, index);
        } else {
            node->right = insert(node->right, data, index);
        }
        return balance(node);
    }
    
    Node* findMin(Node* node) const {
        if (node->left == nullptr) {
            return node;
        }
        return findMin(node->left);
    }
    
    Node* removeMin(Node* node) {
        if (node->left == nullptr) {
            return node->right;
        }
        node->left = removeMin(node->left);
        return balance(node);
    }
    
    Node* remove(Node* node, const T& data) {
        if (node == nullptr) {
            return nullptr;
        }
        if (data < node->data) {
            node->left = remove(node->left, data);
        } else if (data > node->data) {
            node->right = remove(node->right, data);
        } else {
            Node* leftChild = node->left;
            Node* rightChild = node->right;
            delete node;
            if (rightChild == nullptr) {
                return leftChild;
            }
            Node* minNode = findMin(rightChild);
            minNode->right = removeMin(rightChild);
            minNode->left = leftChild;
            return balance(minNode);
        }
        return balance(node);
    }
    

    bool contains(const T& data) const {
        Node* current = root;
        while (current != nullptr) {
            if (data == current->data) {
                return true;
            } else if (data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return false;
    }

};

class Student {
public:
    std::string name;
    std::string fac;
    int pass;
    std::string date;
    std::string room;
    
    Person(const std::string& name, const std::string& fac, const std::string& pass, const std::string& date, const std::string& room) : name(name), fac(fac), pass(pass), date(date), room(room) {}
};

int main() {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    
    std::vector<int> allIds(1000000);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        allIds[i] = i + 1;
    }
    std::shuffle(allIds.begin(), allIds.end(), rng);

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
    std::vector<Student> studentVec;
    for (int i=0; i<100000, ++i) {
        std::string name = firstNames[rand() % 9000] + " " + surnames[rand() % 9000];
        std::string fac = infoVec[rand() % 50000];
        int pass = allIds[rand() % 1000000];
        std::string date = birthDates[rand() % 10000];
	std::string room = roomVec[rand() % 50000];
        avl_int.insert(pass, i);
        avl_string.insert(name, i);
        Student student(name, fac, pass, date, room);
        studentVec.push_back(student);
    }
        
}
