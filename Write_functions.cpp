//
//  File.cpp
//  GPC-code
//
//  Created by Ali Farnudi on 03/01/2014.
//  Copyright (c) 2014 Ali Farnudi. All rights reserved.
//
/*
 Copyright 2012
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "tomo.h"
#include "sphere_mask_gen.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb-master/stb_image_write.h"

void tomo::set_voxel(int x, int y, int z, int voxel_value){
    voxels[z][x][y]=voxel_value;
}

void tomo::save_tomo_bin(string name){
    ofstream write_file;
    char buff[2];
    unsigned char ucbuff[2];
    unsigned short int temp[2];
//    file_name="test";
    file_name=name;
    write_file.open(file_name.c_str(), ios::out|ios::binary);
    for (int k=0; k<z_dim; k++) {
        for (int i=0; i<x_dim; i++) {
            for (int j=0; j<y_dim; j++) {
                //By bit-shiftinf the voxel value we split it up into two bytes
                temp[1]=voxels[k][i][j]>>8;
                temp[0]=voxels[k][i][j]-(temp[1]<<8);
                //next we cast the two seperated bytes to "unsigned char"
                ucbuff[0]=(unsigned char)temp[0];
                ucbuff[1]=(unsigned char)temp[1];
                //Then we copy them bit by bit to a "char" array
                memcpy(buff, ucbuff, 2);
                // We creat a const char array to use in the fstream write command
                const char write[2]={buff[0],buff[1]};
                write_file.write(write, 2);

            }
        }


    }
}

void tomo::save_tomo_sequence(string file_name){
    string save_file_name;
    for (int image=0; image<voxels.size(); image++) {
        ofstream write_file;
        stringstream ss;
        ss <<setw(3) << setfill('0') << image;
        string digit=ss.str();
        save_file_name=file_name;
        save_file_name+=digit+".txt";
        write_file.open(save_file_name.c_str());
        for (int j=0; j<voxels[0].size(); j++) {
            for (int i=0; i<voxels[0][0].size(); i++) {
                write_file<<voxels[image][j][i]<<"\t";
            }
            write_file<<"\n";
            
        }
    }
    cout<<"writing finished sucessfully"<<endl;
}


void tomo::save_tomo_sequence(string file_name, vector<vector<vector<int> > > coloured_voxels){
    string save_file_name;
    for (int image=0; image<coloured_voxels.size(); image++) {
        ofstream write_file;
        stringstream ss;
        ss <<setw(3) << setfill('0') << image;
        string digit=ss.str();
        save_file_name=file_name;
        save_file_name+=digit+".txt";
        write_file.open(save_file_name.c_str());
        for (int j=0; j<coloured_voxels[0].size(); j++) {
            for (int i=0; i<coloured_voxels[0][0].size(); i++) {
                write_file<<coloured_voxels[image][j][i]<<"\t";
            }
            write_file<<"\n";
            
        }
    }
    cout<<"writing finished sucessfully"<<endl;
}

void tomo::save_tomo_sequence(string file_name, vector<vector<vector<int> > > coloured_voxels, int sphere_radius){
    string save_file_name;
    int crop_size=coloured_voxels.size()/2+1;
    for (int image=0; image<coloured_voxels.size(); image++) {
        
        stringstream ss;
        ss <<setw(3) << setfill('0') << image;
        string digit=ss.str();
        save_file_name=file_name;
        save_file_name+=digit+".jpg";
        
        vector<vector<vector<int > > > RGB_voxel;
        RGB_voxel.resize(coloured_voxels[0].size());
        for (int j=0; j<coloured_voxels[0].size(); j++) {
            RGB_voxel[j].resize(coloured_voxels[0][0].size());
            for (int i=0; i<coloured_voxels[0][0].size(); i++) {
                RGB_voxel[j][i].resize(3);
                int temp_r=sqrt((image-crop_size)*(image-crop_size)+(j-crop_size)*(j-crop_size)+(i-crop_size)*(i-crop_size));
                if (temp_r<sphere_radius) {
                    RGB_voxel[j][i][0]=0;
                    RGB_voxel[j][i][1]=0;
                    RGB_voxel[j][i][2]=255;
                } else {
                    RGB_voxel[j][i][0]=0;
                    RGB_voxel[j][i][1]=0;
                    RGB_voxel[j][i][2]=0;
                }
                if (coloured_voxels[image][j][i]!=0) {
                    RGB_voxel[j][i][0]=255;
                    RGB_voxel[j][i][1]=255;
                    RGB_voxel[j][i][2]=255;
                }
            }
        }
        
        const char* name=save_file_name.c_str();
        int w=coloured_voxels[0].size(), h=coloured_voxels[0][0].size();
        const int size=w*h*3;
        unsigned char RGB_image[size];
        for (int i=0; i<w; i++) {
            for (int j=0; j<h; j++) {
                RGB_image[(i*w+j)*3+0]=RGB_voxel[i][j][0];
                RGB_image[(i*w+j)*3+1]=RGB_voxel[i][j][1];
                RGB_image[(i*w+j)*3+2]=RGB_voxel[i][j][2];
                
            }
        }
        stbi_write_jpg(name, w, h, 3, RGB_image, 100);
        
    }
    cout<<"writing finished sucessfully"<<endl;
}

void tomo::save_2D_tomo(string file_name, int sphere_radius){
    string save_file_name;
    
    save_file_name=file_name;
    save_file_name+=".jpg";
    
    vector<vector<vector<int > > > RGB_voxel;
    RGB_voxel.resize(y_dim);
    for (int j=0; j<y_dim; j++) {
        RGB_voxel[j].resize(x_dim);
        for (int i=0; i<x_dim; i++) {
            RGB_voxel[j][i].resize(3);
//            int temp_r=sqrt((image-crop_size)*(image-crop_size)+(j-crop_size)*(j-crop_size)+(i-crop_size)*(i-crop_size));
//            if (temp_r<sphere_radius) {
            if (voxels[0][j][i]>183) {
                RGB_voxel[j][i][0]=0;
                RGB_voxel[j][i][1]=0;
                RGB_voxel[j][i][2]=255;
            } else {
                RGB_voxel[j][i][0]=0;
                RGB_voxel[j][i][1]=0;
                RGB_voxel[j][i][2]=0;
            }
        }
    }
    const char* name=save_file_name.c_str();
    int w=y_dim, h=x_dim;
    const int size=w*h*3;
    unsigned char RGB_image[size];
    for (int i=0; i<w; i++) {
        for (int j=0; j<h; j++) {
            RGB_image[(i*w+j)*3+0]=RGB_voxel[i][j][0];
            RGB_image[(i*w+j)*3+1]=RGB_voxel[i][j][1];
            RGB_image[(i*w+j)*3+2]=RGB_voxel[i][j][2];
            
        }
    }
    stbi_write_jpg(name, w, h, 3, RGB_image, 100);
    cout<<"writing finished sucessfully"<<endl;
    
    
}

void tomo::save_2D_tomo(string file_name, vector<vector<vector<int> > > coloured_voxels){
    string save_file_name;
    ofstream write_file;
    save_file_name=file_name+".txt";
    write_file.open(save_file_name.c_str());
    for (int j=0; j<coloured_voxels[0].size(); j++) {
        for (int i=0; i<coloured_voxels[0][0].size(); i++) {
            write_file<<coloured_voxels[0][j][i]<<"\t";
        }
        write_file<<"\n";
        
    }
    cout<<"writing finished sucessfully"<<endl;
}
