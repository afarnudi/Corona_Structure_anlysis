//
//  shape_processor_function.cpp
//  Mahmoudi Image Processing
//
//  Created by Ali Farnudi on 14/07/2018.
//  Copyright © 2018 Ali FarnudiSUT. All rights reserved.
//

#include <stdio.h>
#include "Cluster.h"
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>

void Cluster::shape_processor(void){
   
   calculate_RG_tensor();
    double data[]={RG_tensor[0][0], RG_tensor[0][1], RG_tensor[0][2],
                   RG_tensor[1][0], RG_tensor[1][1], RG_tensor[1][2],
                   RG_tensor[2][0], RG_tensor[2][1], RG_tensor[2][2]  };
    gsl_matrix_view m
    = gsl_matrix_view_array (data, 3, 3);
    
    gsl_vector *eval = gsl_vector_alloc (3);
    gsl_matrix *evec = gsl_matrix_alloc (3, 3);
    
    gsl_eigen_symmv_workspace * w =
    gsl_eigen_symmv_alloc (3);
    
    gsl_eigen_symmv (&m.matrix, eval, evec, w);
    
    gsl_eigen_symmv_free (w);
    
    gsl_eigen_symmv_sort (eval, evec,
                          GSL_EIGEN_SORT_ABS_ASC);
    
    RG_eigen_values[0]= gsl_vector_get (eval, 2);
    RG_eigen_values[1]= gsl_vector_get (eval, 1);
    RG_eigen_values[2]= gsl_vector_get (eval, 0);
    
    
    gsl_vector_free (eval);
    gsl_matrix_free (evec);

    relative_shape_anisotropy=1-3*(RG_eigen_values[0]*RG_eigen_values[1]+RG_eigen_values[1]*RG_eigen_values[2]+RG_eigen_values[0]*RG_eigen_values[2])/((RG_eigen_values[2]+RG_eigen_values[1]+RG_eigen_values[0])*(RG_eigen_values[2]+RG_eigen_values[1]+RG_eigen_values[0]));
    shape_asphericity=RG_eigen_values[0]-0.5*(RG_eigen_values[1]+RG_eigen_values[2]);
}
