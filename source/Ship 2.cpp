//
//  Ship.cpp
//  Asteroids
//
//  Created by Brian Summa on 6/5/15.
//
//

#include "common.h"

//Ship constructor
Ship::Ship(){
  //made ship shape and color
  ship_vert[0] = vec2(0.0,0.0);
  ship_vert[1] = vec2(.5,-.5);
  ship_vert[2] = vec2(0,1);
  ship_vert[3] = vec2(-.5, -.5);
  ship_vert[4] = vec2(0.0,0.0);
  //flames on end of ship
  ship_vert[5] = vec2(0.0, 0.0);
  ship_vert[6] = vec2(0.25, -3.0);
  ship_vert[7] = vec2(0, -2.0);
  ship_vert[8] = vec2(-0.25, -3.0);
  ship_vert[9] = vec2(0.0, 0.0);
  
  ship_color[0] = vec3(1,1,1);
  ship_color[1] = vec3(1,1,1);
  ship_color[2] = vec3(1,1,1);
  ship_color[3] = vec3(1,1,1);
  ship_color[4] = vec3(1,1,1);
  //flames on end of ship
  ship_color[5] = vec3(1,0,0);
  ship_color[6] = vec3(1,0,0);
  ship_color[7] = vec3(1,0,0);
  ship_color[8] = vec3(1,0,0);
  ship_color[9] = vec3(1,0,0);
  
  state.cur_location = (0.0,0.0);
  state.angle = 0;
  state.pointing = (0.0,1.0);
  state.thruster_on = false;
  state.velocity = (0.0, 0.0);
  state.acceleration = (0.0, 0.0);
};

//Called everytime an animation tick happens
void Ship::update_state(){
  
  // Create a vertex array object
  glGenVertexArrays( 1, &GLvars.vao );
  //Set GL state to use vertex array object
  glBindVertexArray( GLvars.vao );
  
  //Generate buffer to hold our vertex data
  glGenBuffers( 1, &GLvars.buffer );
  //Set GL state to use this buffer
  glBindBuffer( GL_ARRAY_BUFFER, GLvars.buffer );
  
  //Create GPU buffer to hold vertices and color
  glBufferData( GL_ARRAY_BUFFER, sizeof(ship_vert) + sizeof(ship_color), NULL, GL_STATIC_DRAW );
  //First part of array holds vertices
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(ship_vert), ship_vert );
  //Second part of array hold colors (offset by sizeof(triangle))
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(ship_vert), sizeof(ship_color), ship_color );
  
  glEnableVertexAttribArray(GLvars.vpos_location);
  glEnableVertexAttribArray(GLvars.vcolor_location );
  
  glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(ship_vert)) );
  
  glBindVertexArray(0);
  
  if (state.thruster_on){
    state.acceleration.x = state.pointing.x * _ACC;
    state.acceleration.y = state.pointing.y * _ACC;
	
    state.velocity.x += state.acceleration.x * 0.033;
    state.velocity.y += state.acceleration.y * 0.033; //0.033 is the dt
  }
  else {
    //how much to dampen the velocity here?
	state.acceleration.x = 0;
	state.acceleration.y = 0;
	state.velocity.x *= _DAMPING;
	state.velocity.y *= _DAMPING;
  }
  //limit the velocity
  //need to use pythagorean theorem here? What to set velocity to in this case?
  //bc need x and y component
  if (state.velocity.x > _MAX_SPEED) {state.velocity.x = _MAX_SPEED;}
  if (state.velocity.y > _MAX_SPEED) {state.velocity.y = _MAX_SPEED;}
  
  //decrease velocity so that on change of direction, the original
  //acceleration is still decreasing
  //maybe dampen the velocity no matter what here???
  //state.acceleration.x -= 1;
  //state.acceleration.y -= 1;
  
  //update vertices so buffer can draw ship in new location
  for (unsigned int i = 0; i < sizeof(ship_vert)/sizeof(ship_vert[0]); i++){
    ship_vert[i].x = ship_vert[i].x + (state.velocity.x * 0.033);
    ship_vert[i].y = ship_vert[i].y +(state.velocity.y * 0.033);
  }
  
  //update ship location
  state.cur_location.x += state.velocity.x * 0.033;
  state.cur_location.y += state.velocity.y * 0.033;
  
  //detecting if ship moves beyond boundaries and flipping ship to other side
  if (state.cur_location.x > 19.5){
	state.cur_location.x *= -1;
	for (int i = 0; i < sizeof(ship_vert)/sizeof(ship_vert[0]); i++){
	  ship_vert[i].x -= 40;
	}
  }
  
  else if (state.cur_location.x < -19.5){
	state.cur_location.x *= -1;
	for (int i = 0; i < sizeof(ship_vert)/sizeof(ship_vert[0]); i++){
	  ship_vert[i].x += 40;
	}
  }
  
  if (state.cur_location.y > 19.5){
	state.cur_location.y *= -1;
	for (int i = 0; i < sizeof(ship_vert)/sizeof(ship_vert[0]); i++){
	  ship_vert[i].y -= 40;
	}
  }
  else if (state.cur_location.y < -19.5){
	state.cur_location.y *= -1;
	for (int i = 0; i < sizeof(ship_vert)/sizeof(ship_vert[0]); i++){
	  ship_vert[i].y += 40;
	}
  }
  
  // Things to do:
  //a = F
  //Force is in the direction the ship is pointing
  //Clamp acceleration at some maximum value
  
  //v  = old_velocity + a*dt
  // clamp velocity at a maximum value
  // Dampen the velocity at every timestep to lessen intertia

  //p  = old_position + v*dt
  // Wrap the ship position when at the boundary

}

