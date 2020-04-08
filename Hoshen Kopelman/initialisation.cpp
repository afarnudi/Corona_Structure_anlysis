//
//  initialisation.cpp
//  Mahmoudi Image Processing
//
//  Created by Ali Farnudi on 25/06/2018.
//  Copyright © 2018 Ali FarnudiSUT. All rights reserved.
//

#include <stdio.h>
#include "tomo.h"
#include "Hoshen_kopelman_functions.hpp"


void tomo::HK_initilise_couloured_voxel(vector<vector<vector<int> > > &coloured_voxels){
    coloured_voxels.resize(z_dim);
    for (int k=0; k<z_dim; k++) {
        coloured_voxels[k].resize(y_dim);
        for (int j=0; j<y_dim; j++) {
            coloured_voxels[k][j].resize(x_dim);
            for (int i=0; i<x_dim; i++) {
                coloured_voxels[k][j][i]=voxels[k][j][i];
            }
        }
    }
    for (int j=0; j<y_dim; j++) {
        for (int i=0; i<x_dim; i++) {
            coloured_voxels[0][j][i]=0;
        }
    }
    for (int k=1; k<z_dim; k++) {
        for (int i=0; i<x_dim; i++) {
            coloured_voxels[k][0][i]=0;
        }
    }
    for (int k=1; k<z_dim; k++) {
        for (int j=0; j<y_dim; j++) {
            coloured_voxels[k][j][0]=0;
        }
    }
}

void tomo::HK_initilise_couloured_voxel(vector<vector<vector<int> > > &coloured_voxels, int crop_size){
    int voxel_size=2*crop_size+1;
    coloured_voxels.resize(voxel_size);
    for (int k=0; k<voxel_size; k++) {
        coloured_voxels[k].resize(voxel_size);
        for (int j=0; j<voxel_size; j++) {
            coloured_voxels[k][j].resize(voxel_size);
            for (int i=0; i<voxel_size; i++) {
                coloured_voxels[k][j][i]=cropped_voxel[k][j][i];
            }
        }
    }
    for (int j=0; j<voxel_size; j++) {
        for (int i=0; i<voxel_size; i++) {
            coloured_voxels[0][j][i]=0;
        }
    }
    for (int k=1; k<voxel_size; k++) {
        for (int i=0; i<voxel_size; i++) {
            coloured_voxels[k][0][i]=0;
        }
    }
    for (int k=1; k<voxel_size; k++) {
        for (int j=0; j<voxel_size; j++) {
            coloured_voxels[k][j][0]=0;
        }
    }
}

