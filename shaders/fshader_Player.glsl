//
//  fshader_Player.cpp
//  glad
//
//  Created by Gabriel Harris on 12/2/20.
//

#version 150

in  vec4 colorP;
out vec4 fragColorP;

void
main()
{
  fragColorP = colorP;
}
