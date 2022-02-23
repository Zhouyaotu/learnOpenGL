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
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

float planeVertices[] = {
        // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f								
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
    //Model ourModel("../model/mary/Marry.obj");

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

    // set texture
    ///*
    Texture2D texture01 = Texture2D();
    texture01.setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
    texture01.setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
    texture01.setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture01.setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture01.load("../img/metal.png");
    //*/

    // set shader
    Shader objShader("../shader/vertex.vs", "../shader/object.fs");
    Shader oneColorShader("../shader/vertex.vs", "../shader/onlyColor.fs");
    Shader lightShader("../shader/vertex.vs", "../shader/light.fs");
    Shader planeShader("../shader/plane.vs", "../shader/onlyTexture.fs");

    // enable tests
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);

    // draw loop
    while (!glfwWindowShouldClose(window))
    {
        // set clear color
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        glStencilMask(0xFF); // templete test
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // deal with input
        processInput(window);

        // bind texture
        //texture01.bind(GL_TEXTURE0);

        // ligth
        glm::vec3 lightPos(1.5f, 1.0f, 2.0f);
        glm::vec3 lightPos1(-1.9f, 2.0f, 0.0f);
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

        // draw obj
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);

        glm::mat4 v(1.0f);
        v = camera.GetViewMatrix();
        glm::mat4 p(1.0f);
        p = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f);

        glm::mat4 m_obj(1.0f);
        m_obj = glm::translate(m_obj, glm::vec3(0.0, -0.5, 0.0));
        m_obj = glm::scale(m_obj, glm::vec3(0.15));
        
        objShader.use();// use shader program and set uniformValue
        
        objShader.setMat4("v", v);
        objShader.setMat4("p", p);
        objShader.setMat4("m", m_obj);
        objShader.setMat4("NormalMat", glm::transpose(glm::inverse(m_obj)));

        objShader.setVec3("Light[0].lightColor", lightColor);
        objShader.setVec3("Light[0].lightPos", lightPos);
        objShader.setVec3("Light[1].lightColor", lightColor);
        objShader.setVec3("Light[1].lightPos", lightPos1);
        
        objShader.setVec3("eyePos", camera.Position);
        objShader.setVec3("intensityAmbient", glm::vec3(0.1,0.1,0.1));

        ourModel.Draw(objShader);

        // draw selectionModel
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glm::mat4 s_obj(1.0f);
        s_obj = glm::translate(s_obj, glm::vec3(0.0, -0.5, 0.0));
        s_obj = glm::scale(s_obj, glm::vec3(0.153));
        
        oneColorShader.use();// use shader program and set uniformValue
        
        oneColorShader.setMat4("v", v);
        oneColorShader.setMat4("p", p);
        oneColorShader.setMat4("m", s_obj);

        ourModel.Draw(oneColorShader);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);

        // draw light cube0
        ///*
        glm::mat4 m_light(1.0f);
        m_light = glm::translate(m_light, lightPos);
        m_light = glm::scale(m_light, glm::vec3(0.1f));
        
        lightShader.use();
        lightShader.setMat4("v", v);
        lightShader.setMat4("p", p);
        lightShader.setMat4("m", m_light);

        light.drawArray(GL_TRIANGLES, 0);  

        //*/draw light cube1
        glm::mat4 m_light1(1.0f);
        m_light1 = glm::translate(m_light1, lightPos1);
        m_light1 = glm::scale(m_light1, glm::vec3(0.1f));
        
        lightShader.use();
        lightShader.setMat4("v", v);
        lightShader.setMat4("p", p);
        lightShader.setMat4("m", m_light1);

        light.drawArray(GL_TRIANGLES, 0);        
        
        // draw plane
        texture01.bind(GL_TEXTURE0);
        planeShader.use();
        planeShader.setMat4("v", v);
        planeShader.setMat4("p", p);
        planeShader.setMat4("m", glm::mat4(1.0f));
        planeShader.setInt("texture1", 0);

        plane.drawArray(GL_TRIANGLES, 0); 

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