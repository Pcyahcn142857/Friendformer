#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "levels.hpp"
#include "util.hpp"


// sf::Texture stripes("assets/pixil-frame-0-2.png");
// sf::Texture ice("assets/ice.png");

// void init(){
//     stripes.setRepeated(true);
//     ice.setRepeated(true);
// }


int level_count = 12;

void constructMini(std::string blueprint, Level& level, sf::Vector2f position, sf::Color color, bool solid){

    for (int x = 0; x < 5; x++){
        for (int y = 0; y < 5; y++){
            if (blueprint[x+5*y] == '1'){
                sf::RectangleShape shape({10.f, 10.f});
                shape.setFillColor(color);
                shape.setPosition(position);
                shape.move({(float) 10*x, (float) 10*y});

                Platform platform(shape, solid, false);

                level.platforms.push_back(platform);
            }
        }
    }
}

void constructWalls(Level &level){
    sf::RectangleShape wallShape1({1.f, 600.f});
    sf::RectangleShape wallShape2({800.f, 1.f});
    sf::RectangleShape wallShape3({1.f, 600.f});
    sf::RectangleShape wallShape4({800.f, 1.f});

    wallShape1.move({-1.f, 0.f});
    wallShape2.move({0.f, -1.f});
    wallShape3.move({800.f, 0.f});
    wallShape4.move({0.f, 600.f});

    Platform wall1(wallShape1, true, false);
    Platform wall2(wallShape2, true, false);
    Platform wall3(wallShape3, true, false);
    Platform wall4(wallShape4, true, false);

    level.platforms.push_back(wall1);
    // level.platforms.push_back(wall2);
    level.platforms.push_back(wall3);
    level.platforms.push_back(wall4);
}

void constructTestroom1(Level& level1){
    // Platforms
    sf::RectangleShape shape1({200.f, 50.f});
    shape1.setFillColor(sf::Color::Green);
    shape1.setPosition({0.f,300.f});

    Platform platform1(shape1, true, false);

    sf::RectangleShape shape2({300.f, 50.f});
    shape2.setFillColor(sf::Color::Green);
    shape2.setPosition({100.f,150.f});

    Platform platform2(shape2, true, false, {-0.05f, 0.f});

    sf::RectangleShape shape3({100.f, 50.f});
    shape3.setFillColor(sf::Color::Red);
    shape3.setPosition({50.f,250.f});

    Platform platform3(shape3, true, false);

    // sf::RectangleShape shape4({300.f, 50.f});
    // shape4.setFillColor(sf::Color::Green);
    // shape4.setPosition({100.f,50.f});

    sf::RectangleShape shape4({300.f, 50.f});
    shape4.setFillColor(sf::Color::Green);
    shape4.setPosition({500.f,300.f});

    Platform platform4(shape4, true, false);

    sf::RectangleShape shape5({100.f, 50.f});
    shape5.setFillColor(sf::Color::Red);
    shape5.setPosition({550.f,250.f});

    Platform platform5(shape5, true, false);

    level1.platforms.push_back(platform1);
    level1.platforms.push_back(platform2);
    level1.platforms.push_back(platform3);
    level1.platforms.push_back(platform4);
    level1.platforms.push_back(platform5);

    std::string heart = "0101011111111110111000100";
    constructMini(heart, level1, {350, 300}, sf::Color::White, true);

    // Portals

    sf::RectangleShape portalShape1({100.f, 150.f});
    portalShape1.setFillColor(sf::Color::Magenta);
    portalShape1.setPosition({700.f,200.f});

    Platform portalPlatform1(portalShape1, true, false);
    Portal portal1(portalPlatform1, level_count+3);

    

    level1.portals.push_back(portal1);



    // Water
    sf::RectangleShape waterShape({800.f, 200.f});
    waterShape.setFillColor(sf::Color::Blue);
    waterShape.setPosition({0.f,400.f});

    Platform water(waterShape, true, true);

    
    level1.platforms.push_back(water);

    // Bridges

    sf::RectangleShape bridgeShape1({350.f, 50.f});
    bridgeShape1.setFillColor(sf::Color::White);
    bridgeShape1.setPosition({150.f,300.f});

    Platform bridgePlatform1(bridgeShape1, true, false);

    Bridge bridge1(bridgePlatform1, platform3);

    Bridge bridge2(bridgePlatform1, platform5);

    level1.bridges.push_back(bridge1);
    level1.bridges.push_back(bridge2); 
}

