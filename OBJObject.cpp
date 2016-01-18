#include "OBJObject.h"
#include "glee.h"
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include <sstream>
#include <fstream>
#include <string.h>
using namespace std;

#define deleteVector(__vect__) do {\
                                   iter = __vect__->begin();\
                                   end = __vect__->end();\
                                   while(iter != end) delete (*(iter++));\
                                   delete __vect__;\
                               } while(false)


OBJObject::OBJObject(/*std::string filename*/) : Drawable()
{
    this->vertices = new std::vector<Vector3*>();
    this->normals = new std::vector<Vector3*>();
    this->texcoords = new std::vector<Vector3*>();
    this->faces = new std::vector<Face*>();
    
    //parse(filename);
}

OBJObject::~OBJObject()
{
    //Delete any dynamically allocated memory/objects here
    std::vector<Vector3*>::iterator iter;
    std::vector<Vector3*>::iterator end;
    
    deleteVector(vertices);
    deleteVector(normals);
    deleteVector(texcoords);
    
    delete faces;
}

void OBJObject::draw(DrawData& data)
{
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    glBegin(GL_TRIANGLES);
    
    
    //Loop through the faces
    //For each face:
    //  Look up the vertices, normals (if they exists), and texcoords (if they exist)
    //  Draw them as triplets:
    
    //      glTex(texcoords->at(face.ts[0]))
    //      glNorm(normals->at(face.ns[0]))
    //      glVert(vertices->at(face.vs[0]))
    //      Etc.
    //

	//Set color
	//glColor3f(.75, .75, .75);
	glColor3f(1, 1, 1);

	Face* face;
	
	for (int i = 0; i < face_num; i++)
	{
		face = faces->at(i);

		for (int j = 0; j < 3; j++)
		{
			//Set normals
			Vector3 normal = *normals->at(face->ns[j] - 1);
			float xn = normal[0];
			float yn = normal[1];
			float zn = normal[2];
			glNormal3f(xn, yn, zn);
			
			//Set vectors
			Vector3 vertex = *vertices->at(face->vs[j] - 1);
			float xv = vertex[0];
			float yv = vertex[1];
			float zv = vertex[2];
			glVertex3f(xv, yv, zv);

			//Set textures (not yet)
			//Vector3 texture = *texcoords->at(face.ts[j]);
			//float stuff
			//glTex thingy
		}
	}
    
    glEnd();
    
    glPopMatrix();
}

void OBJObject::myDraw(DrawData& data, bool mode)
{
	Face* face;
	Vector3 temp, temp1, temp2;

	if (!mode)
	{
		for (int i = 0; i < face_num; i++)
		{
			face = faces->at(i);

			for (int j = 0; j < 3; j++)
			{
				Vector3 vertex = *vertices->at(face->vs[j] - 1);
				float xv = vertex[0];
				float yv = vertex[1];
				float zv = vertex[2];
				temp = Vector3(xv, yv, zv);
				Globals::rasterizer->rasterize1Vertex(temp.toVector4(1), 1, 1, 1);
			}
		}
	}

	else
	{
		int color1 = 1;

		for (int i = 0; i < face_num; i++)
		{
			face = faces->at(i);

			Vector3 vertex = *vertices->at(face->vs[0] - 1);
			float xv = vertex[0];
			float yv = vertex[1];
			float zv = vertex[2];
			temp = Vector3(xv, yv, zv);

			Vector3 vertex1 = *vertices->at(face->vs[1] - 1);
			xv = vertex1[0];
			yv = vertex1[1];
			zv = vertex1[2];
			temp1 = Vector3(xv, yv, zv);

			Vector3 vertex2 = *vertices->at(face->vs[2] - 1);
			xv = vertex2[0];
			yv = vertex2[1];
			zv = vertex2[2];
			temp2 = Vector3(xv, yv, zv);

			if (Globals::interp)
			{
				Color color = Color((*normals->at(face->ns[0] - 1))[0], (*normals->at(face->ns[0] - 1))[1], (*normals->at(face->ns[0] - 1))[2]);
				Globals::rasterizer->rasterizeVertices(temp.toVector4(1), temp1.toVector4(1), temp2.toVector4(1), color[0], color[1], color[2]);
			}

			else
			{
				if (color1 == 1)
					Globals::rasterizer->rasterizeVertices(temp.toVector4(1), temp1.toVector4(1), temp2.toVector4(1), 1, 0, 0);
				if (color1 == 2)
					Globals::rasterizer->rasterizeVertices(temp.toVector4(1), temp1.toVector4(1), temp2.toVector4(1), 0, 1, 0);
				if (color1 == 3)
					Globals::rasterizer->rasterizeVertices(temp.toVector4(1), temp1.toVector4(1), temp2.toVector4(1), 0, 0, 1);

				if (color1 == 3)
					color1 = 1;
				else
					color1++;
			}
		}
	}
}
void OBJObject::update(UpdateData& data)
{
    //
}

void OBJObject::parse(std::string& filename)
{
    std::ifstream infile(filename);
    std::string line;
    std::vector<std::string> tokens;
    std::string token;
	std::vector<std::string> faceVals;
    
    int lineNum = 0;
    
    
    std::cout << "Starting parse..." << std::endl;
    
    //While all your lines are belong to us
    while (std::getline(infile, line))
    {
        //Progress
        if(++lineNum % 10000 == 0)
            std::cout << "At line " << lineNum << std::endl;

		if (line.empty())
			continue;
        
        //Split a line into tokens by delimiting it on spaces
        //"Er Mah Gerd" becomes ["Er", "Mah", "Gerd"]
        tokens.clear();
        tokens = split(line, ' ', tokens);
        
        //If first token is a v then it gots to be a vertex
        if(tokens.at(0).compare("v") == 0)
        {
            //Parse the vertex line
            float x = std::stof(tokens.at(1));
            float y = std::stof(tokens.at(2));
            float z = std::stof(tokens.at(3));
			vertices->push_back(new Vector3(x, y, z));
        }

        else if(tokens.at(0).compare("vn") == 0)
        {
            //Parse the normal line
			float x = std::stof(tokens.at(1));
			float y = std::stof(tokens.at(2));
			float z = std::stof(tokens.at(3));
			normals->push_back(new Vector3(x, y, z));
        }

        else if(tokens.at(0).compare("f") == 0)
        {
            Face* face = new Face();

			//Parse the face line
			for (int i = 1; i < 4; i++)
			{
				int j = i - 1;

				faceVals = split(tokens.at(i), '/', faceVals);
				face->vs[j] = stoi(faceVals.at(0));
				face->ns[j] = stoi(faceVals.at(2));
				//face.ts[j] = stoi(faceVals.at(1));
				faceVals.clear();
			}

			faces->push_back(face);
			face_num++;
        }

		else if (tokens.at(0).compare("vt") == 0)
		{
			//Parse the textures

			//Parse as appropriate
			//There are more line types than just the above listed
			//See the Wavefront Object format specification for details
		}
    }
    
    std::cout << "Done parsing." << std::endl;
}

//Split functions from the interwebs
//http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string>& OBJObject::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> OBJObject::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void OBJObject::spin(float radians)
{
	Matrix4 rotation;
	rotation.makeRotateY(radians);

	toWorld = toWorld * rotation;
}
