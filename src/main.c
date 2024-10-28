#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "shaders/shader.h"
#include "stb/stb_image.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
}

unsigned int loadTexture(char texturePath[]) {
    int width, height, nrChannels;

    char *fileTypePointer = strrchr(texturePath, '.');

    if (fileTypePointer == NULL) {
        glfwTerminate();

        printf("Illegal filetype. File name must contain a filetype.");

        return -1;
    }

    stbi_set_flip_vertically_on_load(true);

    unsigned char* textureData = stbi_load(texturePath, &width, &height, &nrChannels, 0);

    if (!textureData ) {
        glfwTerminate();

        printf("Failed loading texture: %s\n", texturePath);

        return -1;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    unsigned int texture; 
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    if (
        strcmp(fileTypePointer, ".jpg") == 0 ||
        strcmp(fileTypePointer, ".jpeg") == 0
    ) {
        glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GL_RGB, 
            width,
            height,
            0,
            GL_RGB, 
            GL_UNSIGNED_BYTE,
            textureData
        );
    } else if (strcmp(fileTypePointer, ".png") == 0) {
        glTexImage2D(
            GL_TEXTURE_2D, 
            0,
            GL_RGB, 
            width,
            height,
            0,
            GL_RGBA, 
            GL_UNSIGNED_BYTE,
            textureData
        );
    } else {
        printf("Unknown filetype: %s\n", fileTypePointer);

        return -1;
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(textureData);

    return texture;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);

    if (window == NULL) {
        printf("Failed to create GLFW window\n");

        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");

        glfwTerminate();

        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    unsigned int VBO; 
    glGenBuffers(1, &VBO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    unsigned int shaderProgramID = loadShaders();

    if (!shaderProgramID) {
        glfwTerminate();

        return -1;
    }

    unsigned int wallTexture = loadTexture("./lib/images/container.jpg");
    unsigned int smileyTexture = loadTexture("./lib/images/awesomeface.png");

    if (wallTexture == -1 || smileyTexture == -1) {
        glfwTerminate();
        
        printf("Failed Loading Textures\n");

        return -1;
    }

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };    

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // define colour and vertex attrib pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));

    // enable colour and vertex attrib pointers    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // wireframe 
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glUseProgram(shaderProgramID);

    glUniform1i(glGetUniformLocation(shaderProgramID, "wallTexture"), 0);
    glUniform1i(glGetUniformLocation(shaderProgramID, "smileyTexture"), 1); 

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, wallTexture);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, smileyTexture);


    // render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    
    printf("Goodbye!");

    return 0;
}

