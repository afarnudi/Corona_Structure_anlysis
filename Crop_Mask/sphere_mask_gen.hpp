//
//  sphere_mask_gen.hpp
//  Mahmoudi Image Processing
//
//  Created by Ali Farnudi on 19/05/2018.
//  Copyright © 2018 Ali FarnudiSUT. All rights reserved.
//

#ifndef sphere_mask_gen_hpp
#define sphere_mask_gen_hpp

#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;

void sphere_mask_generator(vector<vector<int> > &sphere_mask, int sphere_radius);
void sphere_mask_generator(vector<vector<int> > &sphere_mask, int inner_sphere_radius, int outer_sphere_radius);

void circle_mask_generator(vector<vector<int> > &circle_mask, int circle_radius);
void circle_mask_generator(vector<vector<int> > &circle_mask, int inner_circle_radius, int outer_circle_radius);

#endif /* sphere_mask_gen_hpp */
