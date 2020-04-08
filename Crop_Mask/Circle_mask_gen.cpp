//
//  sphere_mask_gen.cpp
//  Mahmoudi Image Processing
//
//  Created by Ali Farnudi on 19/05/2018.
//  Copyright © 2018 Ali FarnudiSUT. All rights reserved.
//

#include "sphere_mask_gen.hpp"

void circle_mask_generator(vector<vector<int> > &circle_mask, int circle_radius){
    vector<int> temp_coordinate;
    temp_coordinate.resize(2);
    for (int j=-circle_radius; j<=circle_radius; j++) {
        for (int i=-circle_radius; i<=circle_radius; i++) {
            int temp_r=sqrt(j*j+i*i);
            if (temp_r==circle_radius) {
                temp_coordinate[0]=i;
                temp_coordinate[1]=j;
                circle_mask.push_back(temp_coordinate);
            }
        }
    }
}


void circle_mask_generator(vector<vector<int> > &circle_mask, int inner_circle_radius, int outer_circle_radius){
    vector<int> temp_coordinate;
    temp_coordinate.resize(3);
    for (int j=-outer_circle_radius; j<=outer_circle_radius; j++) {
        for (int i=-outer_circle_radius; i<=outer_circle_radius; i++) {
            int temp_r=sqrt(j*j+i*i);
            if (temp_r<=outer_circle_radius && temp_r>=inner_circle_radius) {
                temp_coordinate[0]=i;
                temp_coordinate[1]=j;
                temp_coordinate[2]=0;
                circle_mask.push_back(temp_coordinate);
            }
        }
    }


}
