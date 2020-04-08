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

int tomo::haugh_transformation_2D(int circle_radius, string name_hough){
    // The accumulator vector stores the information for voxels that have the potential of being the centre of the spheres
    accumulator.resize(1);
    accumulator[0].resize(y_dim);
    for (int j=0; j<y_dim; j++) {
        accumulator[0][j].resize(x_dim);
        for (int i=0; i<x_dim; i++) {
            accumulator[0][j][i]=0;
        }
    }
    cout<<"accumulator initialized"<<endl;
    
    vector<vector<int> > circle_mask;
    circle_mask_generator(circle_mask, circle_radius);
    cout<<circle_radius<<" mask generated\n";
//    cout<<setprecision(3)<<(k-sphere_radius)*100/(z_dim-2*sphere_radius)<<" %"<<endl;
    for (int j=circle_radius; j<y_dim-circle_radius-1; j++) {
        for (int i=circle_radius; i<x_dim-circle_radius-1; i++) {
            if(voxels[0][j][i]==gray_level-1){
                //The process involves drawing(voting) a sphere with a radias of 15 pixels around the specified point
                haugh_vote_2D(i, j, circle_mask);
            }
        }
    }
    cout<<"Voting finished"<<endl;
    
    
    
    int MAX_vote=0;
    for (int j=0; j<y_dim; j++) {
        for (int i=0; i<x_dim; i++) {
            //Determin the maximum number of times the spheres drawn in the previous step (Voting) go through the points at the centre of each sphere
            if(accumulator[0][j][i]>MAX_vote){
                MAX_vote=accumulator[0][j][i];
            }
        }
    }
    cout<<"Max vote: "<<MAX_vote<<endl;
    save_tomo_sequence(name_hough, accumulator);
    cout<<endl<<"File written"<<endl;
    return MAX_vote;
}


void tomo::haugh_vote_2D(int x, int y, vector<vector<int> > circle_mask){
    //The following position are the positions for a circle with a radius of 15 pixels around the coordinate x, y, z
    //The following code will draw a sphere with a radius of 15 around the given coordinate x, y, z
    //In order to speed up the drawing process we have written the position of the points on a sphere shell around a point x, y, z
    //3D
    for (int count=0; count<circle_mask.size(); count++) {
        accumulator[0][y+circle_mask[count][1]][x+circle_mask[count][0]]++;
    }
}
