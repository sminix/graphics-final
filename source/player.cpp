//
//  player.cpp
//  glad
//
//  Created by Gabriel Harris on 12/2/20.
//

#include "player.h"
#include "common.h"
//#class player;

Player::Player(vec2 loc, char team){
  //made player shape and color
  player_vert[0] = loc;
  for (unsigned int i = 0; i <= 18; i ++){
	player_vert[i+1] = vec2(1.5*cos((20 * i)*(3.1415/180)) + loc.x, 1.5*sin((20 * i)*(3.1415/180)) + loc.y);
  }
  if(team == 'r'){
    player_color[0] = vec3(1,0,0);
    for (unsigned int i = 0; i <=18; i++){
      player_color[i+1] = vec3(1,0,0);
    }
  }
  
  else{
    player_color[0] = vec3(0,0,1);
    for (unsigned int i = 0; i <=18; i++){
      player_color[i+1] = vec3(0,0,1);
    }
  }

  state.cur_location = loc;
  state.angle = 0;
  state.pointing = vec2(0.0,1.0);
  state.velocity = vec2(0.0, 0.0);
  state.acceleration = vec2(0.0, 0.0);
  state.team = team;
};

void Player::set_loc(vec2 loc){
  state.cur_location = loc;
  player_vert[0] = loc;
  for (unsigned int i = 0; i <= 18; i ++){
	player_vert[i+1] = vec2(1.5*cos((20 * i)*(3.1415/180)) + loc.x, 1.5*sin((20 * i)*(3.1415/180)) + loc.y);
  }
}
void Player::gl_init(){
  
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
  glBufferData( GL_ARRAY_BUFFER, sizeof(player_vert) + sizeof(player_color), NULL, GL_STATIC_DRAW );
  //First part of array holds vertices
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(player_vert), player_vert );
  //Second part of array hold colors (offset by sizeof(triangle))
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(player_vert), sizeof(player_color), player_color );
  
  glEnableVertexAttribArray(GLvars.vpos_location);
  glEnableVertexAttribArray(GLvars.vcolor_location );
  
  glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(player_vert)) );
  
  glBindVertexArray(0);

}

vec2 Player::release(vec2 cur_pos){
  vec2 head = state.cur_location;
  vec2 tail = cur_pos;
  state.charging= false;
  return 2 * (head - tail);
  /*
  arrow.update_state(vec2(-20, -20), vec2(-20,-20));
  player_vert[0] = state.cur_location + (vel * 0.033);
  for (unsigned int i = 1; i < 20; i ++){
	player_vert[i] = player_vert[i] + (vel * 0.033);
  }
   */
  
  
}

void Player::charge(){
  state.charging= true;
  
  
}


void Player::update_state(){

  state.velocity.x *= .99;
  state.velocity.y *= .99;
  
  if (abs(state.velocity.x) < .1 and abs(state.velocity.y) < .1){
	state.velocity.x = 0;
	state.velocity.y = 0;
  }
  
  //update vertices so buffer can draw ship in new location
  for (unsigned int i = 0; i < 20; i++){
    player_vert[i].x = player_vert[i].x + (state.velocity.x * 0.033);
    player_vert[i].y = player_vert[i].y +(state.velocity.y * 0.033);
  }
  
  //update ship location
  state.cur_location.x += state.velocity.x * 0.033;
  state.cur_location.y += state.velocity.y * 0.033;
  
  //detecting if player moves into the boundaries, reverse velocity
  if (state.cur_location.x > 18 or state.cur_location.x < -18){
	state.velocity.x *= -1;
  }
  
  
  if (state.cur_location.y > 18 or state.cur_location.y < -18){
	state.velocity.y *= -1;
  }
  
}

void Player::draw(mat4 proj){
  
  glUseProgram( GLvars.program );
  glBindVertexArray( GLvars.vao );
  glBindBuffer( GL_ARRAY_BUFFER, GLvars.buffer );
  
  //If you have a modelview matrix, pass it with proj
  glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, proj );
  
  //Draw something
  glDrawArrays(GL_TRIANGLE_FAN, 0, 20);

  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(player_vert), player_vert );
  
  glBindVertexArray(0);
  glUseProgram(0);

}
