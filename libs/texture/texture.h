#pragma once
#include <string>

class Texture{
    private:
        unsigned int ID;
        int width;
        int height;
        int nrChannels;
    public:
        Texture();
        Texture(const std::string &imagePath, unsigned int color_mode);
        unsigned int getID() const;
        void bind(int textureUnit);
};



