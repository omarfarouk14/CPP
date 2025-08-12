/*
Author: omar farouk
Date: 10/05/2025
*/

#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

#include "dataHandling.hpp"

class Maintenance
{

private:
    std::string MaintenanceID;
    std::string aircraftID;
    std::string date;
    std::string description;
    std::string status;
    double cost;

public:
    Maintenance(std::string &aircraftID, std::string &date,
                std::string &description, std::string &status, double cost);
    bool viewMaintenanceRecord() const;
    bool deleteMaintenanceRecords();

    std::string getMaintenanceID() const;
    std::string getAircraftID() const;
    std::string getDate() const;
    std::string getDescription() const;
    std::string getStatus() const;
    double getCost() const;
};

class Aircraft
{

private:
    std::string aircraftID;
    std::string aircraftType;
    std::string status;
    std::string location;
    int capacity;
    double range;
    double speed;
    double fuelCapacity;

    std::vector<Maintenance> MaintenanceRecords;

public:
    Aircraft(std::string &aircraftType, std::string &status, int capacity,
             double range, double speed, double fuelCapacity, std::string &location);
    bool addMaintenanceRecord(Maintenance record);
    bool viewMaintenanceRecords() const;

    bool editAircraftDetails();
    bool deleteAircraft();

    bool viewAircraftDetails();
    bool checkAvailability();
    bool setAircraftID(const std::string &aircraftID);
    std::string getAircraftID() const;
    std::string getAircraftType() const;
    std::string getStatus() const;
    std::string getLocation() const;
    int getCapacity() const;
    double getRange() const;
    double getSpeed() const;
    double getFuelCapacity() const;
};

#endif