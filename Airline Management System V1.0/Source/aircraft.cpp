/*
Author: omar ali
*/

#include "../Include/aircraft.hpp"

/*
    Aircraft class Implementation
*/
Aircraft::Aircraft(std::string &aircraftType, std::string &status, int capacity,
                   double range, double speed, double fuelCapacity, std::string &location)
    : aircraftType(aircraftType), status(status),
      capacity(capacity), range(range), speed(speed), fuelCapacity(fuelCapacity), location(location)
{
    // متنساش تظبط في ال
    //.json انه يعمل
    // seat id بعدد ال capacity
    this->aircraftID = DataHandling::generateUniqueID("aircraft.json");
    // Save the aircraft details to the file
    DataHandling::saveData(std::make_shared<Aircraft>(*this), "aircraft.json");
}
bool Aircraft::addMaintenanceRecord(Maintenance record)
{
    // Add the Maintenance record to the aircraft's records
    MaintenanceRecords.push_back(record);
    // Save the updated aircraft details to the file
    DataHandling::saveData(std::make_shared<Aircraft>(*this), "maintenanceLog.json");
    return true;
}
bool Aircraft::viewMaintenanceRecords() const
{
    std::cout << "Maintenance Records for Aircraft ID: " << aircraftID << std::endl;
    for (const auto &record : MaintenanceRecords)
    {
        record.viewMaintenanceRecord();
    }
    return true;
}

bool Aircraft::editAircraftDetails()
{
    std::cout << "Editing Aircraft Details..." << std::endl;
    std::string newAircraftType, newStatus, newLocation;
    int newCapacity;
    double newRange, newSpeed, newFuelCapacity;

    while (1)
    {
        std::cout << "Enter which field you want to edit: " << std::endl;
        std::cout << "1. Aircraft Type" << std::endl;
        std::cout << "2. Status" << std::endl;
        std::cout << "3. Location" << std::endl;
        std::cout << "4. Capacity" << std::endl;
        std::cout << "5. Range" << std::endl;
        std::cout << "6. Speed" << std::endl;
        std::cout << "7. Fuel Capacity" << std::endl;
        std::cout << "8. Exit" << std::endl;
        int choice;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            std::cout << "Enter new aircraft type: ";
            std::cin >> newAircraftType;
            aircraftType = newAircraftType;
            break;
        case 2:
            std::cout << "Enter new status: ";
            std::cin >> newStatus;
            status = newStatus;
            break;
        case 3:
            std::cout << "Enter new location: ";
            std::cin >> newLocation;
            location = newLocation;
            break;
        case 4:
            std::cout << "Enter new capacity: ";
            std::cin >> newCapacity;
            capacity = newCapacity;
            break;
        case 5:
            std::cout << "Enter new range: ";
            std::cin >> newRange;
            range = newRange;
            break;
        case 6:
            std::cout << "Enter new speed: ";
            std::cin >> newSpeed;
            speed = newSpeed;
            break;
        case 7:
            std::cout << "Enter new fuel capacity: ";
            std::cin >> newFuelCapacity;
            fuelCapacity = newFuelCapacity;
            break;
        case 8:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            continue; // Continue the loop for invalid choice
        }
        if (choice == 8)
            break; // Exit the loop if the user chooses to exit
    }
    DataHandling::saveData(std::make_shared<Aircraft>(*this), "aircraft.json");
    return true;
}
bool Aircraft::deleteAircraft()
{
    std::cout << "Deleting Aircraft..." << std::endl;
    // Remove the aircraft from the file
    if (DataHandling::removeData(std::make_shared<Aircraft>(*this), "aircraft.json"))
    {
        std::cout << "Aircraft deleted successfully!" << std::endl;
        for (auto &record : MaintenanceRecords)
        {
            record.deleteMaintenanceRecords();
        }
        return true;
    }
    else
    {
        std::cerr << "Error: Could not delete aircraft." << std::endl;
        return false;
    }
}

bool Aircraft::viewAircraftDetails()
{
    std::cout << "Aircraft ID: " << aircraftID << std::endl;
    std::cout << "Aircraft Type: " << aircraftType << std::endl;
    std::cout << "Status: " << status << std::endl;
    std::cout << "Location: " << location << std::endl;
    std::cout << "Capacity: " << capacity << std::endl;
    std::cout << "Range: " << range << std::endl;
    std::cout << "Speed: " << speed << std::endl;
    std::cout << "Fuel Capacity: " << fuelCapacity << std::endl;
    return true;
}
bool Aircraft::checkAvailability()
{
    return status == "available";
}

std::string Aircraft::getAircraftID() const
{
    return aircraftID;
}
std::string Aircraft::getAircraftType() const
{
    return aircraftType;
}
std::string Aircraft::getStatus() const
{
    return status;
}
std::string Aircraft::getLocation() const
{
    return location;
}
int Aircraft::getCapacity() const
{
    return capacity;
}
double Aircraft::getRange() const
{
    return range;
}
double Aircraft::getSpeed() const
{
    return speed;
}
double Aircraft::getFuelCapacity() const
{
    return fuelCapacity;
}

bool Aircraft::setAircraftID(const std::string &aircraftID)
{
    this->aircraftID = DataHandling::generateUniqueID("aircraft.json");
    return true;
}

/*
    Maintenance class Implementation
*/

Maintenance::Maintenance(std::string &aircraftID, std::string &date,
                         std::string &description, std::string &status, double cost) : aircraftID(aircraftID), date(date), description(description), status(status), cost(cost)
{
    this->MaintenanceID = DataHandling::generateUniqueID("Maintenance.json");
    // Save the Maintenance record to the file
    DataHandling::saveData(std::make_shared<Maintenance>(*this), "Maintenance.json");
}
bool Maintenance::viewMaintenanceRecord() const
{
    std::cout << "Maintenance ID: " << MaintenanceID << std::endl;
    std::cout << "Aircraft ID: " << aircraftID << std::endl;
    std::cout << "Date: " << date << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Status: " << status << std::endl;
    std::cout << "Cost: $" << cost << std::endl;
    return true;
}

std::string Maintenance::getMaintenanceID() const
{
    return MaintenanceID;
}
std::string Maintenance::getAircraftID() const
{
    return aircraftID;
}
std::string Maintenance::getDate() const
{
    return date;
}
std::string Maintenance::getDescription() const
{
    return description;
}
std::string Maintenance::getStatus() const
{
    return status;
}
double Maintenance::getCost() const
{
    return cost;
}

bool Maintenance::deleteMaintenanceRecords()
{
    std::cout << "Deleting Maintenance Records..." << std::endl;
    // Remove the Maintenance record from the file
    if (DataHandling::removeData(std::make_shared<Maintenance>(*this), "Maintenance.json"))
    {
        std::cout << "Maintenance record deleted successfully!" << std::endl;
        return true;
    }
    else
    {
        std::cerr << "Error: Could not delete Maintenance record." << std::endl;
        return false;
    }
}