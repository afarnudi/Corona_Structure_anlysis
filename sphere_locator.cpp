//
//  tomo.cpp
//  GPC-code
//
//  Created by Ali Farnudi on 24/12/2012.
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

void tomo::sphere_centre_locator(vector<vector<int> > &sphere_centre_coordinates, int sphere_radius){
    vector<vector<double> > temp_coordinate_weighted;
    vector<double> temp_coordinates_w;
    temp_coordinates_w.resize(4);
    bool write=true;
    for (int k=0; k<z_dim; k++) {
        for (int j=0; j<y_dim; j++) {
            for (int i=0; i<x_dim; i++) {
                if (voxels[k][j][i]>=gray_level-300) {//1200//300
                    for (int s=0; s<temp_coordinate_weighted.size(); s++) {
                        double temp_r=sqrt((temp_coordinate_weighted[s][0]-i)*(temp_coordinate_weighted[s][0]-i)+(temp_coordinate_weighted[s][1]-j)*(temp_coordinate_weighted[s][1]-j)+(temp_coordinate_weighted[s][2]-k)*(temp_coordinate_weighted[s][2]-k));
                        if (temp_r<sphere_radius) {
                            write=false;
                            temp_coordinate_weighted[s][0]=(temp_coordinate_weighted[s][0]*temp_coordinate_weighted[s][3]+i)/(temp_coordinate_weighted[s][3]+1) ;
                            temp_coordinate_weighted[s][1]=(temp_coordinate_weighted[s][1]*temp_coordinate_weighted[s][3]+j)/(temp_coordinate_weighted[s][3]+1) ;
                            temp_coordinate_weighted[s][2]=(temp_coordinate_weighted[s][2]*temp_coordinate_weighted[s][3]+k)/(temp_coordinate_weighted[s][3]+1) ;
                            temp_coordinate_weighted[s][3]++;
                            break;
                        } else {
                            write=true;
                        }
                    }
                    if (write==true) {
                        temp_coordinates_w[0]=i;
                        temp_coordinates_w[1]=j;
                        temp_coordinates_w[2]=k;
                        temp_coordinates_w[3]=1;
                        temp_coordinate_weighted.push_back(temp_coordinates_w);
                        write=false;
                    }
                }
            }
        }
    }
    
    
    vector<int> temp;
    temp.resize(3);
    for (int i=0; i<temp_coordinate_weighted.size(); i++) {
        temp[0]=round(temp_coordinate_weighted[i][0]);
        temp[1]=round(temp_coordinate_weighted[i][1]);
        temp[2]=round(temp_coordinate_weighted[i][2]);
        sphere_centre_coordinates.push_back(temp);
    }
    cout<<"Found "<<sphere_centre_coordinates.size()<<" spheres with radius "<<sphere_radius<<endl;
    for (int i=0; i<sphere_centre_coordinates.size(); i++) {
        cout<<sphere_centre_coordinates[i][2]<<"\t"<<sphere_centre_coordinates[i][1]<<"\t"<<sphere_centre_coordinates[i][0]<<endl;
    }
}

void tomo::circle_centre_locator(vector<vector<int> > &circle_centre_coordinates, int circle_radius){
    vector<vector<double> > temp_coordinate_weighted;
    vector<double> temp_coordinates_w;
    temp_coordinates_w.resize(4);
    bool write=true;
    for (int j=0; j<y_dim; j++) {
        for (int i=0; i<x_dim; i++) {
            //1_59kx_3um_360000-->100 gets only 2
            if (voxels[0][j][i]>=gray_level-100) {//
                for (int s=0; s<temp_coordinate_weighted.size(); s++) {
                    double temp_r=sqrt((temp_coordinate_weighted[s][0]-i)*(temp_coordinate_weighted[s][0]-i)+(temp_coordinate_weighted[s][1]-j)*(temp_coordinate_weighted[s][1]-j));
                    if (temp_r<circle_radius) {
                        write=false;
                        temp_coordinate_weighted[s][0]=(temp_coordinate_weighted[s][0]*temp_coordinate_weighted[s][3]+i)/(temp_coordinate_weighted[s][3]+1) ;
                        temp_coordinate_weighted[s][1]=(temp_coordinate_weighted[s][1]*temp_coordinate_weighted[s][3]+j)/(temp_coordinate_weighted[s][3]+1) ;
                        temp_coordinate_weighted[s][2]=0 ;
                        temp_coordinate_weighted[s][3]++;
                        break;
                    } else {
                        write=true;
                    }
                }
                if (write) {
                    temp_coordinates_w[0]=i;
                    temp_coordinates_w[1]=j;
                    temp_coordinates_w[2]=0;
                    temp_coordinates_w[3]=1;
                    temp_coordinate_weighted.push_back(temp_coordinates_w);
                    write=false;
                }
            }
        }
    }
    
    
    vector<int> temp;
    temp.resize(2);
    for (int i=0; i<temp_coordinate_weighted.size(); i++) {
        temp[0]=round(temp_coordinate_weighted[i][0]);
        temp[1]=round(temp_coordinate_weighted[i][1]);
        circle_centre_coordinates.push_back(temp);
    }
    cout<<"Found "<<circle_centre_coordinates.size()<<" circles with radius "<<circle_radius<<endl<<endl;
    for (int i=0; i<circle_centre_coordinates.size(); i++) {
        cout<<circle_centre_coordinates[i][1]<<"\t"<<circle_centre_coordinates[i][0]<<endl;
    }
}


