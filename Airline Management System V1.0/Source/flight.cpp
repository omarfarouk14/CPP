/*
Author: omar ali
*/
#include "../Include/aircraft.hpp"
#include "../Include/users.hpp"
#include "../Include/dataHandling.hpp"
#include "../Include/flight.hpp"
/*
    Flight class implementation
*/
Flight::Flight(std::string departure, std::string arrival, std::string date, int duration, double price,
               std::shared_ptr<Aircraft> aircraft)
    : departure(departure), arrival(arrival), date(date), duration(duration), price(price),
      availableSeats(capacity), aircraft(aircraft)
{
    this->flightID = DataHandling::generateUniqueID("flights.json");
    this->capacity = aircraft->getCapacity();
    this->availableSeats = capacity;
    DataHandling::saveData(std::make_shared<Flight>(*this), "flights.json");
}

bool Flight::addCrewMember(std::shared_ptr<Crew> crewMember)
{
    if (crewMember)
    {
        crewMembers.push_back(crewMember);
        DataHandling::saveData(std::make_shared<Flight>(*this), "flights.json");
        return true;
    }
    return false;
}

bool Flight::removeCrewMember(std::shared_ptr<Crew> crewMember)
{
    auto it = std::find(crewMembers.begin(), crewMembers.end(), crewMember);
    if (it != crewMembers.end())
    {
        crewMembers.erase(it);
        DataHandling::saveData(std::make_shared<Flight>(*this), "flights.json");
        return true;
    }
    return false;
}

bool Flight::addPassenger(std::shared_ptr<Passenger> passenger)
{
    if (passenger && availableSeats > 0)
    {
        passengers.push_back(passenger);
        availableSeats--;
        DataHandling::saveData(std::make_shared<Flight>(*this), "flights.json");
        return true;
    }
    return false;
}

bool Flight::removePassenger(std::shared_ptr<Passenger> passenger)
{
    auto it = std::find(passengers.begin(), passengers.end(), passenger);
    if (it != passengers.end())
    {
        passengers.erase(it);
        availableSeats++;
        DataHandling::saveData(std::make_shared<Flight>(*this), "flights.json");
        return true;
    }
    return false;
}

bool Flight::assignAircraft(std::shared_ptr<Aircraft> aircraft)
{
    if (aircraft)
    {
        this->aircraft = aircraft;
        DataHandling::saveData(std::make_shared<Flight>(*this), "flights.json");
        return true;
    }
    return false;
}

double Flight::getFlightDuration() const
{
    return duration;
}

bool Flight::editFlightDetails()
{
    std::string newDeparture, newArrival, newDate;
    int newDuration;
    double newPrice;

    while (1)
    {
        std::cout << "Enter which field you want to edit: " << std::endl;
        std::cout << "1. Departure" << std::endl;
        std::cout << "2. Arrival" << std::endl;
        std::cout << "3. Date" << std::endl;
        std::cout << "4. Duration" << std::endl;
        std::cout << "5. Price" << std::endl;
        std::cout << "6. Aircraft" << std::endl;
        std::cout << "7. Exit" << std::endl;
        int choice;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            std::cout << "Enter new departure location: ";
            std::cin >> newDeparture;
            departure = newDeparture;
            break;
        case 2:
            std::cout << "Enter new arrival location: ";
            std::cin >> newArrival;
            arrival = newArrival;
            break;
        case 3:
            std::cout << "Enter new date (YYYY-MM-DD): ";
            std::cin >> newDate;
            date = newDate;
            break;
        case 4:
            std::cout << "Enter new duration (in hours): ";
            std::cin >> newDuration;
            duration = newDuration;
            break;
        case 5:
            std::cout << "Enter new price: ";
            std::cin >> newPrice;
            price = newPrice;
            break;
        case 6:
        {
            std::cout << "Available Aircrafts: " << std::endl;
            auto availableAircrafts = DataHandling::loadAllAircraftData("aircraft.json");
            if (availableAircrafts.empty())
            {
                std::cout << "No available aircrafts to choose from." << std::endl;
                break;
            }

            int index = 1;
            for (const auto &aircraft : availableAircrafts)
            {
                std::cout << index++ << ". Model: " << aircraft->getAircraftType()
                          << ", Capacity: " << aircraft->getCapacity() << std::endl;
            }

            std::cout << "Enter the number of the aircraft you want to assign: ";
            int choice;
            std::cin >> choice;

            auto selectedAircraft = availableAircrafts[choice - 1];
            if (assignAircraft(selectedAircraft))
            {
                capacity = selectedAircraft->getCapacity();
                availableSeats = capacity - (capacity - availableSeats); // Adjust available seats
                std::cout << "Aircraft updated successfully." << std::endl;
            }
            else
            {
                std::cout << "Failed to update aircraft." << std::endl;
            }
        }
        break;
        case 7:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            continue; // Continue the loop for invalid choice
        }
        if (choice == 7)
            break; // Exit the loop if the user chooses to exit
    }

    // Save the updated flight details
    DataHandling::saveData(std::make_shared<Flight>(*this), "flights.json");
    return true;
}

