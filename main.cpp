#include <iostream>
#include "services/BookingManager.h"
using namespace std;

int main() {
    BookingManager manager;
    int choice;

    while (true) {
        cout << "/n==============================\n";
        cout << "==== ROOM SCHEDULING SYSTEM ====\n";
        cout << "==============================\n";
        cout << "1. Create Schedule\n";
        cout << "2. View All Schedules\n";
        cout << "3. View Schedule by Room ID\n";
        cout << "4. Search by Schedule ID\n";
        cout << "5. Search by Organizer Name\n";
        cout << "6. Update Schedule\n";
        cout << "7. Cancel Schedule\n";
        cout << "8. Exit\n";
        cout << "==============================\n";
        
        while (true) {
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice >= 1 && choice <= 8) break;

            cout << " Invalid choice. Try again.\n";
        }

        switch (choice) {
            case 1:
                manager.createBooking();
                break;
            case 2:
                manager.viewBookings();
                break;
            case 3:
                manager.viewBookingsByRoom();
                break;
            
            case 4:
                manager.searchById();
                break;
            case 5:
                manager.searchByOrganizer();
                break;
            case 6:
                manager.updateSchedule();
                break;
            case 7:
                manager.cancelSchedule();
                break;
            case 8:
                cout << "Thank you for using Room Scheduling System!\n";
                return 0;

        }
    }
}