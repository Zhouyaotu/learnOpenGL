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

    DataObj light = DataObj<float>();
    light.bindVAO();
    light.loadVertexs(vertices, sizeof(vertices), 6);
    light.setVertexAtrribPointer(0, 3, GL_FLOAT, GL_FALSE, 8, (void *)0);
    light.setVertexAtrribPointer(1, 3, GL_FLOAT, GL_FALSE, 8, (void *)(3 * sizeof(float)));
    light.setVertexAtrribPointer(2, 2, GL_FLOAT, GL_FALSE, 8, (void *)(6 * sizeof(float)));

    // set texture
    /*
    Texture2D texture01 = Texture2D(GL_TEXTURE0);
    texture01.setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
    texture01.setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
    texture01.setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture01.setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture01.load("../img/container2.png");
    */

    // set shader
    Shader objShader("../shader/vertex.vs", "../shader/object.fs");
    Shader lightShader("../shader/vertex.vs", "../shader/light.fs");

    // enable z-test
    glEnable(GL_DEPTH_TEST);

    // draw loop
    while (!glfwWindowShouldClose(window))
    {
        // set clear color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // deal with input
        processInput(window);

        // bind texture
        //texture01.bind(GL_TEXTURE0);

        // mvp
        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
        glm::vec3 objColor(1.0f, 0.5f, 0.31f);

        // mvp
        glm::mat4 v(1.0f);
        v = camera.GetViewMatrix();
        glm::mat4 p(1.0f);
        p = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f);
        glm::mat4 m_obj(1.0f);
        //m_obj = glm::rotate(m_obj, glm::radians(45.0f), glm::vec3(1.0f, 0.3f, 0.5f));

        // use shader program and set uniformValue
        objShader.use();
        
        objShader.setMat4("v", v);
        objShader.setMat4("p", p);
        objShader.setMat4("m", m_obj);

        objShader.setMat4("NormalMat", glm::transpose(glm::inverse(m_obj)));
        objShader.setVec3("lightColor", lightColor);
        objShader.setVec3("lightPos", lightPos);
        
        objShader.setVec3("eyePos", camera.Position);
        objShader.setVec3("M.ka", glm::vec3(0.1f, 0.1f, 0.1f));
        objShader.setVec3("intensityAmbient", glm::vec3(0.2,0.2,0.2));
        objShader.setVec3("M.kd", glm::vec3(0.3f, 0.3f, 0.3f));
        objShader.setVec3("M.ks", glm::vec3(0.2, 0.2, 0.2));
        objShader.setFloat("M.shininess", 64.0);

        // draw
        ourModel.Draw(objShader);

        // draw light cube
        glm::mat4 m_light(1.0f);
        m_light = glm::translate(m_light, lightPos);
        m_light = glm::scale(m_light, glm::vec3(0.1f));
        lightShader.use();
        lightShader.setMat4("v", v);
        lightShader.setMat4("p", p);
        lightShader.setMat4("m", m_light);

        light.drawArray(GL_TRIANGLES, 0);        
        
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