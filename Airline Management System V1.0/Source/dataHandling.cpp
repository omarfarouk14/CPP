/*
Author: omar ali
*/

#include "../Include/aircraft.hpp"
#include "../Include/users.hpp"
#include "../Include/flight.hpp"
#include "../Include/dataHandling.hpp"

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <memory>
#include <vector>



using json = nlohmann::json;

// Utility function to read JSON from a file
static json readJsonFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file: " + filename);
    }
    json data;
    file >> data;
    return data;
}

// Utility function to write JSON to a file
static void writeJsonToFile(const json &data, const std::string &filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file: " + filename);
    }
    file << data.dump(4);
}

void to_json(json &j, const Flight &flight)
{
    j = json{
        {"flightID", flight.getFlightID()},
        {"departure", flight.getDeparture()},
        {"arrival", flight.getArrival()},
        {"date", flight.getDate()},
        {"duration", flight.getDuration()},
        {"capacity", flight.getCapacity()},
        {"availableSeats", flight.getAvailableSeats()},
        {"price", flight.getPrice()},
        {"aircraftID", flight.getAircraftID()},
        {"crewMembers", json::array()},
        {"passengers", json::array()},
        {"reservations", json::array()}};

    // Serialize crew members
    for (const auto &crew : flight.getCrewMembers())
    {
        j["crewMembers"].emplace_back(*crew);
    }

    // Serialize passengers
    for (const auto &passenger : flight.getPassengers())
    {
        j["passengers"].emplace_back(*passenger);
    }
}

// Save data functions
bool DataHandling::saveData(const std::shared_ptr<Reservation> reservation, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        data.emplace_back(*reservation);
        writeJsonToFile(data, filename);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error saving reservation data: " << e.what() << std::endl;
        return false;
    }
}

bool DataHandling::saveData(const std::shared_ptr<Flight> flight, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        data.emplace_back(*flight);
        writeJsonToFile(data, filename);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error saving flight data: " << e.what() << std::endl;
        return false;
    }
}

bool DataHandling::saveData(const std::shared_ptr<Flight> flight, const std::vector<std::shared_ptr<Reservation>> reservations, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        json flightData;
        to_json(flightData, *flight); // Assuming a to_json function exists for Flight

        // Convert reservations to a JSON array
        json reservationsJson = json::array();
        for (const auto &reservation : reservations)
        {
            reservationsJson.emplace_back(*reservation); // Assuming Reservation has a to_json method or is serializable
        }

        flightData["reservations"] = reservationsJson;
        data.push_back(flightData);
        writeJsonToFile(data, filename);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error saving flight with reservations: " << e.what() << std::endl;
        return false;
    }
}
/*
as you know we have three types of payment make this class act accordingly , check by pointer

*/
bool DataHandling::saveData(const std::shared_ptr<PaymentMethod> paymentMethod, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);

        // Check the type of payment method using dynamic_pointer_cast
        if (std::dynamic_pointer_cast<CreditCardMethod>(paymentMethod))
        {
            data["creditCardPayments"].emplace_back(*paymentMethod);
        }
        else if (std::dynamic_pointer_cast<PaypalMethod>(paymentMethod))
        {
            data["paypalPayments"].emplace_back(*paymentMethod);
        }
        else if (std::dynamic_pointer_cast<CashMethod>(paymentMethod))
        {
            data["CashPayment"].emplace_back(*paymentMethod);
        }
        else
        {
            throw std::runtime_error("Unknown payment method type");
        }

        writeJsonToFile(data, filename);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error saving payment method data: " << e.what() << std::endl;
        return false;
    }
}

bool DataHandling::saveData(const std::shared_ptr<Payment> payment, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);

        // Check the type of payment using dynamic_pointer_cast
        if (std::dynamic_pointer_cast<CreditCardMethod>(payment))
        {
            data["creditCardPayments"].emplace_back(*payment);
        }
        else if (std::dynamic_pointer_cast<PaypalMethod>(payment))
        {
            data["paypalPayments"].emplace_back(*payment);
        }
        else if (std::dynamic_pointer_cast<CashMethod>(payment))
        {
            data["cashPayments"].emplace_back(*payment);
        }
        else
        {
            throw std::runtime_error("Unknown payment type");
        }

        writeJsonToFile(data, filename);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error saving payment data: " << e.what() << std::endl;
        return false;
    }
}

