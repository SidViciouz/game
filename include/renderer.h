#pragma once

#include "object.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdexcept>
#include "shader.hpp"
#include "data.h"

class Renderer
{
private:
    Object_holder& object_holder;
    GLFWwindow* window;
    GLuint program;
    GLuint matrix;
    GLuint VAO;
    GLuint vertex_buffer_object;
    GLuint color_buffer_object;

public:
    Renderer() = delete;
    Renderer(Object_holder& object_holder);
    ~Renderer(){}
    void draw();
};