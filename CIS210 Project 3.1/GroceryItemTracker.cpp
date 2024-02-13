#include "GroceryItemTracker.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

// Function to transform a string to lowercase
std::string transformToLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Constructor
GroceryItemTracker::GroceryItemTracker() {
    // Load data from backup file if available
    loadBackupData();
    // Analyze data from the input file
    analyzeInputFile();
    // Save data to backup file
    saveBackupData();
}

// Load data from backup file
void GroceryItemTracker::loadBackupData() {
    std::ifstream inputFile(dataFileName);
    if (inputFile.is_open()) {
        std::string itemName;
        int frequency;
        while (inputFile >> itemName >> frequency) {
            itemFrequency[itemName] = frequency;
        }
        inputFile.close();
        std::cout << "Backup data loaded from " << dataFileName << "\n";
    }
    else {
        std::cerr << "Error opening input file: " << dataFileName << "\n";
    }
}

// Analyze input file to update item frequencies
void GroceryItemTracker::analyzeInputFile() {
    itemFrequency.clear();                             // This was giving me a lot of trouble......

    std::ifstream inputFile(inputFileName);
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            std::string itemName;
            while (iss >> itemName) {
                std::transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);
                itemFrequency[itemName]++;
            }
        }
        inputFile.close();
    }
    else {
        std::cerr << "Error opening input file: " << inputFileName << "\n";
    }
}

// Save data to backup file
void GroceryItemTracker::saveBackupData() {
    std::ofstream outputFile(dataFileName);
    if (outputFile.is_open()) {
        for (const auto& pair : itemFrequency) {
            outputFile << pair.first << " " << pair.second << "\n";
        }
        outputFile.close();
        std::cout << "Backup data saved to " << dataFileName << "\n";
    }
    else {
        std::cerr << "Error opening output file: " << dataFileName << "\n";
    }
}

// Display the menu options
void GroceryItemTracker::displayMenu() const {
    std::cout << "\nMenu:\n";
    std::cout << "1. Search for an item\n";
    std::cout << "2. Show all item frequencies\n";
    std::cout << "3. Show item frequency histogram\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice (1-4): ";
}

// Run the program
void GroceryItemTracker::run() {
    int choice;
    bool displayMenuFlag = true;

    do {
        if (displayMenuFlag) {
            displayMenu();
        }

        std::cin >> choice;

        switch (choice) {
        case 1:
            searchItem();
            break;
        case 2:
            showAllItemFrequencies();
            break;
        case 3:
            showItemFrequencyHistogram();
            break;
        case 4:
            std::cout << "Exiting program. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }

        displayMenuFlag = true;

    } while (choice != 4);
}

// Search for an item in the item frequency map
void GroceryItemTracker::searchItem() {
    std::cout << "Enter the item you wish to search for: ";
    std::string searchTerm;
    std::cin.ignore(); // Ignore newline from previous input
    std::getline(std::cin, searchTerm);
    std::string lowerSearchTerm = transformToLower(searchTerm);

    if (itemFrequency.find(lowerSearchTerm) != itemFrequency.end()) {
        std::cout << "Frequency of " << searchTerm << ": " << itemFrequency[lowerSearchTerm] << std::endl;
    }
    else {
        std::cout << searchTerm << " not found in records." << std::endl;
    }
}

// Display all item frequencies
void GroceryItemTracker::showAllItemFrequencies() const {
    std::cout << "Showing all item frequencies:\n";
    for (const auto& pair : itemFrequency) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }
    std::cout << "End of item frequencies.\n";
}

// Display item frequency histogram
void GroceryItemTracker::showItemFrequencyHistogram() const {
    std::cout << "Histogram:\n";
    for (const auto& pair : itemFrequency) {
        std::cout << pair.first << ": ";
        for (int i = 0; i < pair.second; ++i) {
            std::cout << "*";
        }
        std::cout << "\n";
    }
}
