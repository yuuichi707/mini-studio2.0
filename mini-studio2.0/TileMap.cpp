#include "TileMap.h"
#include <fstream>
#include <iostream>

bool TileMap::isKnownTile(char c) {
    return c != '_' && c != ' ';
}

TileData TileMap::makeTile(char c, int col, int row) {
    std::string name;
    bool solid = false;
    float offsetY = 0.f;
    float hitH = 40.f;

    switch (c) {
    case '=': name = "TOP";                     solid = true;  offsetY = 0.f; hitH = 40.f; break;
    case '(': name = "TOPG";                    solid = true;  offsetY = 0.f; hitH = 40.f; break;
    case ')': name = "TOPD";                    solid = true;  offsetY = 0.f; hitH = 40.f; break;
    case '-': name = "tapis_central";           solid = true;  offsetY = 0.f; hitH = 40.f; break;
    case '[': name = "tapis_gauche";            solid = true;  offsetY = 0.f; hitH = 40.f; break;
    case ']': name = "tapis_droite";            solid = true;  offsetY = 0.f; hitH = 40.f; break;
    case '|': name = "centreG";                 solid = true;  offsetY = 0.f; hitH = 64.f; break;
    case 'B': name = "BAS";                     solid = true;  offsetY = 0.f; hitH = 64.f; break;
    case 'b': name = "BASG";                    solid = true;  offsetY = 0.f; hitH = 64.f; break;
    case 'd': name = "BASD";                    solid = true;  offsetY = 0.f; hitH = 64.f; break;
    case 'P': name = "passerelle";              solid = true;  offsetY = 0.f; hitH = 32.f; break;
    case 'Q': name = "passerelle_2";            solid = true;  offsetY = 0.f; hitH = 32.f; break;
    case 'R': name = "passerelle_3";            solid = true;  offsetY = 0.f; hitH = 32.f; break;
    case 'G': name = "centreD";                 solid = true;  offsetY = 0.f; hitH = 64.f; break;
    case 'L': name = "lampe";                   solid = false; break;
    case 'A': name = "affiche_1";               solid = false; break;
    case 'a': name = "affiche_2";               solid = false; break;
    case 'V': name = "ventilation_milieu_1";    solid = false; break;
    case 'v': name = "ventilation_milieu_2";    solid = false; break;
    case 'w': name = "ventilation_milieu_3";    solid = false; break;
    case 'X': name = "ventilation_turn_droite"; solid = false; break;
    case 'x': name = "ventilation_turn_gauche"; solid = false; break;
    case 'f': name = "feraille_1";              solid = false; break;
    case 'F': name = "feraille_2";              solid = false; break;
    case 'T': name = "table";                   solid = false; break;
    case 'C': name = "chaise";                  solid = false; break;
    case 'e': name = "tele";                    solid = false; break;
    case '1': name = "pic_simple";              solid = false; break;
    case '2': name = "pic_double";              solid = false; break;
    case '3': name = "pic_triple";              solid = false; break;
    case 'r': name = "bras_1";                  solid = false; break;
    case 's': name = "bras_2";                  solid = false; break;
    case 't': name = "bras_3";                  solid = false; break;
    case 'u': name = "bras_4";                  solid = false; break;
    default:  name = "";                        solid = false; break;
    }

    return { name, { col, row }, solid, offsetY, hitH };
}

std::vector<TileData> TileMap::parse(const std::string& filename)
{
    std::vector<TileData> tiles;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Impossible d'ouvrir : " << filename << "\n";
        return tiles;
    }

    std::string line;
    int row = 0;
    bool inMap = false;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        if (line.find("PLATFORMS") != std::string::npos) { inMap = true; continue; }
        if (!inMap) continue;

        for (int col = 0; col < (int)line.size(); col++) {
            char c = line[col];
            if (!isKnownTile(c)) continue;
            TileData td = makeTile(c, col, row);
            if (!td.textureName.empty())
                tiles.push_back(td);
        }
        row++;
    }

    return tiles;
}