bool DataHandling::saveData(const std::shared_ptr<Aircraft> aircraft, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        data.emplace_back(*aircraft);
        writeJsonToFile(data, filename);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error saving aircraft data: " << e.what() << std::endl;
        return false;
    }
}

bool DataHandling::saveData(const std::shared_ptr<Crew> crew, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);

        // Check the type of crew using dynamic_pointer_cast
        if (std::dynamic_pointer_cast<Pilot>(crew))
        {
            data["pilots"].emplace_back(*crew);
        }
        else if (std::dynamic_pointer_cast<FlightAttendant>(crew))
        {
            data["flightAttendants"].emplace_back(*crew);
        }
        else
        {
            throw std::runtime_error("Unknown crew type");
        }

        writeJsonToFile(data, filename);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error saving crew data: " << e.what() << std::endl;
        return false;
    }
}

std::string hashPassword(const std::string& password) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(password));
}

bool DataHandling::saveData(const std::shared_ptr<User> user, const std::string& filename) {
    try {
        json data = readJsonFromFile(filename);
        json userJson = {
            {"userID", user->getUserID()},
            {"username", user->getUsername()},
            {"password", hashPassword(user->getPassword())}, // Hash the password
            {"email", user->getEmail()},
            {"phone", user->getPhone()},
            {"name", user->getName()},
            {"address", user->getAddress()},
            {"loyaltyPoints", user->getLoyaltyPoints()}
        };
        if (std::dynamic_pointer_cast<Administrator>(user)) {
            data["administrators"].push_back(userJson);
        } else if (std::dynamic_pointer_cast<BookingAgent>(user)) {
            data["bookingAgents"].push_back(userJson);
        } else if (std::dynamic_pointer_cast<Passenger>(user)) {
            data["passengers"].push_back(userJson);
        }
        writeJsonToFile(data, filename);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error saving user data: " << e.what() << std::endl;
        return false;
    }
}

bool DataHandling::saveData(const std::shared_ptr<Maintenance> maintenance, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        data.emplace_back(*maintenance);
        writeJsonToFile(data, filename);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error saving maintenance data: " << e.what() << std::endl;
        return false;
    }
}

bool DataHandling::saveData(const std::shared_ptr<Seat> seat, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        data.emplace_back(*seat);
        writeJsonToFile(data, filename);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error saving seat data: " << e.what() << std::endl;
        return false;
    }
}

// Load data functions
std::shared_ptr<Reservation> DataHandling::loadReservationData(const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        return std::make_shared<Reservation>(data);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading reservation data: " << e.what() << std::endl;
        return nullptr;
    }
}

std::shared_ptr<Flight> DataHandling::loadFlightData(const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        return std::make_shared<Flight>(data);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading flight data: " << e.what() << std::endl;
        return nullptr;
    }
}

std::shared_ptr<Crew> DataHandling::loadCrewData(const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        return std::make_shared<Crew>(data);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading crew data: " << e.what() << std::endl;
        return nullptr;
    }
}

std::shared_ptr<User> DataHandling::loadUserData(const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        return std::make_shared<User>(data);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading user data: " << e.what() << std::endl;
        return nullptr;
    }
}

std::shared_ptr<PaymentMethod> DataHandling::loadData(const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        return std::make_shared<PaymentMethod>(data);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading payment method data: " << e.what() << std::endl;
        return nullptr;
    }
}

// Remove data functions
bool DataHandling::removeData(std::shared_ptr<Reservation> reservation, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        auto it = std::remove_if(data.begin(), data.end(), [&](const json &item)
                                 { return item["reservationID"] == reservation->getReservationID(); });
        if (it != data.end())
        {
            data.erase(it, data.end());
            writeJsonToFile(data, filename);
            return true;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error removing reservation data: " << e.what() << std::endl;
    }
    return false;
}

bool DataHandling::removeData(std::shared_ptr<Flight> flight, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        auto it = std::remove_if(data.begin(), data.end(), [&](const json &item)
                                 { return item["flightID"] == flight->getFlightID(); });
        if (it != data.end())
        {
            data.erase(it, data.end());
            writeJsonToFile(data, filename);
            return true;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error removing flight data: " << e.what() << std::endl;
    }
    return false;
}

