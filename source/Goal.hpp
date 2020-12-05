//
//  Goal.hpp
//  glad
//
//  Created by Samuel Minix on 12/5/20.
//

#ifndef Goal_hpp
#define Goal_hpp
#include "common.h"
#include <stdio.h>
class Goal{

  //Placeholders so everything compiles.  Customize for your ship
  vec2 goal_vert[6];
  vec3 goal_color[6];
  
  
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

  Goal(vec2 loc);

  void gl_init();
  
  void draw(mat4 proj);
  
};

#endif /* Goal_hpp */
