//
//  neighbour_voxel_count.cpp
//  Mahmoudi Image Processing
//
//  Created by Ali Farnudi on 19/05/2018.
//  Copyright © 2018 Ali FarnudiSUT. All rights reserved.
//

#include <stdio.h>
#include "tomo.h"

void tomo::neighbour_voxel_2D_counter(void){
    //unsigned short int intbin[2]={0,1};// will use to set the binerized voxel
    
    for (int k=0; k<z_dim; k++) {
        for (int j=20; j<y_dim-20; j++) {
            for (int i=20; i<x_dim-20; i++) {
                
                if (voxels[k][j][i]==gray_level-1) {
                    int counter=0;
                    for (int j2=j-20; j2<j+20; j2++) {
                        for (int i2=i-20; i2<i+20; i2++) {
                            //                            cout<<voxels[k][j2][i2]<<endl;
                            if (voxels[k][j2][i2]==gray_level-1) {
                                counter++;
                            }
                        }
                    }
                    //                    cout<<counter<<endl;
                    if (counter<=150) {
                        voxels[k][j][i]=0;
                    }
                }
                
                
            }
        }
    }
    cout<<"File Modified"<<endl;
}

void tomo::neighbour_voxel_3D_counter(void){
    //unsigned short int intbin[2]={0,1};// will use to set the binerized voxel
    int edge=10;
    for (int k=edge; k<z_dim-edge; k++) {
        for (int j=edge; j<y_dim-edge; j++) {
            for (int i=edge; i<x_dim-edge; i++) {
                
                if (voxels[k][j][i]==gray_level-1) {
                    int counter=0;
                    for (int k2=k-edge; k2<k+edge; k2++) {
                        for (int j2=j-edge; j2<j+edge; j2++) {
                            for (int i2=i-edge; i2<i+edge; i2++) {
                                //                            cout<<voxels[k][j2][i2]<<endl;
                                if (voxels[k2][j2][i2]==gray_level-1) {
                                    counter++;
                                }
                            }
                        }
                        //                    cout<<counter<<endl;
                        if (counter<=40) {
                            voxels[k][j][i]=0;
                        }
                    }
                    
                }
                
                
            }
        }
    }
    cout<<"File Modified"<<endl;
}

