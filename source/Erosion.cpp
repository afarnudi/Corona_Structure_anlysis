//
//  tomo.cpp
//  GPC-code
//
//  Created by Ali Farnudi on 24/12/2012.
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
void tomo::inverse_erosion (void){
    accumulator_in_eros.resize(z_dim);
    for (int k=0; k<z_dim; k++) {
        accumulator_in_eros[k].resize(x_dim);
        for (int i=0; i<x_dim; i++) {
            accumulator_in_eros[k][i].resize(y_dim);
            for (int j=0; j<y_dim; j++) {
                //We shall creat a temporarily list to store the original Voxels before Erosion
                accumulator_in_eros[k][i][j]=0;
            }
        }
    }
    for (int k=1; k<z_dim-1; k++) {
        for (int i=1; i<x_dim-1; i++) {
            for (int j=1; j<y_dim-1; j++) {
                if (voxels[k][i][j]==gray_level-1) {
                    if (voxels[k][i-1][j-1]==0||voxels[k][i][j-1]==0||voxels[k][i+1][j-1]==0||voxels[k][i-1][j]==0||voxels[k][i+1][j]==0||voxels[k][i-1][j+1]==0||voxels[k][i][j+1]==0||voxels[k][i+1][j+1]==0||voxels[k-1][i-1][j-1]==0||voxels[k-1][i][j-1]==0||voxels[k-1][i+1][j-1]==0||voxels[k-1][i-1][j]==0||voxels[k-1][i+1][j]==0||voxels[k-1][i-1][j+1]==0||voxels[k-1][i][j+1]==0||voxels[k-1][i+1][j+1]==0||voxels[k-1][i][j]==0||voxels[k+1][i-1][j-1]==0||voxels[k+1][i][j-1]==0||voxels[k+1][i+1][j-1]==0||voxels[k+1][i-1][j]==0||voxels[k+1][i+1][j]==0||voxels[k+1][i-1][j+1]==0||voxels[k+1][i][j+1]==0||voxels[k+1][i+1][j+1]==0||voxels[k+1][i][j]==0) {
                        accumulator_in_eros[k][i][j]=gray_level-1;
                    }
                }
            }
        }
    }
    
}
//The errosion function will delete any point with at least one black naighbor
void tomo::erosion(void){
    vector<vector<vector<unsigned short int> > > voxels_temp;
    voxels_temp.resize(z_dim);
    for (int k=0; k<z_dim; k++) {
        voxels_temp[k].resize(x_dim);
        for (int i=0; i<x_dim; i++) {
            voxels_temp[k][i].resize(y_dim);
            for (int j=0; j<y_dim; j++) {
                //We shall creat a temporarily list to store the original Voxels before Erosion
                voxels_temp[k][i][j]=voxels[k][i][j];
            }
        }
    }
    for (int k=1; k<z_dim-1; k++) {
        for (int i=1; i<x_dim-1; i++) {
            for (int j=1; j<y_dim-1; j++) {
                if (voxels[k][i][j]==gray_level-1) {
                    if (voxels[k][i-1][j-1]==0||voxels[k][i][j-1]==0||voxels[k][i+1][j-1]==0||voxels[k][i-1][j]==0||voxels[k][i+1][j]==0||voxels[k][i-1][j+1]==0||voxels[k][i][j+1]==0||voxels[k][i+1][j+1]==0||voxels[k-1][i-1][j-1]==0||voxels[k-1][i][j-1]==0||voxels[k-1][i+1][j-1]==0||voxels[k-1][i-1][j]==0||voxels[k-1][i+1][j]==0||voxels[k-1][i-1][j+1]==0||voxels[k-1][i][j+1]==0||voxels[k-1][i+1][j+1]==0||voxels[k-1][i][j]==0||voxels[k+1][i-1][j-1]==0||voxels[k+1][i][j-1]==0||voxels[k+1][i+1][j-1]==0||voxels[k+1][i-1][j]==0||voxels[k+1][i+1][j]==0||voxels[k+1][i-1][j+1]==0||voxels[k+1][i][j+1]==0||voxels[k+1][i+1][j+1]==0||voxels[k+1][i][j]==0) {
                        voxels_temp[k][i][j]=0;
                    }
                }
            }
        }
    }
    for (int k=0; k<z_dim; k++) {
        for (int i=0; i<x_dim; i++) {
            for (int j=0; j<y_dim; j++) {
                voxels[k][i][j]=voxels_temp[k][i][j];
            }
        }
    }
    
}

