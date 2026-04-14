#ifndef BOOKING_H
#define BOOKING_H

#include <string>

class Booking {
public:
    int BookingId;
    int roomId;
    std::string host;
    int startTime;
    int endTime;

    Booking(int id, int rId, std::string h, int s, int e) {
        BookingId = id;
        roomId = rId;
        host = h;
        startTime = s;
        endTime = e;
    }
};

#endif