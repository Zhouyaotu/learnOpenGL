// User Headers
#include "global.h"
#include "function.h"
#include "Shader.h"
#include "Texture.h"
#include "DataObj.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"

// ==== data ====
float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

float planeVertices[] = {
    // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
    5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
    -5.0f, -0.5f, 5.0f, 0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,

    5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
    -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
    5.0f, -0.5f, -5.0f, 2.0f, 2.0f};

float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    // positions   // texCoords
    -1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 0.0f,

    -1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 1.0f};

float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

// ==== MAIN ====
int main()
{
    // init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window as current context
    GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Window Create Failed. \n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // load glad to fit opengl
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD. \n";
        return -1;
    }

    // set callback function
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // bind data to obj
    Model ourModel("../model/black/nanosuit.obj");

    DataObj<float> light = DataObj<float>();
    light.bindVAO();
    light.loadVertexs(vertices, sizeof(vertices), 8);
    light.setVertexAtrribPointer(0, 3, GL_FLOAT, GL_FALSE, 8, (void *)0);
    light.setVertexAtrribPointer(1, 3, GL_FLOAT, GL_FALSE, 8, (void *)(3 * sizeof(float)));
    light.setVertexAtrribPointer(2, 2, GL_FLOAT, GL_FALSE, 8, (void *)(6 * sizeof(float)));

    DataObj<float> plane = DataObj<float>();
    plane.bindVAO();
    plane.loadVertexs(planeVertices, sizeof(planeVertices), 5);
    plane.setVertexAtrribPointer(0, 3, GL_FLOAT, GL_FALSE, 5, (void *)0);
    plane.setVertexAtrribPointer(1, 2, GL_FLOAT, GL_FALSE, 5, (void *)(3 * sizeof(float)));
    
    DataObj<float> skybox = DataObj<float>();
    skybox.bindVAO();
    skybox.loadVertexs(skyboxVertices, sizeof(skyboxVertices),3);
    skybox.setVertexAtrribPointer(0, 3, GL_FLOAT, GL_FALSE, 3, (void*)0);

    // set texture
    Texture2D texturePlane = Texture2D();
    texturePlane.setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
    texturePlane.setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
    texturePlane.setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texturePlane.setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texturePlane.load("../img/metal.png");
    
    // sky box 
    unsigned int textureSkyBox;
    glGenTextures(1, &textureSkyBox);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureSkyBox);
    std::vector<std::string> textures_faces{
        "../img/skybox/right.jpg",
        "../img/skybox/left.jpg",
        "../img/skybox/top.jpg",
        "../img/skybox/bottom.jpg",
        "../img/skybox/front.jpg",
        "../img/skybox/back.jpg"};

    int width, height, nrChannels;
    unsigned char *data;
    for (unsigned int i = 0; i < textures_faces.size(); i++)
    {
        data = stbi_load(textures_faces[i].c_str(), &width, &height, &nrChannels, 0);
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // set shader
    Shader objShader("../shader/vertex_mvp.vs", "../shader/object.fs");
    Shader lightShader("../shader/vertex_mvp.vs", "../shader/onlyColor.fs");
    Shader planeShader("../shader/vertex_mvp_with_no_normal.vs", "../shader/onlyTexture.fs");
    Shader skyboxShader("../shader/skybox.vs","../shader/skybox.fs");

    // draw loop
    while (!glfwWindowShouldClose(window))
    {
        //==================//
        //=== first pass ===//
        //==================//

        // enable tests
        glEnable(GL_DEPTH_TEST);
        // glEnable(GL_STENCIL_TEST);
        // glEnable(GL_CULL_FACE);

        // set clear color
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // deal with input
        processInput(window);

        // set ligth
        glm::vec3 lightPos(1.5f, 1.0f, 2.0f);
        glm::vec3 lightPos1(-1.9f, 2.0f, 0.0f);
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

        // get v-mat & p-mat
        glm::mat4 v(1.0f);
        v = camera.GetViewMatrix();
        glm::mat4 p(1.0f);
        p = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f);

        //===draw obj===
        glm::mat4 m_obj(1.0f);
        m_obj = glm::translate(m_obj, glm::vec3(0.0, -0.5, 0.0));
        m_obj = glm::scale(m_obj, glm::vec3(0.15));

        objShader.use(); // use shader program and set uniformValue

        objShader.setMat4("v", v);
        objShader.setMat4("p", p);
        objShader.setMat4("m", m_obj);
        objShader.setMat4("NormalMat", glm::transpose(glm::inverse(m_obj)));

        objShader.setVec3("Light[0].lightColor", lightColor);
        objShader.setVec3("Light[0].lightPos", lightPos);
        objShader.setVec3("Light[1].lightColor", lightColor);
        objShader.setVec3("Light[1].lightPos", lightPos1);

        objShader.setVec3("eyePos", camera.Position);
        objShader.setVec3("intensityAmbient", glm::vec3(0.1, 0.1, 0.1));

        ourModel.Draw(objShader);

        //===draw plane===
        texturePlane.bind(GL_TEXTURE0);
        planeShader.use();
        planeShader.setMat4("v", v);
        planeShader.setMat4("p", p);
        planeShader.setMat4("m", glm::mat4(1.0f));
        planeShader.setInt("texture1", 0);

        plane.drawArray(GL_TRIANGLES, 0);

        //===draw skybox===
        glDepthFunc(GL_LEQUAL);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureSkyBox);
        glm::mat4 view_not_move = glm::mat4(glm::mat3(v));
        skyboxShader.use();
        skyboxShader.setMat4("v", view_not_move);
        skyboxShader.setMat4("p", p);
        skyboxShader.setInt("skybox", 0);
        skybox.drawArray(GL_TRIANGLES, 0);
        glDepthFunc(GL_LESS);

        //=====================//
        //=== output window ===//
        //=====================//

        // fill frame from buffer
        glfwSwapBuffers(window);
        glfwPollEvents();

        // get time of every frame to caculate deltaTime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }

    // terminate GLFW before close
    glfwTerminate();

    return 0;
}