//
//  Hoshen_kopelman_functions.hpp
//  Mahmoudi Image Processing
//
//  Created by Ali Farnudi on 19/05/2018.
//  Copyright © 2018 Ali FarnudiSUT. All rights reserved.
//

#ifndef Hoshen_kopelman_functions_hpp
#define Hoshen_kopelman_functions_hpp

#include <stdio.h>
#include <vector>

using namespace std;

void set_voxel_colour(vector<vector<vector<int> > > &coloured_voxels, int coordinates[3],vector< int > &Label, vector< int > &Cluster_size, int &colour);

void HK_colour_voxels(vector<vector<vector<int> > > &coloured_voxels, vector< int > &Label, vector< int > &Cluster_size, int &colour);


#endif /* Hoshen_kopelman_functions_hpp */
