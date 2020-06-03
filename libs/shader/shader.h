#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader{
    private:
        unsigned int ID;
        int checkCompileErrors(unsigned int shader, const std::string &type);
        int checkLinkerErrors(unsigned int shader);
    public:
        Shader();
        Shader(const char *vertexPath, const char *fragmentPath);
        unsigned int getID() const;
        void use();
        void set(const std::string &name, int value) const;
        void set(const std::string &name, float value) const;
        void set(const std::string &name, bool value) const;
        void set(const std::string &name, glm::mat4 value) const;
        void set(const std::string &name, glm::vec3 value) const;
};