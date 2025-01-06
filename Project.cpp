#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include <list>
#include <vector>
using namespace std;

// Forward declarations
class Student;
class Course;
class EnrollmentRecord;

// Student Node for Single Linked List
struct StudentNode {
    int studentId;
    string name;
    string email;
    string phone;
    string address;
    string password;
    StudentNode* next;
    
    StudentNode(int id, string n, string e, string p, string a, string pwd) 
        : studentId(id), name(n), email(e), phone(p), address(a), password(pwd), next(nullptr) {}
};

// Course Node for Binary Search Tree
struct CourseNode {
    int courseId;
    string courseName;
    int credits;
    string instructor;
    CourseNode* left;
    CourseNode* right;
    
    CourseNode(int id, string name, int c, string inst) 
        : courseId(id), courseName(name), credits(c), instructor(inst), left(nullptr), right(nullptr) {}
};

// Enrollment Record Node for Double Linked List
struct EnrollmentNode {
    int studentId;
    int courseId;
    string semester;
    string grade;
    EnrollmentNode* prev;
    EnrollmentNode* next;
    
    EnrollmentNode(int sid, int cid, string sem) 
        : studentId(sid), courseId(cid), semester(sem), grade(""), prev(nullptr), next(nullptr) {}
};

// Student Records Management (Single Linked List)
class StudentRecords {
private:
    StudentNode* head;
    
public:
    StudentRecords() : head(nullptr) {}
    
