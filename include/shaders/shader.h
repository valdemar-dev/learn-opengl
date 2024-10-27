#ifndef SHADER_H
#define SHADER_H

int loadVertexShaderFromDisk(
    int* success, 
    char infoLog[512]
);

int loadFragmentShaderFromDisk(    
    int* success, 
    char infoLog[512]
);

int loadShaders();

char* readShaderSource(const char* filePath);

#endif