void constructTestroom2(Level& level2){
    // Platforms

    sf::RectangleShape shape1({250.f, 50.f});
    shape1.setFillColor(sf::Color::Green);
    shape1.setPosition({0.f,100.f});

    Platform platform1(shape1, true, false);

    sf::RectangleShape shape2({50.f, 350.f});
    shape2.setFillColor(sf::Color::Green);
    shape2.setPosition({250.f, 100.f});

    Platform platform2(shape2, true, false);

    sf::RectangleShape shape3({250.f, 50.f});
    shape3.setFillColor(sf::Color::Green);
    shape3.setPosition({300.f, 400.f});

    Platform platform3(shape3, true, false);

    sf::RectangleShape shape4({50.f, 50.f});
    shape4.setFillColor(sf::Color::Green);
    shape4.setPosition({500.f, 100.f});

    Platform platform4(shape4, true, false);

    sf::RectangleShape shape5({300.f, 50.f});
    shape5.setFillColor(sf::Color::Green);
    shape5.setPosition({500.f, 150.f});

    Platform platform5(shape5, true, false);

    sf::RectangleShape shape6({300.f, 50.f});
    shape6.setFillColor(sf::Color::Green);
    shape6.setPosition({500.f, 350.f});

    Platform platform6(shape6, true, false);


    level2.platforms.push_back(platform1);
    level2.platforms.push_back(platform2);
    level2.platforms.push_back(platform3);
    level2.platforms.push_back(platform4);
    level2.platforms.push_back(platform5);
    level2.platforms.push_back(platform6);

    // Water

    sf::RectangleShape waterShape1({200.f, 300.f});
    waterShape1.setFillColor(sf::Color(0, 0, 255, 128));
    waterShape1.setPosition({300.f, 100.f});

    Platform water1(waterShape1, false, false, {0, 0.5f});

    

    sf::RectangleShape waterShape2({200.f, 150.f});
    waterShape2.setFillColor(sf::Color(0, 0, 255, 128));
    waterShape2.setPosition({500.f, 200.f});

    Platform water2(waterShape2, false, false, {0, 0.5f});

    level2.platforms.push_back(water1);
    level2.platforms.push_back(water2);

    // Portals

    sf::RectangleShape portalShape1({100.f, 150.f});
    portalShape1.setFillColor(sf::Color::Magenta);
    portalShape1.setPosition({700.f,200.f});

    Platform portalPlatform1(portalShape1, true, false);
    Portal portal1(portalPlatform1, level_count+3);

    level2.portals.push_back(portal1);



    // sf::RectangleShape portalShape1({350.f, 50.f});
    // portalShape1.setFillColor(sf::Color::Magenta);
    // portalShape1.setPosition({0.f,250.f});

    // Platform portalPlatform1(portalShape1, true, false);
    // Portal portal1(portalPlatform1, 0);

    // level2.portals.push_back(portal1);
}

void constructTestroom3(Level& level3) {

    sf::RectangleShape shape1({800.f, 50.f});
    shape1.setTexture(&ice);
    shape1.setPosition({0.f,300.f});
    shape1.setTextureRect({{0, 0}, {256, 16}});

    Platform platform1(shape1, true, false, {0, 0}, -1);

    sf::RectangleShape shape2({700.f, 50.f});
    shape2.setFillColor(sf::Color::Green);
    shape2.setPosition({100.f,200.f});

    Platform platform2(shape2, true, false, {0, 0}, 0.5);

    level3.platforms.push_back(platform1);
    level3.platforms.push_back(platform2);

    // Portals

    sf::RectangleShape portalShape1({100.f, 50.f});
    portalShape1.setFillColor(sf::Color::White);
    portalShape1.setTexture(&portal);
    portalShape1.setTextureRect({{0, 0}, {32, 16}});
    portalShape1.setPosition({700.f,250.f});

    Platform portalPlatform1(portalShape1, true, false);
    Portal portal1(portalPlatform1, level_count+3);

    level3.portals.push_back(portal1);
}

