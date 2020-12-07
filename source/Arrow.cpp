//
//  Arrow.cpp
//  glad
//
//  Created by Samuel Minix on 12/6/20.
//

#include "Arrow.hpp"
#include "common.h"
Arrow::Arrow(){
  //made arrow shape and color
  
  arrow_vert[0] = vec2(-20.0, -20.0);
  arrow_vert[1] = vec2(-20.0, -20.0);
  arrow_vert[2] = vec2(-20.0, -20.0);

  
  arrow_color[0] = vec3(0.0,0.0,0.0);
  arrow_color[1] = vec3(0.0,0.0,0.0);
  arrow_color[2] = vec3(0.0,0.0,0.0);
  
};

void Arrow::gl_init(){
  
  std::string vshader = shader_path + "vshader_Player.glsl";
  std::string fshader = shader_path + "fshader_Player.glsl";
  
  GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
  GLchar* fragment_shader_source = readShaderSource(fshader.c_str());
  
  GLvars.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(GLvars.vertex_shader, 1, (const GLchar**) &vertex_shader_source, NULL);
  glCompileShader(GLvars.vertex_shader);
  check_shader_compilation(vshader, GLvars.vertex_shader);
  
  GLvars.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(GLvars.fragment_shader, 1, (const GLchar**) &fragment_shader_source, NULL);
  glCompileShader(GLvars.fragment_shader);
  check_shader_compilation(fshader, GLvars.fragment_shader);
  
  GLvars.program = glCreateProgram();
  glAttachShader(GLvars.program, GLvars.vertex_shader);
  glAttachShader(GLvars.program, GLvars.fragment_shader);
  
  glLinkProgram(GLvars.program);
  check_program_link(GLvars.program);
  
  glBindFragDataLocation(GLvars.program, 0, "fragColorP");
  
  GLvars.vpos_location   = glGetAttribLocation(GLvars.program, "vPosP");
  GLvars.vcolor_location = glGetAttribLocation(GLvars.program, "vColorP" );
  GLvars.M_location = glGetUniformLocation(GLvars.program, "MP" );
  
  // Create a vertex array object
  glGenVertexArrays( 1, &GLvars.vao );
  //Set GL state to use vertex array object
  glBindVertexArray( GLvars.vao );
  
  //Generate buffer to hold our vertex data
  glGenBuffers( 1, &GLvars.buffer );
  //Set GL state to use this buffer
  glBindBuffer( GL_ARRAY_BUFFER, GLvars.buffer );
  
  //Create GPU buffer to hold vertices and color
  glBufferData( GL_ARRAY_BUFFER, sizeof(arrow_vert) + sizeof(arrow_color), NULL, GL_STATIC_DRAW );
  //First part of array holds vertices
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(arrow_vert), arrow_vert );
  //Second part of array hold colors (offset by sizeof(triangle))
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(arrow_vert), sizeof(arrow_color), arrow_color );
  
  glEnableVertexAttribArray(GLvars.vpos_location);
  glEnableVertexAttribArray(GLvars.vcolor_location );
  
  glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(arrow_vert)) );
  
  glBindVertexArray(0);

}

void Arrow::draw(mat4 proj){
  
  glUseProgram( GLvars.program );
  glBindVertexArray( GLvars.vao );
  glBindBuffer( GL_ARRAY_BUFFER, GLvars.buffer );
  
  //If you have a modelview matrix, pass it with proj
  glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, proj );
  
  //Draw something
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(arrow_vert), arrow_vert );
  
  glBindVertexArray(0);
  glUseProgram(0);

}

void Arrow::update_state(vec2 cur_pos, vec2 player_pos){
  vec2 dir = vec2(0.0,0.0);
  
  vec2 diff = player_pos - cur_pos;
  
  if (diff.x != 0 or diff.y != 0){
	dir = normalize(diff);
  }
  float theta = atan(dir.y/dir.x);

  arrow_vert[0] = vec2(player_pos.x + (3 * dir.x), player_pos.y + (3 * dir.y));
  arrow_vert[1] = vec2(player_pos.x + (.5*cos(theta - M_PI/2 )), player_pos.y + (.5*sin(theta - M_PI/2)));
  arrow_vert[2] = vec2(player_pos.x + (.5*cos(theta + M_PI/2)), player_pos.y + (.5*sin(theta + M_PI/2)));
  /*
  if (length(diff) < 1.5){
	arrow_color[0] = vec3(0,1.0,0);
	arrow_color[1] = vec3(0,1.0,0);
	arrow_color[2] = vec3(0,1.0,0);
  }
  
  else if (length(diff) < 3){
	arrow_color[0] = vec3(0,1.0,0);
	arrow_color[1] = vec3(0,1.0,0);
	arrow_color[2] = vec3(0,1.0,0);
  }
  else if (length(diff) < 4.5){
	arrow_color[0] = vec3(0.9,0.8,0.1);
	arrow_color[1] = vec3(0.9,0.8,0.1);
	arrow_color[2] = vec3(0.9,0.8,0.1);
  }
   
  else{
	arrow_color[0] = vec3(1.0,0.0,0.0);
	arrow_color[1] = vec3(1.0,0.0,0.0);
	arrow_color[2] = vec3(1.0,0.0,0.0);
  }
   */
  //std::cout<<arrow_color[1]<<std::endl;
}
