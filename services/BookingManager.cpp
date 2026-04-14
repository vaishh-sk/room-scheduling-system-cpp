#include <algorithm>
#include <iostream>
#include "BookingManager.h"
#include "../utils/timeutils.h"
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

void BookingManager::createBooking() {
    int id, roomId, start, end;
    string host;
    string startStr, endStr;

    id = nextId++;
    cout << " Schedule ID: " << id << "\n";

    cout << "Enter Room ID: ";
    cin >> roomId;

    cout << "Room Capacity: " << roomCapacity[roomId] << "\n";
    
    cin.ignore(); // To consume the newline character left by previous input

    cout << "Enter Organizer Name: ";
    getline(cin, host); // To consume the newline character left by previous input
    if (host.empty()) {
    cout << " Organizer name cannot be empty.\n";
    return;
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Start Time (HH:MM AM/PM): ";
    getline(cin, startStr);

    cout << "Enter End Time (HH:MM AM/PM): ";
    getline(cin, endStr);
    
    

    // Convert time strings to minutes
    start = convertToMinutes(startStr);
    end = convertToMinutes(endStr);

    if (start == -1 || end == -1) {
        return;
    }

    //  Step 1: Validate time
    if (start >= end) {
        cout << " Invalid time range!\n";
        return;
    }

     //  Step 2: Check conflict
    for (auto &existing : roomBookings[roomId]) {
        if (start < existing.endTime && end > existing.startTime) {
            cout << " Scheduling conflict detected. \n";
            cout << " Room "  << roomId << " is already scheduled from " << convertTo12Hour(existing.startTime) << " to " << convertTo12Hour(existing.endTime) << " by " << existing.host << ".\n";
            cout << " Please choose a different time slot.\n";
            return;
        }
    }
    Booking b(id,roomId,host,start,end);
    roomBookings[roomId].push_back(b);
    saveToFile();
    cout <<"Room Scheduled Successfully!\n";
}

void BookingManager::viewBookings() {
    if(roomBookings.empty()) {
        cout << "\nNo Schedules Found.\n";
        return;
    }


    cout <<"\n====== ALL SCHEDULES ======\n";
    for(auto &pair : roomBookings) {
        cout << "\nRoom Number: " << pair.first << "\n";
        auto schedules = pair.second;
        sort(schedules.begin(), schedules.end(), [](auto &a, auto &b) {
            return a.startTime < b.startTime;
        });
        cout << "\nRoom " << pair.first << endl;
        cout << "-------------------------------------\n";
        for(auto &b : schedules) {
          
            cout << " Schedule ID: " << b.BookingId << "\n";
            cout << " | Room Number: " << b.roomId << "\n";
            cout << " | Organizer : " << b.host << "\n";
            cout << " | Time: " << convertTo12Hour(b.startTime) << " - " << convertTo12Hour(b.endTime) << "\n";
        }
    }
}

void BookingManager::viewBookingsByRoom() {
    int roomId;
    cout << "\nEnter Room Number to view schedules: ";
    cin >> roomId;

    if(roomBookings.find(roomId) == roomBookings.end()) {
        cout << "\nNo Schedules Available for Room Number: " << roomId << "\n";
        return;
    }

    cout <<"\n====== SCHEDULES FOR ROOM NUMBER: " << roomId << " ======\n";
    auto schedules = roomBookings[roomId];
        sort(schedules.begin(), schedules.end(), [](auto &a, auto &b) {
                return a.startTime < b.startTime;
            });
    for(auto &b : schedules) {
        cout << " Schedule ID: " << b.BookingId << "\n";
        cout << " | Organizer : " << b.host << "\n";
        cout << " | Time: " << convertTo12Hour(b.startTime) << " - " << convertTo12Hour(b.endTime) << "\n";
    }
}

void BookingManager::cancelSchedule() {
    int scheduleId;
    cout << "\nEnter Schedule ID to cancel: ";
    cin >> scheduleId;

    bool found = false;

    for (auto &pair : roomBookings) {
        auto &schedules = pair.second;

        for (auto it = schedules.begin(); it != schedules.end(); ) {
            if (it->BookingId == scheduleId) {
                char confirm;
                cout << "Are you sure you want to cancel this schedule? (y/n): ";
                cin >> confirm;

                if (confirm != 'y' && confirm != 'Y') {
                    cout << " Cancellation aborted.\n";
                    return;
                }
                

                schedules.erase(it);
                saveToFile();
                cout << " Schedule cancelled successfully.\n";

                found = true;
                return;
            } else {
                ++it;
            }
        }
    }

    if (!found) {
        cout << " Schedule ID not found.\n";
    }
}

void BookingManager::saveToFile() {
    cout << "\nSaving schedules to file...\n";
    ofstream file("data/bookings.txt");
    if (!file) {
        cout << "Error opening file!\n";
        return;
    }
    file << " Schedule ID | Room ID | Organizer | Start Time | End Time\n";
    file << "---------------------------------------------\n";
    vector<Booking> allSchedules;

// Collect all schedules
for (auto &pair : roomBookings) {
    for (auto &b : pair.second) {
        allSchedules.push_back(b);
    }
}

// Sort by Schedule ID
sort(allSchedules.begin(), allSchedules.end(), [](const Booking &a, const Booking &b) {
    return a.BookingId < b.BookingId;
});

// Write sorted data to file
for (auto &b : allSchedules) {
    file << b.BookingId << " | "
         << b.roomId << " | "
         << b.host << " | "
         << convertTo12Hour(b.startTime) << " | "
         << convertTo12Hour(b.endTime)
         << "\n";
}

    file.close();
}

void BookingManager::loadFromFile() {
    ifstream file("data/bookings.txt");

    if (!file) return;

    string line;

    getline(file, line); // Skip header
    getline(file, line); // Skip separator

    while (getline(file, line)) {
        stringstream ss(line);

        string idStr, roomStr, host, startStr, endStr;

        getline(ss, idStr, '|');
        getline(ss, roomStr, '|');
        getline(ss, host, '|');
        getline(ss, startStr, '|');
        getline(ss, endStr, '|');

        int id = stoi(idStr);
        int roomId = stoi(roomStr);

        // trim spaces
        auto trim = [](string &s) {
            while (!s.empty() && s[0] == ' ') s.erase(0,1);
            while (!s.empty() && s.back() == ' ') s.pop_back();
        };

        trim(host);
        trim(startStr);
        trim(endStr);

        int start = convertToMinutes(startStr);
        int end   = convertToMinutes(endStr);

        Booking b(id, roomId, host, start, end);
        roomBookings[roomId].push_back(b);
    }

    file.close();
}

void BookingManager::searchById() {
    int id;
    cout << "\nEnter Schedule ID: ";
    cin >> id;

    bool found = false;

    for (auto &pair : roomBookings) {
        for (auto &b : pair.second) {
            if (b.BookingId == id) {

                cout << "\n Schedule Found:\n";
                cout << "Room: " << b.roomId << "\n";
                cout << "Organizer: " << b.host << "\n";
                cout << "Time: "
                     << convertTo12Hour(b.startTime)
                     << " - "
                     << convertTo12Hour(b.endTime) << "\n";

                found = true;
                return;
            }
        }
    }

    if (!found) {
        cout << " Schedule not found.\n";
    }
}

void BookingManager::searchByOrganizer() {
    cin.ignore(); // clear buffer

    string name;
    cout << "\nEnter Organizer Name: ";
    getline(cin, name);

    bool found = false;

    for (auto &pair : roomBookings) {
        for (auto &b : pair.second) {

            if (b.host == name) {
                if (!found) {
                    cout << "\n Schedules found:\n";
                }

                cout << "ID: " << b.BookingId
                     << " | Room: " << b.roomId
                     << " | Time: "
                     << convertTo12Hour(b.startTime)
                     << " - "
                     << convertTo12Hour(b.endTime)
                     << "\n";

                found = true;
            }
        }
    }

    if (!found) {
        cout << " No schedules found for this organizer.\n";
    }
}

void BookingManager::updateSchedule() {
    int id;
    cout << "\nEnter Schedule ID to update: ";
    cin >> id;

    for (auto &pair : roomBookings) {
        for (auto &b : pair.second) {

            if (b.BookingId == id) {

                cout << "\n1. Change Organizer\n";
                cout << "2. Change Time\n";
                cout << "3. Exit\n";

                int choice;
                cout << "Enter choice: ";
                cin >> choice;

                cin.ignore(); // important

                if (choice == 1) {
                    string newName;
                    cout << "Enter new organizer name: ";
                    getline(cin, newName);

                    //  CONFIRM HERE
                    char confirm;
                    cout << "Confirm update? (y/n): ";
                    cin >> confirm;
                    cin.ignore();

                    if (confirm != 'y' && confirm != 'Y') {
                        cout << " Update cancelled.\n";
                        return;
                    }

                    // Apply change
                    b.host = newName;
                    cout << " Organizer updated.\n";
                }
                else if (choice == 2) {
                    string start, end;

                    cout << "Enter new start time: ";
                    getline(cin, start);

                    cout << "Enter new end time: ";
                    getline(cin, end);

                    int newStart = convertToMinutes(start);
                    int newEnd   = convertToMinutes(end);

                    // validate
                    if (newStart >= newEnd) {
                        cout << " Invalid time range.\n";
                        return;
                    }

                    // check conflict (your existing logic here)

                    //  CONFIRM HERE
                    char confirm;
                    cout << "Confirm time update? (y/n): ";
                    cin >> confirm;
                    cin.ignore();

                    if (confirm != 'y' && confirm != 'Y') {
                        cout << " Update cancelled.\n";
                        return;
                    }

                    // Apply update
                    b.startTime = newStart;
                    b.endTime   = newEnd;

                    cout << " Time updated successfully.\n";

                    //  check conflict before updating
                    bool conflict = false;

                    for (auto &other : pair.second) {
                        if (other.BookingId != id &&
                            !(newEnd <= other.startTime || newStart >= other.endTime)) {
                            conflict = true;
                            break;
                        }
                    }

                    if (conflict) {
                        cout << " Time conflict with existing schedule.\n";
                    } else {
                        b.startTime = newStart;
                        b.endTime   = newEnd;
                        cout << " Time updated successfully.\n";
                    }
                }

                //  Save after update
                saveToFile();

                return;
            }
        }
    }

    cout << " Schedule ID not found.\n";
}

BookingManager::BookingManager() {

roomCapacity[101] = 10;
roomCapacity[102] = 20;
roomCapacity[103] = 15;
nextId = 1;
}