void constructTestroomMenu(Level& level) {
    // Platforms

    sf::RectangleShape shape1({800.f, 50.f});
    shape1.setTexture(&stripes);
    shape1.setPosition({0.f,300.f});
    shape1.setTextureRect({{0, 0}, {512, 32}});

    Platform platform1(shape1, true, false);

    level.platforms.push_back(platform1);

    // Water

    sf::RectangleShape waterShape1({800.f, 200.f});
    waterShape1.setFillColor(sf::Color(0, 0, 255, 128));
    waterShape1.setPosition({0.f, 100.f});

    Platform water1(waterShape1, false, false, {0, 0.5f});

    level.platforms.push_back(water1);

    // Portals

    sf::RectangleShape portalShape1({100.f, 50.f});
    portalShape1.setFillColor(sf::Color::Magenta);
    portalShape1.setPosition({100.f,250.f});

    Platform portalPlatform1(portalShape1, true, false);
    Portal portal1(portalPlatform1, level_count);

    sf::RectangleShape portalShape2({100.f, 50.f});
    portalShape2.setFillColor(sf::Color::Magenta);
    portalShape2.setPosition({400.f,250.f});

    Platform portalPlatform2(portalShape2, true, false);
    Portal portal2(portalPlatform2, level_count+1);

    sf::RectangleShape portalShape3({100.f, 50.f});
    portalShape3.setFillColor(sf::Color::Magenta);
    portalShape3.setPosition({700.f,250.f});

    Platform portalPlatform3(portalShape3, true, false);
    Portal portal3(portalPlatform3, level_count+2);

    level.portals.push_back(portal1);
    level.portals.push_back(portal2);
    level.portals.push_back(portal3);
}

void constructLevel1(Level& level){
    // Platforms
    sf::RectangleShape shape1({400.f, 200.f});
    shape1.setFillColor(sf::Color::Green);
    shape1.setPosition({0.f,400.f});

    Platform platform1(shape1, true, false);
    
    sf::RectangleShape shape2({400.f, 300.f});
    shape2.setFillColor(sf::Color::Green);
    shape2.setPosition({400.f,350.f});

    Platform platform2(shape2, true, false);

    level.platforms.push_back(platform1);
    level.platforms.push_back(platform2);

    // Mini icons

    std::string miniUp = "0000000100011100111000000";
    std::string miniDown = "0000001110011100010000000";
    std::string miniLeft = "0000000110011100011000000";
    std::string miniRight = "0000001100011100110000000";

    constructMini(miniUp, level, {100.f, 450.f}, sf::Color::White, false);
    constructMini(miniDown, level, {100.f, 500.f}, sf::Color::White, false);
    constructMini(miniLeft, level, {50.f, 500.f}, sf::Color::White, false);
    constructMini(miniRight, level, {150.f, 500.f}, sf::Color::White, false);

    // Portals

    sf::RectangleShape portalShape1({100.f, 150.f});
    portalShape1.setFillColor(sf::Color::Magenta);
    portalShape1.setPosition({700.f,200.f});

    Platform portalPlatform1(portalShape1, true, false);
    Portal portal1(portalPlatform1, 1);

    level.portals.push_back(portal1);
    
}

void constructLevel2(Level& level){
    // Platforms
    sf::RectangleShape shape1({400.f, 200.f});
    shape1.setFillColor(sf::Color::Green);
    shape1.setPosition({0.f,400.f});

    Platform platform1(shape1, true, false);
    
    sf::RectangleShape shape2({400.f, 300.f});
    shape2.setFillColor(sf::Color::Green);
    shape2.setPosition({400.f,350.f});

    Platform platform2(shape2, true, false);

    level.platforms.push_back(platform1);
    level.platforms.push_back(platform2);

    // Mini icons

    std::string miniM = "1000111011101011000100000";
    std::string miniR = "1110010010111001001000000";
    //std::string miniS = "1111011000001101111000000";

    constructMini(miniM, level, {100.f, 450.f}, sf::Color::White, false);
    constructMini(miniR, level, {100.f, 500.f}, sf::Color::White, false);
    //constructMini(miniS, level, {200.f, 450.f}, sf::Color::White, false);

    // Portals

    sf::RectangleShape portalShape1({100.f, 150.f});
    portalShape1.setFillColor(sf::Color::Magenta);
    portalShape1.setPosition({700.f,200.f});

    Platform portalPlatform1(portalShape1, true, false);
    Portal portal1(portalPlatform1, 2);

    level.portals.push_back(portal1);
}

void constructLevel3(Level& level){
    // Platforms

    sf::RectangleShape shape1({500, 50});
    shape1.setTexture(&ice);
    shape1.setTextureRect({{0, 0}, {160, 16}});
    shape1.setPosition({0.f,100.f});

    Platform platform1(shape1, true, false, {0, 0}, -1);

    sf::RectangleShape shape2({500, 50});
    shape2.setTexture(&slime);
    shape2.setTextureRect({{0, 0}, {160, 16}});
    shape2.setPosition({300.f,250.f});

    Platform platform2(shape2, true, false, {0, 0}, 0.5);

    sf::RectangleShape shape3({500, 50});
    shape3.setTexture(&ice);
    shape3.setTextureRect({{0, 0}, {160, 16}});
    shape3.setPosition({0.f,400.f});

    Platform platform3(shape3, true, false, {0, 0}, -1);

    sf::RectangleShape shape4({500, 50});
    shape4.setTexture(&slime);
    shape4.setTextureRect({{0, 0}, {160, 16}});
    shape4.setPosition({300.f,550.f});

    Platform platform4(shape4, true, false, {0, 0}, 0.5);

    level.platforms.push_back(platform1);
    level.platforms.push_back(platform2);
    level.platforms.push_back(platform3);
    level.platforms.push_back(platform4);

    // Portals

    sf::RectangleShape portalShape1({300.f, 50.f});
    portalShape1.setFillColor(sf::Color::Magenta);
    portalShape1.setPosition({0.f,550.f});

    Platform portalPlatform1(portalShape1, true, false);
    Portal portal1(portalPlatform1, 3);

    level.portals.push_back(portal1);
}

