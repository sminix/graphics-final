#include "common.h"

using namespace Angel;

Ship ship;
Asteroid asteroid;

static void error_callback(int error, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    ship.rotateLeft();
  if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    ship.rotateRight();
  if (key == GLFW_KEY_SPACE){
    if(action == GLFW_PRESS){
      ship.start_thruster();
    }
    if(action == GLFW_RELEASE){
      ship.stop_thruster();
    }
  }
  if (key == GLFW_KEY_Z && action == GLFW_PRESS){
    //!!!!!!!!Fire bullet
  }
}

void init(){
  
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
  ship.gl_init();
  
}

void init_ast(){
  
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
  asteroid.gl_ast_init();
  
}
//Call update function 30 times a second
void animate(){
  if(glfwGetTime() > 0.033){
    glfwSetTime(0.0);
    ship.update_state();
  }
}

void animate_ast(){
  if(glfwGetTime() > 0.033){
    glfwSetTime(0.0);
	asteroid.update_state();
  }
}

int main(void)
{
  GLFWwindow* window;
  
  glfwSetErrorCallback(error_callback);
  
  if (!glfwInit())
    exit(EXIT_FAILURE);
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  glfwWindowHint(GLFW_SAMPLES, 10);
  
  
  window = glfwCreateWindow(1024, 768, "Asteroids!", NULL, NULL);
  if (!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  
  glfwSetKeyCallback(window, key_callback);
  
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  glfwSwapInterval(1);
  
  init();
  init_ast();
  
  while (!glfwWindowShouldClose(window)){
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    //Pick a coordinate system that makes the most sense to you
    //(left, right, top, bottom)
    mat4 proj = Ortho2D(-20.0, 20.0, -20.0, 20.0);
    
    animate();
	//glfwSwapBuffers(window);
	animate_ast();
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    ship.draw(proj);
	asteroid.draw(proj);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    
  }
  
  glfwDestroyWindow(window);
  
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
