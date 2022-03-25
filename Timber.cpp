#include <SFML/Graphics.hpp>

// Make code easier to type with "using namespace"
using namespace sf;

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

       /*
       **********************************
       Update the scene
       **********************************
       */

      // Measure time
        Time dt = clock.restart();
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
            if(spriteCloud1.getPosition().x < 1920){
                //Set it up ready to be a whole new cloud next frame
                cloud1Active = false;
            }
        }


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

      // Show everything we just drew
      window.display();


    }
    return 0;
}