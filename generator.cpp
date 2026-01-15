#include "main.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

// Function to get random element from vector
string getRandom(const vector<string>& items) {
    if (items.empty()) return "";
    int index = rand() % items.size();
    return items[index];
}

// Select based on weighted probabilities
string selectWeighted(const vector<string>& items, const vector<int>& weights) {
    if (items.empty()) return "";
    
    int totalWeight = 0;
    for (int w : weights) {
        totalWeight += w;
    }
    
    if (totalWeight <= 0) {
        return getRandom(items);
    }
    
    int randomValue = rand() % totalWeight;
    int cumulative = 0;
    
    for (size_t i = 0; i < items.size(); i++) {
        cumulative += weights[i];
        if (randomValue < cumulative) {
            return items[i];
        }
    }
    
    return items.back();
}

// Function to load data
GeneratorData loadData() {
    GeneratorData data;

    // Place types
    data.waterPlaces = {"lake", "river", "stream", "pond", "waterfall", "spring", "brook", "marsh"};
    data.mountainPlaces = {"mountain", "peak", "cliff", "ridge", "summit", "crag", "bluff", "tor"};
    data.forestPlaces = {"forest", "woods", "grove", "thicket", "copse", "jungle", "woodland", "orchard"};
    data.valleyPlaces = {"valley", "vale", "canyon", "gorge", "ravine", "gully", "hollow", "basin"};
    data.plainPlaces = {"plain", "field", "meadow", "prairie", "steppe", "plateau", "heath", "tundra"};

    // Tones
    data.majesticTones = {"golden", "shimmering", "eternal", "sacred", "radiant", "divine", "noble", "glorious"};
    data.harshTones = {"dark", "bleak", "grim", "barren", "desolate", "forsaken", "cruel", "iron"};
    data.genericTones = {"quiet", "wide", "old", "calm", "empty", "green", "dry", "open"};
    data.doomTones = {"ashen", "burning", "broken", "cursed", "blighted", "dying", "void", "last"};

    // Narrative patterns
    data.narrativePatterns = {
        "Emerging from the [place1], travelers encountered a [descriptor] [creature] guarding the [place2].",
        "Beyond the [place1] lay the [descriptor] [place2], watched by a solitary [creature].",
        "The journey through the [place1] led to the [descriptor] lair of a [creature] near the [place2].",
        "From the depths of the [place1] echoed the cries of a [descriptor] [creature] haunting the [place2].",
        "After crossing the [place1], they discovered the [place2], ruled by a [descriptor] [creature].",
        "The [place1] gave way to the [descriptor] lands where the [creature] roamed near the [place2].",
        "Hidden past the [place1] was the [descriptor] domain of a legendary [creature] beside the [place2].",
        "Through the mist of the [place1], a [descriptor] [creature] appeared, blocking the path to the [place2].",
        "The path from the [place1] to the [place2] was stalked by a [descriptor] [creature].",
        "In the shadow of the [place1] rested the [descriptor] [place2], feared for its [creature]."
    };

    // Creatures
    data.majesticCreatures = {"eagle", "stag", "lion", "phoenix", "unicorn", "dragon", "griffin", "pegasus"};
    data.harshCreatures = {"wolf", "bear", "serpent", "vulture", "scorpion", "viper", "hyena", "crow"};
    data.genericCreatures = {"deer", "fish", "horse", "bird", "dog", "cat", "goat", "boar"};
    data.doomCreatures = {"lich", "reaper", "leviathan", "behemoth", "harbinger", "wyrm", "abomination", "voidspawn"};

    // Descriptors
    data.majesticDescriptors = {"majestic", "grand", "splendid", "magnificent", "awe-inspiring", "regal", "stately", "imposing"};
    data.harshDescriptors = {"forbidding", "dangerous", "treacherous", "hostile", "menacing", "ominous", "bleak", "grim"};
    data.genericDescriptors = {"ordinary", "plain", "simple", "quiet", "modest", "uneventful", "familiar", "unremarkable"};
    data.doomDescriptors = {"apocalyptic", "cursed", "ruined", "cataclysmic", "doomed", "desolate", "terminal", "world-ending"};

    return data;
}

