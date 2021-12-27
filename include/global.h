#ifndef GLOBAL_H
#define GLOBAL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h> // 包含glad来获取所有的必须OpenGL头文件

#include "stb_image.h"
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Camera.h"

// texture type
enum IMG_TYPE{PNG, JPG};

// Screen parm
float screenWidth = 800;
float screenHeight = 600;

// Camera parm
Camera camera(glm::vec3(0.0, 0.0, 3.0));

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

float lastX = 400, lastY = 300; //init mouse position
bool firstMouse = true;

// model parm
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

#endif