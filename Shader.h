/*
 Copyright (C) 2006 So Yamaoka
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 Modified: Rex West (2015)
 
 */

#ifndef _SHADER_H_
#define _SHADER_H_

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
    #include <OpenGL/glext.h>
#else
    #include "glee.h"
#endif

/*! Handles GLSL shaders.  It can load the code from a file or read straight
 * from a char array. */
class Shader
{
    
private:
    
	char* read(const char *filename);
	void setup(const char *vs, const char *fs);

protected:
    
	GLhandleARB pid;
    static GLhandleARB currentlyBoundShaderID;
    
public:
    
	Shader(const char *vert, const char *frag, bool isFile=true);
	~Shader();
    
	void bind();
	void unbind();
    
	GLhandleARB getPid();
    
	void printLog(const char* tag = "");
    
};

#endif