void constructLevel4(Level& level){
    // Platforms
    sf::RectangleShape shape1({800.f, 300.f});
    shape1.setFillColor(sf::Color::Green);
    shape1.setPosition({0.f,300.f});

    Platform platform1(shape1, true, false);

    sf::RectangleShape shape2({200.f, 50.f});
    shape2.setTexture(&spike);
    shape2.setTextureRect({{0,0}, {64, 16}});
    shape2.setPosition({300.f,250.f});

    Platform platform2(shape2, true, true);

    sf::RectangleShape shape3({50.f, 50.f});
    shape3.setTexture(&spring);
    shape3.setTextureRect({{0,0}, {16, 16}});
    shape3.setPosition({250.f,250.f});

    Platform platform3(shape3, true, false, {0.f, -1.f});

    sf::RectangleShape shape4({1.f, 50.f});
    shape4.setFillColor(sf::Color::Transparent);
    shape4.setPosition({249.f,250.f});

    Platform platform4(shape4, true, false);

    level.platforms.push_back(platform1);
    level.platforms.push_back(platform2);
    level.platforms.push_back(platform3);
    level.platforms.push_back(platform4);

    // Portals

    sf::RectangleShape portalShape1({100.f, 150.f});
    portalShape1.setFillColor(sf::Color::Magenta);
    portalShape1.setPosition({700.f,150.f});

    Platform portalPlatform1(portalShape1, true, false);
    Portal portal1(portalPlatform1, 4);

    level.portals.push_back(portal1);
}

void constructLevel5(Level& level1){

    // Platforms
    sf::RectangleShape shape1({200.f, 50.f});
    shape1.setFillColor(sf::Color::Green);
    shape1.setPosition({0.f,300.f});

    Platform platform1(shape1, true, false);

    sf::RectangleShape shape3({100.f, 50.f});
    shape3.setFillColor(sf::Color::Red);
    shape3.setPosition({50.f,250.f});

    Platform platform3(shape3, true, false);

    // sf::RectangleShape shape4({300.f, 50.f});
    // shape4.setFillColor(sf::Color::Green);
    // shape4.setPosition({100.f,50.f});

    sf::RectangleShape shape4({300.f, 50.f});
    shape4.setFillColor(sf::Color::Green);
    shape4.setPosition({500.f,300.f});

    Platform platform4(shape4, true, false);

    sf::RectangleShape shape5({100.f, 50.f});
    shape5.setFillColor(sf::Color::Red);
    shape5.setPosition({550.f,250.f});

    Platform platform5(shape5, true, false);

    level1.platforms.push_back(platform1);
    level1.platforms.push_back(platform3);
    level1.platforms.push_back(platform4);
    level1.platforms.push_back(platform5);

    // Portals

    sf::RectangleShape portalShape1({100.f, 150.f});
    portalShape1.setFillColor(sf::Color::Magenta);
    portalShape1.setPosition({700.f,200.f});

    Platform portalPlatform1(portalShape1, true, false);
    Portal portal1(portalPlatform1, 5);

    

    level1.portals.push_back(portal1);



    // Water
    sf::RectangleShape waterShape({800.f, 200.f});
    waterShape.setFillColor(sf::Color::Blue);
    waterShape.setPosition({0.f,400.f});

    Platform water(waterShape, true, true);

    
    level1.platforms.push_back(water);

    // Bridges

    sf::RectangleShape bridgeShape1({350.f, 50.f});
    bridgeShape1.setFillColor(sf::Color::White);
    bridgeShape1.setPosition({150.f,300.f});

    Platform bridgePlatform1(bridgeShape1, true, false);

    Bridge bridge1(bridgePlatform1, platform3);

    Bridge bridge2(bridgePlatform1, platform5);

    level1.bridges.push_back(bridge1);
    level1.bridges.push_back(bridge2); 
}

