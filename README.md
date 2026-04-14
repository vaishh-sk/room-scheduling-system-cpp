# Room Scheduling System (C++)

A CLI-based Room Scheduling System built using C++ and STL that enables users to create, manage, and organize room schedules efficiently. The system includes conflict detection, search functionality, and persistent file storage, simulating real-world scheduling applications used in offices, colleges, and organizations.

## Features
- Create, view, update, and delete schedules (CRUD operations)
- Prevents double booking using time conflict detection
- Search functionality by Schedule ID and Organizer name
- View schedules based on Room ID
- Auto-generated unique Schedule IDs
- Persistent data storage using file handling (fstream)
- Sorted data storage for better readability
- User-friendly CLI with structured output
- Input validation for reliable data handling
- Confirmation prompts for critical operations (update/delete)
- Basic room capacity display feature

## Tech Highlights
- Implemented using C++ with Object-Oriented Programming principles
- Utilized STL containers like vector and map for efficient data management
- Designed modular architecture (models, services, utils)
- Implemented time handling using internal minute-based conversion
- Developed conflict detection logic using interval comparison
- Ensured data persistence through file handling (ifstream/ofstream)
- Applied sorting algorithms for organized data storage
- Built scalable and maintainable CLI-based system design

## Tech Stack
- C++
- Standard Template Library (STL)
- File Handling (fstream)

## Use Case
This system can be used in offices, colleges, or organizations to manage meeting rooms, labs, or shared spaces efficiently.

## How to 
1. Clone the repository
2. Open terminal in project directory
3. Compile:
            g++ main.cpp services/BookingManager.cpp -o app
4. Execute: 
            ./app