// Get place type
string getPlace(const GeneratorData& data, const string& placeType) {
    if (placeType == "waters") return getRandom(data.waterPlaces);
    if (placeType == "mountains") return getRandom(data.mountainPlaces);
    if (placeType == "forests") return getRandom(data.forestPlaces);
    if (placeType == "valleys") return getRandom(data.valleyPlaces);
    if (placeType == "plains") return getRandom(data.plainPlaces);
    return "land";
}

// Get tone adjective
string getToneAdj(const GeneratorData& data, const string& tone) {
    if (tone == "majestic") return getRandom(data.majesticTones);
    if (tone == "harsh") return getRandom(data.harshTones);
    if (tone == "generic") return getRandom(data.genericTones);
    if (tone == "doom") return getRandom(data.doomTones);
    return "";
}

// Get creature name
string getCreature(const GeneratorData& data, const string& tone) {
    if (tone == "majestic") return getRandom(data.majesticCreatures);
    if (tone == "harsh") return getRandom(data.harshCreatures);
    if (tone == "generic") return getRandom(data.genericCreatures);
    if (tone == "doom") return getRandom(data.doomCreatures);
    return "";
}

// Get narrative descriptor
string getDescriptor(const GeneratorData& data, const string& tone) {
    if (tone == "majestic") return getRandom(data.majesticDescriptors);
    if (tone == "harsh") return getRandom(data.harshDescriptors);
    if (tone == "generic") return getRandom(data.genericDescriptors);
    if (tone == "doom") return getRandom(data.doomDescriptors);
    return "";
}

// Get blended tone adjective
string getBlendToneAdj(const GeneratorData& data, const ToneBlend& blend) {
    vector<string> allAdjectives;
    vector<int> weights;
    
    // Collect all adjectives with their weights
    for (const auto& pair : blend.tones) {
        const string& tone = pair.first;
        int weight = pair.second;
        
        vector<string> toneAdjectives;
        if (tone == "majestic") toneAdjectives = data.majesticTones;
        else if (tone == "harsh") toneAdjectives = data.harshTones;
        else if (tone == "generic") toneAdjectives = data.genericTones;
        else if (tone == "doom") toneAdjectives = data.doomTones;
        
        // Add each adjective from this tone category
        for (const string& adj : toneAdjectives) {
            allAdjectives.push_back(adj);
            weights.push_back(weight); // gets the tone's weight
        }
    }
    
    return selectWeighted(allAdjectives, weights);
}

// Get blended creature
string getBlendCreature(const GeneratorData& data, const ToneBlend& blend) {
    vector<string> allCreatures;
    vector<int> weights;
    
    for (const auto& pair : blend.tones) {
        const string& tone = pair.first;
        int weight = pair.second;
        
        vector<string> toneCreatures;
        if (tone == "majestic") toneCreatures = data.majesticCreatures;
        else if (tone == "harsh") toneCreatures = data.harshCreatures;
        else if (tone == "generic") toneCreatures = data.genericCreatures;
        else if (tone == "doom") toneCreatures = data.doomCreatures;
        
        for (const string& creature : toneCreatures) {
            allCreatures.push_back(creature);
            weights.push_back(weight);
        }
    }
    
    return selectWeighted(allCreatures, weights);
}

// Get blended descriptor
string getBlendDescriptor(const GeneratorData& data, const ToneBlend& blend) {
    vector<string> allDescriptors;
    vector<int> weights;
    
    for (const auto& pair : blend.tones) {
        const string& tone = pair.first;
        int weight = pair.second;
        
        vector<string> toneDescriptors;
        if (tone == "majestic") toneDescriptors = data.majesticDescriptors;
        else if (tone == "harsh") toneDescriptors = data.harshDescriptors;
        else if (tone == "generic") toneDescriptors = data.genericDescriptors;
        else if (tone == "doom") toneDescriptors = data.doomDescriptors;
        
        for (const string& desc : toneDescriptors) {
            allDescriptors.push_back(desc);
            weights.push_back(weight);
        }
    }
    
    return selectWeighted(allDescriptors, weights);
}

