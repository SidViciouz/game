#include "renderer.h"

Renderer::Renderer(Object_holder& object_holder):
object_holder{object_holder}
{
    if(glfwInit() == GLFW_FALSE)
    {
        throw runtime_error(string("glfwInit error!"));
    }
    glfwWindowHint(GLFW_SAMPLES,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800,600,"GAME",NULL,NULL);
    if(window == NULL)
    {
        throw runtime_error(string("glfwCreateWindow error!"));
    }

    glfwSetWindowPos(window,0,0);

    glfwPollEvents();
    glfwMakeContextCurrent(window);

    glewExperimental = true;

    if(glewInit() != GLEW_OK)
    {
        throw runtime_error(string("glewInit error!"));
    }

    glClearColor(0.0f,0.5f,0.3f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);

    program = LoadShaders("shaders/shader.vert","shaders/shader.frag");
    matrix = glGetUniformLocation(program,"MVP");
    
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1,&vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER,vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glGenBuffers(1,&color_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER,color_buffer_object);
    glBufferData(GL_ARRAY_BUFFER,sizeof(color),color,GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,vertex_buffer_object);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,color_buffer_object);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*)0);
}

void Renderer::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);

    mat4 projection = perspective(radians(45.0f),4.0f/3.0f,0.1f,100.0f);
    mat4 view = lookAt(vec3(10,10,10),vec3(0,3,0),vec3(0,1,0));
    mat4 VP = projection*view;

    //object_holder에서 object의 location과 direction과 type을 가져와서 이에 맞게 그림.
    for(auto it = object_holder.begin(); it != object_holder.end(); it++)
    {
        Position loc = it->second.get_location();
        Object_type type = it->second.get_type();
        mat4 location = translate(mat4(1.0f),vec3(loc.x,loc.z,loc.y));
        mat4 size;
        if(type == PLAYER)
        {
            size = scale(mat4(1.0f),vec3(1.0f,2.0f,1.0f));
        }
        else
        {
            size = scale(mat4(1.0f),vec3(0.5f,0.5f,0.5f));
        }
        mat4 MVP = VP*location*size;

        glUniformMatrix4fv(matrix,1,GL_FALSE,&MVP[0][0]);
        glDrawArrays(GL_TRIANGLES,0,12*3);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}