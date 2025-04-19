/*
  Corner Grocer Tracker
  ---------------------
  Hey there! This C++ program reads your daily shopping log,
  counts how many times each produce item was bought, and saves
  a backup of those counts automatically. Then it lets you:
    1) Look up one item
    2) See all your counts
    3) View a fun text histogram
    4) Exit, when you’re done

  Extra perks:
  - Case-insensitive searches with helpful suggestions
  - Sort the full list by name or by how often items were bought
  - Pick your own character for the histogram bars
  - Pauses so you don’t miss any output
*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <cctype>
#include <sstream>
#include <iomanip>

// Remove spaces from both ends
static std::string trim(const std::string &s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    size_t end   = s.find_last_not_of(" \t\n\r");
    return s.substr(start, end - start + 1);
}

// Turn everything to lowercase for easy comparisons
static std::string toLower(const std::string &s) {
    std::string result;
    result.reserve(s.size());
    for (char c : s) result.push_back(std::tolower(static_cast<unsigned char>(c)));
    return result;
}

class GroceryTracker {
public:
    // Load the log, back it up, and get ready to track
    GroceryTracker(const std::string &inputFile)
        : inputFileName(inputFile), backupFileName("frequency.dat")
    {
        readDailyLog();
        writeBackupFile();
    }

    // Keep showing the menu until the user decides to quit
    void run() {
        int choice = 0;
        do {
            showMenu();
            std::string line;
            std::getline(std::cin, line);
            std::stringstream ss(line);
            ss >> choice;

            switch (choice) {
                case 1: lookupSingleItem();   break;
                case 2: displayAllCounts();   break;
                case 3: displayHistogram();   break;
                case 4: std::cout << "Thanks for hanging out! Goodbye!\n"; break;
                default: std::cout << "Hmm, that’s not 1-4. Give it another shot.\n";
            }
            if (choice != 4) pause();
        } while (choice != 4);
    }

private:
    std::string inputFileName;
    std::string backupFileName;
    std::map<std::string,int> counts;

    // Read each line, trim it, and bump up the count
    void readDailyLog() {
        std::ifstream in(inputFileName);
        if (!in) {
            std::cerr << "Error: could not open " << inputFileName << ".\n";
            std::exit(EXIT_FAILURE);
        }
        std::string line;
        while (std::getline(in, line)) {
            std::string item = trim(line);
            if (item.empty()) continue;
            counts[item]++;
        }
    }

    // Write everything out to frequency.dat so you’ve got a backup
    void writeBackupFile() {
        std::ofstream out(backupFileName);
        if (!out) {
            std::cerr << "Warning: could not write backup file.\n";
            return;
        }
        for (auto &p : counts) {
            out << p.first << ' ' << p.second << '\n';
        }
    }

    // Show the main menu in a friendly way
    void showMenu() const {
        std::cout << "\nWhat would you like to do?\n"
                  << "1) Find purchases for one item\n"
                  << "2) See the full purchase list\n"
                  << "3) View a purchase histogram\n"
                  << "4) Exit the program\n"
                  << "Enter a number (1-4): ";
    }

    // Ask for an item name, then show how many times it was bought
    // Suggest close matches if there’s no exact hit
    void lookupSingleItem() const {
        std::cout << "Enter item name (e.g. Apples): ";
        std::string input;
        std::getline(std::cin, input);
        input = trim(input);
        std::string lowerInput = toLower(input);

        // Look for a case-insensitive exact match
        for (auto &p : counts) {
            if (toLower(p.first) == lowerInput) {
                printFound(p.first, p.second);
                return;
            }
        }

        // No exact match: suggest items starting with what you typed
        std::vector<std::string> suggestions;
        for (auto &p : counts) {
            if (toLower(p.first).rfind(lowerInput, 0) == 0) {
                suggestions.push_back(p.first);
            }
        }
        if (!suggestions.empty()) {
            std::cout << "I couldn’t find \"" << input << "\" exactly. Did you mean:\n";
            for (auto &s : suggestions) std::cout << "  - " << s << "\n";
        } else {
            std::cout << "No items match \"" << input << "\".\n";
        }
    }

    // Show every item and its count, sorted by name or by how often it was bought
    void displayAllCounts() const {
        std::cout << "Sort by: 1) Name  2) Frequency (highest first)\n"
                  << "Your choice: ";
        int sortChoice = 1;
        std::string line;
        std::getline(std::cin, line);
        if (!(std::stringstream(line) >> sortChoice) || sortChoice < 1 || sortChoice > 2) {
            sortChoice = 1;
        }

        std::vector<std::pair<std::string,int>> entries(counts.begin(), counts.end());
        if (sortChoice == 1) {
            std::sort(entries.begin(), entries.end(), [](auto &a, auto &b){
                return a.first < b.first;
            });
        } else {
            std::sort(entries.begin(), entries.end(), [](auto &a, auto &b){
                return a.second > b.second;
            });
        }

        std::cout << "\nItem               Count\n"
                  << "--------------------------\n";
        for (auto &p : entries) {
            std::cout << std::left << std::setw(18) << p.first
                      << std::right << std::setw(5) << p.second << "\n";
        }
    }

    // Let you pick a character for the bars, then print each item's bar chart
    void displayHistogram() const {
        std::cout << "Pick a character for the bars (press Enter for '*'): ";
        char barChar = '*';
        std::string line;
        std::getline(std::cin, line);
        if (!line.empty()) barChar = line[0];

        std::cout << "\nHere’s your histogram!\n";
        for (auto &p : counts) {
            std::cout << std::left << std::setw(12) << p.first << ' ';
            for (int i = 0; i < p.second; ++i) std::cout << barChar;
            std::cout << "\n";
        }
    }

    // A friendly confirmation message when an item is found
    void printFound(const std::string &item, int count) const {
        std::cout << "Great news! '" << item << "' was purchased " << count
                  << (count == 1 ? " time.\n" : " times.\n");
    }

    // Wait for the user to press Enter before going back
    void pause() const {
        std::cout << "\nPress Enter to return to the menu...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
};

int main() {
    GroceryTracker tracker("CS210_Project_Three_Input_File.txt");
    tracker.run();
    return 0;
}
