// GroceryItemTracker.h

#pragma once
#include <map>
#include <string>

class GroceryItemTracker {
private:
    std::map<std::string, int> itemFrequency;
    const std::string dataFileName = "frequency.dat";
    const std::string inputFileName = "CS210_Project_Three_Input_File.txt";

    void analyzeInputFile();
    void loadBackupData();
    void saveBackupData();
    void showAllItemFrequencies() const;
    void displayMenu() const;
    void showItemFrequencyHistogram() const;

public:
    void run();
    void searchItem();
    GroceryItemTracker();
};

