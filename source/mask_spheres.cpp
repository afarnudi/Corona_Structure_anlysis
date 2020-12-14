//
//  mask_spheres.cpp
//  Mahmoudi Image Processing
//
//  Created by Ali Farnudi on 11/07/2018.
//  Copyright © 2018 Ali FarnudiSUT. All rights reserved.
//

#include "tomo.h"
#include "sphere_mask_gen.hpp"


void tomo::mask_sphere_coordinates(vector<vector<int> > &sphere_centre_coordinates, int sphere_radius_in, int sphere_radius_out){
    vector<vector<vector<int> > > voxel_copy;
    voxel_copy=voxels;
    vector <vector<int> > temp;
    temp.resize(y_dim,vector<int>(x_dim, 0));
    voxels.resize(0);
    voxels.resize(z_dim,temp);
    
    //    int inner_sphere_radius=23;
    //    int outer_sphere_radius=43;
    vector<vector<int> > sphere_mask;
    
    sphere_mask_generator(sphere_mask, sphere_radius_in, sphere_radius_out);
    
    for (int count=0; count<sphere_centre_coordinates.size(); count++) {
        for (int i_mask=0; i_mask<sphere_mask.size(); i_mask++) {
            int k=sphere_centre_coordinates[count][2]+sphere_mask[i_mask][2];
            int j=sphere_centre_coordinates[count][1]+sphere_mask[i_mask][1];
            int i=sphere_centre_coordinates[count][0]+sphere_mask[i_mask][0];
            if (signbit(k)==1 || signbit(j)==1 || signbit(i)==1) {
                break;
            }
            voxels[k][j][i]=voxel_copy[k][j][i];
        }
        
    }
    
    save_tomo_sequence("Hough_masked", voxels);
}


void tomo::mask_circle_coordinates(vector<vector<int> > &circle_centre_coordinates, int circle_radius_in, int circle_radius_out){
    vector<vector<vector<int> > > voxel_copy;
    voxel_copy=voxels;
    vector <vector<int> > temp;
    temp.resize(y_dim,vector<int>(x_dim, 0));
    voxels.resize(0);
    voxels.resize(z_dim,temp);
    
    //    int inner_sphere_radius=23;
    //    int outer_sphere_radius=43;
    
    vector<vector<int> > circle_mask;
    circle_mask_generator(circle_mask, circle_radius_in, circle_radius_out);
    
    for (int count=0; count<circle_centre_coordinates.size(); count++) {
        for (int i_mask=0; i_mask<circle_mask.size(); i_mask++) {
            int j=circle_centre_coordinates[count][1]+circle_mask[i_mask][1];
            int i=circle_centre_coordinates[count][0]+circle_mask[i_mask][0];
            if (signbit(j)==1 || signbit(i)==1) {
                break;
            }
            voxels[0][j][i]=voxel_copy[0][j][i];
        }
        
    }
    
    save_2D_tomo("Hough_masked", voxels);
}