bool Flight::cancelFlight()
{
    // Logic to cancel the flight
    passengers.clear();
    crewMembers.clear();
    availableSeats = capacity;
    DataHandling::removeData(std::make_shared<Flight>(*this), "flights.json");
    return true;
}

bool Flight::viewAvailableSeats()
{
    std::cout << "Available Seats: " << availableSeats << std::endl;
    return true;
}

bool Flight::viewCrewMembers()
{
    std::cout << "Crew Members:" << std::endl;
    for (const auto &crew : crewMembers)
    {
        std::cout << crew->getCrewName() << "," << crew->getCrewRole() << std::endl;
    }
    return true;
}

bool Flight::viewPassengers()
{
    std::cout << "Passengers:" << std::endl;
    for (const auto &passenger : passengers)
    {
        std::cout << passenger->getName() << std::endl; // Assuming Passenger has a getName() method
    }
    return true;
}

bool Flight::viewFlightDetails()
{
    std::cout << "Flight Details:" << std::endl;
    std::cout << "Departure: " << departure << std::endl;
    std::cout << "Arrival: " << arrival << std::endl;
    std::cout << "Date: " << date << std::endl;
    std::cout << "Duration: " << duration << " hours" << std::endl;
    std::cout << "Capacity: " << capacity << std::endl;
    std::cout << "Available Seats: " << availableSeats << std::endl;
    std::cout << "Price: $" << price << std::endl;
    return true;
}

bool Flight::addReservation(std::shared_ptr<Reservation> reservation)
{
    if (reservation)
    {
        this->reservations.push_back(reservation);
        DataHandling::saveData(std::make_shared<Flight>(*this), this->reservations, "flights.json");
        return true;
    }
    return false;
}

bool Flight::removeReservation(std::shared_ptr<Reservation> reservation)
{
    auto it = std::find(this->reservations.begin(), this->reservations.end(), reservation);
    if (it != this->reservations.end())
    {
        this->reservations.erase(it);
        DataHandling::saveData(std::make_shared<Flight>(*this), this->reservations, "flights.json");
        return true;
    }
    return false;
}

bool Flight::checkAvailability()
{
    return availableSeats > 0;
}

std::string Flight::getFlightID() const
{
    return flightID;
}

std::string Flight::getDeparture() const
{
    return departure;
}

std::string Flight::getArrival() const
{
    return arrival;
}

std::string Flight::getDate() const
{
    return date;
}

int Flight::getDuration() const
{
    return duration;
}

int Flight::getCapacity() const
{
    return capacity;
}

int Flight::getAvailableSeats() const
{
    return availableSeats;
}

double Flight::getPrice() const
{
    return price;
}

std::string Flight::getAircraftID() const
{
    return aircraft->getAircraftID();
}

std::vector<std::shared_ptr<Crew>> Flight::getCrewMembers() const
{
    return crewMembers;
}
std::vector<std::shared_ptr<Passenger>> Flight::getPassengers() const
{
    return passengers;
}

bool Flight::updateFlightStatus(const std::string& newStatus) {
    status = newStatus;
    DataHandling::saveData(std::make_shared<Flight>(*this), "flights.json");
    std::cout << "Flight " << flightID << " status updated to " << newStatus << std::endl;
    return true;
}

/*
    Crew class Implementation
*/

Crew::Crew(const std::string &name, const std::string &role)
    : name(name), role(role)
{
    this->crewID = DataHandling::generateUniqueID("crew.json");
    DataHandling::saveData(std::make_shared<Crew>(*this), "crew.json");
}

std::string Crew::getCrewID() const
{
    return this->crewID;
}
std::string Crew::getCrewName() const
{
    return this->name;
}
std::string Crew::getCrewRole() const
{
    return this->role;
}

bool Crew::setUserId(std::string crewID)
{
    this->crewID = crewID;
    return true;
}

int Crew::getSalary(void) const
{
    return this->salary;
}
bool Crew::setSalary(int amount)
{
    this->salary = amount;
    return true;
}

/*
    Pilot class Implementation
*/
Pilot::Pilot(const std::string &name, const std::string &role)
    : Crew(name, role)
{
    this->setUserId(DataHandling::generateUniqueID("pilots.json"));
    DataHandling::saveData(std::make_shared<Pilot>(*this), "pilots.json");
}

