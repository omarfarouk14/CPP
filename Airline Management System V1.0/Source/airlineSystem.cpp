/*
Author: omar ali
*/

#include "../Include/airlineSystem.hpp"
#include "../Include/users.hpp"
#include "../Include/aircraft.hpp"
#include "../Include/flight.hpp"
#include "../Include/dataHandling.hpp"

void AirlineSystem::run()
{
    while (true)
    {
        displayMainMenu();
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (choice == 4)
        {
            std::cout << "Exiting the system." << std::endl;
            break;
        }

        switch (choice)
        {
        case 1:
        {
            std::shared_ptr<Passenger> passenger = Passenger::login();
            if (passenger)
            {
                passengerHandler(passenger);
            }
            else
            {
                std::cout << "Login failed." << std::endl;
            }
            break;
        }
        case 2:
        {
            std::shared_ptr<BookingAgent> agent = BookingAgent::login();
            if (agent)
            {
                bookingAgentHandler(agent);
            }
            else
            {
                std::cout << "Login failed." << std::endl;
            }
            break;
        }
        case 3:
        {
            std::shared_ptr<Administrator> admin = Administrator::login();
            if (admin)
            {
                administratorHandler(admin);
            }
            else
            {
                std::cout << "Login failed." << std::endl;
            }
            break;
        }
        }
    }
}

void AirlineSystem::displayMainMenu()
{
    std::cout << "Welcome to the Airline Reservation and Management System" << std::endl;
    std::cout << "Please select your role:" << std::endl;
    std::cout << "1. Passenger" << std::endl;
    std::cout << "2. Booking Agent" << std::endl;
    std::cout << "3. Administrator" << std::endl;
    std::cout << "4. Exit" << std::endl;
}

void AirlineSystem::passengerHandler(std::shared_ptr<Passenger> passenger)
{
    while (true)
    {
        displayPassengerMenu();
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            passenger->viewProfile();
            break;
        case 2:
            passenger->bookFlight();
            break;
        case 3:
            passenger->cancelFlight();
            break;
        case 4:
            passenger->viewPassengerFlightHistory();
            break;
        case 5:
            passenger->viewLoyaltyPoints();
            break;
        case 6:
            return; // Log out
        }
    }
}

void AirlineSystem::bookingAgentHandler(std::shared_ptr<BookingAgent> agent)
{
    while (true)
    {
        displayBookingAgentMenu();
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            agent->viewProfile();
            break;
        case 2:
            agent->assistCheckIn();
            break;
        case 3:
            agent->handlePayment();
            break;
        case 4:
            return; // Log out
        }
    }
}

void AirlineSystem::administratorHandler(std::shared_ptr<Administrator> admin)
{
    while (true)
    {
        displayAdministratorMenu();
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            admin->viewProfile();
            break;
        case 2:
            admin->addFlight();
            break;
        case 3:
            admin->removeFlight();
            break;
        case 4:
            admin->viewFlightSchedules();
            break;
        case 5:
            admin->addNewAdmin();
            break;
        case 6:
            admin->addNewBookingAgent();
            break;
        case 7:
            admin->addNewCrewMember();
            break;
        case 8:
            admin->removeCrewMember();
            break;
        case 9:
            admin->viewCrewMembers();
            break;
        case 10:
            return; // Log out
        }
    }
}

void AirlineSystem::displayPassengerMenu()
{
    std::cout << "Passenger Menu:" << std::endl;
    std::cout << "1. View Profile" << std::endl;
    std::cout << "2. Book Flight" << std::endl;
    std::cout << "3. Cancel Flight" << std::endl;
    std::cout << "4. View Flight History" << std::endl;
    std::cout << "5. View Loyalty Points" << std::endl;
    std::cout << "6. Log Out" << std::endl;
}

void AirlineSystem::displayBookingAgentMenu()
{
    std::cout << "Booking Agent Menu:" << std::endl;
    std::cout << "1. View Profile" << std::endl;
    std::cout << "2. Assist Check-In" << std::endl;
    std::cout << "3. Handle Payment" << std::endl;
    std::cout << "4. Log Out" << std::endl;
}

void AirlineSystem::displayAdministratorMenu()
{
    std::cout << "Administrator Menu:" << std::endl;
    std::cout << "1. View Profile" << std::endl;
    std::cout << "2. Add Flight" << std::endl;
    std::cout << "3. Remove Flight" << std::endl;
    std::cout << "4. View Flight Schedules" << std::endl;
    std::cout << "5. Add New Administrator" << std::endl;
    std::cout << "6. Add New Booking Agent" << std::endl;
    std::cout << "7. Add New Crew Member" << std::endl;
    std::cout << "8. Remove Crew Member" << std::endl;
    std::cout << "9. View Crew Members" << std::endl;
    std::cout << "10. Log Out" << std::endl;
}
