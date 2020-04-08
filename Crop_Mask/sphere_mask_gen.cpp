//
//  sphere_mask_gen.cpp
//  Mahmoudi Image Processing
//
//  Created by Ali Farnudi on 19/05/2018.
//  Copyright © 2018 Ali FarnudiSUT. All rights reserved.
//

#include "sphere_mask_gen.hpp"

void sphere_mask_generator(vector<vector<int> > &sphere_mask, int sphere_radius){
    vector<int> temp_coordinate;
    temp_coordinate.resize(3);
    for (int k=-sphere_radius; k<=sphere_radius; k++) {
        for (int j=-sphere_radius; j<=sphere_radius; j++) {
            for (int i=-sphere_radius; i<=sphere_radius; i++) {
                int temp_r=sqrt(k*k+j*j+i*i);
                if (temp_r==sphere_radius) {
                    temp_coordinate[0]=i;
                    temp_coordinate[1]=j;
                    temp_coordinate[2]=k;
                    sphere_mask.push_back(temp_coordinate);
                }
            }
        }
    }
}


void sphere_mask_generator(vector<vector<int> > &sphere_mask, int inner_sphere_radius, int outer_sphere_radius){
    vector<int> temp_coordinate;
    temp_coordinate.resize(3);
    for (int k=-outer_sphere_radius; k<=outer_sphere_radius; k++) {
        for (int j=-outer_sphere_radius; j<=outer_sphere_radius; j++) {
            for (int i=-outer_sphere_radius; i<=outer_sphere_radius; i++) {
                int temp_r=sqrt(k*k+j*j+i*i);
                if (temp_r<=outer_sphere_radius && temp_r>=inner_sphere_radius) {
                    temp_coordinate[0]=i;
                    temp_coordinate[1]=j;
                    temp_coordinate[2]=k;
                    sphere_mask.push_back(temp_coordinate);
                }
            }
        }
    }
    
    
}
