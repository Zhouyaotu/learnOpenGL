#ifndef TEXTURE_H
#define TEXTURE_H

#include "global.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Texture2D
{
public:
    /* data */
    unsigned int ID;
    unsigned char *img_data;
    std::string type;
    aiString path;
    int height, width, nrChannels;
    GLenum texUnit;

    Texture2D();
    Texture2D(unsigned int id);
    //Texture2D(Texture2D & obj);
    ~Texture2D();
    void bind(GLenum);
    void load(const char* path);
    void setTexture(GLenum format, int width, int height, unsigned char* data);
    void setParameteri(GLenum, GLint);
};
Texture2D::Texture2D()
{
    glGenTextures(1, &ID);
}

Texture2D::Texture2D(unsigned int id)
{
    this->ID = id;
}

Texture2D::~Texture2D()
{
    //glDeleteTextures(1, &ID);
}

void Texture2D::bind(GLenum name)
{
    glActiveTexture(name);
    glBindTexture(GL_TEXTURE_2D, ID);
}

// MUST AFTER BIND IF CALL THESE FUNCTIONS

void Texture2D::load(const char *path)
{
    GLenum format;
    stbi_set_flip_vertically_on_load(false);
    img_data = stbi_load(path, &width, &height, &nrChannels, 0);
    //std::cout << path << " " << sizeof(img_data)<< " " << nrChannels << " " << width << " " <<height <<"\n";
    
    switch (nrChannels)
    {
    case 4:
        format = GL_RGBA;
        break;
    case 3:
        format = GL_RGB;
        break;
    case 1:
        format = GL_RED;
    default:
        format = GL_RGB;
        break;
    }
    if(img_data != nullptr)
    {
        glBindTexture(GL_TEXTURE_2D, ID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, img_data);
        glGenerateMipmap(GL_TEXTURE_2D);       
    }
    else
        std::cout << "Failed to load texture" << std::endl;
        
    stbi_image_free(img_data);
}

void Texture2D::setTexture(GLenum format, int width, int height, unsigned char* data)
{
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, img_data);
    glGenerateMipmap(GL_TEXTURE_2D); 
}

void Texture2D::setParameteri(GLenum pname, GLint param)
{
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, pname, param);
}

#endif