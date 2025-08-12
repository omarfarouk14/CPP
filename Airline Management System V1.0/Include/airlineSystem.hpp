/*
Author: omar aly
*/

#ifndef AIRLINE_SYSTEM_HPP
#define AIRLINE_SYSTEM_HPP

#include <iostream>
#include <memory>
#include "users.hpp"
#include "flight.hpp"
#include "aircraft.hpp"
#include "dataHandling.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <limits> // for std::numeric_limits

class AirlineSystem
{
public:
    void run();

private:
    void displayMainMenu();
    void passengerHandler(std::shared_ptr<Passenger> passenger);
    void bookingAgentHandler(std::shared_ptr<BookingAgent> agent);
    void administratorHandler(std::shared_ptr<Administrator> admin);
    void displayPassengerMenu();
    void displayBookingAgentMenu();
    void displayAdministratorMenu();
};

#endif
