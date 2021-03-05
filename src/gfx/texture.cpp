//
// Created by 16182 on 7/20/2020.
//

#include "texture.hpp"
#include "../io/io.hpp"

GLuint get_BMP(const std::string &file_name) {
    auto buffer = getFileRaw(file_name);
    unsigned char * header = buffer.data();
    unsigned char * data;
    unsigned int dataPos;
    unsigned int imageSize;
    int width, height;
    // Actual RGB data

    // Open the file

    if ( header[0]!='B' || header[1]!='M' ){
        printf("Not a correct BMP file\n");
        return 0;
    }

    // Read the information about the image
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);

    if (imageSize==0)    imageSize=width*height*4;
    if (dataPos==0)      dataPos=54;

    data = buffer.data() + dataPos;

    // ARGB->RGBA
    for(int i = 0; i < imageSize; i+=4){
        unsigned char a = data[i];
        unsigned char b = data[i+1];
        unsigned char g = data[i+2];
        unsigned char r = data[i+3];
        data[i] = r;
        data[i+1] = g;
        data[i+2] = b;
        data[i+3] = a;
    }
    return loadTexture(data, width, height, GL_LINEAR);
}

GLuint loadTexture(const void *data, int width, int height, GLenum filtering) {
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
    glGenerateMipmap(GL_TEXTURE_2D);
    return tex;
}
