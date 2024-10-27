#include <glad/glad.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "shaders/shader.h"
#include <GLFW/glfw3.h>

void checkShaderCompilationStatus(
    int shader,
    int *success,
    char infoLog[512]
) {
    glGetShaderiv(shader, GL_COMPILE_STATUS, success);

    if (!*success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);

        printf("ERROR::SHADER::COMPILATION_FAILED\n");
        printf("%s", infoLog);
    }
}

int loadVertexShaderFromDisk(
    int* success, 
    char infoLog[512]
) {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const char* filePath = "src/shaders/vertex.glsl";
    char* vertexShaderSource = readShaderSource(filePath);

    if (!vertexShaderSource) {
        return -1;
    }

    glShaderSource(vertexShader, 1, (const GLchar**)&vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    free(vertexShaderSource);

    checkShaderCompilationStatus(
        vertexShader,
        success, 
        infoLog
    );

    if (!success) {
        glfwTerminate();
        return -1;
    }

    return vertexShader;
}

int loadFragmentShaderFromDisk(
    int* success, 
    char infoLog[512]
) {
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* filePath = "src/shaders/fragment.glsl";
    char* fragmentShaderSource = readShaderSource(filePath);
    if (!fragmentShaderSource) {
        return -1;
    }

    glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    free(fragmentShaderSource);

    checkShaderCompilationStatus(
        fragmentShader,
        success, 
        infoLog
    );

    if (!success) {
        glfwTerminate();
        return -1;
    }
    return fragmentShader;
}

int loadShaders() {
    int success;
    char infoLog[512];

    int vertexShader = loadVertexShaderFromDisk(
        &success, 
        infoLog
    );

    int fragmentShader = loadFragmentShaderFromDisk(
        &success, 
        infoLog
    );

    if (!fragmentShader || !vertexShader) {
        return -1;
    }

    unsigned int shaderProgramID = glCreateProgram();

    glAttachShader(shaderProgramID, vertexShader);
    glAttachShader(shaderProgramID, fragmentShader);

    glLinkProgram(shaderProgramID);

    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgramID;
}


