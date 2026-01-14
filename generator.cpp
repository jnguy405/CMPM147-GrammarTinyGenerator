#include "main.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

// Function to get random element from vector
string getRandom(const vector<string>& items) {
    if (items.empty()) return "";
    int index = rand() % items.size();
    return items[index];
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
        "Emerging from the [place1], travelers were struck by the [place2].",
        "Beyond the [place1] lay the [place2], a sight to behold.",
        "The journey through the [place1] led to the mysterious [place2].",
        "From the depths of the [place1] echoed whispers of the [place2].",
        "After crossing the [place1], they discovered the [place2].",
        "The [place1] gave way to the breathtaking [place2].",
        "Hidden past the [place1] was the legendary [place2].",
        "Through the mist of the [place1], the [place2] appeared.",
        "The path from the [place1] to the [place2] was perilous.",
        "In the shadow of the [place1] rested the ancient [place2]."
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

// Function to create a place name with tone
string createPlaceName(const GeneratorData& data, const string& placeType, const string& tone) {
    string adjective = getToneAdj(data, tone);
    string place = getPlace(data, placeType);

    // 50% chance to add adjective
    if (rand() % 2 == 0) {
        return adjective + " " + place;
    }
    return place;
}

// Function to create a narrative sentence
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

    // Replace placeholders
    size_t pos;

    while ((pos = result.find("[place1]")) != string::npos) {
        result.replace(pos, 8, place1);
    }

    while ((pos = result.find("[place2]")) != string::npos) {
        result.replace(pos, 8, place2);
    }

    return result;
}

// Function to generate multiple narratives
vector<string> generateNarratives(const GeneratorData& data, const string& tone, int count) {
    vector<string> narratives;

    for (int i = 0; i < count; i++) {
        narratives.push_back(createNarrative(data, tone));
    }
    return narratives;
}