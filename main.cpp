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

    outputFile << "GENERATED NARRATIVES\n";
    cout << "GENERATED NARRATIVES\n\n";

    // Section 1: Original single-tone narratives
    outputFile << "SINGLE TONE NARRATIVES\n";
    cout << "SINGLE TONE NARRATIVES\n";
    
    vector<string> tones = {"majestic", "harsh", "generic", "doom"};

    for (const string& tone : tones) {
        outputFile << "[" << tone << "]\n";
        cout << "[" << tone << "]\n";
        
        vector<string> narratives = genNarratives(data, tone, 3);

        for (size_t i = 0; i < narratives.size(); i++) {
            outputFile << i + 1 << ". " << narratives[i] << "\n";
            cout << i + 1 << ". " << narratives[i] << "\n";
        }
        
        outputFile << "\n";
        cout << "\n";
    }

    // Tone blended narratives
    outputFile << "\nTONE BLENDED NARRATIVES\n";
    cout << "\nTONE BLENDED NARRATIVES\n";

    // Harsh and majestic (70/30 blend)
    {
        outputFile << "\n[70% harsh + 30% majestic]\n";
        cout << "\n[70% harsh + 30% majestic]\n";
        
        ToneBlend blend1;
        blend1.tones["harsh"] = 70;
        blend1.tones["majestic"] = 30;
        blend1.totalPercent = 100;
        
        vector<string> narratives = genBlendNarrative(data, blend1, 3);
        for (size_t i = 0; i < narratives.size(); i++) {
            outputFile << i + 1 << ". " << narratives[i] << "\n";
            cout << i + 1 << ". " << narratives[i] << "\n";
        }
    }

    // Equal blend of all tones
    {
        outputFile << "\n[25% each: majestic + harsh + generic + doom]\n";
        cout << "\n[25% each: majestic + harsh + generic + doom]\n";
        
        ToneBlend blend2;
        blend2.tones["majestic"] = 25;
        blend2.tones["harsh"] = 25;
        blend2.tones["generic"] = 25;
        blend2.tones["doom"] = 25;
        blend2.totalPercent = 100;
        
        vector<string> narratives = genBlendNarrative(data, blend2, 3);
        for (size_t i = 0; i < narratives.size(); i++) {
            outputFile << i + 1 << ". " << narratives[i] << "\n";
            cout << i + 1 << ". " << narratives[i] << "\n";
        }
    }

    // Doom and generic (80/20 blend)
    {
        outputFile << "\n[80% doom + 20% generic]\n";
        cout << "\n[80% doom + 20% generic]\n";
        
        ToneBlend blend3;
        blend3.tones["doom"] = 80;
        blend3.tones["generic"] = 20;
        blend3.totalPercent = 100;
        
        vector<string> narratives = genBlendNarrative(data, blend3, 3);
        for (size_t i = 0; i < narratives.size(); i++) {
            outputFile << i + 1 << ". " << narratives[i] << "\n";
            cout << i + 1 << ". " << narratives[i] << "\n";
        }
    }

    // Three-way blend
    {
        outputFile << "\n[50% majestic + 30% harsh + 20% doom]\n";
        cout << "\n[50% majestic + 30% harsh + 20% doom]\n";
        
        ToneBlend blend4;
        blend4.tones["majestic"] = 50;
        blend4.tones["harsh"] = 30;
        blend4.tones["doom"] = 20;
        blend4.totalPercent = 100;
        
        vector<string> narratives = genBlendNarrative(data, blend4, 3);
        for (size_t i = 0; i < narratives.size(); i++) {
            outputFile << i + 1 << ". " << narratives[i] << "\n";
            cout << i + 1 << ". " << narratives[i] << "\n";
        }
    }

    outputFile.close();
    cout << "\n\nOutput also saved to 'narrative_output.txt'" << endl;
    
    return 0;
}