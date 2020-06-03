#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>


int Shader::checkCompileErrors(unsigned int shader, const std::string &shaderType){
    int CompilationSuccess;
    char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &CompilationSuccess);
    if(!CompilationSuccess)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << shaderType <<"::COMPILATION_FAILED\n" << infoLog << std::endl;
        
    }

    return CompilationSuccess;
}

int Shader::checkLinkerErrors(unsigned int shader){
    int linkSuccess;
    char infoLog[512];

    glGetProgramiv(shader, GL_LINK_STATUS, &linkSuccess);
    if(!linkSuccess)
    {
        glGetProgramInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << "PROGRAM" << "::LINKING_FAILED\n" << infoLog << std::endl;
        
    }

    return linkSuccess;
}

Shader::Shader(){
    ID = 0;
}

Shader::Shader(const char * vertexPath, const char * fragmentPath){
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

    }
    catch(std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_READ_FAILED" << std::endl;
    }

    const char * vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();

    unsigned int vertexShader, fragmentShader, shaderProgram;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
   
    checkLinkerErrors(shaderProgram);

    ID = shaderProgram;
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}
unsigned int Shader::getID() const{
    return ID;
}
void Shader::use(){
    glUseProgram(ID);
}
void Shader::set(const std::string &name, int value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::set(const std::string &name, float value) const{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::set(const std::string &name, bool value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::set(const std::string &name, glm::mat4 value) const{
    int loc = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::set(const std::string &name, glm::vec3 value) const{
    int loc = glGetUniformLocation(ID, name.c_str());
	glUniform3fv(loc, 1, glm::value_ptr(value));
}