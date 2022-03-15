// User Headers
#include "global.h"
#include "function.h"
#include "Shader.h"
#include "Texture.h"
#include "DataObj.h"
#include "Camera.h"

// ==== data ====
float vertices[] = {
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // 右上
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // 右下
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // 左上
};

unsigned int indices[] = {
    // 注意索引从0开始!
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};

float myCube[] = {
    //  --------pos--------   ----uv----
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

glm::vec3 cubePositions[] = {
  glm::vec3( 0.0f,  0.0f,  0.0f), 
  glm::vec3( 2.0f,  5.0f, -15.0f), 
  glm::vec3(-1.5f, -2.2f, -2.5f),  
  glm::vec3(-3.8f, -2.0f, -12.3f),  
  glm::vec3( 2.4f, -0.4f, -3.5f),  
  glm::vec3(-1.7f,  3.0f, -7.5f),  
  glm::vec3( 1.3f, -2.0f, -2.5f),  
  glm::vec3( 1.5f,  2.0f, -2.5f), 
  glm::vec3( 1.5f,  0.2f, -1.5f), 
  glm::vec3(-1.3f,  1.0f, -1.5f)  
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
    DataObj<float> flatFace = DataObj<float>();
    flatFace.bindVAO();
    flatFace.loadVertexs(vertices, sizeof(vertices), 8);
    flatFace.loadIndices(indices, sizeof(indices), 1);
    flatFace.setVertexAtrribPointer(0, 3, GL_FLOAT, GL_FALSE, 8, (void *)0);
    flatFace.setVertexAtrribPointer(1, 3, GL_FLOAT, GL_FALSE, 8, (void *)(3 * sizeof(float)));
    flatFace.setVertexAtrribPointer(2, 2, GL_FLOAT, GL_FALSE, 8, (void *)(6 * sizeof(float)));

    DataObj<float> cubeFace = DataObj<float>();
    cubeFace.bindVAO();
    cubeFace.loadVertexs(myCube, sizeof(myCube), 5);
    cubeFace.setVertexAtrribPointer(0, 3, GL_FLOAT, GL_FALSE, 5, (void *)0);
    cubeFace.setVertexAtrribPointer(1, 2, GL_FLOAT, GL_FALSE, 5, (void *)(3 * sizeof(float)));

    // set texture
    Texture2D texture01 = Texture2D(GL_TEXTURE0);
    texture01.bind(GL_TEXTURE0);
    texture01.setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
    texture01.setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
    texture01.setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture01.setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture01.load("../img/container.jpg");

    Texture2D texture02 = Texture2D(GL_TEXTURE1);
    texture02.bind(GL_TEXTURE1);
    texture02.setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
    texture02.setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
    texture02.setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture02.setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture02.load("../img/awesomeface.png");

    // set shader
    Shader myShader("../shader/vertex.vs", "../shader/fragment.fs");

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
        texture01.bind(GL_TEXTURE0);
        texture02.bind(GL_TEXTURE1);

        // model translate
        glm::mat4 v(1.0f);
        v = camera.GetViewMatrix();
        glm::mat4 p(1.0f);
        p = glm::perspective(glm::radians(55.0f), screenWidth / screenHeight, 0.1f, 100.0f);

        // use shader program and draw
        myShader.use();
        myShader.setInt("texture1", 0);
        myShader.setInt("texture2", 1);
        myShader.setMat4("v", v);
        myShader.setMat4("p", p);

        // draw
        //flatFace.drawElements(GL_TRIANGLES, 0); //
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 m(1.0f);
            m = glm::translate(m, cubePositions[i]);
            float angle = 20.0f * i;
            m = glm::rotate(m, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            myShader.setMat4("m", m);

            cubeFace.drawArray(GL_TRIANGLES, 0);
        }
        
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