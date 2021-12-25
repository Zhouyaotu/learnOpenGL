#ifndef DATAOBJ_H
#define DATAOBJ_H

#include "global.h"
#include "function.h"

template<typename T>
class DataObj
{
public:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    int vertCount;
    int indexCount;

    DataObj();
    ~DataObj();
    void bindVAO();

    void loadVertexs(T* vertices, int totalSize, int step);
    void loadVertexs(DataObj & aObj);

    void loadIndices(unsigned int* indices, int totalSize, int step);
    void loadIndices(std::vector<unsigned int> indices, int totalSize, int step);

    void setVertexAtrribPointer(int location, GLint dataSize, GLenum dataType, GLboolean toNorm, int step, void* offset);

    void drawArray(GLenum mode, int offset);
    void drawElements(GLenum mode, const void* offset);
};

template<typename T>
DataObj<T>::DataObj():vertCount(0),indexCount(0)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

template<typename T>
DataObj<T>::~DataObj()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

template<typename T>
void DataObj<T>::bindVAO()
{
    glBindVertexArray(VAO);
}

template<typename T>
void DataObj<T>::loadVertexs(T* vertices, int totalSize, int step)
{
    bindVAO();
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // load data for opengl
    glBufferData(GL_ARRAY_BUFFER, totalSize, vertices, GL_STATIC_DRAW);
    vertCount = dataCount<T>(totalSize, step);

    glBindVertexArray(0);
}

template<typename T>
void DataObj<T>::loadVertexs(DataObj &aObj)
{
    bindVAO();
    VBO = aObj.VBO;
    vertCount = aObj.vertCount;

    glBindVertexArray(0);
}

template<typename T>
void DataObj<T>::loadIndices(unsigned int *indices, int totalSize, int step)
{
    bindVAO();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // load index
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalSize, indices, GL_STATIC_DRAW);
    indexCount = dataCount<unsigned int>(totalSize, step);

    glBindVertexArray(0);
}

template<typename T>
void DataObj<T>::setVertexAtrribPointer(int location, GLint dataSize, GLenum dataType, GLboolean toNormalize, int step, void* offset)
{
    bindVAO();
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, dataSize, dataType, toNormalize, step * sizeof(T), offset); // set attribt pointer

    glBindVertexArray(0);
}

template<typename T>
void DataObj<T>::drawArray(GLenum mode, int offset)
{
    bindVAO();
    if(vertCount > 0)
        glDrawArrays(mode, offset, vertCount);
    else
        std::cout << "Draw Error : vertices not enough" << std::endl;

    glBindVertexArray(0);
}

template<typename T>
void DataObj<T>::drawElements(GLenum mode, const void* offset)
{
    bindVAO();
    if(indexCount > 0)
        glDrawElements(mode, indexCount, GL_UNSIGNED_INT, offset);
    else
        std::cout << "Draw Error : indices not enough" << std::endl;

    glBindVertexArray(0);
}

#endif