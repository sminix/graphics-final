//
//  Goal.cpp
//  glad
//
//  Created by Samuel Minix on 12/5/20.
//

#include "Goal.hpp"

Goal::Goal(vec2 loc){
  //made player shape and color
  goal_vert[0] = loc;
  goal_vert[1] = vec2(loc.x - 5, loc.y + 2);
  goal_vert[2] = vec2(loc.x + 5, loc.y + 2);
  goal_vert[3] = vec2(loc.x + 5, loc.y - 2);
  goal_vert[4] = vec2(loc.x - 5, loc.y - 2);
  goal_vert[5] = vec2(loc.x - 5, loc.y + 2);
  
  goal_color[0] = vec3(1.0,1.0,1.0);
  goal_color[1] = vec3(1.0,1.0,1.0);
  goal_color[2] = vec3(1.0,1.0,1.0);
  goal_color[3] = vec3(1.0,1.0,1.0);
  goal_color[4] = vec3(1.0,1.0,1.0);
  goal_color[5] = vec3(1.0,1.0,1.0);
}

void Goal::gl_init(){
  
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
  glBufferData( GL_ARRAY_BUFFER, sizeof(goal_vert) + sizeof(goal_color), NULL, GL_STATIC_DRAW );
  //First part of array holds vertices
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(goal_vert), goal_vert );
  //Second part of array hold colors (offset by sizeof(triangle))
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(goal_vert), sizeof(goal_color), goal_color );
  
  glEnableVertexAttribArray(GLvars.vpos_location);
  glEnableVertexAttribArray(GLvars.vcolor_location );
  
  glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(goal_vert)) );
  
  glBindVertexArray(0);

}

void Goal::draw(mat4 proj){
  
  glUseProgram( GLvars.program );
  glBindVertexArray( GLvars.vao );
  glBindBuffer( GL_ARRAY_BUFFER, GLvars.buffer );
  
  //If you have a modelview matrix, pass it with proj
  glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, proj );
  
  //Draw something
  glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
  /*
  if(state.thruster_on){
    //Maybe draw something different if the thruster is on
    glDrawArrays(GL_TRIANGLES, 5, 3);
    glDrawArrays(GL_TRIANGLES, 7, 3);
    
  }
   */
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(goal_vert), goal_vert );
  
  glBindVertexArray(0);
  glUseProgram(0);

}
