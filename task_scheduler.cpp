#include <bits/stdc++.h>
using namespace std;

struct Task {
    string name;
    int priority;
    int deadline;
    vector<string> dependencies;
};

// Comparator for min-heap (priority queue)
struct Compare {
    bool operator()(const Task &a, const Task &b) {
        if (a.deadline == b.deadline) {
            if (a.priority == b.priority)
                return a.name > b.name; 
            return a.priority < b.priority; // Higher priority first
        }
        return a.deadline > b.deadline; // Earlier deadline first
    }
};

map<string, Task> taskMap;
map<string, int> inDegree;
map<string, vector<string>> adjList;
set<string> taskNames;
set<string> completedTasks;
vector<string> executionOrder;



void generateDOTFile() {
    ofstream dotFile("tasks.dot");
    dotFile << "digraph TaskGraph {\n";
    
    for (const auto &entry : taskMap) {
        dotFile << "    \"" << entry.first << "\" [label=\"" << entry.first 
                << "\\nPriority: " << entry.second.priority 
                << "\\nDeadline: " << entry.second.deadline << "\"];\n";
    }

    for (const auto &entry : adjList) {
        for (const string &dependent : entry.second) {
            dotFile << "    \"" << entry.first << "\" -> \"" << dependent << "\";\n";
        }
    }

    dotFile << "}\n";
    dotFile.close();

    // Automatically generate PNG file using Graphviz
    system("\"C:\\Program Files\\Graphviz\\bin\\dot.exe\" -Tpng tasks.dot -o tasks.png");

}


bool createExecutionOrder() {
    priority_queue<Task, vector<Task>, Compare> tempHeap;
    map<string, int> tempInDegree = inDegree;
    executionOrder.clear();

    for (const auto &entry : taskMap) {
        if (tempInDegree[entry.first] == 0) {
            tempHeap.push(entry.second);
        }
    }

    while (!tempHeap.empty()) {
        Task current = tempHeap.top();
        tempHeap.pop();
        executionOrder.push_back(current.name);

        for (const string &dependent : adjList[current.name]) {
            tempInDegree[dependent]--;
            if (tempInDegree[dependent] == 0) {
                tempHeap.push(taskMap[dependent]);
            }
        }
    }

    if (executionOrder.size() != taskMap.size()) {
        cout << "Error: Circular dependency detected!\n";
        executionOrder.clear();
        return false;
    }
    return true;
}

bool addTask(int t) {
    Task task;
    string depInput;
    vector<string> dependencies;

    cout << "Enter Task Name, Priority, Deadline, Dependencies (comma-separated or 'none'): ";
    cin >> task.name >> task.priority >> task.deadline;
    cin.ignore();
    getline(cin, depInput);

    if (taskMap.find(task.name) != taskMap.end()) {
        cout << "Error: Task with name '" << task.name << "' already exists!\n";
        return false;
    }

    if (depInput != "none") {
        stringstream ss(depInput);
        string dep;
        while (getline(ss, dep, ',')) {
            dep.erase(remove_if(dep.begin(), dep.end(), ::isspace), dep.end());
            if (t != 1 && taskNames.find(dep) == taskNames.end()) {
                cout << "Error: Task '" << task.name << "' depends on non-existent task '" << dep << "'!\n";
                return false;
            }
            dependencies.push_back(dep);
        }
    }

    task.dependencies = dependencies;
    taskMap[task.name] = task;
    taskNames.insert(task.name);

    for (const string &dep : dependencies) {
        adjList[dep].push_back(task.name);
        inDegree[task.name]++;
    }

    if (inDegree.find(task.name) == inDegree.end()) {
        inDegree[task.name] = 0;
    }

    if (t != 1 && !createExecutionOrder()) {
        taskMap.erase(task.name);
        taskNames.erase(task.name);
        for (const string &dep : dependencies) {
            adjList[dep].pop_back();
            inDegree[task.name]--;
        }
        return false;
    }
    generateDOTFile();
    return true;
}

void deleteTask() {
    string taskName;
    cout << "Enter the task name to delete: ";
    cin >> taskName;

    if (taskMap.find(taskName) == taskMap.end()) {
        cout << "Error: Task '" << taskName << "' does not exist!\n";
        return;
    }

    taskMap.erase(taskName);
    taskNames.erase(taskName);
    inDegree.erase(taskName);
    adjList.erase(taskName);

    for (auto &entry : adjList) {
        entry.second.erase(remove(entry.second.begin(), entry.second.end(), taskName), entry.second.end());
    }

    createExecutionOrder();
    cout << "Task '" << taskName << "' deleted successfully.\n";
    generateDOTFile();
}

void reprioritizeTask() {
    string taskName;
    int newPriority;
    cout << "Enter the task name to change priority: ";
    cin >> taskName;

    if (taskMap.find(taskName) == taskMap.end()) {
        cout << "Error: Task '" << taskName << "' does not exist!\n";
        return;
    }

    cout << "Enter new priority: ";
    cin >> newPriority;
    taskMap[taskName].priority = newPriority;

    createExecutionOrder();
    cout << "Priority updated successfully.\n";
}

void displayExecutionOrder() {
    if (executionOrder.empty()) {
        cout << "No valid execution order available.\n";
        return;
    }

    cout << "\nOptimized Task Execution Order:\n";
    for (const string &taskName : executionOrder) {
        Task &task = taskMap[taskName];
        cout << task.name << " | Priority: " << task.priority << " | Deadline: " << task.deadline << endl;
    }
}

void markTaskCompleted() {
    string taskName;
    cout << "Enter the task name to mark as completed: ";
    cin >> taskName;

    if (taskMap.find(taskName) == taskMap.end()) {
        cout << "Error: Task '" << taskName << "' does not exist!\n";
        return;
    }

    taskMap.erase(taskName);
    taskNames.erase(taskName);
    completedTasks.insert(taskName);

    for (auto &entry : adjList) {
        entry.second.erase(remove(entry.second.begin(), entry.second.end(), taskName), entry.second.end());
    }
    adjList.erase(taskName);
    inDegree.erase(taskName);

    createExecutionOrder();
    cout << "Task '" << taskName << "' marked as completed.\n";
    generateDOTFile(); 
}

void displayAllDependencies() {
    cout << "\nTask Dependencies:\n";
    for (const auto &entry : taskMap) {
        cout << "Task: " << entry.first << " | Dependencies: ";
        if (entry.second.dependencies.empty()) {
            cout << "None";
        } else {
            for (const string &dep : entry.second.dependencies) {
                cout << dep << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter number of tasks: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        if (!addTask(1)) return 0;
    }

    if (!createExecutionOrder()) return 0;

    displayExecutionOrder();

    int choice;
    while (true) {
        cout << "\nTask Scheduler Menu:\n";
        cout << "1. Add Task\n2. Change Priority\n3. Display Execution Order\n4. Mark Task as Completed\n5. Delete Task\n6. Display All Dependencies\n7. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addTask(2); break;
            case 2: reprioritizeTask(); break;
            case 3: displayExecutionOrder(); break;
            case 4: markTaskCompleted(); 
                    cout<<"Updated execution Order : "<<endl;
                    displayExecutionOrder();
                    break;
            case 5: deleteTask();
                    cout<<"Updated execution Order : "<<endl;
                    displayExecutionOrder();
                    break;
            case 6: displayAllDependencies(); break;
            case 7: cout << "Exiting program...\n"; return 0;
            default: cout << "Invalid choice! Please try again.\n";
        }
    }
}
