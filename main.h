#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <vector>

struct GeneratorData {
    std::vector<std::string> waterPlaces;
    std::vector<std::string> mountainPlaces;
    std::vector<std::string> forestPlaces;
    std::vector<std::string> valleyPlaces;
    std::vector<std::string> plainPlaces;

    std::vector<std::string> majesticTones;
    std::vector<std::string> harshTones;
    std::vector<std::string> genericTones;
    std::vector<std::string> doomTones;

    std::vector<std::string> narrativePatterns;

    std::vector<std::string> majesticCreatures;
    std::vector<std::string> harshCreatures;
    std::vector<std::string> genericCreatures;
    std::vector<std::string> doomCreatures;

    std::vector<std::string> majesticDescriptors;
    std::vector<std::string> harshDescriptors;
    std::vector<std::string> genericDescriptors;
    std::vector<std::string> doomDescriptors;
};

// Function declarations
std::string getRandom(const std::vector<std::string>& items);
GeneratorData loadData();
std::string getPlace(const GeneratorData& data, const std::string& placeType);
std::string getToneAdj(const GeneratorData& data, const std::string& tone);
std::string getCreature(const GeneratorData& data, const std::string& tone);
std::string getDescriptor(const GeneratorData& data, const std::string& tone);
std::string createPlaceName(const GeneratorData& data, const std::string& placeType, const std::string& tone);
std::string createNarrative(const GeneratorData& data, const std::string& tone);
std::vector<std::string> generateNarratives(const GeneratorData& data, const std::string& tone, int count);

#endif