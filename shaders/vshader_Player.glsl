//
//  vshader_Player.cpp
//  glad
//
//  Created by Gabriel Harris on 12/2/20.
//

#version 150

in vec4 vPosP;
in vec4 vColorP;
out vec4 colorP;

uniform mat4 MP;


void
main()
{
  gl_Position = MP*vPosP;
  colorP = vColorP;
}
