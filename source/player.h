//
//  player.hpp
//  glad
//
//  Created by Gabriel Harris on 12/2/20.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include "common.h"
#include "Arrow.hpp"

#define _MAX_SPEED 10
#define _DAMPING 0.98
#define _ACC 3
#define _ROT 15

class Player{
public:
  Player(vec2 loc, char team);

  //Placeholders so everything compiles.  Customize for your ship
  vec2 player_vert[20];
  vec3 player_color[20];
  
  //Record of the ship's state
  struct {
    vec2 cur_location;   //Current position of the center
    float angle;         //Rotation angle
    vec2 pointing;       //Vector pointing to the front of the ship
	bool charging;
    //This function will be helpful to keep track of the direction the ship
    //is pointing
    mat2 RotateZ2D( const GLfloat theta ){
      GLfloat angle = DegreesToRadians * theta;
      mat2 c;
      c[0][0] = c[1][1] = cos(angle);
      c[1][0] = sin(angle);
      c[0][1] = -c[1][0];
      return c;
    }
    vec2 acceleration;   //Acceleration
    vec2 velocity;       //Velocity
    //bool thruster_on;    //Boolean if a thruster is on
    char team;
  } state;
  
  //OpenGL variables for a ship
  struct {
    GLuint vao;           //Vertex array object
    GLuint program;       //shader program
    GLuint buffer;        //Vertex buffer objects
    GLuint vertex_shader, fragment_shader;  //Shaders
    GLint vpos_location, vcolor_location;   //reference to pos and color in shaders
    GLint M_location;     //Reference to matrix in shader
  } GLvars;

  
public:
  

  Player();
  void charge();
  vec2 release(vec2 cur_pos);
  void set_loc(vec2 loc);
	
  //inline void start_thruster(){ state.thruster_on= true;}
  //inline void stop_thruster() { state.thruster_on= false;}
  /*
  inline void rotateLeft() {
    state.angle+=_ROT;
    mat2 c = state.RotateZ2D(state.angle);
    mat2 d = state.RotateZ2D(_ROT);
    for (unsigned int i = 0; i < sizeof(ball_vert)/sizeof(ball_vert[0]); i++){
      ball_vert[i] = (d * (ball_vert[i] - state.cur_location)) + state.cur_location;
    }
    state.pointing = normalize(c * vec2(0,1));
    
  }
  inline void rotateRight(){
    state.angle-=_ROT;
    mat2 d = state.RotateZ2D(-1 * _ROT);
    mat2 c = state.RotateZ2D(state.angle);
    for (unsigned int i = 0; i < sizeof(ball_vert)/sizeof(ball_vert[0]); i++){
      ball_vert[i] = (d * (ball_vert[i] - state.cur_location)) + state.cur_location;
    }
    state.pointing = normalize(c * vec2(0, 1));
  }
   */
    
  void update_state();
  
  void gl_init();
  
  void draw(mat4 proj);
  
};


//#endif /* defined(__Asteroids__Ship__) */


#endif /* player_hpp */
