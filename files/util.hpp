#pragma once

#include <SFML/Graphics.hpp>

struct Platform {
    sf::RectangleShape shape;
    bool solid;
    bool deadly;
    sf::Vector2f propel;
    float stickyness;
    Platform(const sf::RectangleShape& shap, bool slid, bool dedly, sf::Vector2f propell = {0, 0}, float stick = 0) {
        shape = shap;
        solid = slid;
        deadly = dedly;
        propel = propell;
        stickyness = stick;
    }
    Platform() : solid(false), deadly(false) {}
};

struct Bridge {
    Platform button;
    Platform platform;
    bool inverted;
    Bridge(Platform platfom, Platform buttn, bool invert = false) {
        platform = platfom;
        button = buttn;
        inverted = invert;
    }
};

struct Portal {
    Platform platform;
    int destination;

    Portal(Platform platfom, int to) {
        platform = platfom;
        destination = to;
    }
};

struct Level {
    std::vector<Platform> platforms;
    std::vector<Bridge> bridges;
    std::vector<Portal> portals;
    std::string title;

    Level(std::string titl) {
        title = titl;
    }
};


extern sf::Texture stripes;
extern sf::Texture ice;
extern sf::Texture portal;
extern sf::Texture slime;
extern sf::Texture spike;
extern sf::Texture spring;
extern sf::Texture start;

void loadTextures();