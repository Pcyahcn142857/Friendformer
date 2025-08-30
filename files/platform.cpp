#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <optional>
#include <vector>
#include <iostream>
#include <string>
#include "levels.hpp"
#include "util.hpp"
#include <enet/enet.h>
#include <unordered_map>


// Player
sf::RectangleShape player({50.f, 50.f});
sf::RectangleShape player2({50.f, 50.f});
sf::Color playerColor(sf::Color::Magenta);
sf::Color playerColor2(sf::Color::Magenta);
sf::Vector2f vel = {0.f, 0.f};
sf::Vector2f vel2 = {0.f, 0.f};
sf::FloatRect playerBB = player.getGlobalBounds();
sf::FloatRect playerBB2 = player2.getGlobalBounds();
sf::RenderWindow window(sf::VideoMode({800, 600}), "Friendformer");
sf::Music bgm("assets/Cipher - Electronic Light.mp3");


// sf::Texture backgroundTexture("assets/unnamed.png");
// sf::Sprite background(backgroundTexture);



// textures

sf::Texture chickRight("assets/chickity-chick-pixilart copy.png");
sf::Texture chickLeft("assets/image-2 copy.png");
sf::Texture sphere("assets/pixilart-drawing-2.png");
sf::Texture cube("assets/pixilart-drawing-3 copy 3.png");

sf::Texture playerRight(chickRight);
sf::Texture playerLeft(chickLeft);

sf::Texture playerRight2(chickRight);
sf::Texture playerLeft2(chickLeft);

uint8_t playerTextureID = 2;



float speed;
bool onGround = false;
bool onGround2 = false;
bool inWater = false;
float grav = 0.0005f;
bool nothing;





// Lists
std::vector<Level> levels;
int levelNumber = 11;


// Functions
// Util
void reset() {
    speed = 0.1f;
    onGround = false;
    player.setPosition({0, 0});
    vel = {0, 0};
    player.setTexture(&playerRight);

    onGround2 = false;
    player2.setPosition({0, 0});
    vel2 = {0, 0};
    player2.setTexture(&playerRight2);
}

bool collide(Platform platform, sf::RectangleShape& player1, bool& onGround1, sf::Vector2f& vel1){
    sf::FloatRect playerBB1 = player1.getGlobalBounds();
    sf::RectangleShape shape = platform.shape;
            
    sf::FloatRect platformBB = shape.getGlobalBounds();
    window.draw(shape);

    if (const auto intersection = playerBB1.findIntersection(platformBB))
    {
        if (platform.solid == true){
            // if (intersection->size.y <= intersection->size.x){
            //     if (intersection->position.y <= platformBB.getCenter().y){
            //         // Snap player to top of platform
            //         player.setPosition({player.getPosition().x, shape.getPosition().y - playerBB.size.y});
            //         vel.y = 0.f; // stop falling
            //         onGround = true; // on ground
            //     } else {
            //         // Snap player to bottom of platform
            //         player.setPosition({player.getPosition().x, shape.getPosition().y + playerBB.size.y});
            //         vel.y = 0.f; // stop rising
            //     }
            // }
            // if (intersection->size.x < intersection->size.y){
            //     if (intersection->position.x <= platformBB.getCenter().x){
            //         // Snap player to right of platform
            //         player.setPosition({shape.getPosition().x - playerBB.size.x, player.getPosition().y});
            //         vel.y = 0.f; // this is for wall slide
                    
            //     } else {
            //         // Snap player to left of platform
            //         player.setPosition({shape.getPosition().x + playerBB.size.x, player.getPosition().y});
            //         vel.y = 0.f; // this is for wall slide
            //     }
            //     onGround = true; // this is for wall jumps
            // }
            
            if (intersection->size.x < intersection->size.y) {
                onGround1 = true; // wall jump
                if (player1.getPosition().x < platformBB.getCenter().x)
                    player1.move({-intersection->size.x, 0}); // move left
                else
                    player1.move({intersection->size.x, 0});  // move right
               
            } else {
                if (player1.getPosition().y < platformBB.getCenter().y){
                    onGround1 = true;
                    player1.move({0, -intersection->size.y}); // move up
                }
                else{
                    player1.move({0, intersection->size.y});  // move down
                }
                vel1.y = 0;
            }
            inWater = false; // touched ground
            

            vel1 += platform.propel; // this handles vertical
            player1.move(platform.propel); // this handles horizontal
            player1.move(vel1 * -platform.stickyness); // handle stickyness
            
            if (platform.deadly == true){
                reset(); // die
            }
            return true;
        } else {
            vel1 += -intersection->size.x * intersection->size.y * grav / 1000 * platform.propel; // buoyancy
            vel1 *= 0.999f;
            inWater = true;
        }
    }
    return false;
}


