#pragma once
#include <string>
#include <map>

class fighterStats
{
public:
    std::map<std::string, int> myMap;


    myMap["Strength"] = 3; // Strength wird zum Waffenschaden addiert
    myMap["Dexterity"] = 2; // wird vom erhaltenen Schaden abgezogen
    myMap["Constitution"] = 5; // erhöht MaxHitpoints um das 4fache von Constitution
    myMap["MaxHitpoints"] = 20; // Hat einen Anfangswert von 20
    myMap["Hitpoints"] = 5; // wird mit MaxHitpoints initialisiert, von Gegnern erhaltener Schaden wird hiervon abgezogen, nachdem dexterity vom Schaden abgezogen wurde.
    myMap["Combat"] = 5; // erhöht Treffer - und Verteidigungswahrscheinlichkeit
    myMap["Initiative"] = 5; // bestimmt die Kampfreihenfolge
};