    void add(int id, string name, string email, string phone, string address, string password) {
        StudentNode* newNode = new StudentNode(id, name, email, phone, address, password);
        if (!head || head->studentId > id) {
            newNode->next = head;
            head = newNode;
            return;
        }
        
        StudentNode* current = head;
        while (current->next && current->next->studentId < id) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    
    void remove(int id) {
        if (!head) return;
        
        if (head->studentId == id) {
            StudentNode* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        
        StudentNode* current = head;
        while (current->next && current->next->studentId != id) {
            current = current->next;
        }
        
        if (current->next) {
            StudentNode* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
    }
    
    void display() {
        StudentNode* current = head;
        while (current) {
            cout << "ID: " << current->studentId << "\nName: " << current->name 
                 << "\nEmail: " << current->email << "\nPhone: " << current->phone << "\n\n";
            current = current->next;
        }
    }

    StudentNode* searchStudent(int id) {
        StudentNode* current = head;
        while (current) {
            if (current->studentId == id) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void updateStudent(int id, string email, string phone, string address) {
        StudentNode* student = searchStudent(id);
        if (student) {
            student->email = email;
            student->phone = phone;
            student->address = address;
            cout << "Student updated successfully!" << endl;
        } else {
            cout << "Student not found!" << endl;
        }
    }
};

// Course Records Management (Binary Search Tree)
class CourseRecords {
private:
    CourseNode* root;
    
    CourseNode* insertRecursive(CourseNode* node, int id, string name, int credits, string instructor) {
        if (!node) {
            return new CourseNode(id, name, credits, instructor);
        }
        
        if (id < node->courseId) {
            node->left = insertRecursive(node->left, id, name, credits, instructor);
        } else if (id > node->courseId) {
            node->right = insertRecursive(node->right, id, name, credits, instructor);
        }
        
        return node;
    }
    
    CourseNode* findMin(CourseNode* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }
    
    CourseNode* deleteRecursive(CourseNode* node, int id) {
        if (!node) return nullptr;
        
        if (id < node->courseId) {
            node->left = deleteRecursive(node->left, id);
        } else if (id > node->courseId) {
            node->right = deleteRecursive(node->right, id);
        } else {
            if (!node->left) {
                CourseNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                CourseNode* temp = node->left;
                delete node;
                return temp;
            }
            
            CourseNode* temp = findMin(node->right);
            node->courseId = temp->courseId;
            node->courseName = temp->courseName;
            node->credits = temp->credits;
            node->instructor = temp->instructor;
            node->right = deleteRecursive(node->right, temp->courseId);
        }
        return node;
    }
    
public:
    CourseRecords() : root(nullptr) {}
    
    void addCourse(int id, string name, int credits, string instructor) {
        root = insertRecursive(root, id, name, credits, instructor);
    }
    
    void dropCourse(int id) {
        root = deleteRecursive(root, id);
    }

    CourseNode* searchCourse(int id) {
        CourseNode* current = root;
        while (current) {
            if (id == current->courseId) {
                return current;
            } else if (id < current->courseId) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return nullptr;
    }

    void displayCourses(CourseNode* node) {
        if (node) {
            displayCourses(node->left);
            cout << "Course ID: " << node->courseId << "\nName: " << node->courseName 
                 << "\nCredits: " << node->credits << "\nInstructor: " << node->instructor << "\n\n";
            displayCourses(node->right);
        }
    }
};

// Course Enrollment History (Double Linked List)
class EnrollmentHistory {
private:
    EnrollmentNode* head;
    EnrollmentNode* tail;
    
public:
    EnrollmentHistory() : head(nullptr), tail(nullptr) {}
    
    void add(int studentId, int courseId, string semester) {
        EnrollmentNode* newNode = new EnrollmentNode(studentId, courseId, semester);
        
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    void view(int studentId) {
        EnrollmentNode* current = head;
        while (current) {
            if (current->studentId == studentId) {
                cout << "Course ID: " << current->courseId 
                     << " | Semester: " << current->semester 
                     << " | Grade: " << current->grade << "\n";
            }
            current = current->next;
        }
    }

    void updateGrade(int studentId, int courseId, string grade) {
        EnrollmentNode* current = head;
        while (current) {
            if (current->studentId == studentId && current->courseId == courseId) {
                current->grade = grade;
                cout << "Grade updated successfully!" << endl;
                return;
            }
            current = current->next;
        }
        cout << "Enrollment not found!" << endl;
    }

    void removeEnrollment(int studentId, int courseId) {
        EnrollmentNode* current = head;
        while (current) {
            if (current->studentId == studentId && current->courseId == courseId) {
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }
                if (current->next) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }
                delete current;
                cout << "Enrollment removed successfully!" << endl;
                return;
            }
            current = current->next;
        }
        cout << "Enrollment not found!" << endl;
    }
};

// Course Prerequisites Management (Stack)
class PrerequisiteChecker {
private:
    unordered_map<int, stack<int>> coursePrereqs;
    
public:
    bool validatePrerequisites(int courseId, int studentId, EnrollmentHistory& history) {
        if (coursePrereqs.find(courseId) == coursePrereqs.end()) {
            return true;  // No prerequisites
        }
        
        stack<int> prereqs = coursePrereqs[courseId];
        // Implementation would check student's enrollment history against prerequisites
        return true;  // Placeholder
    }

    void addPrerequisite(int courseId, int prerequisiteId) {
        coursePrereqs[courseId].push(prerequisiteId);
    }

    void displayPrerequisites(int courseId) {
        if (coursePrereqs.find(courseId) == coursePrereqs.end()) {
            cout << "No prerequisites for this course." << endl;
        } else {
            stack<int> prereqs = coursePrereqs[courseId];
            cout << "Prerequisites for Course ID " << courseId << ":\n";
            while (!prereqs.empty()) {
                cout << prereqs.top() << endl;
                prereqs.pop();
            }
        }
    }
};

// Course Waitlist Management (Queue)
class WaitlistManager {
private:
    unordered_map<int, queue<int>> courseWaitlists;
    
public:
    void enqueue(int courseId, int studentId) {
        courseWaitlists[courseId].push(studentId);
    }
    
    int dequeue(int courseId) {
        if (courseWaitlists[courseId].empty()) {
            return -1;
        }
        
        int studentId = courseWaitlists[courseId].front();
        courseWaitlists[courseId].pop();
        return studentId;
    }

    void displayWaitlist(int courseId) {
        if (courseWaitlists[courseId].empty()) {
            cout << "No students on the waitlist for this course." << endl;
        } else {
            queue<int> waitlist = courseWaitlists[courseId];
            cout << "Waitlist for Course ID " << courseId << ":\n";
            while (!waitlist.empty()) {
                cout << waitlist.front() << endl;
                waitlist.pop();
            }
        }
    }
};

// Hash Table for Fast Access
class FastAccessManager {
private:
    static const int TABLE_SIZE = 1000;
    vector<list<pair<int, CourseNode*>>> hashTable;
    
    int hashFunction(int courseId) {
        return courseId % TABLE_SIZE;
    }
    
public:
    FastAccessManager() : hashTable(TABLE_SIZE) {}
    
    void insert(CourseNode* course) {
        int index = hashFunction(course->courseId);
        hashTable[index].push_back({course->courseId, course});
    }
    
    CourseNode* searchWithHashing(int courseId) {
        int index = hashFunction(courseId);
        for (const auto& pair : hashTable[index]) {
            if (pair.first == courseId) {
                return pair.second;
            }
        }
        return nullptr;
    }

    void removeCourse(int courseId) {
        int index = hashFunction(courseId);
        for (auto it = hashTable[index].begin(); it != hashTable[index].end(); ++it) {
            if (it->first == courseId) {
                hashTable[index].erase(it);
                cout << "Course removed from hash table!" << endl;
                return;
            }
        }
        cout << "Course not found in hash table!" << endl;
    }
};

// Main function with user interaction
int main() {
    StudentRecords students;
    CourseRecords courses;
    EnrollmentHistory enrollments;
    PrerequisiteChecker prereqs;
    WaitlistManager waitlists;
    FastAccessManager fastAccess;

    int choice;
    while (true) {
        cout << "\n===== University Management System =====" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Add Course" << endl;
        cout << "3. Enroll Student in Course" << endl;
        cout << "4. Search Course by ID" << endl;
        cout << "5. Display All Students" << endl;
        cout << "6. Display Enrollments for a Student" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string name, email, phone, address, password;
            cout << "Enter Student ID: ";
            cin >> id;
            cin.ignore(); // Clear the input buffer
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Email: ";
            getline(cin, email);
            cout << "Enter Phone: ";
            getline(cin, phone);
            cout << "Enter Address: ";
            getline(cin, address);
            cout << "Enter Password: ";
            getline(cin, password);
            students.add(id, name, email, phone, address, password);
            cout << "Student added successfully!" << endl;
        } else if (choice == 2) {
            int id, credits;
            string name, instructor;
            cout << "Enter Course ID: ";
            cin >> id;
            cin.ignore(); // Clear the input buffer
            cout << "Enter Course Name: ";
            getline(cin, name);
            cout << "Enter Credits: ";
            cin >> credits;
            cin.ignore(); // Clear the input buffer
            cout << "Enter Instructor: ";
            getline(cin, instructor);
            CourseNode* newCourse = new CourseNode(id, name, credits, instructor);
            courses.addCourse(id, name, credits, instructor);
            fastAccess.insert(newCourse); // Insert the course into the hash table
            cout << "Course added successfully!" << endl;
        } else if (choice == 3) {
            int studentId, courseId;
            string semester;
            cout << "Enter Student ID: ";
            cin >> studentId;
            cout << "Enter Course ID: ";
            cin >> courseId;
            cin.ignore(); // Clear the input buffer
            cout << "Enter Semester: ";
            getline(cin, semester);
            enrollments.add(studentId, courseId, semester);
            cout << "Enrollment successful!" << endl;
        } else if (choice == 4) {
            int courseId;
            cout << "Enter Course ID to search: ";
            cin >> courseId;
            CourseNode* foundCourse = fastAccess.searchWithHashing(courseId);
            if (foundCourse) {
                cout << "===== Course Details =====" << endl;
                cout << "Course ID: " << foundCourse->courseId << endl;
                cout << "Course Name: " << foundCourse->courseName << endl;
                cout << "Credits: " << foundCourse->credits << endl;
                cout << "Instructor: " << foundCourse->instructor << endl;
            } else {
                cout << "Course not found!" << endl;
            }
        } else if (choice == 5) {
            cout << "===== All Students =====" << endl;
            students.display();
        } else if (choice == 6) {
            int studentId;
            cout << "Enter Student ID to view enrollments: ";
            cin >> studentId;
            cout << "===== Enrollments for Student ID " << studentId << " =====" << endl;
            enrollments.view(studentId);
        } else if (choice == 7) {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}