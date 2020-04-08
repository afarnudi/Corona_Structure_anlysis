//
//  Hoshen_kopelman_functions.cpp
//  Mahmoudi Image Processing
//
//  Created by Ali Farnudi on 19/05/2018.
//  Copyright © 2018 Ali FarnudiSUT. All rights reserved.
//

#include "Hoshen_kopelman_functions.hpp"
#include "tomo.h"



void HK_colour_voxels(vector<vector<vector<int> > > &coloured_voxels, vector< int > &Label, vector< int > &Cluster_size, int &colour){

    for (int k=1; k<coloured_voxels.size(); k++) {
        for (int j=1; j<coloured_voxels[1].size(); j++) {
            for (int i=1; i<coloured_voxels[1][1].size(); i++) {
                if (coloured_voxels[k][j][i]!=0) {
                    int coordinates[3]={k,j,i};
                    set_voxel_colour(coloured_voxels, coordinates, Label, Cluster_size, colour);
                }
            }
        }
    }
    for (int k=1; k<coloured_voxels.size(); k++) {
        for (int j=1; j<coloured_voxels[1].size(); j++) {
            for (int i=1; i<coloured_voxels[1][1].size(); i++) {
                coloured_voxels[k][j][i]=Label[coloured_voxels[k][j][i]];
            }
        }
    }
}


void tomo::HK_mask(vector<vector<vector<int> > > &coloured_voxels, int cluster_threshold, vector< int > Cluster_size){
    
    for (int k=1; k<z_dim; k++) {
        for (int j=1; j<y_dim; j++) {
            for (int i=1; i<x_dim; i++) {
                int temp_colour=coloured_voxels[k][j][i];
                if (Cluster_size[temp_colour]<=cluster_threshold && temp_colour!=0) {
                    coloured_voxels[k][j][i]=0;
                }
            }
        }
    }
    string HC_save_name="Hoshen_kopelman_";
    HC_save_name+=to_string(cluster_threshold);
    save_tomo_sequence(HC_save_name, coloured_voxels);
}


void tomo::HK_mask(vector<vector<vector<int> > > &coloured_voxels, int min_cluster_size, int max_cluster_size, vector< int > Cluster_size){
    
    for (int k=1; k<z_dim; k++) {
        for (int j=1; j<y_dim; j++) {
            for (int i=1; i<x_dim; i++) {
                int temp_colour=coloured_voxels[k][j][i];
                if (temp_colour!=0) {
                    if (Cluster_size[temp_colour]<min_cluster_size || Cluster_size[temp_colour]>max_cluster_size) {
                        coloured_voxels[k][j][i]=0;
                    }
                }
                
            }
        }
    }
    string HC_save_name="Hoshen_kopelman_";
    HC_save_name+=to_string(min_cluster_size);
    HC_save_name+="_and_";
    HC_save_name+=to_string(max_cluster_size);
    save_tomo_sequence(HC_save_name, coloured_voxels);
}


