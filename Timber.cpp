#include <SFML/Graphics.hpp>

// Make code easier to type with "using namespace"
using namespace sf;

// This is where our game starts from
int main()
{
    // Create a video mode object
    VideoMode vm(1366, 768);

    // Create and open a window for the game
    RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

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
    spriteTree.setPosition(810, 0);

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



      /*
       **********************************
       Draw the scene
       **********************************
       */
      //Clear everything from the last frame
      window.clear();

      //Draw our game scene here
      window.draw(spriteBackground);

      // Show everything we just drew
      window.display();


    }
    return 0;
}