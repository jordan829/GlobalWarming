#ifndef CSE167_Texture_h
#define CSE167_Texture_h

#include <iostream>
#include <string>

class Texture
{
    
protected:
    
    const char* filename;
    
    static unsigned char* loadPPM(const char*, int&, int&);
    
public:
    
    unsigned int id;
	unsigned char* tdata;
    
    static Texture* emptyTexture;
    
    Texture(void);
    Texture(const char* filename);
    virtual ~Texture(void);
    
    void bind(void);
    void unbind(void);
    
};

#endif
