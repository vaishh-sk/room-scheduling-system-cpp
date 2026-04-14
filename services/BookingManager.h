#ifndef BOOKINGMANAGER_H
#define BOOKINGMANAGER_H

#include <vector>
#include <unordered_map>
#include "../models/Booking.h"
#include <map>


class BookingManager {
    int nextId;
private:
    std::unordered_map<int, std::vector<Booking>> roomBookings;
    std::map<int, int> roomCapacity;
public:
    BookingManager();
    void createBooking();
    void viewBookings();
    void viewBookingsByRoom();
    void cancelSchedule();
    void saveToFile();
    void loadFromFile();
    void searchById();
    void searchByOrganizer();
    void updateSchedule();
};

#endif