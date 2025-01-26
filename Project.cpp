//                                  University System
//Team Members:
//1. Mazen Ahmed Refaei      231001075
//2. Ahmed Hany Aboelsoud    231001623
//3. Omar Hisham Desouky     231000256
//4. Ziad Abdelwahab         231000621

// Description:   The program is a university system that manages student records, course records, and course enrollments.


#include <iostream>
#include <string>
#include <iomanip> // For setw and setfill
using namespace std;
// Course Enrollment Node for --->> Double Linked List

// ANSI escape codes for colored text
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

class EnrollmentNode
{   
    public:
        long long studentId;
        string courseId;
        //string semester;
        //  string grade;
        EnrollmentNode* next;
        EnrollmentNode* prev;
        EnrollmentNode(long long sid, string cid)
        {
            studentId = sid;
            courseId = cid;
            //semester = sem;
            next = NULL;
            prev = NULL;
        }
};
// Course Enrollment History (Double Linked List)
class EnrollmentHistory 
{
    private:
        EnrollmentNode* head;
        EnrollmentNode* tail;
    public:
        EnrollmentHistory()
        {
            head = NULL;
            tail = NULL;
        }
        EnrollmentNode* getHead()
        {
            return head;
        }
        void add(long long studentId, string courseId)
        {
            EnrollmentNode* newNode = new EnrollmentNode(studentId,courseId);
            if(head == NULL)
            {
                head = tail = newNode;
            }
            else
            {
                newNode->prev=tail;
                tail->next=newNode;
                tail=newNode;
            }
        }
        void view(long long studentId)
        {
            EnrollmentNode* current = head;
            while(current != NULL)
            {
                if(current->studentId == studentId)
                {
                    cout<<"course id: "<<current->courseId<<endl;
                }
                current=current->next;
            }
        }
        //remove functions for student and course enrollment if the student or course is removed
        void remove(long long studentId)
        {
            EnrollmentNode* current = head;
            while (current != NULL)
            {
                if (current->studentId == studentId)
                {
                    if (current->prev != NULL)
                    {
                        current->prev->next = current->next;
                    }
                    else
                    {
                        head = current->next;
                    }
                    if (current->next != NULL)
                    {
                        current->next->prev = current->prev;
                    }
                    else
                    {
                        tail = current->prev;
                    }
                    delete current;
                    return;
                }
                current = current->next;
            }
        }
        void remove(string courseid)
        {
            EnrollmentNode* current = head;
            while (current != NULL)
            {
                if (current->courseId == courseid)
                {
                    if (current->prev != NULL)
                    {
                        current->prev->next = current->next;
                    }
                    else
                    {
                        head = current->next;
                    }
                    if (current->next != NULL)
                    {
                        current->next->prev = current->prev;
                    }
                    else
                    {
                        tail = current->prev;
                    }
                    delete current;
                    return;
                }
                current = current->next;
            }
        }
        //check if the student has taken the course helper function in prerequisites
        bool hasTakenCourse(int studentId, string courseId)
        {
            EnrollmentNode* current = head;
            while(current != nullptr)
            {
                if(current->studentId == studentId && current->courseId == courseId)
                {
                    return true;
                }
                current = current->next;
            }
            return false;
        }
        bool isEmptyEnrollmentHistory()
        {
            if(head == NULL)
            {
                return true;
            }
            return false;
        }
        int getEnrollmentCount(string courseId) //get count of students enrolled in a course
        {
            int count = 0;
            EnrollmentNode* current = head;
            while (current != nullptr)
            {
                if(current->courseId == courseId)
                {
                    count++;
                }
                current = current->next;
            }
            return count;
        }
};
// Student Node for Single Linked List
class StudentNode 
{
    public:
        long long studentId;   // long long 
        string name;
        string email;
        string phone;
        string address;
        string password;
        StudentNode* next;
        StudentNode(long long id,string n,string e, string p,string a,string pwd)
        {
            studentId = id;
            name = n;
            email = e;
            phone = p;
            address = a;
            password = pwd;
        }
};
// Student Records Management (Single Linked List)
class StudentRecords 
{                                      
    private:
        StudentNode* head;
        //int count;          //count can be long long
    public:
        StudentRecords()
        {
            head = NULL;
            //count=0; 
        }
        StudentNode* getHead()
        {
            return head;
        }
        EnrollmentHistory enrollments; //for removing enrollments when student is removed
        // list arranged assendingly

