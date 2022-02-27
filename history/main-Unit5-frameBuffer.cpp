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

float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
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

    DataObj<float> quad = DataObj<float>();
    quad.bindVAO();
    quad.loadVertexs(quadVertices, sizeof(quadVertices), 4);
    quad.setVertexAtrribPointer(0, 2, GL_FLOAT, GL_FALSE, 4, (void *)0);
    quad.setVertexAtrribPointer(1, 2, GL_FLOAT, GL_FALSE, 4, (void *)(2 * sizeof(float)));

    // set texture
    Texture2D texturePlane = Texture2D();
    texturePlane.setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
    texturePlane.setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
    texturePlane.setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texturePlane.setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texturePlane.load("../img/metal.png");

    Texture2D textureQuad = Texture2D();
    textureQuad.setTexture(GL_RGB, screenWidth/6.0, screenHeight/6.0, nullptr);
    textureQuad.setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    textureQuad.setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // set shader
    Shader objShader("../shader/vertex_mvp.vs", "../shader/object.fs");
    Shader oneColorShader("../shader/vertex_mvp.vs", "../shader/onlyColor.fs");
    Shader lightShader("../shader/vertex_mvp.vs", "../shader/onlyColor.fs");
    Shader planeShader("../shader/vertex_mvp_with_no_normal.vs", "../shader/onlyTexture.fs");
    Shader quadShader("../shader/vertex_2d.vs", "../shader/onlyTexture.fs");

    // bind tex & rbo to frameBuffer
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureQuad.ID, 0);  

    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenWidth/6.0, screenHeight/6.0);  
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // draw loop
    while (!glfwWindowShouldClose(window))
    {
        //==================//
        //=== first pass ===//
        //==================//
        glViewport(0, 0, screenWidth/6.0, screenHeight/6.0);
        // enable tests
        glEnable(GL_DEPTH_TEST);
        //glEnable(GL_STENCIL_TEST);
        //glEnable(GL_CULL_FACE);

        // bind fbo
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        
        // set clear color
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // deal with input
        processInput(window);

        // ligth
        glm::vec3 lightPos(1.5f, 1.0f, 2.0f);
        glm::vec3 lightPos1(-1.9f, 2.0f, 0.0f);
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

        // draw obj
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
       
        // draw light cube0
        glm::mat4 m_light(1.0f);
        m_light = glm::translate(m_light, lightPos);
        m_light = glm::scale(m_light, glm::vec3(0.1f));
        
        lightShader.use();
        lightShader.setMat4("v", v);
        lightShader.setMat4("p", p);
        lightShader.setMat4("m", m_light);

        light.drawArray(GL_TRIANGLES, 0);  

        // draw light cube1
        glm::mat4 m_light1(1.0f);
        m_light1 = glm::translate(m_light1, lightPos1);
        m_light1 = glm::scale(m_light1, glm::vec3(0.1f));
        
        lightShader.use();
        lightShader.setMat4("v", v);
        lightShader.setMat4("p", p);
        lightShader.setMat4("m", m_light1);

        light.drawArray(GL_TRIANGLES, 0);        
        
        // draw plane
        //glDisable(GL_DEPTH_TEST);
        texturePlane.bind(GL_TEXTURE0);
        planeShader.use();
        planeShader.setMat4("v", v);
        planeShader.setMat4("p", p);
        planeShader.setMat4("m", glm::mat4(1.0f));
        planeShader.setInt("texture1", 0);

        plane.drawArray(GL_TRIANGLES, 0); 

        //===================//
        //=== second pass ===//
        //===================//
        glViewport(0, 0, screenWidth, screenHeight);
        // bind defualt fbo
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // set clear color
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // draw a flat
        textureQuad.bind(GL_TEXTURE0);
        quadShader.use();
        quadShader.setMat4("v", glm::mat4(1.0f));
        quadShader.setMat4("p", glm::mat4(1.0f));
        quadShader.setMat4("m", glm::mat4(1.0f));
        quadShader.setInt("texture1", 0);
        quad.drawArray(GL_TRIANGLES, 0);

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