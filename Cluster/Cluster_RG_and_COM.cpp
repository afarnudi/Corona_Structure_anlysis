//
//  Cluster_RG_and_COM.cpp
//  Mahmoudi Image Processing
//
//  Created by Ali Farnudi on 13/07/2018.
//  Copyright © 2018 Ali FarnudiSUT. All rights reserved.
//

#include "Cluster.h"

void Cluster::calculate_com_position (void){
    com_position[0]=0;
    com_position[1]=0;
    com_position[2]=0;
    for (int i=0; i<voxel_coordinates.size(); i++) {
        com_position[0]+=voxel_coordinates[i][0];
        com_position[1]+=voxel_coordinates[i][1];
        com_position[2]+=voxel_coordinates[i][2];
    }
    com_position[0]/=size;
    com_position[1]/=size;
    com_position[2]/=size;
    com_pos_length=sqrt(com_position[0]*com_position[0]+com_position[1]*com_position[1]+com_position[2]*com_position[2]);
    com_flag=true;
}

void Cluster::calculate_radius_of_gyration (void){
    double r_mean_squared=0;
    if (!com_flag) {
        calculate_com_position();
    }
    for (int i=0; i<size; i++) {
        r_mean_squared+=(voxel_coordinates[i][0]-com_position[0])*(voxel_coordinates[i][0]-com_position[0])+            (voxel_coordinates[i][1]-com_position[1])*(voxel_coordinates[i][1]-com_position[1])+(voxel_coordinates[i][2]-com_position[2])*(voxel_coordinates[i][2]-com_position[2]);
    }
//    r_mean=sqrt(com_position[0]*com_position[0]+com_position[1]*com_position[1]+com_position[2]*com_position[2]);
    r_mean_squared/=size;
    radius_of_gyration=sqrt(r_mean_squared);
    RG_flag=true;
}
