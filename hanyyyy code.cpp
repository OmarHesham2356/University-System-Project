#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

// Student class for storing student information
class Student {
public:
    int studentID;
    string name;
    string email;
    string phone;
    string address;
    string password;
    Student* next;

    Student(int id, string n, string e, string p, string a, string pwd)
        : studentID(id), name(n), email(e), phone(p), address(a), password(pwd), next(nullptr) {}
};

// Course class for storing course information
class Course {
public:
    int courseID;
    string courseName;
    int credits;
    string instructor;
    Course* left;
    Course* right;

    Course(int id, string name, int c, string inst)
        : courseID(id), courseName(name), credits(c), instructor(inst), left(nullptr), right(nullptr) {}
};

// Enrollment record for double linked list
class EnrollmentRecord {
public:
    int studentID;
    int courseID;
    string semester;
    string grade;
    EnrollmentRecord* prev;
    EnrollmentRecord* next;

    EnrollmentRecord(int sid, int cid, string sem, string g)
        : studentID(sid), courseID(cid), semester(sem), grade(g), prev(nullptr), next(nullptr) {}
};

// Prerequisite structure
class Prerequisite {
public:
    stack<int> prerequisites; // Stack for prerequisites
};

// Waitlist structure
class Waitlist {
public:
    queue<int> studentQueue; // Queue for students on waitlist
};

// Hash table for fast access
class HashTable {
private:
    unordered_map<int, Course*> courseMap; // Hash table for courses

public:
    void addCourseToHash(Course* course) {
        courseMap[course->courseID] = course;
    }

    Course* searchWithHashing(int courseID) {
        if (courseMap.find(courseID) != courseMap.end())
            return courseMap[courseID];
        return nullptr;
    }
};

// Student Records Management using Single Linked List
class StudentManager {
private:
    Student* head;

public:
    StudentManager() : head(nullptr) {}

    void add(int id, string name, string email, string phone, string address, string password) {
        Student* newStudent = new Student(id, name, email, phone, address, password);
        if (!head) {
            head = newStudent;
            return;
        }
        if (id < head->studentID) {
            newStudent->next = head;
            head = newStudent;
            return;
        }
        Student* current = head;
        while (current->next && current->next->studentID < id) {
            current = current->next;
        }
        newStudent->next = current->next;
        current->next = newStudent;
    }