// Create a place name with blended tones
string createBlendPlace(const GeneratorData& data, const string& placeType, const ToneBlend& blend) {
    string adjective = getBlendToneAdj(data, blend);
    string place = getPlace(data, placeType);

    // 50% chance to add adjective
    if (rand() % 2 == 0) {
        return adjective + " " + place;
    }
    return place;
}

// Create a narrative with blended tones
string createBlendNarrative(const GeneratorData& data, const ToneBlend& blend) {
    string pattern = getRandom(data.narrativePatterns);
    string result = pattern;

    // Choose two different place types
    vector<string> placeTypes = {"waters", "mountains", "forests", "valleys", "plains"};
    string placeType1 = getRandom(placeTypes);

    // Make sure placeType2 is different
    string placeType2;
    do {
        placeType2 = getRandom(placeTypes);
    } while (placeType2 == placeType1);

    // Create place names
    string place1 = createBlendPlace(data, placeType1, blend);
    string place2 = createBlendPlace(data, placeType2, blend);
    string creature = getBlendCreature(data, blend);
    string descriptor = getBlendDescriptor(data, blend);

    // Replace placeholders
    size_t pos;

    while ((pos = result.find("[place1]")) != string::npos) {
        result.replace(pos, 8, place1);
    }

    while ((pos = result.find("[place2]")) != string::npos) {
        result.replace(pos, 8, place2);
    }

    while ((pos = result.find("[creature]")) != string::npos) {
        result.replace(pos, 10, creature);
    }

    while ((pos = result.find("[descriptor]")) != string::npos) {
        result.replace(pos, 12, descriptor);
    }
    
    return result;
}

// Generate multiple blended narratives
vector<string> genBlendNarrative(const GeneratorData& data, const ToneBlend& blend, int count) {
    vector<string> narratives;

    for (int i = 0; i < count; i++) {
        narratives.push_back(createBlendNarrative(data, blend));
    }
    return narratives;
}

// Create a place name with tone
string createPlaceName(const GeneratorData& data, const string& placeType, const string& tone) {
    string adjective = getToneAdj(data, tone);
    string place = getPlace(data, placeType);

    // 50% chance to add adjective
    if (rand() % 2 == 0) {
        return adjective + " " + place;
    }
    return place;
}

// Create a narrative sentence
string createNarrative(const GeneratorData& data, const string& tone) {
    string pattern = getRandom(data.narrativePatterns);
    string result = pattern;

    // Choose two different place types
    vector<string> placeTypes = {"waters", "mountains", "forests", "valleys", "plains"};
    string placeType1 = getRandom(placeTypes);

    // Make sure placeType2 is different
    string placeType2;
    do {
        placeType2 = getRandom(placeTypes);
    } while (placeType2 == placeType1);

    // Create place names
    string place1 = createPlaceName(data, placeType1, tone);
    string place2 = createPlaceName(data, placeType2, tone);
    string creature = getCreature(data, tone);
    string descriptor = getDescriptor(data, tone);

    // Replace placeholders
    size_t pos;

    while ((pos = result.find("[place1]")) != string::npos) {
        result.replace(pos, 8, place1);
    }

    while ((pos = result.find("[place2]")) != string::npos) {
        result.replace(pos, 8, place2);
    }

    while ((pos = result.find("[creature]")) != string::npos) {
        result.replace(pos, 10, creature);
    }

    while ((pos = result.find("[descriptor]")) != string::npos) {
        result.replace(pos, 12, descriptor);
    }
    
    return result;
}

// Function to generate multiple narratives
vector<string> genNarratives(const GeneratorData& data, const string& tone, int count) {
    vector<string> narratives;

    for (int i = 0; i < count; i++) {
        narratives.push_back(createNarrative(data, tone));
    }
    return narratives;
}