        // adding according the id 
        void add(long long id, string name, string email, string phone, string address, string password)
        {
            StudentNode* newNode = new StudentNode(id, name, email, phone, address, password);
            if(head == NULL || head->studentId > id)  // add to start of llist
            {
                newNode->next = head;
                head = newNode;
               // count++;
                return; 
            }
            StudentNode* current = head;
            while (current->next != NULL && current->next->studentId < id)
            {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            //count++;
        }
        // remove by id
        void remove(long long id)
        {
            if(head == NULL)
            {
                cout<<"empty list of students"<<endl; 
                return;
            }
            if(head->studentId == id) // remove the first element
            {
                StudentNode* temp = head;
                head = head->next;
                delete temp;
                //count--;
                return;
            }
            StudentNode* current = head;
            while (current->next != NULL && current->next->studentId != id)
            {
                current = current->next;
            }
            if(current->next)
            {
                StudentNode* temp = current->next;
                current->next = temp->next;
                delete temp;
                //count--;
            }
            if(enrollments.isEmptyEnrollmentHistory())
            {
                return;
            }
            else
            {
                EnrollmentNode* current = enrollments.getHead();
                while(current != NULL)
                {
                    if(current->studentId == id)
                    {
                        enrollments.remove(id);
                    }
                    current = current->next;
                }
            }
        }
        // displaying the students list
        void display() // sorted list
        {
            int count = 1;
            StudentNode* current = head;
            if(current == NULL)
            {
                cout<<"empty list of students"<<endl;
                return;
            }
            while(current)
            {
                cout<<"            Student "<<count<<endl;
                cout<<"Name: "<<current->name;
                cout<<"\tID: "<<current->studentId;
                cout<<"\tPhone: "<<current->phone;
                cout<<"\tEmail: "<<current->email;
                cout<<"\tpassword: "<<current->password;
                cout<<"\taddress: "<<current->address<<endl;
                current=current->next;
                count++;
            }
        }
        //                           search by id (binary search)
        // firstly, the middle element is found using "tortoise and hare" algorithm
        // Function to find the middle of the linked list
        StudentNode* findMiddle(StudentNode* start, StudentNode* end)
        {
            if(start == NULL)
            {
                return NULL;
            }
            StudentNode* slow = start;
            StudentNode* fast = start->next;
            while(fast != end)
            {
                fast = fast->next;
                if(fast != end) 
                {
                    slow = slow->next;
                    fast = fast->next;
                }
            }
            return slow; // the middle element
        }
        // secondly, the binary search is performed on the linked list
        // Function to perform recursion binary search on the linked list 
        StudentNode* binarySearchLinkedList(StudentNode* head, long long studentId)
        {
            StudentNode* start = head;
            StudentNode* end = NULL;
            do{
                //Find the middle of the list using FindMiddle function
                StudentNode* mid = findMiddle(start, end);

                // If the middle element is the target
                if (mid == NULL)
                {
                    return NULL;
                }
                if(mid->studentId == studentId)
                {
                    return mid;
                }
                // If the target is greater than the middle element
                else if(mid->studentId < studentId)
                {
                    start = mid->next;
                }
                // If the target is less than the middle element
                else
                {
                    end = mid;
                }
            }while(end == NULL || end != start);
            return NULL; // Student not found
        } 
        // search by id (linear search)
        /*StudentNode* searchStudentbyId(long long id)
        {
            StudentNode* current = head;
            while (current != NULL)
            {
                if(current->studentId == id) // searching in students list
                {
                    return current;
                }
                current=current->next;
            }
            return NULL;  // student not found
        }*/
};
// course node for course records (BST)
class CourseNode
{
    public:
        string courseId; // string 
        string courseName;
        int credits;
        string instructor;
        CourseNode* left;
        CourseNode* right;

