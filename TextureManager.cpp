#include "TextureManager.h"

TextureManager::TextureManager() {}

std::map<std::string, sf::Texture*> TextureManager::textures;


int TextureManager::getLength() { // Get length of textures array
    return textures.size();
}

// Get Texture by Name
sf::Texture *TextureManager::getTexture(std::string name) {
    
    if(textures.find(name) != textures.end()) { // See if we have already loaded this texture
        return textures[name];
    } else {
        return NULL;
    }
}

sf::Texture *TextureManager::loadTexture(std::string name, std::string path) { //loading a texture from a file path, and giving it a name

    sf::Texture *texture = new sf::Texture(); //new texture object
    
    if(texture->loadFromFile(path)) { //if file could be loaded
        
        textures[name] = texture;
        return textures[name];
    } else { //if could not load the file

        delete texture;
        return NULL;
    }
    
}

TextureManager::~TextureManager() { //delete the map of textures
    
    sf::Texture *texture;
    std::map<std::string, sf::Texture*>::iterator iter = textures.begin();

    while(iter != textures.end()) {
        
        texture = iter->second;
        delete texture;
        iter++;
    }
}