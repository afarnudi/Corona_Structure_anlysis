//
//  Hough Tranformation for a Sphere.cpp
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
 GNU General Public License for m8ore details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "tomo.h"
#include "sphere_mask_gen.hpp"

void tomo::haugh_transformation(int sphere_radius, string name_hough){
    // The accumulator vector stores the information for voxels that have the potential of being the centre of the spheres
    accumulator.resize(z_dim);
    for (int k=0; k<z_dim; k++) {
        accumulator[k].resize(y_dim);
        for (int j=0; j<y_dim; j++) {
            accumulator[k][j].resize(x_dim);
            for (int i=0; i<x_dim; i++) {
                accumulator[k][j][i]=0;
            }
        }
    }
    cout<<"accumulator initialized"<<endl;
    
    vector<vector<int> > sphere_mask;
    sphere_mask_generator(sphere_mask, sphere_radius);
    
    for (int k=sphere_radius; k<z_dim-sphere_radius-1; k++) {
        cout<<setprecision(3)<<(k-sphere_radius)*100/(z_dim-2*sphere_radius)<<" %"<<endl;
        for (int j=sphere_radius; j<y_dim-sphere_radius-1; j++) {
            for (int i=sphere_radius; i<x_dim-sphere_radius-1; i++) {
                if(voxels[k][j][i]==gray_level-1){
                    //The process involves drawing(voting) a sphere with a radias of 15 pixels around the specified point
                    haugh_vote_2(i, j, k, sphere_mask);
                }
            }
        }
    }
    cout<<"Voting finished"<<endl;
    
    
    
    int MAX_vote=0;
    for (int k=0; k<z_dim; k++) {
        for (int j=0; j<y_dim; j++) {
            for (int i=0; i<x_dim; i++) {
                //Determin the maximum number of times the spheres drawn in the previous step (Voting) go through the points at the centre of each sphere
                if(accumulator[k][j][i]>MAX_vote){
                    MAX_vote=accumulator[k][j][i];
                }
            }
        }
    }
    cout<<"Max vote: "<<MAX_vote<<endl;
    save_tomo_sequence(name_hough, accumulator);
    cout<<endl<<"File written"<<endl;
   
}

//This method will apply the Hough transformation method for the desired radius
void tomo::haugh_vote_link(int x, int y, int z, int R){
    for (int k=-R; k<=R; k++) {
        for (int j=-R; j<=R; j++) {
            for (int i=-R; i<=R; i++) {
                if (int(k*k+j*j+i*i)==R*R) {
                    //cout<<k<<"\t"<<j<<"\t"<<i<<"\n";
                    mini_accumulator[z+k][x+i][y+j]+=10;
                }
            }
        }
    }
}


void tomo::haugh_vote_2(int x, int y, int z, vector<vector<int> > sphere_mask){
    //The following position are the positions for a circle with a radius of 15 pixels around the coordinate x, y, z
    //The following code will draw a sphere with a radius of 15 around the given coordinate x, y, z
    //In order to speed up the drawing process we have written the position of the points on a sphere shell around a point x, y, z
    //3D
    for (int count=0; count<sphere_mask.size(); count++) {
        accumulator[z+sphere_mask[count][2]][y+sphere_mask[count][1]][x+sphere_mask[count][0]]++;
    }
}
