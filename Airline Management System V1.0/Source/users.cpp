/*
Author: omar ali
*/

#include "../Include/users.hpp"

/*
    User class Implementation
*/

User::User(std::string &username, std::string &password, std::string &email, std::string &phone, std::string &name, std::string &address)
{
    this->username = username;
    this->password = password;
    this->email = email;
    this->phone = phone;
    this->name = name;
    this->address = address;
    this->userID = DataHandling::generateUniqueID("users.json");
}

std::string User::getUsername(void) const
{
    return this->username;
}
std::string User::getPassword(void) const
{
    return this->password;
}
std::string User::getEmail(void) const
{
    return this->email;
}
std::string User::getPhone(void) const
{
    return this->phone;
}
std::string User::getName(void) const
{
    return this->name;
}
std::string User::getAddress(void) const
{
    return this->address;
}
std::string User::getUserID(void) const
{
    return this->userID;
}

bool User::registerUser(void)
{

    std::string N_username, N_password, N_email, N_phone, N_name, N_address, N_userID;
    std::cout << "Registering New Passenger..." << std::endl;
    std::cout << "Enter username: ";
    std::cin >> N_username;
    std::cout << "Enter password: ";
    std::cin >> N_password;
    std::cout << "Enter email: ";
    std::cin >> N_email;
    std::cout << "Enter phone: ";
    std::cin >> N_phone;
    std::cout << "Enter name: ";
    std::cin >> N_name;
    std::cout << "Enter address: ";
    std::cin >> N_address;
    N_userID = DataHandling::generateUniqueID("passengers.json");
    std::shared_ptr<Passenger> newPassenger = std::make_shared<Passenger>(N_username, N_password, N_email, N_phone, N_name, N_address);
    if (!DataHandling::saveData(newPassenger, "passengers.json"))
    {
        std::cerr << "Error: Could not save user data." << std::endl;
        return false;
    }
    return true;
}

// edit it to view profile
bool User::SearchUser(std::string &userId)
{
    if (DataHandling::searchPassenger(userId, "passengers.json"))
    {
        std::cout << "User found!" << std::endl;
        /*
            view passenger profile 23tqd 2fdl tb2a implemented gwa search Passenger
        */
        return true;
    }
    else
    {
        std::cout << "User not found!" << std::endl;
        return false;
    }
}

bool User::setUserId(const std::string &userId)
{
    this->userID = userId;
    return true;
}

int User::getLoyaltyPoints(void) const
{
    return this->loyaltyPoints;
}

void User::setLoyaltyPoints(int amount)
{
    this->loyaltyPoints += amount;
}

bool User::deleteProfile(void)
{
    if (DataHandling::removeData(std::make_shared<Passenger>(*this), "passengers.json"))
    {
        std::cout << "User deleted successfully!" << std::endl;
        return true;
    }
    else
    {
        std::cerr << "Error: Could not delete user data." << std::endl;
        return false;
    }
}

bool User::setUsername(const std::string &username)
{
    this->username = username;
    return true;
}
bool User::setPassword(const std::string &password)
{
    this->password = password;
    return true;
}
bool User::setEmail(const std::string &email)
{
    this->email = email;
    return true;
}
bool User::setPhone(const std::string &phone)
{
    this->phone = phone;
    return true;
}
bool User::setName(const std::string &name)
{
    this->name = name;
    return true;
}
bool User::setAddress(const std::string &address)
{
    this->address = address;
    return true;
}

