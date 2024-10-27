#include <stdio.h>
#include <stdlib.h>
#include "shaders/shader.h"

char* readShaderSource(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", filePath);
        return NULL;
    }

    // Move to the end of the file to find the file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    // Allocate memory for the file contents + null terminator
    char* shaderSource = (char*)malloc(fileSize + 1);
    if (!shaderSource) {
        fprintf(stderr, "Could not allocate memory for shader source\n");
        fclose(file);
        return NULL;
    }

    // Read the file contents into the buffer
    fread(shaderSource, 1, fileSize, file);
    shaderSource[fileSize] = '\0'; // Null-terminate the string

    fclose(file);
    return shaderSource;
}
