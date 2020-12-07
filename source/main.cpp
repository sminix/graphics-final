#include "common.h"
//#include "Arrow.hpp"

using namespace Angel;

Ball *ball;

Player *player1;
Player *player2;
Player *player3;
Player *player4;
Player *player5;
Player *player6;

Goal *rgoal;
Goal *bgoal;

Arrow *arrow;

std::vector < Player > players;

unsigned int red_score;
unsigned int blue_score;

std::vector<bool> in_out;
std::vector<bool> launch;

double xpos, ypos;

unsigned int count;


static void error_callback(int error, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}
//if a goal is scored
unsigned int score(char goal){
  if (goal == 'r'){
	red_score += 1;
  }
  if (goal == 'b'){
	blue_score += 1;
  }
  
  std::cout << "Red: " << red_score << " Blue: " << blue_score << std::endl;
  
  if (red_score == 3){
	std::cout <<"RED WINS!!!" << std::endl;
	return 1;
  }
  if (blue_score == 3){
	std::cout <<"BLUE WINS!!!" << std::endl;
	return 1;
  }
  else return 0;
}

bool inside;

//TODO: Inside outside test
//See if the mouse is inside a player
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
  rgoal->gl_init();
  bgoal->gl_init();
  arrow->gl_init();
  
}

//collision functions checks if the current player is colliding with any other player or the ball
unsigned int collision(unsigned int i, Ball ball){
  //get player based on index i
  Player player1 = players[i];
  //go through rest of list
  for (unsigned int j = 0; j < 6 ; j++){
	if (i == j){
	  continue;
	}
	//get second player
	Player player2 = players[j];
	//if the two players are too close, return the index of the player
	if ((abs(player1.state.cur_location.x - player2.state.cur_location.x) < 3.001) and (abs(player1.state.cur_location.y - player2.state.cur_location.y) < 3.001)){
	  return j;
	}
  }
  //if the player and ball are too close, return 10 to represent collision with the ball
  if ((abs(player1.state.cur_location.x - ball.get_loc().x) < 2.51) and (abs(player1.state.cur_location.y - ball.get_loc().y) < 2.51)){
	return 10;
  }
  
  return 100;
}

//Reset the players to there original position
void reset(mat4 proj){
  
  for (unsigned int i = 0; i < 6; i ++){
	Player player = players[i];
	players[i].state.velocity = vec2(0, 0);
	if (i == 0){
	  players[i].set_loc(vec2(-10,-10));
	}
	if (i == 1){
	  players[i].set_loc(vec2(0,-10));
	}
	if (i == 2){
	  players[i].set_loc(vec2(10,-10));
	}
	if (i == 3){
	  players[i].set_loc(vec2(-10, 10));
	}
	if (i == 4){
	  players[i].set_loc(vec2(0,10));
	}
	if (i == 5){
	  players[i].set_loc(vec2(10,10));
	}
  }

  for (unsigned int i = 0; i < 6; i++){
	players[i].draw(proj);
  }
   
}
//Call update function 30 times a second
void animate(){
  if(glfwGetTime() > 0.033){
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
  blue_score = 0;
  red_score = 0;
  
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
  //make players, ball and goals
  player1 = new Player(vec2(-10,-10), 'r');
  player2 = new Player(vec2(0,-10), 'r');
  player3 = new Player(vec2(10,-10), 'r');
  
  player4 = new Player(vec2(-10, 10), 'b');
  player5 = new Player(vec2(0, 10), 'b');
  player6 = new Player(vec2(10, 10), 'b');
  
  rgoal = new Goal(vec2(0,-19));
  bgoal = new Goal(vec2(0,19));
  ball = new Ball();
  
  arrow = new Arrow();
  
  init();
  //add players to players list
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
  unsigned int over = 0;
  count = 0;
  std::cout << "Red: " << red_score << " Blue: " << blue_score << std::endl;
  while (!glfwWindowShouldClose(window)){
	
    animate();
    mat4 proj = Ortho2D(-20.0, 20.0, -20.0, 20.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
	
	rgoal->draw(proj);
	bgoal->draw(proj);
    ball->draw(proj);
	arrow->draw(proj);
	for (unsigned int i = 0; i < 6; i++){
	  players[i].draw(proj);
	}
	
	vec2 ball_loc = ball->get_loc();
	
	if (ball_loc.y >18.1 and ball_loc.x < 5 and ball_loc.x > -5){
	  //reset();
	  ball->set_vel(vec2(0,0));
	  ball->set_loc(vec2 (0,0));
	  ball->draw(proj);
	  reset(proj);
	  over = score('r');
	}
	if (ball_loc.y < - 18.1 and ball_loc.x < 5 and ball_loc.x > -5){
	  ball->set_vel(vec2(0,0));
	  ball->set_loc(vec2 (0,0));
	  ball->draw(proj);
	  reset(proj);
	  over = score('b');
	}
	if (over == 1){
	  glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    //Collision detection check
	for (unsigned int i = 0; i < 6; i++){
	  unsigned int j = collision(i, *ball);
	  //j = 100 when no collision, so check if there is a collision
	  if (j != 100){
		//if the collision is between a player and the ball
		if (j == 10){
		  vec2 dir = normalize(players[i].state.cur_location - ball->get_loc());
		  float power = length(players[i].state.velocity) + length(ball->get_vel());
		  players[i].state.velocity = dir * power / 3;
		  ball->set_vel(-2 * dir * power / 3);
		}
		//if it is a collision between 2 players
		else{
		  vec2 dir = normalize(players[j].state.cur_location - players[i].state.cur_location);
		  float power = length(players[i].state.velocity) + length(players[j].state.velocity);
		  players[i].state.velocity = -dir * power / 2;
		  players[j].state.velocity = dir * power / 2;
		}
	  }
	  
	}
    glfwSwapBuffers(window);
    glfwPollEvents();
	
	//Launching for loop
	for (unsigned int i = 0; i < 6; i ++){
	  //See if another player is primed to launch
	  unsigned int primed = 0;
	  for (unsigned int m = 0; m < 6; m ++){
		if (m != i){
		  //if another player is primed to launch, primed is set to true
		  if (launch[m] == true){
			primed = 1;
			break;
		  }
		  //else, primed is 0
		  else{
			primed = 0;
		  }
		}
	  }
	  
	  Player player = players[i];
	  
	  //get state of the mouse button
	  int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	  //if it is pressed and no other player is primed, prepare launch
	  if (state == GLFW_PRESS and primed == 0){
		if (in_out[i] == true){
		  player.charge();
		  launch[i] = true;
		}
		
		glfwGetCursorPos(window, &xpos, &ypos);
		xpos = xpos/width*40.0 - 20.0;
		ypos = -(ypos/height*40.0 - 20.0);
		
		arrow->update_state(vec2(xpos, ypos), player.state.cur_location);
		 
		
	  }
	  //if the player is ready to launch and the button is released, get mouse coorditates and launch player
	  else if (state == GLFW_RELEASE and launch[i] == true){
		glfwGetCursorPos(window, &xpos, &ypos);
		xpos = xpos/width*40.0 - 20.0;
		ypos = -(ypos/height*40.0 - 20.0);
		vec2 vel = player.release(vec2(xpos, ypos));
		players[i].state.velocity = vel;
		launch[i] = false;
		
		arrow->update_state(vec2(-20,-20), vec2(-20,-20));
		
		
		
	  }
	  
	  
	  players[i].update_state();
	  


	}
	  
  }
    
	
	
  
  glfwDestroyWindow(window);
  
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