bool DataHandling::removeData(std::shared_ptr<Aircraft> aircraft, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        auto it = std::remove_if(data.begin(), data.end(), [&](const json &item)
                                 { return item["aircraftID"] == aircraft->getAircraftID(); });
        if (it != data.end())
        {
            data.erase(it, data.end());
            writeJsonToFile(data, filename);
            return true;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error removing aircraft data: " << e.what() << std::endl;
    }
    return false;
}

bool DataHandling::removeData(std::shared_ptr<Crew> crew, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        auto it = std::remove_if(data.begin(), data.end(), [&](const json &item)
                                 { return item["crewID"] == crew->getCrewID(); });
        if (it != data.end())
        {
            data.erase(it, data.end());
            writeJsonToFile(data, filename);
            return true;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error removing crew data: " << e.what() << std::endl;
    }
    return false;
}

bool DataHandling::removeData(std::shared_ptr<User> user, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        auto it = std::remove_if(data.begin(), data.end(), [&](const json &item)
                                 { return item["userID"] == user->getUserID(); });
        if (it != data.end())
        {
            data.erase(it, data.end());
            writeJsonToFile(data, filename);
            return true;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error removing user data: " << e.what() << std::endl;
    }
    return false;
}

bool DataHandling::removeData(std::shared_ptr<Maintenance> maintenance, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        auto it = std::remove_if(data.begin(), data.end(), [&](const json &item)
                                 { return item["maintenanceID"] == maintenance->getMaintenanceID(); });
        if (it != data.end())
        {
            data.erase(it, data.end());
            writeJsonToFile(data, filename);
            return true;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error removing maintenance data: " << e.what() << std::endl;
    }
    return false;
}

