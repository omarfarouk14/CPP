/*
Author: omar ali
*/

#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <memory>
#include <map>

class Flight;
class Passenger;
class PaymentMethod;
class Aircraft;
class Crew;
class Reservation;

std::map<std::string, double> crewSalaryPerHourIn$ = {
    {"Pilot", 96.00},
    {"Flight Attendant", 28.0}};

    
// المفروض يقري من الفايل الكرو الموجودين
class Crew
{
private:
    std::string crewID;
    std::string name;
    std::string role;
    int salary;

protected:
    Crew(const std::string &, const std::string &);

public:
    virtual bool assignSalary(double duration) = 0;
    virtual bool viewCrewDetails() = 0;
    virtual bool deleteCrew() = 0;

    std::string getCrewID() const;
    std::string getCrewName() const;
    std::string getCrewRole() const;

    int getSalary(void) const;
    bool setSalary(int amount);

    bool setUserId(std::string);
};

class Pilot : public Crew
{
public:
    Pilot(const std::string &name, const std::string &role = "Pilot");
    bool assignSalary(double duration);
    bool viewCrewDetails();
    bool editCrewDetails();
    bool deleteCrew();
};

class FlightAttendant : public Crew
{
public:
    FlightAttendant(const std::string &name, const std::string &role = "Flight Attendant");
    bool assignSalary(double duration);
    bool viewCrewDetails();
    bool editCrewDetails();
    bool deleteCrew();
};

class Seat
{
private:
    std::string seatID;
    std::string seatClass;
    bool isAvailable;

public:
    bool viewAvailableSeats();
    bool bookSeat();
    bool cancelSeat();

    std::string getSeatID() const;
    std::string getSeatClass() const;
    bool getIsAvailable() const;
    void setIsAvailable(bool available);
};
/*
    implement strategy pattern for payment methods
*/
class PaymentMethod
{

public:
    virtual bool processPayment(double amount) = 0;
    virtual bool refundPayment() = 0;
};

class PaypalMethod : public PaymentMethod
{
public:
    bool processPayment(double amount) override;
    bool refundPayment() override;
};

class CreditCardMethod : public PaymentMethod
{

public:
    bool processPayment(double amount) override;
    bool refundPayment() override;
};

class CashMethod : public PaymentMethod
{

public:
    bool processPayment(double amount) override;
    bool refundPayment() override;
};

class Payment
{
private:
    std::shared_ptr<PaymentMethod> paymentMethod;
    double amount;
    bool status;
    std::string transactionID;
    std::string date;

public:
    Payment(std::shared_ptr<PaymentMethod> method);
    bool pay(double amount);
    bool refund();
    double getAmount() const;
};

class Reservation
{
private:
    std::string reservationID;
    std::string flightID;
    std::string passengerID;
    std::string seatID;
    std::string date;
    std::string status;
    Seat seat;
    Payment payment;
    std::shared_ptr<Flight> flight;
    std::shared_ptr<Passenger> passenger;

public:
    Reservation(std::shared_ptr<Flight> flight, std::shared_ptr<Passenger> passenger, std::shared_ptr<PaymentMethod> payment);
    bool bookFlight();
    bool deleteReservation();
    bool viewReservation();

    std::string getReservationID() const;
    std::string getFlightID() const;
    std::string getPassengerID() const;
    std::string getSeatID() const;
    std::string getDate() const;
    std::string getStatus() const;
    bool checkIn();
};

class Flight
{
private:
    std::string flightID;
    std::string departure;
    std::string arrival;
    std::string date;
    int duration;
    int capacity;
    int availableSeats;
    double price;
    std::string status = "on time";
    std::shared_ptr<Aircraft> aircraft;
    std::vector<std::shared_ptr<Crew>> crewMembers;
    std::vector<std::shared_ptr<Passenger>> passengers;
    std::vector<std::shared_ptr<Crew>> crew;
    std::vector<std::shared_ptr<Reservation>> reservations;

public:
    Flight(std::string departure, std::string arrival, std::string date, int duration, double price,
           std::shared_ptr<Aircraft> aircraft);

    bool addCrewMember(std::shared_ptr<Crew> crewMember);
    bool removeCrewMember(std::shared_ptr<Crew> crewMember);

    bool addPassenger(std::shared_ptr<Passenger> passenger);
    bool removePassenger(std::shared_ptr<Passenger> passenger);

    bool assignAircraft(std::shared_ptr<Aircraft> aircraft);

    double getFlightDuration() const;

    bool editFlightDetails();
    bool cancelFlight();

    bool viewAvailableSeats();
    bool viewCrewMembers();
    bool viewPassengers();
    bool viewFlightHistory();
    bool viewFlightDetails();

    bool addReservation(std::shared_ptr<Reservation> reservation);
    bool removeReservation(std::shared_ptr<Reservation> reservation);
    bool checkAvailability();
    bool updateFlightStatus(const std::string& newStatus);

    std::string getFlightID() const;
    std::string getDeparture() const;
    std::string getArrival() const;
    std::string getDate() const;
    int getDuration() const;
    int getCapacity() const;
    int getAvailableSeats() const;
    double getPrice() const;
    std::string getStatus() const { return status; }
    std::string getAircraftID() const;
    std::vector<std::shared_ptr<Crew>> getCrewMembers() const;
    std::vector<std::shared_ptr<Passenger>> getPassengers() const;
};
#endif