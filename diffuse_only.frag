#version 120
#extension GL_EXT_gpu_shader4 : enable

varying vec4 position;
varying vec3 normal;
varying vec4 objPos;
uniform float waterLevel;
uniform float maxHeight;

void main()
{
    //Declare variables for intermediate calculations
    vec4 finalColor;
    vec3 lightDir;
	vec3 diffuseColor;
	vec3 ambientColor;
    float attenuation;
    float distance;
    
    //Declare and initialize variables for storing lighting results
    vec3 finalLighting = vec3(gl_FrontMaterial.emission);
    vec3 ambientReflection = vec3(0.0,0.0,0.0);
    vec3 diffuseReflection = vec3(0.0,0.0,0.0);
    
    //Loop through all 8 lights that the OpenGL fixed function pipeline supports
    for (int i = 0; i < 1; ++i)
    {
        //Calculate the light direction
        lightDir = gl_LightSource[i].position.xyz - position.xyz;
        
        //Add the ambient light factor to the ambient accumulator
        //ambientReflection += vec3(gl_FrontMaterial.ambient) * vec3(gl_LightSource[i].ambient);

		float distance = maxHeight - waterLevel;

		if(objPos.y <= waterLevel)	//water
		{
			diffuseColor = vec3(0, 0, 1);
			ambientColor = vec3(0, 0, 1);
		}

		else if(objPos.y <= distance / 13 + waterLevel)	//sand
		{
			diffuseColor = vec3(1, 1, .3);
			ambientColor = vec3(1, 1, .3);
		}

		else if(objPos.y <= distance / 10 * 3 + waterLevel)	//grass
		{
			diffuseColor = vec3(.2, .6, 0);
			ambientColor = vec3(.2, .6, 0);
		}

		else if(objPos.y <= distance * .8 + waterLevel)	//rock
		{
			diffuseColor = vec3(.5, .5, .5);
			ambientColor = vec3(.5, .5, .5);
		}

		else	//snow
		{
			diffuseColor = vec3(1, 1, 1);
			ambientColor = vec3(1, 1, 1);
		}

		ambientReflection += ambientColor * vec3(gl_LightSource[i].ambient);
        
        //If the light is behind the surface, continue
        if(dot(normal, lightDir) < 0.0)
            continue;
        
        //Set the default attenuation to none (by the multiplicative identity, this is 1.0)
        attenuation = 1.0;
        
        //If the light is not a directional light, then apply the appropriate attenuation
        if (0.0 != gl_LightSource[i].position.w)
        {
            distance = length(lightDir);
            attenuation = 1.0 / (gl_LightSource[i].constantAttenuation
                                 + gl_LightSource[i].linearAttenuation * distance
                                 + gl_LightSource[i].quadraticAttenuation * distance * distance);
        }
        
        //Calculate the diffuse reflectance and add it to the diffuse accumulator
        //diffuseReflection += attenuation * vec3(gl_LightSource[i].diffuse) * vec3(gl_FrontMaterial.diffuse) * max(0.0, dot(normal, normalize(lightDir)));
		diffuseReflection += attenuation * vec3(gl_LightSource[i].diffuse) * diffuseColor * max(0.0, dot(normal, normalize(lightDir)));
    }
    
    //Sum all of the lighting together
    finalLighting = finalLighting + ambientReflection + diffuseReflection;
    
    //Return the final lighting
    gl_FragColor = vec4(finalLighting, 1.0);
}