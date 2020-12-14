//
//  Hoshen_Kopelman.cpp
//  Mahmoudi Image Processing
//
//  Created by Ali Farnudi on 19/05/2018.
//  Copyright © 2018 Ali FarnudiSUT. All rights reserved.
//

#include <stdio.h>
#include "tomo.h"
#include "Hoshen_kopelman_functions.hpp"




void tomo::Hoshen_Kopelman_3D(vector<vector<vector<int> > > &coloured_voxels, vector< int > &Cluster_size){
    vector< int > Label;
    Label.push_back(0);
    Cluster_size.push_back(0);
    vector<double> temp_coordinates;
    temp_coordinates.resize(3);
    temp_coordinates[0]=0;
    temp_coordinates[1]=0;
    temp_coordinates[2]=0;
    int colour=0;
    
    HK_initilise_couloured_voxel(coloured_voxels);
    HK_colour_voxels(coloured_voxels, Label, Cluster_size, colour);
    
    cout<<colour<<endl;
    save_tomo_sequence("coloured", coloured_voxels);
}



void tomo::Hoshen_Kopelman_3D(vector<vector<vector<int> > > &coloured_voxels, vector< int > &Cluster_size, int crop_size){
    
    vector< int > Label;
    Label.push_back(0);
    Cluster_size.push_back(0);
    vector<double> temp_coordinates;
    temp_coordinates.resize(3);
    temp_coordinates[0]=0;
    temp_coordinates[1]=0;
    temp_coordinates[2]=0;
    int colour=0;
    
    HK_initilise_couloured_voxel(coloured_voxels, crop_size);
    HK_colour_voxels(coloured_voxels, Label, Cluster_size, colour);
    
}



