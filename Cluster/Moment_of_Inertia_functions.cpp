//
//  Moment_of_Inertia_functions.cpp
//  Mahmoudi Image Processing
//
//  Created by Ali Farnudi on 13/07/2018.
//  Copyright © 2018 Ali FarnudiSUT. All rights reserved.
//

#include <stdio.h>
#include "Cluster.h"

void Cluster::calculate_RG_tensor(void){
    double RG_xx=0, RG_yy=0, RG_zz=0, RG_xy=0, RG_xz=0, RG_yz=0;
    
    for (int i=0; i<size; i++) {
        RG_zz+=(voxel_coordinates[i][0]-com_position[0])*(voxel_coordinates[i][0]-com_position[0]);
        RG_yy+=(voxel_coordinates[i][1]-com_position[1])*(voxel_coordinates[i][1]-com_position[1]);
        RG_xx+=(voxel_coordinates[i][2]-com_position[2])*(voxel_coordinates[i][2]-com_position[2]);
        
        RG_xy+=(voxel_coordinates[i][2]-com_position[2])*(voxel_coordinates[i][1]-com_position[1]);
        RG_yz+=(voxel_coordinates[i][1]-com_position[1])*(voxel_coordinates[i][0]-com_position[0]);
        RG_xz+=(voxel_coordinates[i][2]-com_position[2])*(voxel_coordinates[i][0]-com_position[0]);
    }
    //    matrix
    RG_tensor[0][0]=RG_xx/size;
    RG_tensor[0][1]=RG_xy/size;
    RG_tensor[0][2]=RG_xz/size;
    RG_tensor[1][0]=RG_xy/size;
    RG_tensor[1][1]=RG_yy/size;
    RG_tensor[1][2]=RG_yz/size;
    RG_tensor[2][0]=RG_xz/size;
    RG_tensor[2][1]=RG_yz/size;
    RG_tensor[2][2]=RG_zz/size;
    
}
void Cluster::calculate_MI_tensor(void){
    double I_xx=0, I_yy=0, I_zz=0, I_xy=0, I_xz=0, I_yz=0;
    for (int i=0; i<voxel_coordinates[i].size(); i++) {
        I_zz+=voxel_coordinates[i][1]*voxel_coordinates[i][1]+voxel_coordinates[i][2]*voxel_coordinates[i][2];
        I_yy+=voxel_coordinates[i][2]*voxel_coordinates[i][2]+voxel_coordinates[i][0]*voxel_coordinates[i][0];
        I_xx+=voxel_coordinates[i][1]*voxel_coordinates[i][1]+voxel_coordinates[i][0]*voxel_coordinates[i][0];
        I_xy-=voxel_coordinates[i][2]*voxel_coordinates[i][1];
        I_yz-=voxel_coordinates[i][0]*voxel_coordinates[i][1];
        I_xz-=voxel_coordinates[i][0]*voxel_coordinates[i][2];
    }
//    matrix
    moment_of_inertia[0][0]=I_xx;
    moment_of_inertia[0][1]=I_xy;
    moment_of_inertia[0][2]=I_xz;
    moment_of_inertia[1][0]=I_xy;
    moment_of_inertia[1][1]=I_yy;
    moment_of_inertia[1][2]=I_yz;
    moment_of_inertia[2][0]=I_xz;
    moment_of_inertia[2][1]=I_yz;
    moment_of_inertia[2][2]=I_zz;
}

void Cluster::rotation_about_z(void){
    double cos_gamma, sin_gamma;
    double rx2_ry2=sqrt(com_position[1]*com_position[1]+com_position[2]*com_position[2]);
    cos_gamma=com_position[2]/rx2_ry2;
    sin_gamma=com_position[1]/rx2_ry2;
    
    for (int i=0; i<voxel_coordinates.size(); i++) {
        double temp_x=voxel_coordinates[i][2]*cos_gamma+voxel_coordinates[i][1]*sin_gamma;
        double temp_y=-voxel_coordinates[i][2]*sin_gamma+voxel_coordinates[i][1]*cos_gamma;
        voxel_coordinates[i][2]=temp_x;
        voxel_coordinates[i][1]=temp_y;
    }
    
}
void Cluster::rotation_about_y(void){
    double cos_beta, sin_beta;
    cos_beta=com_position[0]/com_pos_length;
    sin_beta=sqrt(1-cos_beta*cos_beta+0.000001);
    
    for (int i=0; i<voxel_coordinates.size(); i++) {
        double temp_x=voxel_coordinates[i][2]*cos_beta-voxel_coordinates[i][0]*sin_beta;
        double temp_z=voxel_coordinates[i][2]*sin_beta+voxel_coordinates[i][0]*cos_beta;
        voxel_coordinates[i][2]=temp_x;
        voxel_coordinates[i][1]=temp_z;
    }
}
