#include "input.h"

Input::Input():
shoot{false,false}
{
    object = Object::create(PLAYER,{0,0,0},{0,0,0});
    thread input(input_thread,ref(object),ref(object_mutex),ref(shoot),ref(shoot_mutex));
    input.detach();
}
void Input::send_change(int socket)
{
    //오브젝트 전송.
    Position location;
    {
        lock_guard<mutex> lock(object_mutex);
        location = object.get_location();
    }
    send(socket,Message::make(string("player")+to_string(socket),(char*)"move",0,location,{0,0,0}).GetString(),1024,0);

    bool shot = false;
    {
        lock_guard<mutex> lock(shoot_mutex);
        shot = shoot.shoot;
        if(shot)
        {
            shoot.shoot = false;
        }
    }
    if(shot)
    {
        send(socket,Message::make(string("player")+to_string(socket),(char*)"shot",0,location,{-1.0f,0,0}).GetString(),1024,0);
    }

}
void Input::register_player(int socket)
{
    send(socket,Message::make(string("player")+to_string(socket),(char*)"register",0,{0,0,0},{0,0,0}).GetString(),1024,0);
}


void input_thread(Object& object,mutex& object_mutex,Shoot& shoot,mutex& shoot_mutex)
{
    int gameJoystick = -1;

    while(gameJoystick == -1)
    {
        for(int i=0; i<16; ++i)
        {
            if(glfwJoystickPresent(i) == GL_TRUE)
            {
                gameJoystick = i;
                break;
            }
        }
    }

    GLFWgamepadstate state;
    glfwGetGamepadState(gameJoystick,&state);
    float x = 0.0f;
    float y = 0.0f;
    float pivot_x = state.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
    float pivot_y = state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];
    bool shot = false;
    timespec req,rem;
    req.tv_sec = 0;
    req.tv_nsec = 10000000;

    while(1)
    {
        nanosleep(&req,&rem); // tick을 만들어야할듯. 슬립할때랑 안할때 x,y값이 변하는 속도차이가 큼.
        glfwGetGamepadState(gameJoystick,&state);
        x = state.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
        y = state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];
        shot = state.buttons[GLFW_GAMEPAD_BUTTON_CIRCLE];
        
        if(fabsf(x - pivot_x) > 0.1f)
        {
            lock_guard<mutex> lock(object_mutex);
            object.add_x(x/10.0f);
        }
        if(fabsf(y - pivot_y) > 0.1f)
        {
            lock_guard<mutex> lock(object_mutex);
            object.add_y(y/10.0f);
        }
        if(shot == GLFW_PRESS)
        {
            if(!shoot.pressed)
            {
                lock_guard<mutex> lock(shoot_mutex);
                shoot.pressed = true; //mutex 붙여야함.
                shoot.shoot = true;
            }
        }
        else
        {
            if(shoot.pressed)
            {
                lock_guard<mutex> lock(shoot_mutex);
                shoot.pressed = false;
            }
        }
    }
}