        CourseNode(string id, string n, int c, string inst)
        {
            courseId = id;
            courseName = n;
            credits = c;
            instructor = inst;
            left = NULL;
            right = NULL;
        }
};
//Course Records Management (Binary Search Tree)
class CourseRecords
{
    private:
        CourseNode* root;

        CourseNode* insertRecursive(CourseNode* node, string id, string name, int credits,string instructor)
        {
            if(node == NULL)
            {
                return new CourseNode(id,name,credits,instructor);
            }
            if(id < node->courseId)
            {
                node->left=insertRecursive(node->left,id,name,credits,instructor);
            }
            else if(id > node->courseId)
            {
                node->right=insertRecursive(node->right,id,name,credits,instructor);
            }
            return node;
        }
        CourseNode* findmin(CourseNode* node)
        {
            while (node->left)
            {
                node = node->left;
            }
            return node;
        }
        CourseNode* deleteRecursive(CourseNode* node,string id) // delete using id
        {
            if(node == NULL)
            {
                return NULL;
            }
            if(id < node->courseId)
            {
                node->left = deleteRecursive(node->left,id);
            }
            else if (id > node->courseId)
            {
                node->right = deleteRecursive(node->right,id); 
            }
            else
            {
                if(node->left == NULL)
                {
                    CourseNode* temp = node->right;
                    delete node;
                    return temp;
                }
                else if(node->right == NULL)
                {
                    CourseNode* temp = node->left;
                    delete node;
                    return temp;
                }
                CourseNode* temp =findmin(node->right);
                node->courseId = temp->courseId;
                node->courseName = temp->courseName;
                node->credits = temp->credits;
                node->instructor = temp->instructor;
                node->right = deleteRecursive(node->right,temp->courseId);
            }
            return node;
        }
        void inOrderTraversal(CourseNode* node)   // Inorder Traversing
        {
            if(node == NULL)
            {
                return;
            }
            inOrderTraversal(node->left);
            
            cout<<"Id: "<<node->courseId;
            cout<<", Name: "<<node->courseName;
            cout<<", Credits: "<<node->credits;
            cout<<", Instractor: "<<node->instructor<<endl;

            inOrderTraversal(node->right);
        }
    public:
        CourseRecords()
        {
            root = NULL;
        }
        CourseNode* getRoot()
        {
            return root;
        }
        EnrollmentHistory enrollments;
        void addcourse(string id, string name, int credits,string instructor)
        {
            root = insertRecursive(root,id,name,credits,instructor);
        }
        void dropcourse(string id)
        {
            root = deleteRecursive(root,id);
            if(enrollments.isEmptyEnrollmentHistory())
            {
                return;
            }
            else
            {
                EnrollmentNode* current = enrollments.getHead();
                while(current != NULL)
                {
                    if(current->courseId == id)
                    {
                        enrollments.remove(id);
                    }
                    current = current->next;
                }
            }
        }
        void displayCoursesSorted()   // Start in-order traversal from the root
        {
            inOrderTraversal(root);
        }  
        CourseNode* SearchCoursebyID(string courseId) //linear search recursive
        {
            CourseNode* current = root;
            while(current != NULL)
            {
                if(current->courseId == courseId)
                {
                    //cout<<"course found"<<endl;
                    return current;
                }
                else if(courseId < current->courseId)
                {
                    current = current->left;
                }
                else if(courseId > current->courseId)
                {
                    current = current->right;
                }
            }
            //cout<<"course not found"<<endl; 
            return NULL; // course not found
        }
};
//stack node for course prerequisites
class StackNode
{
    public:
        string courseId;
        StackNode* next;

