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
	
	float xmax = player.player_vert[0].x;
	float xmin = player.player_vert[0].x;
	float ymax = player.player_vert[0].y;
	float ymin = player.player_vert[0].y;
	
	for (unsigned int j = 1; j<20; j++){
	  float x = player.player_vert[j].x;
	  float y = player.player_vert[j].y;
	  
	  if (x > xmax){
		xmax = x;
	  }
	  if (x < xmin){
		xmin = x;
	  }
	  if (y > ymax){
		ymax = y;
	  }
	  if (y < ymin){
		ymin = y;
	  }
	}
	std::cout << xmax << " " << xmin << " " << ymax << " " <<  ymin << std::endl;
	std::cout << point.x << " " << point.y << std::endl;
	if (point.x < xmax and point.x > xmin and point.y < ymax and point.y > ymin){
	  in_out[i] = true;
	}
	else {
	  in_out[i] = false;
	}
	
	/*
	int counter = 0;
	
	for (unsigned int j = 1; j < 20; j++){

	  //create p1 and p2
	  vec2 tail = player.player_vert[j];
	  //std::cout << p1 << std::endl;
	  vec2 head;
	  if (j+1 >= 19){
		head = player.player_vert[1];
	  }
	  else{
		head = player.player_vert[j+1];
	  }
	  
	  if (tail.y < head.y){
		std::swap(head,tail);
	  }
	  //horizontal test
	  if (tail.y-head.y ==0){
		continue;
	  }
	  
	  if (point.y < head.y and point.y < tail.y){
		continue;
	  }
	  if (point.y > head.y and point.y > tail.y){
		continue;
	  }
	  
	  float cross_prod = ((tail.x - head.x) * (point.y - head.y)) - ((tail.y - head.y) * (point.x - head.x));
	  //std::cout << "Cross Prod: " << cross_prod << std::endl;
	  
	  if (cross_prod > 0){
		counter +=1;
	  }
	  //else{
		//inside = false;
		//break;
	  //}
	}
	  
	//std::cout << "End"<< std::endl;
	if (counter % 2==0){
	  inside = false;
	}
	
	else{
	  inside = true;
	}
  
	in_out[i] = inside;
	 */
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
  if(glfwGetTime() > 0.033){
    glfwSetTime(0.0);
    ball->update_state();
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
    player1->draw(proj);
    player2->draw(proj);
    player3->draw(proj);
    player4->draw(proj);
    player5->draw(proj);
    player6->draw(proj);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
	
	for (unsigned int i = 0; i < 6; i ++){
	  std::cout << i + 1 <<  ": " << in_out[i] << std::endl;
	}
	
	std::cout << " " << std::endl;
	
    
  }
  
  glfwDestroyWindow(window);
  
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
