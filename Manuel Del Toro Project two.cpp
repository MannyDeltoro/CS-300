
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;



class Subject {
public: // setting up the subjects and there variables 
    string subjectCode;
    string subjectName;
    vector<string> prereqSubjects;

    Subject(string code, string name, vector<string> prereqs) //defualt contructor 
        : subjectCode(code), subjectName(name), prereqSubjects(prereqs) {}
};
class Node { // nodes for the linked list and variables 
public:
    Subject subject;
    Node* next;

    Node(Subject subject) : subject(subject), next(nullptr) {} // defualt contructor for the node 
};
class SubjectList {
public:
    SubjectList() : top(nullptr) {}
    ~SubjectList();

    void readSubjectsFromFile(const string& filename);
    void displayAllSubjects();
    void displaySubjectDetails(const string& subjectCode);

private:
    Node* top;
    // private variables for inheritance 
    void addSubject(Subject subject);
    void removeAll();
};

SubjectList::~SubjectList() {
    SubjectList();
}

void SubjectList::removeAll() {
    Node* currentCourse = top;
    while (currentCourse != nullptr) {
        Node* toDeleteCourse = currentCourse;
        currentCourse = currentCourse->next;
        delete toDeleteCourse;
    }
    top = nullptr;
}

void SubjectList::addSubject(Subject Subject) { // function to add functions to the linked list 
    Node* newCourseNode = new Node(Subject);

    if (!top || Subject.subjectCode < top->subject.subjectCode) {
        newCourseNode->next = top;
        top = newCourseNode;
    }
    else {
        Node* currentCourse = top;
        while (currentCourse->next && currentCourse->next->subject.subjectCode < Subject.subjectCode) {
            currentCourse = currentCourse->next; // processing nodes and next nodes 
        }
        newCourseNode->next = currentCourse->next;
        currentCourse->next = newCourseNode;
    }
}

void SubjectList::readSubjectsFromFile(const string& filename) { // reading subjects from a file 
    ifstream fileStream(filename);

    if (!fileStream) {
        cout << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    while (getline(fileStream, line)) {
        istringstream iss(line); // getting the file from the csv file 
        string id, title, prereq;
        vector<string> prerequisites;

        getline(iss, id, ',');
        getline(iss, title, ',');

        while (getline(iss, prereq, ',')) {
            prerequisites.push_back(prereq);
        }

        Subject courseInfo(id, title, prerequisites);
        addSubject(courseInfo);
    }

    fileStream.close();
    cout << "Courses loaded successfully!" << endl;
}

void SubjectList::displayAllSubjects() { // function to display subjects
    Node* currentCourse = top;

    while (currentCourse != nullptr) {
        cout << currentCourse->subject.subjectCode << ": " << currentCourse->subject.subjectName << endl;
        currentCourse = currentCourse->next;
    }
}

void SubjectList::displaySubjectDetails(const string& courseID) {
    Node* currentCourse = top;

    while (currentCourse != nullptr && currentCourse->subject.subjectCode != courseID) {
        currentCourse = currentCourse->next; // pointing to next node 
    }

    if (currentCourse == nullptr) {
        cout << "Course not found!" << endl;
    }
    else {
        Subject course = currentCourse->subject; // going to next subject
        cout << "Course ID: " << course.subjectCode << endl;
        cout << "Course Title: " << course.subjectName << endl;
        cout << "Prerequisites: "; //printing out variables 

        if (course.prereqSubjects.empty()) {
            cout << "None" << endl;
        }
        else {
            for (const auto& prereq : course.prereqSubjects) {
                cout << prereq << " ";
            }
            cout << endl;
        }
    }
}

void displayMenu() { //function to display menu
    cout << "Menu:" << endl;
    cout << "1. Load the file data into the data structure" << endl;
    cout << "2. Print an alphanumeric list of all the courses in the Computer Science department" << endl;
    cout << "3. Print the course title and the prerequisites for any individual course" << endl;
    cout << "9. Exit the program" << endl;
}

int main() {
    SubjectList courseHandler;
    int selection;
    string fileName;
    string courseCode;

    do {
        displayMenu(); //display menu
        cout << "Enter your selection: ";
        cin >> selection;

        switch (selection) {
        case 1:
            cout << "Enter the file name: ";
            cin >> fileName;
            courseHandler.readSubjectsFromFile(fileName); // load subjects from file 
            break;

        case 2:
            courseHandler.displayAllSubjects();//display subject 
            break;

        case 3:
            cout << "Enter the course code: ";
            cin >> courseCode;
            courseHandler.displaySubjectDetails(courseCode); //display subject details 
            break;

        case 9:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid selection. Please try again." << endl;
        }
    } while (selection != 9); // case to stop do while 

    return 0;
}