void constructLevel6(Level& level){
    sf::RectangleShape shape1({700, 50});
    shape1.setFillColor(sf::Color::Green);
    shape1.setPosition({50.f, 100.f});

    Platform platform1(shape1, true, false);

    sf::RectangleShape shape2({750, 50});
    shape2.setFillColor(sf::Color::Green);
    shape2.setPosition({50.f, 200.f});

    Platform platform2(shape2, true, false, {-0.2f, 0});
    
    sf::RectangleShape shape3({700, 50});
    shape3.setFillColor(sf::Color::Green);
    shape3.setPosition({50.f, 300.f});

    Platform platform3(shape3, true, false, {0.2f, 0});

    sf::RectangleShape shape4({750, 50});
    shape4.setFillColor(sf::Color::Green);
    shape4.setPosition({50.f, 400.f});

    Platform platform4(shape4, true, false, {-0.2f, 0});

    sf::RectangleShape shape5({750, 50});
    shape5.setFillColor(sf::Color::Green);
    shape5.setPosition({0.f, 500.f});

    Platform platform5(shape5, true, false, {0.2f, 0});

    level.platforms.push_back(platform1);
    level.platforms.push_back(platform2);
    level.platforms.push_back(platform3);
    level.platforms.push_back(platform4);
    level.platforms.push_back(platform5);

    // Buttons

    sf::RectangleShape buttonShape1({100, 50});
    buttonShape1.setFillColor(sf::Color::Red);
    buttonShape1.setPosition({100.f, 50.f});

    Platform button1(buttonShape1, true, false);

    sf::RectangleShape buttonShape2({100, 50});
    buttonShape2.setFillColor(sf::Color::Red);
    buttonShape2.setPosition({300.f, 50.f});

    Platform button2(buttonShape2, true, false);

    sf::RectangleShape buttonShape3({100, 50});
    buttonShape3.setFillColor(sf::Color::Red);
    buttonShape3.setPosition({500.f, 50.f});

    Platform button3(buttonShape3, true, false);

    sf::RectangleShape buttonShape4({100, 50});
    buttonShape4.setFillColor(sf::Color::Red);
    buttonShape4.setPosition({700.f, 50.f});

    Platform button4(buttonShape4, true, false);

    level.platforms.push_back(button1);
    level.platforms.push_back(button2);
    level.platforms.push_back(button3);
    // level.platforms.push_back(button4);

    // Doors

    sf::RectangleShape doorShape1({50, 50});
    doorShape1.setTexture(&spike);
    doorShape1.setPosition({400.f, 150.f});

    Platform doorPlatform1(doorShape1, true, true);

    Bridge door1(doorPlatform1, button1, true);

    sf::RectangleShape doorShape2({50, 50});
    doorShape2.setTexture(&spike);
    doorShape2.setPosition({400.f, 250.f});

    Platform doorPlatform2(doorShape2, true, true);

    Bridge door2(doorPlatform2, button2, true);

    sf::RectangleShape doorShape3({50, 50});
    doorShape3.setTexture(&spike);
    doorShape3.setPosition({400.f, 350.f});

    Platform doorPlatform3(doorShape3, true, true);

    Bridge door3(doorPlatform3, button3, true);

    sf::RectangleShape doorShape4({50, 50});
    doorShape4.setFillColor(sf::Color::Green);
    doorShape4.setPosition({0.f, 100.f});

    Platform doorPlatform4(doorShape4, true, false);

    Bridge door4(doorPlatform4, platform5, true); // TODO: change to true

    sf::RectangleShape doorShape5({50, 50});
    doorShape5.setFillColor(sf::Color::Green);
    doorShape5.setPosition({0.f, 300.f});

    Platform doorPlatform5(doorShape5, true, false, {0.2f, 0.f});

    Bridge door5(doorPlatform5, platform5, true); // TODO: change to true

    level.bridges.push_back(door1);
    level.bridges.push_back(door2);
    level.bridges.push_back(door3);
    level.bridges.push_back(door4);
    level.bridges.push_back(door5);

    // Portals

    sf::RectangleShape portalShape1({50, 50});
    portalShape1.setFillColor(sf::Color::Magenta);
    portalShape1.setPosition({750.f, 500.f});

    Platform portalPlatform1(portalShape1, true, false);
    
    Portal portal1(portalPlatform1, 6);

    level.portals.push_back(portal1);
}