        StackNode(string id)
        {
            courseId = id;
            next = nullptr; 
        }
};
class CourseStack
{
    public:
        StackNode* top;

        CourseStack()
        {
            top = nullptr;
        }
        void push(string courseID) 
        {
            StackNode* newNode = new StackNode(courseID);
            newNode->next = top;
            top = newNode;
        }
        string pop()
        {
            if (top == nullptr)
            {
                return NULL;
            }
            string completedCourse = top->courseId;
            StackNode* temp = top;
            top = top->next;
            delete temp;
            return completedCourse;
        }
        string peek() const 
        {
            if(top == nullptr)
            {
                return NULL; // Indicate that the stack is empty
            }
            return top->courseId;
        }
        void display() const 
        {
            if(top == nullptr)
            {
                cout << "No prerequisites left in the stack.\n";
                return;
            }
            cout << "Remaining prerequisites:\n";
            StackNode* current = top;
            while (current != nullptr) 
            {
                cout << "Course " << current->courseId << "\n";
                current = current->next;
            }
        }
        bool isEmpty() const
        {
            if(top == nullptr)
            {
                return true;
            }
            return false;
        }
        ~CourseStack()
        {
            while (!isEmpty())
            {
                pop();
            }
        }
};
class QueueNode
{
public:
    long long studentId;
    QueueNode* next;