//Initialize the gl state and variables
void Ship::gl_init(){
  
  std::string vshader = shader_path + "vshader_Ship.glsl";
  std::string fshader = shader_path + "fshader_Ship.glsl";
  
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
  
  glBindFragDataLocation(GLvars.program, 0, "fragColor");
  
  GLvars.vpos_location   = glGetAttribLocation(GLvars.program, "vPos");
  GLvars.vcolor_location = glGetAttribLocation(GLvars.program, "vColor" );
  GLvars.M_location = glGetUniformLocation(GLvars.program, "M" );
  
  // Create a vertex array object
  glGenVertexArrays( 1, &GLvars.vao );
  //Set GL state to use vertex array object
  glBindVertexArray( GLvars.vao );
  
  //Generate buffer to hold our vertex data
  glGenBuffers( 1, &GLvars.buffer );
  //Set GL state to use this buffer
  glBindBuffer( GL_ARRAY_BUFFER, GLvars.buffer );
  
  //Create GPU buffer to hold vertices and color
  glBufferData( GL_ARRAY_BUFFER, sizeof(ship_vert) + sizeof(ship_color), NULL, GL_STATIC_DRAW );
  //First part of array holds vertices
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(ship_vert), ship_vert );
  //Second part of array hold colors (offset by sizeof(triangle))
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(ship_vert), sizeof(ship_color), ship_color );
  
  glEnableVertexAttribArray(GLvars.vpos_location);
  glEnableVertexAttribArray(GLvars.vcolor_location );
  
  glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(ship_vert)) );
  
  glBindVertexArray(GLvars.vao);

}

//Draw a ship
void Ship::draw(mat4 proj){
  
  glUseProgram( GLvars.program );
  glBindVertexArray( GLvars.vao );
  
  //If you have a modelview matrix, pass it with proj
  glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, proj );
  
  //Draw something
  glDrawArrays(GL_LINE_LOOP, 0, 5);
  
  if(state.thruster_on){
    //Maybe draw something different if the thruster is on
    glDrawArrays(GL_TRIANGLES, 5, 3);
    glDrawArrays(GL_TRIANGLES, 7, 3);
    
  }
  
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(ship_vert), ship_vert );
  
  glBindVertexArray(0);
  glUseProgram(0);

}


