# Optimized Task Scheduling System (CLI-Based)

## 🚀 Overview
The **Optimized Task Scheduling System** is a command-line interface (CLI) application designed to efficiently assign tasks based on resource availability, priority, deadlines, and dependencies. The system utilizes **Priority Queues** for task prioritization, **Greedy Algorithms** for optimal task assignment, and **Graph Theory (Topological Sorting)** to manage dependencies.

This CLI-based task scheduler allows users to add, update, delete, and view tasks. It ensures an optimized execution order while detecting and preventing circular dependencies. Additionally, the system generates a **Graphviz DOT file** for task dependency visualization.

## 🛠️ Technologies & Algorithms Used
- **C++** (for high-performance task management)
- **Graph Theory (Topological Sorting)** (for dependency resolution)
- **Priority Queue (Min-Heap)** (for efficient task prioritization)
- **Greedy Algorithms** (for optimal task execution order)
- **Graphviz** (for visualizing task dependencies)

## 🎯 Features
✅ **Task Management**: Add, update, and delete tasks with priority levels and deadlines.
✅ **Optimized Scheduling**: Utilizes priority queues and greedy algorithms to efficiently assign tasks.
✅ **Dependency Handling**: Ensures correct execution order using topological sorting and detects circular dependencies.
✅ **Task Visualization**: Generates a Graphviz DOT file to visually represent task dependencies.
✅ **Reprioritization**: Allows users to update task priorities dynamically.
✅ **Execution Order Display**: Provides the optimal order of task execution.

## 🚀 Installation & Setup
### Prerequisites
Ensure you have the following installed:
- **C++ Compiler** (e.g., GCC, Clang, MSVC)
- **Graphviz** (for generating task dependency graphs)

### Steps to Run the Project
1. **Clone the Repository**:
   ```sh
   git clone https://github.com/DineshDumka/CLI-TaskScheduler.git
   cd CLI-TaskScheduler
   ```
2. **Compile the Code**:
   ```sh
   g++ -o task_scheduler task_scheduler.cpp
   ```
3. **Run the Application**:
   ```sh
   ./task_scheduler
   ```
4. **Generate Task Dependency Graph** (if using Graphviz):
   ```sh
   dot -Tpng tasks.dot -o tasks.png
   ```

## 📌 Usage
### Available Commands:
- **Add Task**: Enter task name, priority, deadline, and dependencies.
- **Delete Task**: Remove a task and update dependencies accordingly.
- **Reprioritize Task**: Modify the priority of an existing task.
- **Display Execution Order**: Show the optimal order of task execution.
- **Visualize Dependencies**: Generate a Graphviz DOT file for dependency visualization.

## 🤝 Contributors
- **Dinesh Dumka**

## 📬 Contact
For any questions or feedback, feel free to reach out! 😊