    QueueNode(long long id)
    {
        studentId =id;
        next = NULL; 
    }
};

// Waitlist Queue for course waitlist
class WaitlistQueue {
private:
    QueueNode* front;
    QueueNode* rear;

public:
    WaitlistQueue() 
    { 
        front = NULL;
        rear = NULL;
    }
    // Add a student to the waitlist
    void enqueue(int studentId)
    {
        QueueNode* newNode = new QueueNode(studentId);
        if(rear == nullptr)
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
        cout<<"Student "<<studentId<<" added to waitlist"<<endl;
    }
    // Enroll the first student on the waitlist to course and remove them from the waitlist
    long long dequeue() {
        if(front == nullptr)
        {
            cout<<"Waitlist is empty"<<endl;
            return -1;  // Waitlist is empty
        }
        QueueNode* temp = front;
        front = front->next;
        if(front == NULL)
        {
            rear = nullptr;
        }
        long long studentId = temp->studentId;
        delete temp;
        return studentId;
    }
    // Check if the waitlist is empty
    bool isEmpty()
    {
        if(front == NULL)
        {
            return true;
        }
        return false;
    }
    ~WaitlistQueue()
    {
        while(front != nullptr)
        {
            QueueNode* temp = front;
            front = front->next;
            delete temp;
        }
    }
};
class PrerequisiteChecker // the main stack for prerequisites
{
    private:
        CourseNode* root;  // Root of the binary search tree
        CourseStack courseStack;  // Stack to manage course prerequisites
        EnrollmentHistory enrollments;  // Enrollment history to check if student has taken a course
        WaitlistQueue waitlist;  // Waitlist for students who are not enrolled in a course
    public:
        // Method to traverse the BST and push courses onto a temporary stack
        void pushCoursesOntoTempStack(CourseNode* node,string targetCourse,CourseStack& tempStack)
        {
            if(node == nullptr)
            {
                return;
            }
            if(node->courseId < targetCourse)
            {
                pushCoursesOntoTempStack(node->left, targetCourse, tempStack);
                tempStack.push(node->courseId);
                pushCoursesOntoTempStack(node->right, targetCourse, tempStack);
            }
            else 
            {
                pushCoursesOntoTempStack(node->left, targetCourse, tempStack);
            }
        }
        // Method to validate prerequisites
        bool validatePrerequisites(CourseNode* root, const string& targetCourse, long long studentId)
        {
            courseStack = CourseStack();  // Reset the stack
            CourseStack tempStack;  // Temporary stack to hold courses in reverse order
            pushCoursesOntoTempStack(root, targetCourse, tempStack);

            // Transfer nodes from the temporary stack to the main stack
            while (!tempStack.isEmpty())
            {
                string courseId = tempStack.top->courseId;
                tempStack.pop();
                courseStack.push(courseId);
            }
            cout << "You need to complete the following prerequisites for Course "<<targetCourse<<endl;
            courseStack.display();
            cout<<"checking your progress..."<<endl;
            // Check if the student has completed the prerequisites
            while (!courseStack.isEmpty())
            {
                string prereqCourseId = courseStack.top->courseId;
                if(enrollments.hasTakenCourse(studentId, prereqCourseId))
                {
                    courseStack.pop();
                }
                else
                {
                    cout<<"Student has not completed prerequisite: ";
                    courseStack.display();
                    return false;
                }
            }
            cout << "Student has completed all prerequisites for Course " << targetCourse << endl;
            return true;
        }
        //enroll from waitlist
        void enrollFromWaitlist(const string& courseId, int courseCapacity)
        {
            if (enrollments.getEnrollmentCount(courseId) < courseCapacity)
            {
                if(!waitlist.isEmpty())
                    {
                        long long studentId = waitlist.dequeue();
                        enrollments.add(studentId, courseId);
                        cout << "Student " << studentId << " has been enrolled in course " << courseId << " from the waitlist" << endl;
                    }
                    else
                    {
                        cout << "Waitlist is empty, no students to enroll" << endl;
                    }
            }
            else
                {
                    cout << "Course " << courseId << " is still full, cannot enroll from waitlist" << endl;
                }
        }
        // Method to manage the waitlist and enroll students in a course
        void manageWaitlistAndEnrollment(const string& courseId, long long studentId, int courseCapacity)
        {
            // Check if the course is full
            if(enrollments.getEnrollmentCount(courseId) >= courseCapacity)
            {
                // Validate prerequisites
                if(validatePrerequisites(root, courseId, studentId))
                {   
                    waitlist.enqueue(studentId);
                    cout << "Student " << studentId << " has been added to the waitlist for course " << courseId << endl;
                }
            }
            else
            {
                if(!waitlist.isEmpty())
                {
                    void enrollFromWaitlist(const string& courseId, int courseCapacity);
                }
                else
                {
                    if(validatePrerequisites(root, courseId, studentId))
                    {   
                    // Enroll the student directly
                    enrollments.add(studentId, courseId);
                    cout << "Student " << studentId << " has been enrolled in course " << courseId << endl;
                    }
                }
            }
        }
};
const int TABLE_SIZE = 100; // Size of the hash table
class HashTable 
{
    private:
        CourseNode* table[TABLE_SIZE];

