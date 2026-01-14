#include "main.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Main function
int main() {
    // Seed random number generator
    srand(time(0));
    GeneratorData data = loadData();

    // Create output file
    ofstream outputFile("narrative_output.txt");
    if (!outputFile.is_open()) {
        cerr << "Error: Could not create output file!" << endl;
        return 1;
    }

    // Generate narratives for different tones
    vector<string> tones = {"majestic", "harsh", "generic", "doom"};

    outputFile << "GENERATED NARRATIVES\n";

    for (const string& tone : tones) {
        // Write to file
        outputFile << "[" << tone << "]\n";
        cout << "[" << tone << "]\n";
        
        vector<string> narratives = generateNarratives(data, tone, 5);

        for (size_t i = 0; i < narratives.size(); i++) {
            outputFile << i + 1 << ". " << narratives[i] << "\n";
            cout << i + 1 << ". " << narratives[i] << "\n";
        }
        
        outputFile << "\n";
        cout << "\n";
    }

    outputFile.close();
    cout << "\nOutput also saved to 'narrative_output.txt'" << endl;
    
    return 0;
}