//
//  Otsu Binerization.cpp
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

void tomo::otsu_binerization(void){
    double wk_background;//Probability of background class appearence
    double wk_object;//Probability of object class appearence
    double mu_backgraound;//background mean class level
    double mu_object;//object mean class level
    double sigma2_B;//Between class variance
    double sum_hist_background;// sum of the histograms of the background class
    double sum_hist_object;// sum of the histograms of the object class
    double sigma_max=0;
    int N=x_dim*y_dim*z_dim;
    //unsigned char intbin[2]={'!','Z'};// will use to set the binerized voxel
    cout<<x_dim<<endl;
    histogram();
    
    for (int k=0; k<gray_level; k++) {
        wk_background=0;
        wk_object=0;
        mu_backgraound=0;
        mu_object=0;
        sum_hist_background=0;
        sum_hist_object=0;
        
        
        // calculation of the Probability of background class appearence, background mean class level for a given k
        for (int i=0; i<k; i++) {
            wk_background+=hist[i]/N;
            mu_backgraound+=i*hist[i];
            sum_hist_background+=hist[i];
        }
        mu_backgraound/=sum_hist_background;
        
        
        // calculation of the Probability of object class appearence, object mean class level for a given k
        for (int i=k; i<gray_level; i++) {
            wk_object+=hist[i]/N;
            mu_object+=i*hist[i];
            sum_hist_object+=hist[i];
        }
        mu_object/=sum_hist_object;
        
        
        //calculating the between class variance, the maximum variance will be the Otsu threshold
        sigma2_B=wk_background*wk_object*(mu_backgraound-mu_object)*(mu_backgraound-mu_object);
        if (sigma2_B>=sigma_max) {
            k_threshold=k;
            sigma_max=sigma2_B;
        }
        
    }
    for (int k=0; k<z_dim; k++) {
        for (int j=0; j<y_dim; j++) {
            for (int i=0; i<x_dim; i++) {
                if (voxels[k][j][i]>=k_threshold) {
                    voxels[k][j][i]=gray_level-1;//(unsigned short int)intbin[1];
                }else {
                    voxels[k][j][i]=0;//(unsigned short int)intbin[0];
                }
                
            }
        }
    }
    cout<<"File binerized using the Otsu method with a threshold of "<<k_threshold<<endl;
}

