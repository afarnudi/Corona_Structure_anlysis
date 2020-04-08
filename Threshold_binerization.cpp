//
//  threshold_binerization.cpp
//  test
//
//  Created by Ali Farnudi on 28/04/2013.
//
//
/*
 Copyright 2012
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "tomo.h"

void tomo::threshold_binerization(int threshold){
    //unsigned short int intbin[2]={0,1};// will use to set the binerized voxel
    k_threshold=threshold;
    for (int k=0; k<z_dim; k++) {
        for (int j=0; j<y_dim; j++) {
            for (int i=0; i<x_dim; i++) {
                if (voxels[k][j][i]>=k_threshold) {
                    voxels[k][j][i]=0;
                }else {
                    voxels[k][j][i]=gray_level-1;
                }
                
            }
        }
    }
    cout<<"File binerized  with a threshold of "<<k_threshold<<endl;
    string save_name="hc_th_58_";
//    save_tomo_sequence(save_name);
}

