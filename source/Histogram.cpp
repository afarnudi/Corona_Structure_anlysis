//
//  Histogram.cpp
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

void tomo::histogram (void){
//    for (int i=0; i<gray_level; i++) {
//        hist[i]=0;
//    }
//    cout<<x_dim<<endl;
    int temp;
    for (int k=0; k<z_dim; k++) {
        for (int j=0; j<y_dim; j++) {
            for (int i=0; i<x_dim; i++) {
                cout<<i<<"\t"<<x_dim<<endl;
                temp = voxels[k][j][i];
                hist[temp]+=1;
            }
            cout<<endl;
        }
    }
}