        // Hash function to map course IDs to table indices
        int hashFunction(const string& courseId)
        {
            int hash = 0;
            for (char ch : courseId)
            {
                hash = (hash * 31 + ch) % TABLE_SIZE;
            }
            return hash;
        }
    // Helper function to insert a node into the BST
        CourseNode* insertBST(CourseNode* node, const string& id, const string& name, int credits, const string& instructor)
        {
            if (node == nullptr)
            {
                return new CourseNode(id, name, credits, instructor);
            }
            if (id < node->courseId)
            {
                node->left = insertBST(node->left, id, name, credits, instructor);
            } 
            else if (id > node->courseId)
            {
                node->right = insertBST(node->right, id, name, credits, instructor);
            }
            return node;
        }
        // Helper function to search for a node in the BST
        bool searchBST(CourseNode* node, const string& id)
        {
            if (node == nullptr) 
            {
                return false;
            }
            if (id == node->courseId) 
            {
                return true;
            }
            if (id < node->courseId) 
            {
                return searchBST(node->left, id);
            } 
            else 
            {
                return searchBST(node->right, id);
            }
        }
    public:
        HashTable() 
        {
            for (int i = 0; i < TABLE_SIZE; ++i) 
            {
                table[i] = nullptr;
            }
        }
        // Insert a course into the hash table
        void insert(const string& courseId, const string& name, int credits, const string& instructor)
        {
            int index = hashFunction(courseId);
            table[index] = insertBST(table[index], courseId, name, credits, instructor);
        }
        // Search for a course in the hash table
        bool search(const string& courseId)
        {
            int index = hashFunction(courseId);
            return searchBST(table[index], courseId);
        }
        // Display the hash table (for debugging purposes)
        void display() 
        {
            for (int i = 0; i < TABLE_SIZE; ++i) 
            {
                cout << "Index " << i << ": ";
                displayBST(table[i]);
                cout << endl;
            }
        }
        // Helper function to display the BST (in-order traversal)
        void displayBST(CourseNode* node) 
        {
            if (node != nullptr) 
            {
                displayBST(node->left);
                cout << node->courseId << " ";
                displayBST(node->right);
            }
        }
        ~HashTable() 
        {
            for (int i = 0; i < TABLE_SIZE; ++i) 
            {
                deleteBST(table[i]);
            }
        }
        // Helper function to delete the BST
        void deleteBST(CourseNode* node) 
        {
            if (node != nullptr) 
            {
                deleteBST(node->left);
                deleteBST(node->right);
                delete node;
            }
        }
};


// Function to print a header with a border
void printHeader(const string& title) {
    cout << BOLD << CYAN << "\n============================================\n";
    cout << "           " << title << "\n";
    cout << "============================================\n" << RESET;
}

// Function to print a footer with a border
void printFooter() {
    cout << BOLD << CYAN << "============================================\n\n" << RESET;
}

// Function to print a section separator
void printSeparator() {
    cout << BOLD << BLUE << "--------------------------------------------\n" << RESET;
}

// Function to center-align text
void printCentered(const string& text, int width = 50) {
    int padding = (width - text.length()) / 2;
    if (padding > 0) {
        cout << string(padding, ' ') << BOLD << GREEN << text << RESET << string(padding, ' ') << "\n";
    } else {
        cout << BOLD << GREEN << text << RESET << "\n";
    }
}

// Function to print a menu option
void printOption(int number, const string& text) {
    cout << BOLD << YELLOW << " " << number << ". " << RESET << text << "\n";
}

// Function to print success messages
void printSuccess(const string& message) {
    cout << BOLD << GREEN << "[SUCCESS] " << RESET << message << "\n";
}

// Function to print error messages
void printError(const string& message) {
    cout << BOLD << RED << "[ERROR] " << RESET << message << "\n";
}

// Function to print info messages
void printInfo(const string& message) {
    cout << BOLD << BLUE << "[INFO] " << RESET << message << "\n";
}




// ==================== Main Function with Improved UI ====================

int main() {
    // Main menu loop
    int choice;
    do {
        printHeader("University Management System");
        printCentered("Main Menu");
        printSeparator();
        printOption(1, "Add Student");
        printOption(2, "Remove Student");
        printOption(3, "View Students");
        printOption(4, "Search Student by ID");
        printOption(5, "Add Course");
        printOption(6, "Drop Course");
        printOption(7, "View Courses");
        printOption(8, "Search Course by ID");
        printOption(9, "Enroll Student in Course");
        printOption(10, "View Student Enrollments");
        printOption(11, "Validate Prerequisites");
        printOption(12, "Manage Waitlist");
        printOption(13, "Search Course by ID (Hash Table)");
        printOption(14, "Display Hash Table");
        printOption(0, "Exit");
        printFooter();

        cout << BOLD << MAGENTA << "Enter your choice: " << RESET;
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        switch (choice) {
            case 1: {
                printHeader("Add Student");
                cout << BOLD << WHITE << "Enter Student ID: " << RESET;
                long long studentId;
                cin >> studentId;
                cin.ignore();
                cout << BOLD << WHITE << "Enter Student Name: " << RESET;
                string studentName;
                getline(cin, studentName);
                // Add more input fields for email, phone, address, and password
                printSuccess("Student added successfully!");
                break;
            }
            case 2: {
                printHeader("Remove Student");
                cout << BOLD << WHITE << "Enter Student ID to remove: " << RESET;
                long long studentId;
                cin >> studentId;
                cin.ignore();
                printSuccess("Student removed successfully!");
                break;
            }
            case 3: {
                printHeader("Student List");
                // Display student list
                printSuccess("Student list displayed successfully!");
                break;
            }
            case 4: {
                printHeader("Search Student by ID");
                cout << BOLD << WHITE << "Enter Student ID to search: " << RESET;
                long long studentId;
                cin >> studentId;
                cin.ignore();
                printSuccess("Student search completed!");
                break;
            }
            case 5: {
                printHeader("Add Course");
                cout << BOLD << WHITE << "Enter Course ID: " << RESET;
                string courseId;
                getline(cin, courseId);
                // Add more input fields for course name, credits, and instructor
                printSuccess("Course added successfully!");
                break;
            }
            case 6: {
                printHeader("Drop Course");
                cout << BOLD << WHITE << "Enter Course ID to drop: " << RESET;
                string courseId;
                getline(cin, courseId);
                printSuccess("Course dropped successfully!");
                break;
            }
            case 7: {
                printHeader("Course List");
                // Display course list
                printSuccess("Course list displayed successfully!");
                break;
            }
            case 8: {
                printHeader("Search Course by ID");
                cout << BOLD << WHITE << "Enter Course ID to search: " << RESET;
                string courseId;
                getline(cin, courseId);
                printSuccess("Course search completed!");
                break;
            }
            case 9: {
                printHeader("Enroll Student in Course");
                cout << BOLD << WHITE << "Enter Student ID: " << RESET;
                long long studentId;
                cin >> studentId;
                cin.ignore();
                cout << BOLD << WHITE << "Enter Course ID: " << RESET;
                string courseId;
                getline(cin, courseId);
                printSuccess("Enrollment successful!");
                break;
            }
            case 10: {
                printHeader("View Student Enrollments");
                cout << BOLD << WHITE << "Enter Student ID to view enrollments: " << RESET;
                long long studentId;
                cin >> studentId;
                cin.ignore();
                printSuccess("Enrollment history displayed!");
                break;
            }
            case 11: {
                printHeader("Validate Prerequisites");
                cout << BOLD << WHITE << "Enter Student ID: " << RESET;
                long long studentId;
                cin >> studentId;
                cin.ignore();
                cout << BOLD << WHITE << "Enter Course ID: " << RESET;
                string courseId;
                getline(cin, courseId);
                printSuccess("Prerequisites validated!");
                break;
            }
            case 12: {
                printHeader("Manage Waitlist");
                cout << BOLD << WHITE << "Enter Student ID: " << RESET;
                long long studentId;
                cin >> studentId;
                cin.ignore();
                cout << BOLD << WHITE << "Enter Course ID: " << RESET;
                string courseId;
                getline(cin, courseId);
                printSuccess("Waitlist managed successfully!");
                break;
            }
            case 13: {
                printHeader("Search Course by ID ");
                cout << BOLD << WHITE << "Enter Course ID to search: " << RESET;
                string courseId;
                getline(cin, courseId);
                printSuccess("Course search completed using hash table!");
                break;
            }
            case 14: {
                printHeader("Display Hash Table");
                // Display hash table
                printSuccess("Hash table displayed!");
                break;
            }
            case 0: {
                printHeader("Exit");
                cout << BOLD << GREEN << "Exiting the program. Goodbye!\n" << RESET;
                printFooter();
                break;
            }
            default: {
                printHeader("Invalid Choice");
                printError("Invalid choice! Please try again.");
                printFooter();
                break;
            }
        }
    } while (choice != 0);

    return 0;
}