bool Pilot::assignSalary(double duration)
{
    if (duration > 0)
    {
        setSalary(duration * crewSalaryPerHourIn$["Pilot"]); // Assuming hourlyRate is a predefined constant
        DataHandling::saveData(std::make_shared<Pilot>(*this), "pilots.json");
        return true;
    }
    return false;
}

bool Pilot::viewCrewDetails()
{
    std::cout << "Pilot Details:" << std::endl;
    std::cout << "Name: " << getCrewName() << std::endl;
    std::cout << "Pilot ID: " << getCrewID() << std::endl;
    std::cout << "Salary: $" << getSalary() << std::endl;
    return true;
}

bool Pilot::deleteCrew()
{
    DataHandling::removeData(std::make_shared<Pilot>(*this), "pilots.json");
    return true;
}

/*
    FlightAttendant class Implementation
*/
FlightAttendant::FlightAttendant(const std::string &name, const std::string &role)
    : Crew(name, role)
{
    this->setUserId(DataHandling::generateUniqueID("flight_attendants.json"));
    DataHandling::saveData(std::make_shared<FlightAttendant>(*this), "flight_attendants.json");
}

bool FlightAttendant::assignSalary(double duration)
{
    if (duration > 0)
    {
        setSalary(duration * crewSalaryPerHourIn$["Flight Attendant"]); // Assuming hourlyRate is a predefined constant
        DataHandling::saveData(std::make_shared<FlightAttendant>(*this), "flight_attendants.json");
        return true;
    }
    return false;
}

bool FlightAttendant::viewCrewDetails()
{
    std::cout << "Flight Attendant Details:" << std::endl;
    std::cout << "Name: " << getCrewName() << std::endl;
    std::cout << "Role: " << getCrewRole() << std::endl;
    std::cout << "Attendant ID: " << getCrewID() << std::endl;
    std::cout << "Salary: $" << getSalary() << std::endl;
    return true;
}

bool FlightAttendant::deleteCrew()
{
    DataHandling::removeData(std::make_shared<FlightAttendant>(*this), "flight_attendants.json");
    return true;
}

/*
    Seat class Implementation
*/
bool Seat::viewAvailableSeats()
{
    std::cout << "Available Seats:" << std::endl;
    auto seats = DataHandling::loadAircraftSeats("seats.json");
    for (const auto &seat : seats)
    {
        if (seat->getIsAvailable())
        {
            std::cout << "Seat ID: " << seat->getSeatID()
                      << ", Class: " << seat->getSeatClass();
        }
    }
    return true;
}

bool Seat::bookSeat()
{
    if (getIsAvailable())
    {
        setIsAvailable(false);
        DataHandling::saveData(std::make_shared<Seat>(*this), "seats.json");
        return true;
    }
    return false;
}

bool Seat::cancelSeat()
{
    if (!getIsAvailable())
    {
        setIsAvailable(true);
        DataHandling::saveData(std::make_shared<Seat>(*this), "seats.json");
        return true;
    }
    return false;
}

std::string Seat::getSeatID() const
{
    return seatID; // Assuming `seatID` is a member variable
}

std::string Seat::getSeatClass() const
{
    return seatClass; // Assuming `seatClass` is a member variable
}

bool Seat::getIsAvailable() const
{
    return isAvailable; // Assuming `isAvailable` is a member variable
}

void Seat::setIsAvailable(bool available)
{
    isAvailable = available; // Assuming `isAvailable` is a member variable
}
/*
    PaypalMethod class Implementation
*/
bool PaypalMethod::processPayment(double amount)
{
    std::cout << "Processing payment of $" << amount << " via PayPal." << std::endl;
    // Logic to process payment using PayPal API
    DataHandling::saveData(std::make_shared<PaypalMethod>(*this), "payments.json");
    return true; // Assuming payment is successful
}

bool PaypalMethod::refundPayment()
{
    std::cout << "Refunding payment via PayPal." << std::endl;
    // Logic to deduct the refunded amount from the existing data
    auto paymentData = DataHandling::loadData("payments.json");
    // if (paymentData.contains("paypal_balance")) {
    //     paymentData["paypal_balance"] = paymentData["paypal_balance"].get<double>() - amount;
    // }
    DataHandling::saveData(paymentData, "payments.json");
    return true; // Assuming refund is successful
}

/*
CreditCardMethod class Implementation
*/
bool CreditCardMethod::processPayment(double amount)
{
    std::cout << "Processing payment of $" << amount << " via Credit Card." << std::endl;
    // Logic to process payment using Credit Card API
    DataHandling::saveData(std::make_shared<CreditCardMethod>(*this), "payments.json");
    return true; // Assuming payment is successful
}

