//
//  UI.cpp
//  Mahmoudi Image Processing
//
//  Created by Ali Farnudi on 18/05/2018.
//  Copyright © 2018 Ali FarnudiSUT. All rights reserved.
//

#include "UI.hpp"
#include <iostream>
#include <unistd.h>
using namespace std;

void help (void){
    cerr<< "\nHow to use tomo:\n ./tomo <Flags> <name of the vol file to load> <name of the new file to save(optional)>"
    << "\n  Flags:"
    << "\n  -?     : This message"
    << "\n  -x xxx : X Dimention of the Vol file (deafult: 550)"
    << "\n  -y xxx : y Dimention of the Vol file (deafult: 550)"
    << "\n  -z xxx : z Dimention of the Vol file (deafult: 500)"
    << "\n  -b     : Binerize Vol file using the Otsu method"
    << "\n  -k xxx : Binerize using given value"
    << "\n  -e     : Errosion on (Default off)"
    << "\n  -h     : Haugh Transformation on (Default off)"
    << "\n  -f     : Find chains"
    <<endl;
}


//void set_flags (char val){
//    while (val!=-1){
//        switch (val) {
//            case '?' :
//                help();
//                return 0;
//            case 'x' :
//                X=atoi(optarg);
//                break;
//            case 'y' :
//                Y=atoi(optarg);
//                break;
//            case 'z' :
//                Z=atoi(optarg);
//                break;
//            case 'b' :
//                bflag=1;
//                break;
//            case 'k' :
//                kflag=1;
//                k_value=atoi(optarg);
//                break;
//            case 'e' :
//                errosion=1;
//                break;
//            case 'h' :
//                haugh_transformation=1;
//                break;
//            case 'f':
//                find_chains=1;
//                break;
//            default:
//                help();
//                return 0;
//                
//        }
//    }
//    
//    
//}