// Specialized functions
std::shared_ptr<Flight> DataHandling::loadFlightData(std::string &flightID, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        for (const auto &item : data)
        {
            if (item["flightID"] == flightID)
            {
                return std::make_shared<Flight>(item);
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading flight data: " << e.what() << std::endl;
    }
    return nullptr;
}

std::shared_ptr<Reservation> DataHandling::loadReservationData(std::string &reservationID, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        for (const auto &item : data)
        {
            if (item["reservationID"] == reservationID)
            {
                return std::make_shared<Reservation>(item);
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading reservation data: " << e.what() << std::endl;
    }
    return nullptr;
}

std::shared_ptr<Passenger> DataHandling::loadPassengerData(std::string &passengerID, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        for (const auto &item : data)
        {
            if (item["userID"] == passengerID)
            {
                return std::make_shared<Passenger>(item);
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading passenger data: " << e.what() << std::endl;
    }
    return nullptr;
}

std::shared_ptr<BookingAgent> DataHandling::loadBookingAgentData(std::string &agentID, const std::string &filename){
    try
    {
        json data = readJsonFromFile(filename);
        for (const auto &item : data)
        {
            if (item["userID"] == agentID)
            {
                return std::make_shared<BookingAgent>(item);
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading Booking Agent data: " << e.what() << std::endl;
    }
    return nullptr;
}

std::shared_ptr<Administrator> DataHandling::loadAdministrator(std::string &adminID, const std::string &filename){
    try
    {
        json data = readJsonFromFile(filename);
        for (const auto &item : data)
        {
            if (item["userID"] == adminID)
            {
                return std::make_shared<Administrator>(item);
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading Administrator data: " << e.what() << std::endl;
    }
    return nullptr;
}

std::shared_ptr<Aircraft> DataHandling::loadAircraftData(std::string &aircraftID, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        for (const auto &item : data)
        {
            if (item["aircraftID"] == aircraftID)
            {
                return std::make_shared<Aircraft>(item);
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading aircraft data: " << e.what() << std::endl;
    }
    return nullptr;
}

std::shared_ptr<Crew> DataHandling::loadCrewData(std::string &crewID, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        for (const auto &item : data)
        {
            if (item["crewID"] == crewID)
            {
                return std::make_shared<Crew>(item);
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading crew data: " << e.what() << std::endl;
    }
    return nullptr;
}

// Load all data functions
std::vector<std::shared_ptr<Reservation>> DataHandling::loadReservationsForPassenger(std::string &passengerID, const std::string &filename)
{
    std::vector<std::shared_ptr<Reservation>> reservations;
    try
    {
        json data = readJsonFromFile(filename);
        for (const auto &item : data)
        {
            if (item["userID"] == passengerID)
            {
                reservations.push_back(std::make_shared<Reservation>(item));
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading reservations for passenger: " << e.what() << std::endl;
    }
    return reservations;
}

std::vector<std::shared_ptr<Crew>> DataHandling::loadAllCrewData(const std::string &filename)
{
    std::vector<std::shared_ptr<Crew>> crewList;
    try
    {
        json data = readJsonFromFile(filename);
        for (const auto &item : data)
        {
            crewList.push_back(std::make_shared<Crew>(item));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading all crew data: " << e.what() << std::endl;
    }
    return crewList;
}

std::vector<std::shared_ptr<Aircraft>> DataHandling::loadAllAircraftData(const std::string &filename)
{
    std::vector<std::shared_ptr<Aircraft>> aircraftList;
    try
    {
        json data = readJsonFromFile(filename);
        for (const auto &item : data)
        {
            aircraftList.push_back(std::make_shared<Aircraft>(item));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading all aircraft data: " << e.what() << std::endl;
    }
    return aircraftList;
}

std::vector<std::shared_ptr<Seat>> DataHandling::loadAircraftSeats(const std::string &filename)
{
    std::vector<std::shared_ptr<Seat>> seats;
    try
    {
        json data = readJsonFromFile(filename);
        for (const auto &item : data)
        {
            seats.push_back(std::make_shared<Seat>(item));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading aircraft seats: " << e.what() << std::endl;
    }
    return seats;
}

// Utility functions
bool DataHandling::searchPassenger(std::string &passengerID, const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        for (const auto &item : data)
        {
            if (item["userID"] == passengerID)
            {
                return true;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error searching passenger: " << e.what() << std::endl;
    }
    return false;
}


std::string DataHandling::authenticateUser(const std::string& username, const std::string& password, const std::string& filename) {
    try {
        json data = readJsonFromFile(filename);
        for (const auto& item : data) {
            if (item["username"] == username && item["password"] == hashPassword(password)) {
                return item["userID"].get<std::string>(); // Return userID if credentials match
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error authenticating user: " << e.what() << std::endl;
    }
    return ""; // Return empty string if authentication fails
}

std::string DataHandling::generateUniqueID(const std::string &filename)
{
    try
    {
        json data = readJsonFromFile(filename);
        return "ID_" + std::to_string(data.size() + 1);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error generating unique ID: " << e.what() << std::endl;
    }
    return "ID_1";
}

void DataHandling::generateFlightReport(const std::string& filename) {
    auto allFlights = loadAllFlights(filename);
    std::cout << "Flight Report:" << std::endl;
    for (const auto& flight : allFlights) {
        flight->viewFlightDetails(); // Assumes this method exists
        std::cout << "Status: " << flight->getStatus() << std::endl;
        std::cout << "Number of passengers: " << flight->getPassengers().size() << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
}

std::vector<std::shared_ptr<Flight>> DataHandling::loadAllFlights(const std::string& filename) {
    std::vector<std::shared_ptr<Flight>> flights;
    try {
        json data = readJsonFromFile(filename); // Existing function to read JSON
        for (const auto& item : data) {
            flights.push_back(std::make_shared<Flight>(item)); // Assumes Flight has a json constructor
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading all flights: " << e.what() << std::endl;
    }
    return flights;
}

std::vector<std::shared_ptr<Flight>> DataHandling::searchFlights(const std::string& date, 
                                                                const std::string& destination, 
                                                                double maxPrice) {
    auto allFlights = loadAllFlights("flights.json");
    std::vector<std::shared_ptr<Flight>> result;
    for (const auto& flight : allFlights) {
        bool matches = true;
        if (!date.empty() && flight->getDate() != date) {
            matches = false;
        }
        if (!destination.empty() && flight->getArrival() != destination) {
            matches = false;
        }
        if (maxPrice >= 0 && flight->getPrice() > maxPrice) {
            matches = false;
        }
        if (matches) {
            result.push_back(flight);
        }
    }
    return result;
}