bool CreditCardMethod::refundPayment()
{
    std::cout << "Refunding payment via Credit Card." << std::endl;
    // Logic to deduct the refunded amount from the existing data
    auto paymentData = DataHandling::loadData("payments.json");
    // if (paymentData.contains("credit_card_balance")) {
    //     paymentData["credit_card_balance"] = paymentData["credit_card_balance"].get<double>() - amount;
    // }
    DataHandling::saveData(paymentData, "payments.json");
    return true; // Assuming refund is successful
}
/*
CashMethod class Implementation
*/
bool CashMethod::processPayment(double amount)
{
    std::cout << "Processing cash payment of $" << amount << "." << std::endl;
    // Logic to handle cash payment
    DataHandling::saveData(std::make_shared<CashMethod>(*this), "payments.json");
    return true; // Assuming payment is successful
}

bool CashMethod::refundPayment()
{
    std::cout << "Refunding cash payment." << std::endl;
    // Logic to handle cash refund
    // std::cout << "Please ensure the cash refund of $" << amount << " is handed to the customer." << std::endl;
    // // Logic to deduct the refunded amount from the existing data
    auto paymentData = DataHandling::loadData("payments.json");
    // if (paymentData.contains("cash_balance")) {
    //     paymentData["cash_balance"] = paymentData["cash_balance"].get<double>() - amount;
    // }
    DataHandling::saveData(paymentData, "payments.json");
    return true;
}

/*
    Payment class Implementation
*/

Payment::Payment(std::shared_ptr<PaymentMethod> method) : paymentMethod(method), amount(0.0), status(false)
{
    this->transactionID = DataHandling::generateUniqueID("payments.json");
    DataHandling::saveData(std::make_shared<Payment>(*this), "payments.json");
}

bool Payment::pay(double amount)
{
    this->amount = amount;
    if (paymentMethod)
    {
        status = paymentMethod->processPayment(amount);
        DataHandling::saveData(std::make_shared<Payment>(*this), "payments.json");
        return status;
    }
    return false;
}
bool Payment::refund()
{
    if (paymentMethod)
    {
        status = paymentMethod->refundPayment();
        DataHandling::saveData(std::make_shared<Payment>(*this), "payments.json");
        return status;
    }
    return false;
}
double Payment::getAmount() const
{
    return amount;
}

/*
    Reservation class Implementation
*/
Reservation::Reservation(std::shared_ptr<Flight> flight, std::shared_ptr<Passenger> passenger,
                         std::shared_ptr<PaymentMethod> payment) : flight(flight), passenger(passenger), payment(payment)
{
    this->reservationID = DataHandling::generateUniqueID("reservations.json");
    this->flightID = flight->getFlightID();
    this->passengerID = passenger->getUserID();
    this->seatID = seat.getSeatID();
    this->date = flight->getDate();
    this->status = "Pending";
    DataHandling::saveData(std::make_shared<Reservation>(*this), "reservations.json");
}

bool Reservation::bookFlight()
{
    if (flight->checkAvailability())
    {
        flight->addPassenger(passenger);
        flight->addReservation(std::make_shared<Reservation>(*this));
        seat.bookSeat();
        payment.pay(flight->getPrice());
        status = "Confirmed";
        DataHandling::saveData(std::make_shared<Reservation>(*this), "reservations.json");
        return true;
    }
    return false;
}
bool Reservation::deleteReservation()
{
    if (status == "Confirmed")
    {
        flight->removePassenger(passenger);
        flight->removeReservation(std::make_shared<Reservation>(*this));
        seat.cancelSeat();
        payment.refund();
        status = "Cancelled";
        DataHandling::saveData(std::make_shared<Reservation>(*this), "reservations.json");
        return true;
    }
    return false;
}

bool Reservation::viewReservation()
{
    std::cout << "Reservation ID: " << reservationID << std::endl;
    std::cout << "Flight ID: " << flightID << std::endl;
    std::cout << "Passenger ID: " << passengerID << std::endl;
    std::cout << "Seat ID: " << seatID << std::endl;
    std::cout << "Date: " << date << std::endl;
    std::cout << "Status: " << status << std::endl;
    return true;
}

std::string Reservation::getReservationID() const
{
    return reservationID;
}
std::string Reservation::getFlightID() const
{
    return flightID;
}
std::string Reservation::getPassengerID() const
{
    return passengerID;
}
std::string Reservation::getSeatID() const
{
    return seatID;
}
std::string Reservation::getDate() const
{
    return date;
}
std::string Reservation::getStatus() const
{
    return status;
}
bool Reservation::checkIn()
{
    if (status == "Confirmed")
    {
        status = "Checked In";
        DataHandling::saveData(std::make_shared<Reservation>(*this), "reservations.json");
        return true;
    }
    return false;
}