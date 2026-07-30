#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader_L.h"
#include <iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


// 前置声明回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// 设置窗口大小
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float xOffset = 0.5f;

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello GLFW", nullptr, nullptr);
    if(window == nullptr){
        std::cout<<"Failed to create window"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout<<"Failed to initialize GLAD"<<std::endl;
        return -1;
    }
    Shader ourShader("3.3Shader_Class/3.3.Shader.vs","3.3Shader_Class/3.3.Shader.fs");
   float vertices_Star[] = {
    // 外顶点（大半径 0.5f）
    0.0f,    0.5f,   0.0f,  1.0f, 0.0f, 0.0f,   // 0: 上 (红)
    0.475f,  0.154f, 0.0f,  0.0f, 1.0f, 0.0f,   // 1: 右上 (绿)
    0.294f, -0.404f, 0.0f,  0.0f, 0.0f, 1.0f,   // 2: 右下 (蓝)
    -0.294f, -0.404f, 0.0f, 1.0f, 1.0f, 0.0f,   // 3: 左下 (黄)
    -0.475f, 0.154f, 0.0f,  1.0f, 0.0f, 1.0f,   // 4: 左上 (紫)
    
    // 内顶点（小半径 0.2f）
    0.0f,    0.2f,   0.0f,  1.0f, 1.0f, 1.0f,   // 5: 内上 (白)
    0.19f,   0.062f, 0.0f,  1.0f, 1.0f, 1.0f,   // 6: 内右上 (白)
    0.118f, -0.162f, 0.0f,  1.0f, 1.0f, 1.0f,   // 7: 内右下 (白)
    -0.118f, -0.162f, 0.0f,  1.0f, 1.0f, 1.0f,   // 8: 内左下 (白)
    -0.19f,  0.062f, 0.0f,  1.0f, 1.0f, 1.0f,   // 9: 内左上 (白)
};

// 画五角星的10个三角形
unsigned int Star[] = {
    // 5个外三角形
    0, 5, 9,
    1, 6, 5,
    2, 7, 6,
    3, 8, 7,
    4, 9, 8,
    // 5个内三角形
    5, 6, 9,
    6, 7, 9,
    7, 8, 9,
    5, 9, 7,
};

    unsigned int  EBO,VAO,VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_Star), vertices_Star, GL_STATIC_DRAW);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Star), Star, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glm::vec4 vec = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    
    
   
    while (!glfwWindowShouldClose(window))
    {
        // 处理输入
        processInput(window);
        //渲染指令
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        // 清除颜色缓冲区
        glClear(GL_COLOR_BUFFER_BIT);
        //清除深度缓冲区
        //glClear(GL_DEPTH_BUFFER_BIT);
        //清除模板缓冲区
        //glClear(GL_STENCIL_BUFFER_BIT);
        glm::mat4 trans = glm::mat4(1.0f);
        //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        float scaleAmount = static_cast<float>(sin(glfwGetTime()));
        trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
        
        ourShader.use();
        
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        ourShader.setFloat("xOffset",xOffset);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);  
        // 检查并调用事件，交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(ourShader.ID);


    glfwTerminate();
    return 0;
    
}
//输入响应
void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

}
//窗口大小改变回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

