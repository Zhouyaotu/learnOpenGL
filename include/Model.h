#ifndef MODEL_H
#define MODEL_H

#include "global.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Model 
{
    public:
        /*  函数   */
        Model(const char *path)
        {
            loadModel(path);
        }
        void Draw(Shader shader);

    private:
        /*  模型数据  */
        std::vector<Texture2D> textures_loaded;
        std::vector<Mesh> meshes;
        std::string directory;
        /*  函数   */
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture2D> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, glm::vec3 &ka, glm::vec3 &kd, glm::vec3 &ks);
};

void Model::Draw(Shader shader)
{
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(shader);
}

void Model::loadModel(std::string path)
{
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    // retrieve the directory path of the filepath
    directory = path.substr(0, path.find_last_of('/'));

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    // 处理节点所有的网格（如果有的话）
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        meshes.push_back(processMesh(mesh, scene));         
    }
    // 接下来对它的子节点重复这一过程
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture2D> textures;
    //std::cout << mesh->mNumVertices;
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // 处理顶点位置、法线和纹理坐标
        glm::vec3 vector; 
        
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z; 
        vertex.Position = vector;

        if(mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }

        if(mesh->mTextureCoords[0]) // 网格是否有纹理坐标？
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        vertices.push_back(vertex);
    }

    // 处理索引
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // 处理材质
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::cout<< "model - vert:index " <<mesh->mNumVertices << ":" << mesh->mNumFaces << std::endl;
        
        glm::vec3 ka, kd, ks;

        std::vector<Texture2D> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", ka, kd, ks);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture2D> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", ka, kd, ks);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture2D> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, glm::vec3 &ka, glm::vec3 &kd, glm::vec3 &ks)
{
    std::vector<Texture2D> textures;

    for(int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str, name;
        aiColor3D color;
        
        mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
        ka = glm::vec3(color.r, color.g, color.b);
        mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        kd = glm::vec3(color.r, color.g, color.b);
        mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
        ks = glm::vec3(color.r, color.g, color.b);
        //std::cout << color.r << std::endl;

        mat->GetTexture(type, i, &str);
        //mat->Get(AI_MATKEY_TEXTURE(type, i), str);
        //std::cout << "texture" <<str.C_Str() << std::endl;
        

        bool skip = false;
        for(unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if(std::strcmp(textures_loaded[j].path.C_Str(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; 
                break;
            }
        }
        //std::cout << skip << std::endl;
        if(!skip)
        {   // 如果纹理还没有被加载，则加载它
            Texture2D texture = Texture2D();
            //std::cout << textureID << "\n";

            std::string filename = std::string(str.C_Str());
            filename = this->directory + '/' + filename;
            texture.load(filename.c_str());

            texture.setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
            texture.setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
            texture.setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            texture.setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            texture.type = typeName;
            texture.path = str.C_Str();

            textures.push_back(texture);
            textures_loaded.push_back(texture); // 添加到已加载的纹理中
        }
    }
    return textures;
}

#endif 