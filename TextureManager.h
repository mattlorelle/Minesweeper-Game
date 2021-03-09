#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager {
public:
   // The textures that are loaded
   static std::map<std::string, sf::Texture*> textures;

   // Constructor that is not used
   TextureManager();

   // Destructor which deletes textures (since using pointers)
   ~TextureManager();
    
   static int getLength();

   // Get texutre by name specified in loadTexture, or return null
   static sf::Texture *getTexture(std::string);
    
   // Loads the texture and returns a pointer to it
   static sf::Texture *loadTexture(std::string, std::string);
};