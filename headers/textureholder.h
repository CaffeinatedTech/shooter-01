#ifndef TEXTUREHOLDER_H
#define TEXTUREHOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class TextureHolder {
private:
    // A map container from the STL,
    // that holds related pairs of String and Texture
    map<string, Texture> textures;

    // A pointer of the same type as the class itself
    // the one and only instance
    static TextureHolder* instance;

public:
    TextureHolder();
    static Texture& GetTexture(string const& filename);
};

#endif //TEXTUREHOLDER_H