void constructLevel7(Level& level){
    // Water

    sf::RectangleShape waterShape1({800.f, 550.f});
    waterShape1.setFillColor(sf::Color(0, 0, 255, 64));
    waterShape1.setPosition({0.f, 50.f});

    Platform water1(waterShape1, false, false, {0.f, 0.5f});

    level.platforms.push_back(water1);

    // Buttons

    sf::RectangleShape buttonShape1({600.f, 50.f});
    buttonShape1.setFillColor(sf::Color::Red);
    buttonShape1.setPosition({0.f, 550.f});

    Platform button1(buttonShape1, true, false);

    sf::RectangleShape buttonShape2({150.f, 50.f});
    buttonShape2.setFillColor(sf::Color::Red);
    buttonShape2.setPosition({250.f, 550.f});

    Platform button2(buttonShape2, true, false);

    sf::RectangleShape buttonShape3({800.f, 50.f});
    buttonShape3.setFillColor(sf::Color::Red);
    buttonShape3.setPosition({200.f, 550.f});

    Platform button3(buttonShape3, true, false);

    sf::RectangleShape buttonShape4({150.f, 50.f});
    buttonShape4.setFillColor(sf::Color::Red);
    buttonShape4.setPosition({650.f, 550.f});

    Platform button4(buttonShape4, true, false);

    level.platforms.push_back(button1);
    // level.platforms.push_back(button2);
    level.platforms.push_back(button3);
    // level.platforms.push_back(button4);

    // Platforms

    sf::RectangleShape platformShape1({50.f, 250.f});
    platformShape1.setFillColor(sf::Color::Green);
    platformShape1.setPosition({200.f, 0.f});

    Platform platform1(platformShape1, true, false);

    sf::RectangleShape platformShape2({50.f, 250.f});
    platformShape2.setFillColor(sf::Color::Green);
    platformShape2.setPosition({200.f, 350.f});

    Platform platform2(platformShape2, true, false);

    sf::RectangleShape platformShape3({50.f, 250.f});
    platformShape3.setFillColor(sf::Color::Green);
    platformShape3.setPosition({400.f, 0.f});

    Platform platform3(platformShape3, true, false);

    sf::RectangleShape platformShape4({50.f, 250.f});
    platformShape4.setFillColor(sf::Color::Green);
    platformShape4.setPosition({400.f, 350.f});

    Platform platform4(platformShape4, true, false);

    sf::RectangleShape platformShape5({50.f, 250.f});
    platformShape5.setFillColor(sf::Color::Green);
    platformShape5.setPosition({600.f, 0.f});

    Platform platform5(platformShape5, true, false);

    sf::RectangleShape platformShape6({50.f, 250.f});
    platformShape6.setFillColor(sf::Color::Green);
    platformShape6.setPosition({600.f, 350.f});

    Platform platform6(platformShape6, true, false);

    sf::RectangleShape platformShape7({800.f, 50.f});
    platformShape7.setFillColor(sf::Color::Green);
    platformShape7.setPosition({0.f, -50.f});

    Platform platform7(platformShape7, true, false);

    level.platforms.push_back(platform1);
    level.platforms.push_back(platform2);
    // level.platforms.push_back(platform3);
    // level.platforms.push_back(platform4);
    level.platforms.push_back(platform5);
    level.platforms.push_back(platform6);
    level.platforms.push_back(platform7);

    // Doors

    sf::RectangleShape doorShape1({50.f, 100.f});
    doorShape1.setFillColor(sf::Color::Green);
    doorShape1.setPosition({200.f, 250.f});

    Platform doorPlatform1(doorShape1, true, false);

    Bridge door1(doorPlatform1, button1, true);
    Bridge door2(doorPlatform1, button2, true);

    sf::RectangleShape doorShape2({50.f, 100.f});
    doorShape2.setFillColor(sf::Color::Green);
    doorShape2.setPosition({400.f, 250.f});

    Platform doorPlatform2(doorShape2, true, false);

    Bridge door3(doorPlatform2, button2, true);
    Bridge door4(doorPlatform2, button3, true);

    sf::RectangleShape doorShape3({50.f, 100.f});
    doorShape3.setFillColor(sf::Color::Green);
    doorShape3.setPosition({600.f, 250.f});

    Platform doorPlatform3(doorShape3, true, false);

    Bridge door5(doorPlatform3, button3, true);
    Bridge door6(doorPlatform3, button4, true);

    level.bridges.push_back(door1);
    // level.bridges.push_back(door2);
    // level.bridges.push_back(door3);
    // level.bridges.push_back(door4);
    level.bridges.push_back(door5);
    // level.bridges.push_back(door6);

    // Portals

    sf::RectangleShape portalShape1({50.f, 150.f});
    portalShape1.setFillColor(sf::Color::Magenta);
    portalShape1.setPosition({750.f, 250.f});

    Platform portalPlatform1(portalShape1, true, false);

    Portal portal1(portalPlatform1, 7);

    level.portals.push_back(portal1);

}

