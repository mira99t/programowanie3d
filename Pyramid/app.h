#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Application/application.h"
#include "Application/utils.h"

#include "glad/gl.h"

class SimpleShapeApplication : public xe::Application
{
public:
    SimpleShapeApplication(int width, int height, std::string title, bool debug) : Application(width, height, title, debug) {}

    void init() override;

    void frame() override;

private:
    GLuint vao_;
    std::vector<GLushort> indices;

    static void setColorToVertices();

    static void setVerticesData();

    static unsigned int generateIndicesBuffer(std::vector<GLushort> vertices);

    static unsigned int generateVertexBuffer(std::vector<GLfloat> vertices);

    static void setDataToVertexBuffer(GLuint buffer);

    static void setDataToIndicesBuffer(GLuint buffer);

    static unsigned int generateUniformBuffer(float strength, std::vector<GLfloat> color);

    static void bindDataToUniformBuffer(GLuint uniformBuffer, GLuint transformationBuffer);

    static unsigned int generateTransformationBuffer(glm::mat4 pvm);
};