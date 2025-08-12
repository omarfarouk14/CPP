/*
Author: omar ali
*/

#ifndef USERS_HPP
#define USERS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "dataHandling.hpp"
#include "flight.hpp"
#include "aircraft.hpp"

enum rank
{
    ADMINISTRATOR,
    BOOKING_AGENT
};

class User
{
private:
    std::string username;
    std::string password;
    std::string email;
    std::string phone;
    std::string name;
    std::string address;
    std::string userID;
    int loyaltyPoints = 0;

public:
    User(std::string &, std::string &, std::string &, std::string &, std::string &, std::string &);
    virtual bool logout(void) = 0;
    virtual bool viewProfile(void) = 0;
    virtual bool editProfile(void);
    bool deleteProfile(void);
    bool registerUser(void);

    bool SearchUser(std::string &userId); // view its profile

    std::string getUsername(void) const;
    std::string getPassword(void) const;
    std::string getEmail(void) const;
    std::string getPhone(void) const;
    std::string getName(void) const;
    std::string getAddress(void) const;
    std::string getUserID(void) const;

    int getLoyaltyPoints(void) const;
    void setLoyaltyPoints(int);

    bool setUserId(const std::string &userId);
    bool setUsername(const std::string &username);
    bool setPassword(const std::string &password);
    bool setEmail(const std::string &email);
    bool setPhone(const std::string &phone);
    bool setName(const std::string &name);
    bool setAddress(const std::string &address);
};

class Passenger : public User
{

public:
    Passenger(std::string &, std::string &, std::string &, std::string &, std::string &, std::string &);
    static std::shared_ptr<Passenger> login(void);
    bool logout(void) override;
    bool viewProfile(void) override;
    bool editProfile(void) override;

    bool bookFlight(void);
    bool cancelFlight(void);
    bool viewPassengerFlightHistory(void);

    bool viewLoyaltyPoints(void);
    bool redeemLoyaltyPoints(void);

    bool SearchUser(std::string &userId) = delete; // passengers can't search for other users
    bool registerUser(void) = delete;              // passengers can't register themselves
};

class Administrator : public User
{

private:
public:
    Administrator(std::string &, std::string &, std::string &, std::string &, std::string &, std::string &);
    static std::shared_ptr<Administrator> login(void) ;
    bool logout(void) override;
    bool viewProfile(void) override;
    bool editProfile(void) override;

    bool addFlight(void);
    bool removeFlight(void);
    bool viewFlightSchedules(void);

    bool addNewAdmin(void);
    bool addNewBookingAgent(void);

    bool addNewCrewMember(void);
    bool removeCrewMember(void);
    bool viewCrewMembers(void);

    bool addNewAircraft(void);
    bool removeAircraft(void);
    bool viewAircrafts(void);

    int getLoyaltyPoints(void) const = delete;
};

class BookingAgent : public User
{
public:
    BookingAgent(std::string &, std::string &, std::string &, std::string &, std::string &, std::string &);
    static std::shared_ptr<BookingAgent> login(void) ;
    bool logout(void) override;
    bool viewProfile(void) override;
    bool editProfile(void) override;

    bool assistCheckIn(void);
    bool handlePayment(void);

    int getLoyaltyPoints(void) const = delete;
};

#endif