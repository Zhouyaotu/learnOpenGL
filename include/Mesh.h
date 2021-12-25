#ifndef MESH_H
#define MESH_H

#include "global.h"
#include "Texture.h"
#include "DataObj.h"
#include "Shader.h"
#include <vector>

class Mesh {
    public:
        /*  网格数据  */
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture2D> textures;
        /*  函数  */
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture2D> textures);
        void Draw(Shader shader);

    private:
        /*  渲染数据  */
        DataObj<Vertex> vertData;
        /*  函数  */
        void setupMesh();
};  

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture2D> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->vertData = DataObj<Vertex>();
    setupMesh();
}

void Mesh::setupMesh()
{
    vertData.loadVertexs(&vertices[0], vertices.size() * sizeof(Vertex), 1);
    vertData.loadIndices(&indices[0], indices.size() * sizeof(unsigned int), 3);
    vertData.setVertexAtrribPointer(0, 3, GL_FLOAT, GL_FALSE, 1, (void*)0);
    vertData.setVertexAtrribPointer(1, 3, GL_FLOAT, GL_FALSE, 1, (void*)offsetof(Vertex, Normal));
    vertData.setVertexAtrribPointer(2, 2, GL_FLOAT, GL_FALSE, 1, (void*)offsetof(Vertex, TexCoords));
}

void Mesh::Draw(Shader shader) 
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        //glActiveTexture(GL_TEXTURE0 + i); // 在绑定之前激活相应的纹理单元
        textures[i].bind(GL_TEXTURE0 + i);
        // 获取纹理序号（diffuse_textureN 中的 N）
        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);

        shader.setInt(("M." + name + number).c_str(), i);
        //glBindTexture(GL_TEXTURE_2D, textures[i].ID);
    }
    glActiveTexture(GL_TEXTURE0);

    // 绘制网格
    vertData.drawElements(GL_TRIANGLES, 0);
}

#endif