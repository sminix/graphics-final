#include "common.h"

using namespace Angel;

Ball *ball;

Player *player1;
Player *player2;
Player *player3;
Player *player4;
Player *player5;
Player *player6;

std::vector < Player > players;

std::vector<bool> in_out;
std::vector<bool> launch;


static void error_callback(int error, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    ball->rotateLeft();
  if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    ball->rotateRight();
  
  if (key == GLFW_KEY_SPACE){
    if(action == GLFW_PRESS){
      //ball->start_thruster();
    }
    if(action == GLFW_RELEASE){
      //ball->stop_thruster();
    }
  }
   
  if (key == GLFW_KEY_Z && action == GLFW_PRESS){
    //!!!!!!!!Fire bullet
  }
}

bool inside;

//TODO: Inside outside test
void inside_outside_test(vec2 point){
  
  
  for (unsigned int i = 0; i < 6; i++){
	Player player = players[i];

	float px = player.player_vert[0].x;
	float py = player.player_vert[0].y;
	//add and subtract 1.5 because that is radius of the player
	if (point.x < px + 1.5 and point.x > px - 1.5 and point.y < py + 1.5 and point.y > py - 1.5){
	  in_out[i] = true;
	}
	else {
	  in_out[i] = false;
	}
  }

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
  if (button == GLFW_MOUSE_BUTTON_LEFT){
	for (unsigned int i = 0; i < 6; i++){
	  if (in_out[i] == true){
		if(action == GLFW_PRESS){
		  //std::cout << "charge" << std::endl;
		}
	  }
	}
    
    if(action == GLFW_RELEASE){
      //player->release()
    }
  }
  
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
  //Assuming the default frustrum with extents from -1 to 1, this converts
  //the screen cursor position to world coordinates
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  xpos = xpos/width*40.0 - 20.0;
  ypos = -(ypos/height*40.0 - 20.0);
  
  inside_outside_test(vec2(xpos, ypos));
}

void init(){
  
  glClearColor(.49, .98, 0.0, 1.0);
  glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
  ball->gl_init();
  player1->gl_init();
  player2->gl_init();
  player3->gl_init();
  player4->gl_init();
  player5->gl_init();
  player6->gl_init();
  
}



//Call update function 30 times a second
void animate(){
  if(glfwGetTime() > .033){
    glfwSetTime(0.0);
    ball->update_state();
	player1->update_state();
	player2->update_state();
	player3->update_state();
	player4->update_state();
	player5->update_state();
	player6->update_state();
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
  
  
  window = glfwCreateWindow(1024, 768, "Soccer!", NULL, NULL);
  if (!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);
  
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  glfwSwapInterval(1);
  
  player1 = new Player(vec2(-10,-10), 'r');
  player2 = new Player(vec2(0,-10), 'r');
  player3 = new Player(vec2(10,-10), 'r');
  player4 = new Player(vec2(-10, 10), 'b');
  player5 = new Player(vec2(0, 10), 'b');
  player6 = new Player(vec2(10, 10), 'b');
  ball = new Ball();
  init();
  
  players.push_back(*player1);
  players.push_back(*player2);
  players.push_back(*player3);
  players.push_back(*player4);
  players.push_back(*player5);
  players.push_back(*player6);
  
  for (unsigned int i = 0; i < 6; i ++){
	in_out.push_back(false);
	launch.push_back(false);
  }
  
  while (!glfwWindowShouldClose(window)){
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    //Pick a coordinate system that makes the most sense to you
    //(left, right, top, bottom)
    mat4 proj = Ortho2D(-20.0, 20.0, -20.0, 20.0);
    
    animate();
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    ball->draw(proj);
	for (unsigned int i = 0; i < 6; i++){
	  players[i].draw(proj);
	}
    //player1->draw(proj);
    //player2->draw(proj);
    //player3->draw(proj);
    //player4->draw(proj);
    //player5->draw(proj);
    //player6->draw(proj);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
	
	for (unsigned int i = 0; i < 6; i ++){
	  Player player = players[i];
	  int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	  if (state == GLFW_PRESS){
		if (in_out[i] == true){
		  player.charge();
		  launch[i] = true;
		  std::cout << "charge" << std::endl;
		}
	  }
	  else if (state == GLFW_RELEASE and launch[i] == true){
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		xpos = xpos/width*40.0 - 20.0;
		ypos = -(ypos/height*40.0 - 20.0);
		vec2 vel = player.release(vec2(xpos, ypos));
		players[i].state.velocity = vel;
		launch[i] = false;
		std::cout << "release" << std::endl;
	  }
	  players[i].update_state();
	}
	
	for (unsigned int i = 0; i < 6; i ++){
	  //std::cout<< i + 1 << ": " << in_out[i]<< std::endl;
	  std::cout << i + 1 << ": " << players[i].state.velocity << ", " << players[i].state.cur_location << std::endl;
	}

	
    
  }
  
  glfwDestroyWindow(window);
  
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
