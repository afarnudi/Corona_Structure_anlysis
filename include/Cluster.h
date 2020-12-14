//
//  Cluster.h
//  Mahmoudi Image Processing
//
//  Created by Ali Farnudi on 10/07/2018.
//  Copyright © 2018 Ali FarnudiSUT. All rights reserved.
//

#ifndef Cluster_h
#define Cluster_h

#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

class Cluster{
    int size=0;
    bool com_flag=false, RG_flag=false;
    double radius_of_gyration=0, com_position[3]={0};
    vector<vector<int> > voxel_coordinates;
    double moment_of_inertia[3][3]={0};
    double RG_tensor[3][3]={0};
    double RG_eigen_values[3]={0};
    double relative_shape_anisotropy=0;
    double shape_asphericity=0;
    double com_pos_length=0;
    
    void calculate_radius_of_gyration (void);
    void calculate_com_position (void);
    void rotation_about_z(void);
    void rotation_about_y(void);
    void calculate_MI_tensor(void);
    void calculate_RG_tensor(void);
public:
    void shape_processor(void);
    
    void add_voxel(int k, int j, int i){
        vector<int> coor;
        coor.resize(3);
        coor[0]=k;
        coor[1]=j;
        coor[2]=i;
        voxel_coordinates.push_back(coor);
        size++;
    }
    int return_size(void){
        return size;
    }
    double return_radius_of_gyration (void){
        if (!RG_flag) {
            calculate_radius_of_gyration();
        }
        return radius_of_gyration;
    }
    double com_distance_from_a_point(double k, double j, double i){
        if (!com_flag) {
            calculate_com_position();
        }
        return sqrt((com_position[0]-k)*(com_position[0]-k)+(com_position[1]-j)*(com_position[1]-j)+(com_position[2]-i)*(com_position[2]-i));
    }
    void shift_cluster(double k, double j, double i){
        for (int i=0; i<voxel_coordinates.size(); i++) {
            voxel_coordinates[i][0]+=k;
            voxel_coordinates[i][1]+=j;
            voxel_coordinates[i][2]+=i;
        }
        if (!com_flag) {
            calculate_com_position();
        }
        com_position[0]+=k;
        com_position[1]+=j;
        com_position[2]+=i;
        com_pos_length=sqrt(com_position[0]*com_position[0]+com_position[1]*com_position[1]+com_position[2]*com_position[2]);
    }
    double lambda_1(void){
        return RG_eigen_values[0];
    }
    double lambda_2(void){
        return RG_eigen_values[1];
    }
    double lambda_3(void){
        return RG_eigen_values[2];
    }
    double anisotropy(void){
        return relative_shape_anisotropy;
    }
    double asphericity(void){
        return shape_asphericity;
    }
};

#endif /* Cluster_h */