// Level construction

Level test1("1. Beta Testing Room - Bridges and Conveyor Belts");
Level test2("2. Beta Testing Room - Water and Ducking");
Level test3("3. Beta Testing Room - Stickyness and Textures");
Level tests("11. How did you get here? - Welcome to the Secret Room");
Level level1("1. The Basics");
Level level2("2. Hotkeys you should know");
Level level3("3. Stick 'N' Slide - Welcome to the Friction Room");
Level level4("4. First sign of danger");
Level level5("5. Bridges and Buttons");
Level level6("6. Pipes and blockages");
Level level7("7. Underwater TM - Welcome to the Bouyancy Room");
Level level8("8. Cave Explorers");
Level level9("9. Timed Buttom");
Level level10("10. Precise Manuver");
Level winScreen("You won! Go through the portal to restart.");
Level menuScreen("Press the button to start");

int main()
{
    sf::Font font("assets/Ubuntu-Regular copy 2.ttf"); // Throws sf::Exception if an error occurs
    loadTextures();
    
    constructTestroom1(test1);
    constructTestroom2(test2);
    constructTestroom3(test3); 
    constructTestroomMenu(tests); 
    constructLevel1(level1);
    constructLevel2(level2);
    constructLevel3(level3);
    constructLevel4(level4);
    constructLevel5(level5);
    constructLevel6(level6);
    constructLevel7(level7);
    constructLevel8(level8);
    constructLevel9(level9);
    constructLevel10(level10);
    constructWinScreen(winScreen);
    constructMenu(menuScreen);

    constructWalls(test1);
    constructWalls(test2);
    constructWalls(test3);
    constructWalls(tests);
    constructWalls(level1);
    constructWalls(level2);
    constructWalls(level3);
    constructWalls(level4);
    constructWalls(level5);
    constructWalls(level6);
    constructWalls(level7);
    constructWalls(level8);
    constructWalls(level9);
    constructWalls(level10);
    constructWalls(winScreen);
    constructWalls(menuScreen);

    levels.push_back(level1);
    levels.push_back(level2);
    levels.push_back(level3);
    levels.push_back(level4);
    levels.push_back(level5);
    levels.push_back(level6);
    levels.push_back(level7);
    levels.push_back(level8);
    levels.push_back(level9);
    levels.push_back(level10);
    levels.push_back(winScreen);
    levels.push_back(menuScreen);
    levels.push_back(test1);
    levels.push_back(test2);
    levels.push_back(test3);
    levels.push_back(tests);
    

    // std::cout << "Enter password: " << std::endl;

    // std::string password;

    // std::cin >> password;

    // if (password != "again"){
    //     std::cout << "wrong password. access denied." << std::endl;
    //     return 1;
    // }


    reset();

    bgm.setLooping(true);
    

    // if (enet_initialize() != 0) {
    //     std::cerr << "ENet initialization failed\n";
    //     return 1;
    // }
    // atexit(enet_deinitialize);

    // ENetHost* client = enet_host_create(NULL, 1, 2, 0, 0);
    // ENetAddress address;
    // enet_address_set_host(&address, "127.0.0.1");
    // address.port = 1234;
    // ENetPeer* peer = enet_host_connect(client, &address, 2, 0);

    // ENetEvent event;

    std::cout << "Enter Player one color and character. Options:" << std::endl;

    std::cout << "0: White, 1: Red, 2: Orange, 3: Yellow, 4: Green" << 
    ", 5: Blue, 6: Purple, 7: Pink, 8: Magenta, 9: Grey" << std::endl;

    std::cout << "b: bird, s: sphere, c: cube" << std::endl;

    std::cout << "Now choose: " << std::endl;

    int n;
    char character;
    std::cin >> n >> character;
    {
        if (n == 0){
            playerColor = sf::Color::White;
        }
        if (n == 1){
            playerColor = sf::Color::Red;
        }
        if (n == 2){
            playerColor = sf::Color(255, 128, 0);
        }
        if (n == 3){
            playerColor = sf::Color::Yellow;
        }
        if (n == 4){
            playerColor = sf::Color::Green;
        }
        if (n == 5){
            playerColor = sf::Color::Cyan;
        }
        if (n == 6){
            playerColor = sf::Color(128, 0, 255);
        }
        if (n == 7){
            playerColor = sf::Color(255, 128, 255);
        }
        if (n == 8){
            playerColor = sf::Color::Magenta;
        }
        if (n == 9){
            playerColor = sf::Color(128, 128, 128);
        }
        if (character == 'b'){
            playerRight = chickRight;
            playerLeft = chickLeft;
            player.setTexture(&playerRight);
            playerTextureID = 2;
        }
        if (character == 'c'){
            playerRight = cube;
            playerLeft = cube;
            player.setTexture(&playerRight);
            playerTextureID = 1;
        }
        if (character == 's'){
            playerRight = sphere;
            playerLeft = sphere;
            player.setTexture(&playerRight);
            playerTextureID = 0;
        }
    }

    std::cout << "Now choose for player 2: " << std::endl;

    std::cin >> n >> character;
    {
        if (n == 0){
            playerColor2 = sf::Color::White;
        }
        if (n == 1){
            playerColor2 = sf::Color::Red;
        }
        if (n == 2){
            playerColor2 = sf::Color(255, 128, 0);
        }
        if (n == 3){
            playerColor2 = sf::Color::Yellow;
        }
        if (n == 4){
            playerColor2 = sf::Color::Green;
        }
        if (n == 5){
            playerColor2 = sf::Color::Cyan;
        }
        if (n == 6){
            playerColor2 = sf::Color(128, 0, 255);
        }
        if (n == 7){
            playerColor2 = sf::Color(255, 128, 255);
        }
        if (n == 8){
            playerColor2 = sf::Color::Magenta;
        }
        if (n == 9){
            playerColor2 = sf::Color(128, 128, 128);
        }
        if (character == 'b'){
            playerRight2 = chickRight;
            playerLeft2 = chickLeft;
            player2.setTexture(&playerRight2);
            playerTextureID = 2;
        }
        if (character == 'c'){
            playerRight2 = cube;
            playerLeft2 = cube;
            player2.setTexture(&playerRight2);
            playerTextureID = 1;
        }
        if (character == 's'){
            playerRight2 = sphere;
            playerLeft2 = sphere;
            player2.setTexture(&playerRight2);
            playerTextureID = 0;
        }
    }

    player.setFillColor(playerColor);
    player2.setFillColor(playerColor2);

    bgm.play();

    while (window.isOpen())
    {
        // // Handle ENet events
        // while (enet_host_service(client, &event, 0) > 0) {
        //     switch (event.type) {
        //         case ENET_EVENT_TYPE_CONNECT:
        //             std::cout << "Connected to server!\n";
        //             break;

        //         case ENET_EVENT_TYPE_RECEIVE: {
        //             // On RECEIVE event:
        //             if (event.packet->dataLength == sizeof(PlayerState)) {
        //                 PlayerState* state = (PlayerState*) event.packet->data;
        //                 // store in a map
        //                 players[event.peer] = *state;
        //             }
        //             enet_packet_destroy(event.packet);

        //         }

        //         case ENET_EVENT_TYPE_DISCONNECT:
        //             std::cout << "Disconnected from server.\n";
        //             break;

        //         default:
        //             break;
        //     }
        // }
        while (const std::optional event1 = window.pollEvent())
        {
            if (event1->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event1->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Up){
                    if (onGround){
                        vel.y = -0.3f; // jump upwards
                        onGround = false; // not on ground anymore
                    }
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::W){
                    if (onGround2){
                        vel2.y = -0.3f; // jump upwards
                        onGround2 = false; // not on ground anymore
                    }
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::R){
                    reset();
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::M){
                    bgm.setVolume(100 - bgm.getVolume());
                }
            }
        }

        // Handle Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) {
            vel.x = speed; // move right
            player.setTexture(&playerRight);
            if(playerTextureID >= 2){
                playerTextureID = 3;
            }
        } else{
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) {
                vel.x = -speed; // move left
                player.setTexture(&playerLeft);
                if(playerTextureID >= 2){
                    playerTextureID = 2;
                }
            } else{
                vel.x = 0.f; // stop
            }
        }
        // Handle Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
            vel2.x = speed; // move right
            player2.setTexture(&playerRight2);
        } else{
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
                vel2.x = -speed; // move left
                player2.setTexture(&playerLeft2);
            } else{
                vel2.x = 0.f; // stop
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down)) {
            player.setScale({1, 0.5});
        } else {
            player.setScale({1, 1});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) {
            player2.setScale({1, 0.5});
        } else {
            player2.setScale({1, 1});
        }
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down) && inWater) {
        //     vel.y = 0.1f; // move down
        // }

        // Update Players
        vel.y += grav;
        vel2.y += grav;

        player.move(vel);
        player2.move(vel2);

        

        // Draw
        window.clear(sf::Color(115, 171, 235));
        // window.draw(background);
        window.draw(player);
        window.draw(player2);

        // Game logic

        Level level = levels[levelNumber];

        // Collision checks
        
        playerBB = player.getGlobalBounds();
        playerBB2 = player2.getGlobalBounds();
        for (const auto bridge : level.bridges){
            
            sf::FloatRect buttonBB = bridge.button.shape.getGlobalBounds();
            
            bool coll;
            if (!bridge.inverted){
                coll = false;
                if (const auto intersection = playerBB.findIntersection(buttonBB)){
                    coll = true;
                } else {
                    if (const auto intersection = playerBB2.findIntersection(buttonBB))
                    {
                        coll = true;
                    }
                }
            }
            if (bridge.inverted){
                coll = true;
                if (const auto intersection = playerBB.findIntersection(buttonBB)){
                    coll = false;
                }
                if (const auto intersection = playerBB2.findIntersection(buttonBB)){
                    coll = false;
                }
            }
            if (coll){
                collide(bridge.platform, player, onGround, vel);
                collide(bridge.platform, player2, onGround2, vel2);
                window.draw(bridge.platform.shape);
            }
        }

        for (const auto platform : level.platforms){
            collide(platform, player, onGround, vel);
            collide(platform, player2, onGround2, vel2);
        }

        for (const auto portal : level.portals){
            bool player1collide = collide(portal.platform, player, onGround, vel);
            bool player2collide = collide(portal.platform, player2, onGround2, vel2);
            if (player1collide && player2collide){
                levelNumber = portal.destination;
                reset();
            }
        }

        

        sf::Text text(font);

        text.setString(level.title);

        window.draw(text);

        
        
        window.display();
    }
    

return 0;
}



/*
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
    level.platforms.push_back(wall2);
    level.platforms.push_back(wall3);
    level.platforms.push_back(wall4);
}

void constructLevel1(){
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
    Portal portal1(portalPlatform1, 1);

    

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

void constructLevel2(){
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
    Portal portal1(portalPlatform1, 2);

    level2.portals.push_back(portal1);



    // sf::RectangleShape portalShape1({350.f, 50.f});
    // portalShape1.setFillColor(sf::Color::Magenta);
    // portalShape1.setPosition({0.f,250.f});

    // Platform portalPlatform1(portalShape1, true, false);
    // Portal portal1(portalPlatform1, 0);

    // level2.portals.push_back(portal1);
}

void constructLevel3() {

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
    portalShape1.setFillColor(sf::Color::Magenta);
    portalShape1.setPosition({700.f,250.f});

    Platform portalPlatform1(portalShape1, true, false);
    Portal portal1(portalPlatform1, 0);

    level3.portals.push_back(portal1);
}
*/