#include "textureholder.h"
#include <assert.h>

TextureHolder* TextureHolder::instance = nullptr;

TextureHolder::TextureHolder() {
  assert(instance == nullptr);
  instance = this;
}

Texture & TextureHolder::GetTexture(const string &filename) {
  // Get a reference to m_Textures using m_s_Instance
  auto& m = instance->textures;
  // auto is the equivalent of map<string, texture>

  // Create an iterator to hold a key-value-pair (kvp)
  // and search for the required kvp
  auto keyValuePair = m.find(filename);
  // auto is equivalent of map<string, Texture>::iterator

  // Did we find a match?
  if (keyValuePair != m.end()) {
    // Yes, return the texture
    return keyValuePair->second;
  }
  else {
    // File name not found
    // Create a new key value pair using the filename
    auto& texture = m[filename];
    // Load the texture from file in the usual way
    texture.loadFromFile(filename);
    // Return the texture to the calling code
    return texture;
  }
}
