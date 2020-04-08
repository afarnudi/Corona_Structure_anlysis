//
//  Colouring.cpp
//  Mahmoudi Image Processing
//
//  Created by Ali Farnudi on 25/06/2018.
//  Copyright © 2018 Ali FarnudiSUT. All rights reserved.
//

#include "Hoshen_kopelman_functions.hpp"
#include "tomo.h"

void set_voxel_colour(vector<vector<vector<int> > > &coloured_voxels, int coordinates[3], vector< int > &Label, vector< int > &Cluster_size, int &colour){
    
    int k=coordinates[0],j=coordinates[1],i=coordinates[2];
    int under=Label[coloured_voxels[k-1][j][i]];
    int left=Label[coloured_voxels[k][j][i-1]];
    int down=Label[coloured_voxels[k][j-1][i]];

    if (under==0 && left==0 && down==0){
        colour++;
        Label.push_back(colour);
        Cluster_size.push_back(1);
        coloured_voxels[k][j][i]=colour;
        
    } else if (under!=0){
        coloured_voxels[k][j][i]=under;
        Cluster_size[Label[under]]++;
        if (down!=0 && down!=under) {
            int Min=min(down, under), Max=max(down, under);
            
            Cluster_size[Min]+=Cluster_size[Max];
            Cluster_size[Max]=0;
            Label[Max]=Min;
        }
        if (left!=0 && left!=Label[under]) {
            int Min=min(left, Label[under]), Max=max(left, Label[under]);
            
            Cluster_size[Min]+=Cluster_size[Max];
            Cluster_size[Max]=0;
            Label[Max]=Min;
        }
    } else if (down!=0){
        coloured_voxels[k][j][i]=down;
        Cluster_size[down]++;
        if (left!=0 && left!=down) {
            int Min=min(left, down), Max=max(left, down);
            
            Cluster_size[Min]+=Cluster_size[Max];
            Cluster_size[Max]=0;
            Label[Max]=Min;
        }
    } else if (left!=0){
        coloured_voxels[k][j][i]=left;
        Cluster_size[left]++;
    }
    
}

