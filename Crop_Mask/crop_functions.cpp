//
//  crop_functions.cpp
//  Mahmoudi Image Processing
//
//  Created by Ali Farnudi on 23/05/2018.
//  Copyright © 2018 Ali FarnudiSUT. All rights reserved.
//

#include "tomo.h"
#include "Cluster.h"
#include "sphere_mask_gen.hpp"


void tomo::crop_sphere_coordinates(vector<vector<int> > sphere_centre_coordinates, int crop_size, vector<vector<int> > mask_coordinates, int count){
    vector <vector<int> > temp;
    temp.resize(2*crop_size+1,vector<int>(2*crop_size+1, 0));
    cropped_voxel.resize(0);
    cropped_voxel.resize(2*crop_size+1,temp);
    
    for (int i_mask=0; i_mask<mask_coordinates.size(); i_mask++) {
        int k=sphere_centre_coordinates[count][2]+mask_coordinates[i_mask][2];
        int j=sphere_centre_coordinates[count][1]+mask_coordinates[i_mask][1];
        int i=sphere_centre_coordinates[count][0]+mask_coordinates[i_mask][0];
        
        int k2=crop_size+mask_coordinates[i_mask][2];
        int j2=crop_size+mask_coordinates[i_mask][1];
        int i2=crop_size+mask_coordinates[i_mask][0];
        
        if (signbit(k)==1 || signbit(j)==1 || signbit(i)==1) {
            break;
        }
        cropped_voxel[k2][j2][i2]=voxels[k][j][i];
    }
    
}

