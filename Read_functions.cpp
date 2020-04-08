//
//  read-write functions.cpp
//  test
//
//  Created by Ali Farnudi on 28/04/2013.
//
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



unsigned int tomo::get_voxel(int x, int y, int z){
    return voxels[z][y][x];
}



void tomo::read_tomo_bin(string file){
    
    ifstream read_file;
    file_name=file;
    
    //Thease two arrays are used to read two bytes from the xxx.vol file and convert them to "unsigned char"
    char buff[2];
    unsigned char ucbuff[2];
    read_file.open(file_name.c_str(), ios::in|ios::binary);
    if(!read_file) {
        cout << "Cannot open file.\n";
    } else {
        for (int k=0; k<z_dim; k++) {
            for (int i=0; i<x_dim; i++) {
                for (int j=0; j<y_dim; j++) {
                    //We read 2 bytes from the xxx.vol file
                    read_file.read(buff, 2);
                    //Then we convert the 2 characters to unsigned characters
                    memcpy(ucbuff, buff, 2);
                    //now by using bit-shifting the charechters we calculate the value of the two bytes to "unsigned short int"
                    voxels[k][i][j]= (unsigned short int)ucbuff[0]+((unsigned short int)ucbuff[1]<<8);
                }
            }
        }
    }
    if(!read_file.good()) {
        cout << "A file error occurred.\n";
    }else cout<< "File read succesfully.\n";
    
}

void tomo::read_tomo_sequence(string file){
    
    for (int image=0; image<z_dim; image++) {
        ifstream read_file;
        stringstream ss;
        ss <<setw(3) << setfill('0') << image;
        string digit=ss.str();
        file_name=file;
//        cout<<digit<<endl;
        file_name+=digit+".txt";
//        cout<<file_name<<endl;
        read_file.open(file_name.c_str());
        double temp;
        for (int j=0; j<y_dim; j++) {
            for (int i=0; i<x_dim; i++) {
                //We read 2 bytes from the xxx.vol file
                read_file>>temp;
                voxels[image][j][i]=temp;
//                cout<<voxels[image][j][i]<<"\t";
                if (voxels[image][j][i]>gray_level) {
                    exit(EXIT_FAILURE);
                }
                //                        cout<<voxels[k][i][j]<<"\t";
            }
        }
//        }
//        if(!read_file.good()) {
//            cout << "A file error occurred.\n";
//        }else cout<< "File read succesfully.\n";
    }
    
}

void tomo::read_2D_image(string file){
    
    ifstream read_file;
    file_name=file+".txt";
    read_file.open(file_name.c_str());
    double temp;
    for (int j=0; j<y_dim; j++) {
        for (int i=0; i<x_dim; i++) {
            //We read 2 bytes from the xxx.vol file
            read_file>>temp;
            voxels[0][j][i]=temp;
            //                cout<<voxels[image][j][i]<<"\t";
            if (voxels[0][j][i]>gray_level) {
                exit(EXIT_FAILURE);
            }
            
        }
//        cout<<"first ("<<j<<"): "<<voxels[0][j][0]<<"\tlast : "<<voxels[0][j][x_dim-1]<<"\n";
    }
    //        }
    //        if(!read_file.good()) {
    //            cout << "A file error occurred.\n";
    //        }else cout<< "File read succesfully.\n";
    
}
