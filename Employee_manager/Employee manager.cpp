#include <iostream>
#include <string>
#include <stack>
#include <iomanip>

using namespace std;

struct Data {
    struct Info {
        string code;        // Mã nhân viên
        string name;        // Tên nhân viên
        string marital;     // Tình trạng hôn nhân
        int children;       // Số con
        string degree;      // Trình độ
        int basic_salary;   // Lương cơ bản
    };
    struct Salary {
        int sabbatical;     // Số ngày nghỉ có phép
        int unexcused;      // Số ngày nghỉ không phép
        int overtime;       // Tăng ca
        string result;      // Kết quả công việc
        int monthly_salary; // Lương tháng
    };

    Info info;
    Salary salary;
};

struct Node {
    Data data;
    Node* next;
};

struct List {
    Node* pHead;
    Node* pTail;
};

void init(List& l) {
    l.pHead = NULL;
    l.pTail = NULL;
}

void freeList(List& l) {
    Node* current = l.pHead;
    Node* next;

    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }

    l.pHead = nullptr;
    l.pTail = nullptr;
}

void inputData(Data& employee) {
    cout << "Enter code: ";
    cin >> employee.info.code;

    cout << "Enter name: ";
    cin.ignore();
    getline(cin, employee.info.name);

    cout << "Enter marital status: ";
    getline(cin, employee.info.marital);

    cout << "Enter number of children: ";
    cin >> employee.info.children;

    cout << "Enter degree: ";
    cin.ignore();
    getline(cin, employee.info.degree);

    cout << "Enter basic salary: ";
    cin >> employee.info.basic_salary;

    cout << "Enter sabbatical days: ";
    cin >> employee.salary.sabbatical;

    cout << "Enter unexcused days: ";
    cin >> employee.salary.unexcused;

    cout << "Enter overtime days: ";
    cin >> employee.salary.overtime;

    cout << "Enter job result: ";
    cin.ignore();
    getline(cin, employee.salary.result);
}

string return_Marital(Data& employee) {
    if (employee.info.marital == "M")
        return "Married";
    else if (employee.info.marital == "S")
        return "Single";
    else
        return "Invalid input";
}

string return_Degree(Data& employee) {
    if (employee.info.degree == "C1")
        return "Cap 1";
    else if (employee.info.degree == "C2")
        return "Cap 2";
    else if (employee.info.degree == "C3")
        return "Cap 3";
    else if (employee.info.degree == "DH")
        return "Dai hoc";
    else if (employee.info.degree == "CH")
        return "Cao hoc";
    else
        return "Invalid input";
}

string return_Result(Data& employee) {
    if (employee.salary.result == "T")
        return "Tot";
    else if (employee.salary.result == "TB")
        return "Dat";
    else if (employee.salary.result == "K")
        return "Kem";
    else
        return "Invalid input";
}

int extra(Data& employee) {
    int bonus = 0;
    if (employee.info.children > 2)
        bonus = employee.info.basic_salary * 5 / 100;
    if (employee.info.degree == "CH")
        bonus += employee.info.basic_salary * 10 / 100;
    bonus += employee.salary.overtime * employee.info.basic_salary * 4 / 100;
    return bonus;
}

void calculator_Salary(Data& employee) {
    employee.salary.monthly_salary = employee.info.basic_salary + extra(employee);
}

void addEmployee(List& l) {
    Node* newNode = new Node;
    newNode->next = NULL;

    cout << "\n-----Add employee------\n" << endl;

    inputData(newNode->data);
    calculator_Salary(newNode->data);
    if (l.pHead == NULL) {
        l.pHead = newNode;
        l.pTail = newNode;
    }
    else {
        l.pTail->next = newNode;
        l.pTail = newNode;
    }

    cout << "\nEmployee added successfully." << endl;
}

void updateEmployee(List& l) {
    string code;
    cout << "\n-----Update employee------\n" << endl;
    cout << "Enter the code of the employee to update: ";
    cin >> code;

    Node* currentNode = l.pHead;

    while (currentNode != NULL) {
        if (currentNode->data.info.code == code) {
            cout << "Enter new information for employee " << currentNode->data.info.name << ":" << endl;

            inputData(currentNode->data);

            cout << "Employee updated successfully." << endl;
            return;
        }

        currentNode = currentNode->next;
    }

    cout << "Employee with code " << code << " not found." << endl;
}