    void remove(int id) {
        if (!head) return;
        if (head->studentID == id) {
            Student* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Student* current = head;
        while (current->next && current->next->studentID != id) {
            current = current->next;
        }
        if (current->next) {
            Student* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
    }

    void display() {
        Student* current = head;
        while (current) {
            cout << "ID: " << current->studentID << endl
                 << "Name: " << current->name << endl
                 << "Email: " << current->email << endl
                 << "Phone: " << current->phone << endl
                 << "Address: " << current->address << endl << endl;
            current = current->next;
        }
    }

    Student* search(int id) {
        Student* current = head;
        while (current && current->studentID != id) {
            current = current->next;
        }
        return current;
    }

    // Binary Search for Student by ID (if sorted)
    int binarySearch(vector<Student>& students, int studentID) {
        int left = 0, right = students.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (students[mid].studentID == studentID) {
                return mid;  // Found the student
            }
            if (students[mid].studentID < studentID) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;  // Student not found
    }
};

// Course Management using Binary Search Tree
class CourseManager {
private:
    Course* root;

    Course* insertRecursive(Course* node, int id, string name, int credits, string instructor) {
        if (!node) {
            return new Course(id, name, credits, instructor);
        }
        if (id < node->courseID) {
            node->left = insertRecursive(node->left, id, name, credits, instructor);
        } else if (id > node->courseID) {
            node->right = insertRecursive(node->right, id, name, credits, instructor);
        }
        return node;
    }

    Course* findMin(Course* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    Course* deleteRecursive(Course* node, int id) {
        if (!node) return nullptr;
        if (id < node->courseID) {
            node->left = deleteRecursive(node->left, id);
        } else if (id > node->courseID) {
            node->right = deleteRecursive(node->right, id);
        } else {
            if (!node->left) {
                Course* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Course* temp = node->left;
                delete node;
                return temp;
            }
            Course* temp = findMin(node->right);
            node->courseID = temp->courseID;
            node->courseName = temp->courseName;
            node->credits = temp->credits;
            node->instructor = temp->instructor;
            node->right = deleteRecursive(node->right, temp->courseID);
        }
        return node;
    }

public:
    CourseManager() : root(nullptr) {}

    void addCourse(int id, string name, int credits, string instructor) {
        root = insertRecursive(root, id, name, credits, instructor);
    }

    void dropCourse(int id) {
        root = deleteRecursive(root, id);
    }

    Course* searchCourse(int id) {
        Course* current = root;
        while (current) {
            if (id == current->courseID) {
                return current;
            } else if (id < current->courseID) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return nullptr;
    }
};

// Enrollment History (DLL)
class EnrollmentHistory {
private:
    EnrollmentRecord* head;
    EnrollmentRecord* tail;

public:
    EnrollmentHistory() : head(nullptr), tail(nullptr) {}

    void add(int studentID, int courseID, string semester, string grade) {
        EnrollmentRecord* record = new EnrollmentRecord(studentID, courseID, semester, grade);
        if (!head) {
            head = tail = record;
        } else {
            record->prev = tail;
            tail->next = record;
            tail = record;
        }
    }

    void view(int studentID) {
        EnrollmentRecord* current = head;
        while (current) {
            if (current->studentID == studentID) {
                cout << "Course ID: " << current->courseID << endl
                     << "Semester: " << current->semester << endl
                     << "Grade: " << current->grade << endl << endl;
            }
            current = current->next;
        }
    }

    bool hasCompleted(int studentID, int courseID) {
        EnrollmentRecord* current = head;
        while (current) {
            if (current->studentID == studentID && current->courseID == courseID) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

// Prerequisite Validation Using Stack
class PrerequisiteManager {
public:
    stack<int> prerequisites;

    void validatePrerequisites(int courseID, EnrollmentHistory& enrollmentHistory, int studentID) {
        stack<int> tempStack = prerequisites;  // Use a temporary stack to avoid modifying the original stack
        bool isEligible = true;
        
        cout << "Checking prerequisites for course " << courseID << "...\n";
        while (!tempStack.empty()) {
            int prereq = tempStack.top();
            if (!enrollmentHistory.hasCompleted(studentID, prereq)) {
                cout << "Missing prerequisite: " << prereq << endl;
                isEligible = false;
            }
            tempStack.pop();
        }

        if (isEligible) {
            cout << "Student is eligible to register for course " << courseID << endl;
        } else {
            cout << "Student is not eligible due to missing prerequisites.\n";
        }
    }
};

// Main Function
int main() {
    // Managers
    StudentManager studentManager;
    CourseManager courseManager;
    EnrollmentHistory enrollmentHistory;
    PrerequisiteManager prerequisiteManager;
    HashTable hashTable;

    // Example usage
    studentManager.add(1, "Alice", "alice@example.com", "1234567890", "123 Main St", "password123");
    studentManager.add(2, "Bob", "bob@example.com", "0987654321", "456 Elm St", "password456");

    courseManager.addCourse(101, "Math", 3, "Dr. Smith");
    courseManager.addCourse(102, "Physics", 4, "Dr. Johnson");

    // Adding to hash table
    hashTable.addCourseToHash(new Course(101, "Math", 3, "Dr. Smith"));
    hashTable.addCourseToHash(new Course(102, "Physics", 4, "Dr. Johnson"));

    enrollmentHistory.add(1, 101, "Fall 2023", "A");

    // Waitlist
    Waitlist waitlist;
    waitlist.studentQueue.push(2);

    // Prerequisites
    prerequisiteManager.prerequisites.push(101);
    prerequisiteManager.validatePrerequisites(102, enrollmentHistory, 1);

    cout << "Students:" << endl;
    studentManager.display();

    cout << "Enrollments for student 1:" << endl;
    enrollmentHistory.view(1);

    return 0;
}
