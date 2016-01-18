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

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "Shader.h"

GLhandleARB Shader::currentlyBoundShaderID = 0x0;

Shader::Shader(const char *vert, const char *frag, bool isFile)
{
	if(isFile)
	{
        //Read in the vertex and fragment shaders
        //We must delete these after we are finished compiling the shaders
		char* vv = read(vert);
		char* vf = read(frag);
        
        //Setup the shader
		setup(vv, vf);
        
        //Delete the file data arrays we allocted
		delete[] vv;
		delete[] vf;
	}
	else
    {
        //Treat the vert and frag parameters as shader code and directly compile them
		setup(vert, frag);
    }
}

Shader::~Shader()
{
	glDeleteObjectARB(pid);
}

void Shader::bind()
{
    if(currentlyBoundShaderID != pid)
    {
        currentlyBoundShaderID = pid;
        glUseProgramObjectARB(pid);
    }
}

void Shader::unbind()
{
    if(currentlyBoundShaderID != /*(void*)*/(0x0))
    {
        currentlyBoundShaderID = /*(void*)*/(0x0);
        glUseProgramObjectARB(0);
    }
}

void Shader::printLog(const char* tag)
{
	char glslLog[1024];
	GLsizei glslLogSize;
    
    //Extract the error log for this shader's pid
	glGetInfoLogARB(pid, 1024, &glslLogSize, glslLog);
    
    //If the log isn't empty, print the contents
	if(glslLogSize > 0)
        std::cerr << tag << "(" << pid << ") -  Shader error log:" << std::endl << glslLog << std::endl;
	else
        std::cerr << tag << "(" << pid << ") -  Shaders compiled successfully!" << std::endl;
}

char* Shader::read(const char *filename)
{
	char* shaderFile = 0;
	
    //Open the file
	FILE* fp = fopen(filename, "rb");
	if(!fp)
    {
        std::cerr << "File doesn't exist [" << filename << "]" << std::endl;
        std::exit(-1);
    }
    
	//Obtain the file size
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	rewind(fp);
    
	//Alloc memory - will be deleted while setting the shader up
	shaderFile = new char[size+1];
    
	//Copy the file to the shaderFile
	fread(shaderFile, sizeof(char), size, fp);
	shaderFile[size]='\0'; //Eliminate the garbage at EOF
	fclose(fp);
    
	return shaderFile;
}

void Shader::setup(const char *vs, const char *fs)
{
    //Create two new Shader Object IDs
	GLhandleARB vid = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	GLhandleARB fid = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	
    //Pass the shader source code to OpenGL
	glShaderSourceARB(vid, 1, &vs, 0);
	glShaderSourceARB(fid, 1, &fs, 0);
	
    //Compile the shader files
	glCompileShaderARB(vid);
	glCompileShaderARB(fid);
    
	char glslLog[1024];
	GLsizei glslLogSize;
    
    //Get the error log for the Vertex shader
	glGetInfoLogARB(vid, 1024, &glslLogSize, glslLog);
	if (glslLogSize)
		std::cerr << "Vertex program log: " << glslLog << std::endl;
    
    //Get the error log for the Fragment shader
	glGetInfoLogARB(fid, 1024, &glslLogSize, glslLog);
	if (glslLogSize)
		std::cerr << "Fragment program log: " << glslLog << std::endl;
    
    //Create a new Shader Program
	pid = glCreateProgramObjectARB();
    
    //Attach the Vertex and Fragment shaders to the Shader Program
	glAttachObjectARB(pid, vid);
	glAttachObjectARB(pid, fid);
    
	//Delete shader objects since they have been attached to a program
	glDeleteObjectARB(vid);
	glDeleteObjectARB(fid);
	
	//Link it!
	glLinkProgramARB(pid);
}

GLhandleARB Shader::getPid()
{
	return pid;
}
