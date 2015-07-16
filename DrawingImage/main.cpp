//
//  main.cpp
//  DrawingImage
//
//  Created by RyomaABE on 2015/07/09.
//  Copyright (c) 2015年 RyomaABE. All rights reserved.
//

#include <iostream>
#include "GLFW/glfw3.h"
#include <OpenGL/OpenGL.h>
#include <cstdlib>
#include <math.h>
#include <stdio.h>

#define IMGFILE "/Users/Ryoma/cvip/matlab_scripts/output.bmp"
#define CANNEL 1

int width;
int height;
GLubyte* image;

void loadImage(const char* filepath);
static void cleanup();

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.8, 1.0, 1.0, 1.0);
    
    glRasterPos2d(-0.5, -0.5);
   
    glDrawPixels(width, height, GL_LUMINANCE, GL_UNSIGNED_BYTE, image);
    
    printf("width=%d \n height=%d \n",width,height);
    }

static void cleanup(){
    glfwTerminate();
}

void loadImage(const char* filepath){
    int i;
    int size;
    FILE* fp;
    
    fp = fopen(filepath, "rb");
    if(fp == NULL){
        fprintf(stderr,"faild loading image");
        exit(EXIT_FAILURE);
    }
    
    fseek(fp,18,SEEK_SET);
    fread(&width,4,1,fp);
    fread(&height,4,1,fp);
    
    fseek(fp,54+1024,SEEK_SET);
    size = width * height * CANNEL;
    image = (GLubyte*)malloc(size);
    if(image == NULL){
        fprintf(stderr,"faild ");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < size; i++){
        fread(&image[i],sizeof(GLubyte),1,fp);
    }
    fclose(fp);
}

int main(){
    if(glfwInit()==GL_FALSE){
        std::cerr << "Can't initialize GLFW" << std::endl;
        return 1;
    }
    
    atexit(cleanup);
    
    loadImage(IMGFILE);
    GLFWwindow *const window(glfwCreateWindow(3400,2300,"hello!",NULL,NULL));
    if (window == NULL){
        std::cerr << "Can't create GLFW window." << std::endl;
        glfwTerminate();
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    
    while (glfwWindowShouldClose(window)==GL_FALSE && glfwGetKey(window, GLFW_KEY_ESCAPE) != true){
        glClear(GL_COLOR_BUFFER_BIT);
        
        //glMatrixMode(GL_PROJECTION);
        //glLoadIdentity();
        //glOrtho(-1, 1, -1, 1, 0, 5);
        //glMatrixMode(GL_MODELVIEW);
        
        display();
        
        glfwSwapBuffers(window);
        
        glfwWaitEvents();
    }
}

