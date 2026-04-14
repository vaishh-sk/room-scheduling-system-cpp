#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

int convertToMinutes(string time) {
    // 🔥 Step 1: remove extra spaces at start
    while (!time.empty() && time[0] == ' ') time.erase(0, 1);

    // 🔥 Step 2: convert to lowercase
    transform(time.begin(), time.end(), time.begin(), ::tolower);

    // 🔥 Step 3: remove dots (a.m. → am)
    time.erase(remove(time.begin(), time.end(), '.'), time.end());

    int hour, minute;
    string period;

    stringstream ss(time);

    ss >> hour;
    ss.ignore(1); // skip ':'
    ss >> minute >> period;

    if (ss.fail()) {
        cout << "❌ Invalid time format!\n";
        return -1;
    }

    // 🔥 Normalize AM/PM
    if (period == "am") {
        if (hour == 12) hour = 0;
    } else if (period == "pm") {
        if (hour != 12) hour += 12;
    } else {
        cout << "❌ Use AM or PM!\n";
        return -1;
    }

    return hour * 60 + minute;
}

string convertTo12Hour(int minutes) {
    int hour = minutes / 60;
    int min = minutes % 60;

    string period = (hour >= 12) ? "PM" : "AM";

    if (hour == 0) hour = 12;
    else if (hour > 12) hour -= 12;

    return (hour < 10 ? "0" : "") + to_string(hour) + ":" +
           (min < 10 ? "0" : "") + to_string(min) + " " + period;
}

#endif