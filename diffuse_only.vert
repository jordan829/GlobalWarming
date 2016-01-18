#version 120

varying vec4 position;
varying vec3 normal;
varying vec4 objPos;
uniform float waterLevel;

void main()
{
    //Transform the normal into world coordinates
    normal = normalize(gl_NormalMatrix * gl_Normal);
    
	objPos = gl_Vertex;
	position = gl_Vertex;

	if (position.y <= waterLevel)
	{
		position.y = waterLevel;
		normal = vec3(0,1,0);
	}

    //Transform the vertex into world coordinates
    position = gl_ModelViewMatrix * position;
    
    //Set the gl position of this vertex
    gl_Position = gl_ProjectionMatrix * position;
}