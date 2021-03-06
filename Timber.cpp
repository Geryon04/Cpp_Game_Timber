#include <sstream>
#include <SFML/Graphics.hpp>


// Make code easier to type with "using namespace"
using namespace sf;

//Function declaration
void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

//Where is the player/branch?
//Left or Right
enum class side{ LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

// This is where our game starts from
int main()
{
    // Create a video mode object
    VideoMode vm(960, 540);

    // Create and open a window for the game
    //RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

    //low res code
    RenderWindow window(vm, "Timber!!!");
    View view(sf::FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    //Create a texture to hold a graphic on the GPU
    Texture textureBackground;

    //Load a graphic into the texture
    textureBackground.loadFromFile("graphics/background.png");

    //Create a sprite
    Sprite spriteBackground;

    //Attack the texture to the sprite
    spriteBackground.setTexture(textureBackground);

    //Set the spriteBackground to cover the screen
    spriteBackground.setPosition(0 , 0);

    //Make a tree sprite
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(683, 0);

    //Prepare the bee
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0 , 350);

    //Is the bee currently moving?
    bool beeActive = false;

    //How fast can the bee fly
    float beeSpeed = 0.0f;

    //Make 3 cloud sprites from 1 texture
    Texture textureCloud;

    //Load 1 new texture
    textureCloud.loadFromFile("graphics/cloud.png");

    //3 new sprites with the same texture
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);

    //Position the clouds on the left of the screen at different heights
    spriteCloud1.setPosition(0,0);
    spriteCloud2.setPosition(0, 250);
    spriteCloud3.setPosition(0, 150);

    //Are the clouds currently on screen?
    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;

    //How fast is each cloud?
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

    //Variables to control time itself
    Clock clock;

    //Time bar
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((960 / 2) - timeBarStartWidth / 2, 540);

    Time gameTimeTotal;
    float timeRemaing = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaing;

    //Track whether the game is running
    bool paused = true;

    //Draw some text
    int score = 0;

    Text messageText;
    Text scoreText;

    //We need to choose a font
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    //Set the font to our message
    messageText.setFont(font);
    scoreText.setFont(font);
    
    //Assing the actual message
    messageText.setString("Press Enter to start");
    scoreText.setString("Score = 0");

    //Make it really big
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);

    //Choose a color
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    //Position the text
    FloatRect textRect = messageText.getLocalBounds();

    messageText.setOrigin(textRect.left +
        textRect.width / 2.0f,
        textRect.top +
        textRect.height / 2.0f);

    messageText.setPosition(960 / 2.0f, 540 / 2.0f);

    scoreText.setPosition(20, 20);
    //Game loop
    while (window.isOpen()){
        /*
        *********************************
        Handle the players input
        *********************************
        */
       if(Keyboard::isKeyPressed(Keyboard::Escape)){
           window.close();
       }

       //Start the game
       if(Keyboard::isKeyPressed(Keyboard::Enter)){
           paused = false;

           //Reset the time and the score
           score = 0;
           timeRemaing = 6;
       }

       /*
       **********************************
       Update the scene
       **********************************
       */
      if(!paused){
        // Measure time
        Time dt = clock.restart();

        //Subtract from the amount of time remaining
        timeRemaing -= dt.asSeconds();
        //Resize up the time bar
        timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaing, timeBarHeight));

        if(timeRemaing <= 0.0f){

            //Pause the game
            paused = true;

            //Change the message show to the player
            messageText.setString("Out of time!!");

            //Reposition the text basedon its size
            FloatRect textRect = messageText.getLocalBounds();
            messageText.setOrigin(textRect.left +
                textRect.width / 2.0f,
                textRect.top +
                textRect.height / 2.0f);

            messageText.setPosition(960 / 2.0f, 540 / 2.0f);
        }

        // Setup the bee
        if (!beeActive)
        {
            // How fast is the bee
            srand((int)time(0));
            beeSpeed = (rand() % 200) + 200;

            // How high is the bee
            srand((int)time(0) * 10);
            float height = (rand() % 500) + 500;
            spriteBee.setPosition(2000, height);
            beeActive = true;
        }
        else
        //Move the bee
        {
            spriteBee.setPosition(
                spriteBee.getPosition().x -(beeSpeed * dt.asSeconds()),
                spriteBee.getPosition().y);
            
            //Has the bee reached the left-hand edge of the screen?
            if(spriteBee.getPosition().x < -100){
                //Set it up ready to be a whole new bee next frame
                beeActive = false;
            }

        }

        //Manage the clouds
        //Cloud 1
        if(!cloud1Active){
            //How fast is the cloud
            srand((int)time(0) * 10);
            cloud1Speed = (rand() % 200);

            //How high is the cloud
            srand((int)time(0) * 10);
            float height = (rand() % 150);
            spriteCloud1.setPosition(-200, height);
            cloud1Active = true;
        }
        else{
            spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), 
            spriteCloud1.getPosition().y);

            //Has the cloud reached the right hand edge ot the screen?
            if(spriteCloud1.getPosition().x > 1920){
                //Set it up ready to be a whole new cloud next frame
                cloud1Active = false;
            }
        }

        //Cloud 2
        if(!cloud2Active){
            //How to fast is the cloud
            srand((int)time(0) * 20);
            cloud2Speed = (rand() % 200);

            //How high is the cloud
            srand((int)time(0) * 20);
            float height = (rand() % 300) - 150;
            spriteCloud2.setPosition(-200, height);
            cloud2Active = true;
        }
        else{
            spriteCloud2.setPosition(spriteCloud2.getPosition().x +
             (cloud2Speed * dt.asSeconds()),
            spriteCloud2.getPosition().y);

            //Has the cloud reached the right hand edge of the screen?
            if(spriteCloud2.getPosition().x > 1920){
                //Set it up ready to be a whole new cloud next frame
                cloud2Active = false;
            }
        }

        //Cloud 3
        if(!cloud3Active){
            //How fast is the cloud
            srand((int)time(0) * 30);
            cloud3Speed = (rand() % 200);

            //How high is the cloud
            srand((int)time(0) * 30);
            float height = (rand() % 450) - 150;
            spriteCloud3.setPosition(-200, height);
            cloud3Active = true;
        }
        else{
            spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), 
            spriteCloud3.getPosition().y);

            //Has the cloud reached the right hand edge of the screen?
            if(spriteCloud3.getPosition().x > 1920){
                //Set it up ready tio be a whole new cloud next frame
                cloud3Active = false;
            }
        }

        //Update the score text
        std::stringstream ss;
        ss << "Score = " << score;
        scoreText.setString(ss.str());

      }//End if(!paused)
      /*
       **********************************
       Draw the scene
       **********************************
       */
      //Clear everything from the last frame
      window.clear();

      //Draw our game scene here
      window.draw(spriteBackground);

      //Draw the clouds
      window.draw(spriteCloud1);
      window.draw(spriteCloud2);
      window.draw(spriteCloud3);

      //Draw the tree
      window.draw(spriteTree);

      //Draw the insect
      window.draw(spriteBee);

      //Draw the score
      window.draw(scoreText);

      //Draw the timebar
      window.draw(timeBar);

      if(paused){
          //Draw our mesagge
          window.draw(messageText);
      }

      // Show everything we just drew
      window.display();


    }
    return 0;
}