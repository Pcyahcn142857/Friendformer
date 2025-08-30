#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "util.hpp"


sf::Texture stripes("assets/pixil-frame-0-2.png");
sf::Texture ice("assets/ice.png");
sf::Texture portal("assets/portal-pixilart.png");
sf::Texture slime("assets/slime.png");
sf::Texture spike("assets/spike.png");
sf::Texture spring("assets/spring.png");
sf::Texture start("assets/start.png");

// stripes.setRepeated(true);
// ice.setRepeated(true);

void loadTextures() {
    stripes.setRepeated(true);
    ice.setRepeated(true);
    portal.setRepeated(true);
    slime.setRepeated(true);
    spike.setRepeated(true);
    spring.setRepeated(true);
    start.setRepeated(true);
    // if (!stripes.loadFromFile("assets/pixil-frame-0-2.png")) {
    //     // Handle loading error (e.g., print error message)
    //     std::cerr << "Failed to load stripes texture!" << std::endl;
    // }
    // if (!ice.loadFromFile("assets/ice.png")) {
    //     // Handle loading error
    //     std::cerr << "Failed to load ice texture!" << std::endl;
    // }

    // stripes.setRepeated(true);
    // ice.setRepeated(true);
}