bool User::editProfile(void)
{
    std::string newUsername, newPassword, newEmail, newPhone, newName, newAddress;
    while (1)
    {
        std::cout << "Enter which field you want to edit: " << std::endl;
        std::cout << "1. Username" << std::endl;
        std::cout << "2. Password" << std::endl;
        std::cout << "3. Email" << std::endl;
        std::cout << "4. Phone" << std::endl;
        std::cout << "5. Name" << std::endl;
        std::cout << "6. Address" << std::endl;
        std::cout << "7. Exit" << std::endl;
        int choice;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            std::cout << "Enter new username: ";
            std::cin >> newUsername;
            setUsername(newUsername);
            break;
        case 2:
            std::cout << "Enter new password: ";
            std::cin >> newPassword;
            setPassword(newPassword);
            break;
        case 3:
            std::cout << "Enter new email: ";
            std::cin >> newEmail;
            setEmail(newEmail);
            break;
        case 4:
            std::cout << "Enter new phone: ";
            std::cin >> newPhone;
            setPhone(newPhone);
            break;
        case 5:
            std::cout << "Enter new name: ";
            std::cin >> newName;
            setName(newName);
            break;
        case 6:
            std::cout << "Enter new address: ";
            std::cin >> newAddress;
            setAddress(newAddress);
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
    return true;
}
/*
    Passenger class Implementation
*/
Passenger::Passenger(std::string &username, std::string &password, std::string &email, std::string &phone,
                     std::string &name, std::string &address) : User(username, password, email, phone, name, address)
{
    this->setUserId(DataHandling::generateUniqueID("passengers.json"));
    DataHandling::saveData(std::make_shared<Passenger>(*this), "passengers.json");
}


std::shared_ptr<Passenger> Passenger::login(void) {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    // Authenticate and get userID
    std::string userID = DataHandling::authenticateUser(username, password, "passengers.json");
    if (!userID.empty()) {
        // Load passenger data using userID
        std::shared_ptr<Passenger> passenger = DataHandling::loadPassengerData(userID, "passengers.json");
        if (passenger) {
            std::cout << "Login successful!" << std::endl;
            return passenger;
        }
    }
    std::cerr << "Login failed!" << std::endl;
    return nullptr;
}

bool Passenger::logout(void)
{
    std::cout << "Logging out..." << std::endl;
    return true;
}

bool Passenger::viewProfile(void)
{
    std::cout << "Username: " << this->getUsername() << std::endl;
    std::cout << "Password: " << this->getPassword() << std::endl;
    std::cout << "Email: " << this->getEmail() << std::endl;
    std::cout << "Phone: " << this->getPhone() << std::endl;
    std::cout << "Name: " << this->getName() << std::endl;
    std::cout << "Address: " << this->getAddress() << std::endl;
    std::cout << "User ID: " << this->getUserID() << std::endl;
    std::cout << "Loyalty Points: " << this->getLoyaltyPoints() << std::endl;
    return true;
}

bool Passenger::editProfile(void)
{

    User::editProfile();
    DataHandling::saveData(std::make_shared<Passenger>(*this), "passengers.json");
    return true;
}

bool Passenger::bookFlight(void)
{
    std::string flightID;
    std::cout << "Enter flight ID: ";
    std::cin >> flightID;

    std::shared_ptr<Flight> flight = DataHandling::loadFlightData(flightID, "flight.json");
    if (flight)
    {
        std::shared_ptr<Reservation> reservation = std::make_shared<Reservation>(flight, std::make_shared<Passenger>(*this));
        if (reservation->bookFlight())
        {
            std::cout << "Flight booked successfully!" << std::endl;
            setLoyaltyPoints(10); // Add loyalty points for booking
            return true;
        }
        else
        {
            std::cerr << "Error: Could not book flight." << std::endl;
            return false;
        }
    }
    else
    {
        std::cerr << "Error: Flight not found." << std::endl;
        return false;
    }
}

bool Passenger::cancelFlight(void)
{
    std::string reservationID;
    std::cout << "Enter reservation ID: ";
    std::cin >> reservationID;

    std::shared_ptr<Reservation> reservation = DataHandling::loadReservationData(reservationID, "reservation.json");
    if (reservation)
    {
        if (reservation->deleteReservation())
        {
            std::cout << "Flight canceled successfully!" << std::endl;
            return true;
        }
        else
        {
            std::cerr << "Error: Could not cancel flight." << std::endl;
            return false;
        }
    }
    else
    {
        std::cerr << "Error: Reservation not found." << std::endl;
        return false;
    }
}

bool Passenger::viewPassengerFlightHistory(void)
{
    std::string passengerID;
    std::cout << "Enter passenger ID: ";
    std::cin >> passengerID;

    std::shared_ptr<Passenger> passenger = DataHandling::loadPassengerData(passengerID, "passengers.json");
    if (passenger)
    {
        std::vector<std::shared_ptr<Reservation>> reservations = DataHandling::loadReservationsForPassenger(passengerID, "reservations.json");
        if (reservations.empty())
        {
            std::cout << "No flight history found." << std::endl;
            return false;
        }

        std::cout << "Flight History:" << std::endl;
        for (const auto &reservation : reservations)
        {
            reservation->viewReservation();
        }
        return true;
    }
    else
    {
        std::cerr << "Error: Passenger not found." << std::endl;
        return false;
    }
}

bool Passenger::viewLoyaltyPoints(void)
{
    std::cout << "Loyalty Points: " << this->getLoyaltyPoints() << std::endl;
    return true;
}
bool Passenger::redeemLoyaltyPoints(void)
{
    int points;
    std::cout << "Enter points to redeem: ";
    std::cin >> points;

    if (points > this->getLoyaltyPoints())
    {
        std::cerr << "Error: Not enough loyalty points." << std::endl;
        return false;
    }
    else
    {
        this->setLoyaltyPoints(-points);
        std::cout << "Loyalty points redeemed successfully!" << std::endl;
        DataHandling::saveData(std::make_shared<Passenger>(*this), "passengers.json");
        return true;
    }
}

/*
    Booking Agent
*/
BookingAgent::BookingAgent(std::string &username, std::string &password, std::string &email, std::string &phone,
                           std::string &name, std::string &address) : User(username, password, email, phone, name, address)
{
    this->setUserId(DataHandling::generateUniqueID("bookingAgent.json"));
    DataHandling::saveData(std::make_shared<BookingAgent>(*this), "bookingAgent.json");
}

std::shared_ptr<BookingAgent> BookingAgent::login(void)
{
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    std::string userID = DataHandling::authenticateUser(username, password, "bookingAgent.json");
    if (!userID.empty() )
    {
    // Load booking agent data using userID
    std::shared_ptr<BookingAgent> bookingAgent = DataHandling::loadBookingAgentData(userID, "bookingAgent.json");
       if(bookingAgent){
         std::cout << "Login successful!" << std::endl;
        return bookingAgent;
    }
    }
    else
    {
        std::cerr << "Login failed!" << std::endl;
        return nullptr;
    }
}
bool BookingAgent::logout(void)
{
    std::cout << "Logging out..." << std::endl;
    return true;
}
bool BookingAgent::viewProfile(void)
{
    std::cout << "Username: " << this->getUsername() << std::endl;
    std::cout << "Password: " << this->getPassword() << std::endl;
    std::cout << "Email: " << this->getEmail() << std::endl;
    std::cout << "Phone: " << this->getPhone() << std::endl;
    std::cout << "Name: " << this->getName() << std::endl;
    std::cout << "Address: " << this->getAddress() << std::endl;
    std::cout << "User ID: " << this->getUserID() << std::endl;
    return true;
}
bool BookingAgent::editProfile(void)
{
    User::editProfile();
    DataHandling::saveData(std::make_shared<BookingAgent>(*this), "bookingAgent.json");
    return true;
}

bool BookingAgent::assistCheckIn(void)
{
    std::string flightID;
    std::cout << "Enter flight ID: ";
    std::cin >> flightID;

    std::shared_ptr<Flight> flight = DataHandling::loadFlightData(flightID, "flight.json");
    if (flight)
    {
        std::cout << "Flight found!" << std::endl;

        std::string reservationID;
        std::cout << "Enter reservation ID: ";
        std::cin >> reservationID;

        std::shared_ptr<Reservation> reservation = DataHandling::loadReservationData(reservationID, "reservation.json");
        if (reservation)
        {
            if (reservation->getFlightID() == flightID)
            {
                std::cout << "Reservation verified for this flight." << std::endl;

                // Perform check-in logic
                if (reservation->checkIn())
                {
                    std::cout << "Check-in successful!" << std::endl;
                    return true;
                }
                else
                {
                    std::cerr << "Error: Check-in failed." << std::endl;
                    return false;
                }
            }
            else
            {
                std::cerr << "Error: Reservation does not match the flight ID." << std::endl;
                return false;
            }
        }
        else
        {
            std::cerr << "Error: Reservation not found." << std::endl;
            return false;
        }
    }
    else
    {
        std::cerr << "Error: Flight not found." << std::endl;
        return false;
    }
}
bool BookingAgent::handlePayment(void)
{
    std::string paymentMethod;
    std::cout << "Enter payment method (credit card, cash, paypal): ";
    std::cin >> paymentMethod;

    std::shared_ptr<PaymentMethod> method;
    if (paymentMethod == "credit card")
    {
        method = std::make_shared<CreditCardMethod>();
    }
    else if (paymentMethod == "cash")
    {
        method = std::make_shared<CashMethod>();
    }
    else if (paymentMethod == "paypal")
    {
        method = std::make_shared<PaypalMethod>();
    }
    else
    {
        std::cerr << "Invalid payment method!" << std::endl;
        return false;
    }

    double amount;
    std::cout << "Enter amount: ";
    std::cin >> amount;

    Payment payment(method);
    if (payment.pay(amount))
    {
        std::cout << "Payment successful!" << std::endl;
        return true;
    }
    else
    {
        std::cerr << "Payment failed!" << std::endl;
        return false;
    }
}

/*
    Administrator class Implementation
*/

Administrator::Administrator(std::string &username, std::string &password, std::string &email, std::string &phone,
                             std::string &name, std::string &address) : User(username, password, email, phone, name, address)
{
    this->setUserId(DataHandling::generateUniqueID("admin.json"));
    DataHandling::saveData(std::make_shared<Administrator>(*this), "admin.json");
}

std::shared_ptr<Administrator> Administrator::login(void)
{
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    std::string userID = DataHandling::authenticateUser(username, password, "admin.json");

    if (!userID.empty())
    {
        std::shared_ptr<Administrator> admin = DataHandling::loadAdministrator(userID, "admin.json");
        if(admin){
            std::cout << "Login successful!" << std::endl;
        return admin;
    }
    }
    else
    {
        std::cerr << "Login failed!" << std::endl;
        return nullptr;
    }
}
bool Administrator::logout(void)
{
    std::cout << "Logging out..." << std::endl;
    return true;
}
bool Administrator::viewProfile(void)
{
    std::cout << "Username: " << this->getUsername() << std::endl;
    std::cout << "Password: " << this->getPassword() << std::endl;
    std::cout << "Email: " << this->getEmail() << std::endl;
    std::cout << "Phone: " << this->getPhone() << std::endl;
    std::cout << "Name: " << this->getName() << std::endl;
    std::cout << "Address: " << this->getAddress() << std::endl;
    std::cout << "User ID: " << this->getUserID() << std::endl;
    return true;
}
bool Administrator::editProfile(void)
{
    User::editProfile();
    DataHandling::saveData(std::make_shared<Administrator>(*this), "admin.json");
    return true;
}

bool Administrator::addFlight(void)
{
    std::string flightId = DataHandling::generateUniqueID("flight.json");
    std::string flightName, flightSource, flightDestination, flightDate, flightTime, aircraftId;
    int flightDuration;
    double flightPrice;

    std::cout << "Enter flight name: ";
    std::cin >> flightName;
    std::cout << "Enter flight source: ";
    std::cin >> flightSource;
    std::cout << "Enter flight destination: ";
    std::cin >> flightDestination;
    std::cout << "Enter flight date (YYYY-MM-DD): ";
    std::cin >> flightDate;
    std::cout << "Enter flight time (HH:MM): ";
    std::cin >> flightTime;
    std::cout << "Enter flight duration (in minutes): ";
    std::cin >> flightDuration;
    std::cout << "Enter flight price: ";
    std::cin >> flightPrice;

    // Assign aircraft
    std::cout << "Enter aircraft ID: ";
    std::cin >> aircraftId;

    std::shared_ptr<Aircraft> aircraft = DataHandling::loadAircraftData(aircraftId, "aircraft.json");
    if (!aircraft)
    {
        std::cerr << "Error: Aircraft not found." << std::endl;
        return false;
    }

    int flightCapacity = aircraft->getCapacity();

    std::shared_ptr<Flight> newFlight = std::make_shared<Flight>(flightId, flightName, flightSource, flightDestination,
                                                                 flightDate, flightTime, flightDuration, flightCapacity, flightPrice, aircraftId);
    if (!DataHandling::saveData(newFlight, "flightData.json"))
    {
        std::cerr << "Error: Could not save flight data." << std::endl;
        return false;
    }
    std::cout << "Flight added successfully with Aircraft ID: " << aircraftId << " and Capacity: " << flightCapacity << std::endl;
    return true;
}
bool Administrator::removeFlight(void)
{
    std::string flightID;
    std::cout << "Enter flight ID: ";
    std::cin >> flightID;

    std::shared_ptr<Flight> flight = DataHandling::loadFlightData(flightID, "flight.json");
    if (flight)
    {
        if (DataHandling::removeData(flight, "flight.json"))
        {
            std::cout << "Flight removed successfully!" << std::endl;
            return true;
        }
        else
        {
            std::cerr << "Error: Could not remove flight." << std::endl;
            return false;
        }
    }
    else
    {
        std::cerr << "Error: Flight not found." << std::endl;
        return false;
    }
}
bool Administrator::viewFlightSchedules(void)
{

    std::string flightID;
    std::cout << "Enter flight ID: ";
    std::cin >> flightID;

    std::shared_ptr<Flight> flight = DataHandling::loadFlightData(flightID, "flight.json");
    if (flight)
    {
        // Display flight schedule
        flight->viewFlightDetails();
        return true;
    }
    else
    {
        std::cerr << "Error: Flight not found." << std::endl;
        return false;
    }
}

bool Administrator::addNewAdmin(void)
{
    std::string username, password, email, phone, name, address;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    std::cout << "Enter email: ";
    std::cin >> email;
    std::cout << "Enter phone: ";
    std::cin >> phone;
    std::cout << "Enter name: ";
    std::cin >> name;
    std::cout << "Enter address: ";
    std::cin >> address;

    std::shared_ptr<Administrator> newAdmin = std::make_shared<Administrator>(username, password, email, phone, name, address);
    newAdmin->setUserId(DataHandling::generateUniqueID("admin.json"));
    if (!DataHandling::saveData(newAdmin, "admin.json"))
    {
        std::cerr << "Error: Could not save admin data." << std::endl;
        return false;
    }
    return true;
}
bool Administrator::addNewBookingAgent(void)
{
    std::string username, password, email, phone, name, address;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    std::cout << "Enter email: ";
    std::cin >> email;
    std::cout << "Enter phone: ";
    std::cin >> phone;
    std::cout << "Enter name: ";
    std::cin >> name;
    std::cout << "Enter address: ";
    std::cin >> address;

    std::shared_ptr<BookingAgent> newBookingAgent = std::make_shared<BookingAgent>(username, password, email, phone, name, address);
    newBookingAgent->setUserId(DataHandling::generateUniqueID("bookingAgent.json"));
    if (!DataHandling::saveData(newBookingAgent, "bookingAgent.json"))
    {
        std::cerr << "Error: Could not save booking agent data." << std::endl;
        return false;
    }
    return true;
}

bool Administrator::addNewCrewMember(void)
{
    std::string username, password, email, phone, name, address;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    std::cout << "Enter email: ";
    std::cin >> email;
    std::cout << "Enter phone: ";
    std::cin >> phone;
    std::cout << "Enter name: ";
    std::cin >> name;
    std::cout << "Enter address: ";
    std::cin >> address;

    std::cout << "Enter crew role: ";
    std::string role;
    std::cin >> role;
    if (role == "Pilot")
    {
        std::shared_ptr<Crew> newCrewMember = std::make_shared<Pilot>(name);
        newCrewMember->setUserId(DataHandling::generateUniqueID("crew.json"));
        if (!DataHandling::saveData(newCrewMember, "crew.json"))
        {
            std::cerr << "Error: Could not save crew member data." << std::endl;
            return false;
        }
        return true;
    }
    else if (role == "Flight Attendant")
    {
        std::shared_ptr<Crew> newCrewMember = std::make_shared<FlightAttendant>(name);
        newCrewMember->setUserId(DataHandling::generateUniqueID("crew.json"));
        if (!DataHandling::saveData(newCrewMember, "crew.json"))
        {
            std::cerr << "Error: Could not save crew member data." << std::endl;
            return false;
        }
        return true;
    }
    else
    {
        std::cerr << "Error: Invalid crew role." << std::endl;
        return false;
    }
}
bool Administrator::removeCrewMember(void)
{
    std::string crewID;
    std::cout << "Enter crew member ID: ";
    std::cin >> crewID;

    std::shared_ptr<Crew> crewMember = DataHandling::loadCrewData(crewID, "crew.json");
    if (crewMember)
    {
        if (DataHandling::removeData(crewMember, "crew.json"))
        {
            std::cout << "Crew member removed successfully!" << std::endl;
            return true;
        }
        else
        {
            std::cerr << "Error: Could not remove crew member." << std::endl;
            return false;
        }
    }
    else
    {
        std::cerr << "Error: Crew member not found." << std::endl;
        return false;
    }
}
bool Administrator::viewCrewMembers(void)
{
    std::vector<std::shared_ptr<Crew>> crewMembers = DataHandling::loadAllCrewData("crew.json");
    if (crewMembers.empty())
    {
        std::cout << "No crew members found." << std::endl;
        return false;
    }

    std::cout << "Crew Members:" << std::endl;
    for (const auto &crewMember : crewMembers)
    {
        std::cout << "Crew ID: " << crewMember->getCrewID() << std::endl;
        std::cout << "Name: " << crewMember->getCrewName() << std::endl;
        std::cout << "Role: " << crewMember->getCrewRole() << std::endl;
        std::cout << "-------------------------" << std::endl;
    }

    return true;
}

bool Administrator::addNewAircraft(void)
{
    std::string aircraftID, aircraftType, status, location;
    int capacity;
    double range, speed, fuelCapacity;

    std::cout << "Enter aircraft ID: ";
    std::cin >> aircraftID;
    std::cout << "Enter aircraft type: ";
    std::cin >> aircraftType;
    std::cout << "Enter status: ";
    std::cin >> status;
    std::cout << "Enter location: ";
    std::cin >> location;
    std::cout << "Enter capacity: ";
    std::cin >> capacity;
    std::cout << "Enter range: ";
    std::cin >> range;
    std::cout << "Enter speed: ";
    std::cin >> speed;
    std::cout << "Enter fuel capacity: ";
    std::cin >> fuelCapacity;

    // Create a new Aircraft object
    std::shared_ptr<Aircraft> newAircraft = std::make_shared<Aircraft>(aircraftType, status, location,
                                                                       capacity, range, speed, fuelCapacity);
    newAircraft->setAircraftID(aircraftID);

    if (!DataHandling::saveData(newAircraft, "aircraft.json"))
    {
        std::cerr << "Error: Could not save aircraft data." << std::endl;
        return false;
    }

    return true;
}
bool Administrator::removeAircraft(void)
{
    std::string aircraftID;
    std::cout << "Enter aircraft ID: ";
    std::cin >> aircraftID;

    std::shared_ptr<Aircraft> aircraft = DataHandling::loadAircraftData(aircraftID, "aircraft.json");
    if (aircraft)
    {
        if (DataHandling::removeData(aircraft, "aircraft.json"))
        {
            std::cout << "Aircraft removed successfully!" << std::endl;
            return true;
        }
        else
        {
            std::cerr << "Error: Could not remove aircraft." << std::endl;
            return false;
        }
    }
    else
    {
        std::cerr << "Error: Aircraft not found." << std::endl;
        return false;
    }
}
bool Administrator::viewAircrafts(void)
{
    std::vector<std::shared_ptr<Aircraft>> aircrafts = DataHandling::loadAllAircraftData("aircraft.json");
    if (aircrafts.empty())
    {
        std::cout << "No aircraft found." << std::endl;
        return false;
    }

    std::cout << "Aircrafts:" << std::endl;
    for (const auto &aircraft : aircrafts)
    {
        std::cout << "Aircraft ID: " << aircraft->getAircraftID() << std::endl;
        std::cout << "Type: " << aircraft->getAircraftType() << std::endl;
        std::cout << "Status: " << aircraft->getStatus() << std::endl;
        std::cout << "Location: " << aircraft->getLocation() << std::endl;
        std::cout << "Capacity: " << aircraft->getCapacity() << std::endl;
        std::cout << "Range: " << aircraft->getRange() << std::endl;
        std::cout << "Speed: " << aircraft->getSpeed() << std::endl;
        std::cout << "Fuel Capacity: " << aircraft->getFuelCapacity() << std::endl;
        std::cout << "-------------------------" << std::endl;
    }

    return true;
}