void constructLevel8(Level& level){
    // Platforms

    sf::RectangleShape platformShape1({800.f, 200.f});
    platformShape1.setFillColor(sf::Color::Green);
    platformShape1.setPosition({0.f, 400.f});

    Platform platform1(platformShape1, true, false);

    sf::RectangleShape platformShape2({400.f, 100.f});
    platformShape2.setFillColor(sf::Color(128, 128, 128));
    platformShape2.setPosition({400.f, 100.f});

    Platform platform2(platformShape2, true, false);

    level.platforms.push_back(platform1);
    level.platforms.push_back(platform2);

    // Buttons

    sf::RectangleShape buttonShape1({100.f, 50.f});
    buttonShape1.setFillColor(sf::Color::Red);
    buttonShape1.setPosition({150.f, 350.f});

    Platform button1(buttonShape1, true, false);

    sf::RectangleShape buttonShape2({100.f, 50.f});
    buttonShape2.setFillColor(sf::Color::Red);
    buttonShape2.setPosition({450.f, 350.f});

    Platform button2(buttonShape2, true, false);

    level.platforms.push_back(button1);
    level.platforms.push_back(button2);

    // Doors and Bridges

    sf::RectangleShape doorShape1({100.f, 300.f});
    doorShape1.setFillColor(sf::Color(128, 128, 128));
    doorShape1.setPosition({300.f, 100.f});

    Platform doorPlatform1(doorShape1, true, false);

    Bridge door1(doorPlatform1, button1, true);

    sf::RectangleShape bridgeShape1({100.f, 300.f});
    bridgeShape1.setFillColor(sf::Color(128, 128, 128));
    bridgeShape1.setPosition({300.f, 0.f});

    Platform bridgePlatform1(bridgeShape1, true, false);

    Bridge bridge1(bridgePlatform1, button1);

    sf::RectangleShape bridgeShape2({50.f, 50.f});
    bridgeShape2.setTexture(&spring);
    bridgeShape2.setPosition({250.f, 350.f});

    Platform bridgePlatform2(bridgeShape2, true, false, {0.f, -0.5f});

    Bridge bridge2(bridgePlatform2, button2);

    level.bridges.push_back(door1);
    level.bridges.push_back(bridge1);
    level.bridges.push_back(bridge2);

    // Portals

    sf::RectangleShape portalShape1({100.f, 400.f});
    portalShape1.setFillColor(sf::Color::Magenta);
    portalShape1.setPosition({700.f,0.f});

    Platform portalPlatform1(portalShape1, true, false);
    Portal portal1(portalPlatform1, 8);

    // sf::RectangleShape portalShape2({100.f, 100.f});
    // portalShape2.setFillColor(sf::Color::Magenta);
    // portalShape2.setPosition({700.f,250.f});

    // Platform portalPlatform2(portalShape2, true, false);
    // Portal portal2(portalPlatform2, 8);

    level.portals.push_back(portal1);
    // level.portals.push_back(portal2);
}

void constructLevel9(Level& level){
    // Platforms

    sf::RectangleShape platformShape1({800.f, 200.f});
    platformShape1.setFillColor(sf::Color::Green);
    platformShape1.setPosition({0.f, 400.f});

    Platform platform1(platformShape1, true, false);

    level.platforms.push_back(platform1);

    // Buttons

    sf::RectangleShape buttonShape1({100.f, 50.f});
    buttonShape1.setFillColor(sf::Color::Red);
    buttonShape1.setPosition({100.f, 350.f});

    Platform button1(buttonShape1, true, false, {0.125f, 0.f});

    sf::RectangleShape buttonShape2({100.f, 50.f});
    buttonShape2.setFillColor(sf::Color::Red);
    buttonShape2.setPosition({500.f, 350.f});

    Platform button2(buttonShape2, true, false, {0.15f, 0.f});

    level.platforms.push_back(button1);
    level.platforms.push_back(button2);

    // Doors


    sf::RectangleShape doorShape1({200.f, 50.f});
    doorShape1.setTexture(&spike);
    doorShape1.setTextureRect({{0,0}, {64, 16}});
    doorShape1.setPosition({250.f,350.f});

    Platform doorPlatform1(doorShape1, true, true);

    Bridge door1(doorPlatform1, button1, true);

    sf::RectangleShape bridgeShape1({50.f, 50.f});
    bridgeShape1.setTexture(&spring);
    bridgeShape1.setPosition({200.f,350.f});

    Platform bridgePlatform1(bridgeShape1, true, false, {0, -0.75f});

    Bridge bridge1(bridgePlatform1, button2); // TODO: remove true

    level.bridges.push_back(door1);
    level.bridges.push_back(bridge1);
    
    // Portals

    sf::RectangleShape portalShape1({100.f, 150.f});
    portalShape1.setFillColor(sf::Color::Magenta);
    portalShape1.setPosition({700.f,250.f});

    Platform portalPlatform1(portalShape1, true, false);
    Portal portal1(portalPlatform1, 9);

    level.portals.push_back(portal1);
}