void deleteEmployee(List& l) {
    string code;
    cout << "\n-----Delete employee------\n" << endl;
    cout << "Enter the code of the employee to delete: ";
    cin >> code;

    Node* currentNode = l.pHead;
    Node* prevNode = NULL;

    while (currentNode != NULL) {
        if (currentNode->data.info.code == code) {
            if (prevNode == NULL) {
                l.pHead = currentNode->next;
            }
            else {
                prevNode->next = currentNode->next;
            }

            delete currentNode;

            cout << "Employee deleted successfully." << endl;
            return;
        }

        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    cout << "Employee with code " << code << " not found." << endl;
}

void searchEmployee(List l) {
    string code;
    cout << "\n-----Search employee------\n" << endl;
    cout << "Enter the code of the employee to search: ";
    cin >> code;

    Node* currentNode = l.pHead;

    while (currentNode != NULL) {
        if (currentNode->data.info.code == code) {
            cout << "Employee found:" << endl;
            cout << "Code: " << currentNode->data.info.code << endl;
            cout << "Name: " << currentNode->data.info.name << endl;
            cout << "Marital Status: " << currentNode->data.info.marital << endl;
            cout << "Number of Children: " << currentNode->data.info.children << endl;
            cout << "Degree: " << currentNode->data.info.degree << endl;
            cout << "Basic Salary: " << currentNode->data.info.basic_salary << endl;
            cout << "Sabbatical Days: " << currentNode->data.salary.sabbatical << endl;
            cout << "Unexcused Days: " << currentNode->data.salary.unexcused << endl;
            cout << "Overtime Hours: " << currentNode->data.salary.overtime << endl;
            cout << "Job Result: " << currentNode->data.salary.result << endl;
            cout << "Monthly Salary: " << currentNode->data.salary.monthly_salary << endl;

            return;
        }

        currentNode = currentNode->next;
    }

    cout << "Employee with code " << code << " not found." << endl;
}

void displayData(List l) {
    cout << "\n-----Display employee data------\n" << endl;
    if (l.pHead == NULL) {
        cout << "The list is empty." << endl;
        return;
    }

    Node* currentNode = l.pHead;
    int count = 1;

    while (currentNode != NULL) {
        cout << "Employee " << count << ":" << endl;

        // Display employee information
        cout << "Code: " << currentNode->data.info.code << endl;
        cout << "Name: " << currentNode->data.info.name << endl;
        cout << "Marital Status: " << return_Marital(currentNode->data) << endl;
        cout << "Number of Children: " << currentNode->data.info.children << endl;
        cout << "Degree: " << return_Degree(currentNode->data) << endl;
        cout << "Basic Salary: " << currentNode->data.info.basic_salary << endl;

        // Display employee salary information
        cout << "Sabbatical Days: " << currentNode->data.salary.sabbatical << endl;
        cout << "Unexcused Days: " << currentNode->data.salary.unexcused << endl;
        cout << "Overtime Hours: " << currentNode->data.salary.overtime << endl;
        cout << "Job Result: " << return_Result(currentNode->data) << endl;
        calculator_Salary(currentNode->data);
        cout << "Monthly Salary: " << currentNode->data.salary.monthly_salary << endl;

        cout << endl;

        currentNode = currentNode->next;
        count++;
    }
}

void displaySalaryTable(List l) {
    cout << "\n-----Display salary table------\n" << endl;
    if (l.pHead == NULL) {
        cout << "The list is empty." << endl;
        return;
    }

    Node* currentNode = l.pHead;
    cout << "Salary Table:" << endl;
    cout << "----------------------------------------" << endl;
    cout << left << setw(8) << "Code";
    cout << left << setw(20) << "Name";
    cout << "Monthly salary" << endl;

    while (currentNode != NULL) {
        cout << left << setw(8) << currentNode->data.info.code;
        cout << left << setw(20) << currentNode->data.info.name;
        cout << currentNode->data.salary.monthly_salary << endl;
        currentNode = currentNode->next;
    }

    cout << "----------------------------------------" << endl;
}

void swapData(Node* a, Node* b) {
    Data temp = a->data;
    a->data = b->data;
    b->data = temp;
}

Node* getLastNode(Node* node) {
    while (node != nullptr && node->next != nullptr) {
        node = node->next;
    }
    return node;
}

Node* partition(Node* l, Node* h) {
    int pivot = h->data.salary.monthly_salary;
    Node* i = l;
    Node* j = l;

    while (j != h) {
        if (j->data.salary.monthly_salary < pivot) {
            swapData(i, j);
            i = i->next;
        }
        j = j->next;
    }

    swapData(i, h);
    return i;
}

void quickSortIterative(List& l) {
    if (l.pHead == nullptr || l.pHead == l.pTail)
        return;

    stack<Node*> stack;
    stack.push(l.pHead);
    stack.push(getLastNode(l.pHead));

    while (!stack.empty()) {
        Node* high = stack.top();
        stack.pop();
        Node* low = stack.top();
        stack.pop();

        if (low != nullptr && high != nullptr && low != high && low != high->next) {
            Node* pivot = partition(low, high);

            Node* leftPrev = low == pivot ? nullptr : l.pHead;
            while (leftPrev != nullptr && leftPrev->next != pivot) {
                leftPrev = leftPrev->next;
            }
            if (leftPrev != nullptr) {
                stack.push(low);
                stack.push(leftPrev);
            }

            if (pivot != nullptr && pivot != high) {
                stack.push(pivot->next);
                stack.push(high);
            }
        }
    }
}

int main() {
    List employeeList;
    init(employeeList);

    char choice;

    do {
        cout << "=========MENU=========" << endl;
        cout << "1. Add employee" << endl;
        cout << "2. Update employee" << endl;
        cout << "3. Delete employee" << endl;
        cout << "4. Search employee" << endl;
        cout << "5. Display employee data" << endl;
        cout << "6. Display salary table" << endl;
        cout << "7. Sort by monthly salary" << endl;
        cout << "0. Exit" << endl;
        cout << "---------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case '1':
            addEmployee(employeeList);
            break;
        case '2':
            updateEmployee(employeeList);
            break;
        case '3':
            deleteEmployee(employeeList);
            break;
        case '4':
            searchEmployee(employeeList);
            break;
        case '5':
            displayData(employeeList);
            break;
        case '6':
            displaySalaryTable(employeeList);
            break;
        case '7':
            quickSortIterative(employeeList);
            cout << "Salary table sorted by monthly salary:" << endl;
            displaySalaryTable(employeeList);
            break;
        case '0':
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    } while (choice != '0');

    freeList(employeeList);
    return 0;
}
