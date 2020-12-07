//
//  Arrow.hpp
//  glad
//
//  Created by Samuel Minix on 12/6/20.
//

#ifndef Arrow_hpp
#define Arrow_hpp

#include "common.h"
#include <stdio.h>


class Arrow{

  //Placeholders so everything compiles.  Customize for your ship
  vec2 arrow_vert[7];
  vec3 arrow_color[7];
  
  
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

  Arrow();

  void gl_init();
  
  void draw(mat4 proj);
  
  void update_state(vec2 cur_pos, vec2 player_pos);
  
};

#endif /* Arrow_hpp */