void constructLevel10(Level& level){

    // Platforms

    sf::RectangleShape platformShape1({800.f, 200.f});
    platformShape1.setFillColor(sf::Color::Green);
    platformShape1.setPosition({0.f, 400.f});

    Platform platform1(platformShape1, true, false);

    sf::RectangleShape platformShape2({200.f, 50.f});
    platformShape2.setFillColor(sf::Color::Green);
    platformShape2.setPosition({100.f, 200.f});

    Platform platform2(platformShape2, true, false);

    sf::RectangleShape platformShape3({100.f, 50.f});
    platformShape3.setFillColor(sf::Color::Green);
    platformShape3.setPosition({600.f, 200.f});

    Platform platform3(platformShape3, true, false);

    level.platforms.push_back(platform1);
    // level.platforms.push_back(platform2);
    level.platforms.push_back(platform3);

    // Buttons

    sf::RectangleShape buttonShape1({100.f, 50.f});
    buttonShape1.setFillColor(sf::Color::Red);
    buttonShape1.setPosition({100.f, 200.f});

    Platform button1(buttonShape1, true, false, {0, 0}, -49);

    sf::RectangleShape buttonShape2({100.f, 50.f});
    buttonShape2.setFillColor(sf::Color::Red);
    buttonShape2.setPosition({650.f, 350.f});

    Platform button2(buttonShape2, true, false);

    level.platforms.push_back(button1);
    level.platforms.push_back(button2);

    // Bridges and Doors

    sf::RectangleShape doorShape1({400.f, 50.f});
    doorShape1.setTexture(&spike);
    doorShape1.setTextureRect({{0, 0}, {128, 16}});
    doorShape1.setPosition({200.f, 350.f});

    Platform doorPlatform1(doorShape1, true, true);

    Bridge door1(doorPlatform1, button1, true); // todo: change to true

    sf::RectangleShape bridgeShape1({400.f, 50.f});
    bridgeShape1.setFillColor(sf::Color::White);
    bridgeShape1.setPosition({200.f, 200.f});

    Platform bridgePlatform1(bridgeShape1, true, false);

    Bridge bridge1(bridgePlatform1, button2);

    level.bridges.push_back(door1);
    level.bridges.push_back(bridge1);

    // Portals

    sf::RectangleShape portalShape1({100.f, 150.f});
    portalShape1.setFillColor(sf::Color::Magenta);
    portalShape1.setPosition({600.f, 50.f});

    Platform portalPlatform1(portalShape1, true, false);

    Portal portal1(portalPlatform1, 10);

    level.portals.push_back(portal1);
}

void constructWinScreen(Level& level){
    sf::RectangleShape platformShape1({800.f, 200.f});
    platformShape1.setFillColor(sf::Color::Green);
    platformShape1.setPosition({0.f, 400.f});

    Platform platform1(platformShape1, true, false);

    level.platforms.push_back(platform1);

    // Portals

    sf::RectangleShape portalShape1({100.f, 150.f});
    portalShape1.setFillColor(sf::Color::Magenta);
    portalShape1.setPosition({300.f, 250.f});

    Platform portalPlatform1(portalShape1, true, false);

    Portal portal1(portalPlatform1, level_count - 1);

    sf::RectangleShape portalShape2({100.f, 150.f});
    portalShape2.setFillColor(sf::Color(255, 255, 255, 0));
    portalShape2.setPosition({200.f, 50.f});

    Platform portalPlatform2(portalShape2, true, false);

    Portal portal2(portalPlatform2, level_count + 3);

    level.portals.push_back(portal1);
    level.portals.push_back(portal2);
}

void constructMenu(Level& level){
    // Platforms
    sf::RectangleShape platformShape1({800.f, 100.f});
    platformShape1.setFillColor(sf::Color::Green);
    platformShape1.setPosition({0.f, 500.f});

    Platform platform1(platformShape1, true, false);

    level.platforms.push_back(platform1);
    // Portals
    sf::RectangleShape portalShape1({200.f, 200.f});
    portalShape1.setTexture(&start);
    portalShape1.setPosition({300.f, 300.f});

    Platform portalPlatform1(portalShape1, true, false);

    Portal portal1(portalPlatform1, 0);

    level.portals.push_back(portal1);
}

