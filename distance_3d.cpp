using namespace std ; 
#include <time.h>
#include <iostream>  
#include <cstdlib> 
#include <math.h> 
class point3d {
public: 
    int x,y,z; 
}; 
float distance(point3d p1 , point3d p2) {
    int a = p1.x - p2.x ;
    int b = p1.y -p2.y ;
    int c = p1.z -p2.z ;
    int j = pow(a,2) ;
    int k = pow(b,2) ; 
    int l = pow(c,2) ; 
    int s = j + k + l; 
    float res = sqrt(s) ; 
    return res ;  
}

int comparex(const void* a ,const void* b) { 
    point3d *p1 = (point3d *)a, *p2 = (point3d *)b;
    return (p1->x - p2->x);
}

int comparey(const void* a ,const void* b) { 
    point3d *p1 = (point3d *)a, *p2 = (point3d *)b;
    return (p1->y - p2->y);
}

int comparez(const void* a ,const void* b) { 
    point3d *p1 = (point3d *)a, *p2 = (point3d *)b;
    return (p1->z - p2->z);
} 

float bruteforcealgo(point3d p[] , int n) { 
    int min = 200; 
    for (int i = 0 ; i<n ; i++) { 
        for ( int j= i+1 ; j<n; j++ ) { 
            if(distance(p[i],p[j])<min) { 
                min = distance(p[i],p[j]); 
            }
        }
    }
    return min ; 
}
 
float min2distance(float a ,float b ) { 
    return (a<b) ? a:b ; 
} 

float closestbyY(point3d point[] , int n , float d ) { 
    float min = d ; 
    qsort(point , n , sizeof(point3d) , comparey) ; 

    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n && (point[j].y - point[i].y) < min; ++j) {
            if (distance(point[i],point[j]) < min) {
                min = distance(point[i], point[j]);
            } 
        } 
    }
    return min;
} 


float closest1(point3d point[] , int n) { 
    if(n<=3){ 
        return bruteforcealgo(point,n) ; 
    }

    int middle = n/2 ; 
    point3d middlepoint = point[middle] ; 

    float cl = closest1(point,middle) ;
    float cr = closest1(point + middle ,n-middle) ; 


    float closest = min2distance(cl,cr) ; 

    point3d horizontal[n] ; 
    int s = 0 ; 
    for(int i= 0 ; i <n ; i++ ) { 
        if(abs(point[i].x - middlepoint.x)<closest) { 
            horizontal[s] = point[i] , s++ ; 
        }
    }

    return min2distance(closest,closestbyY(horizontal,s,closest))  ; 
}

float closest2(point3d point[] , int n) { 
    if(n<=3){ 
        return bruteforcealgo(point,n) ; 
    }

    int middle = n/2 ; 
    point3d middlepoint = point[middle] ; 

    float cl = closest2(point,middle) ;
    float cr = closest2(point + middle ,n-middle) ; 


    float closest = min2distance(cl,cr) ; 

    point3d horizontal[n] ; 
    int s = 0 ; 
    for(int i= 0 ; i <n ; i++ ) { 
        if(abs(point[i].z- middlepoint.z)<closest) { 
            horizontal[s] = point[i] , s++ ; 
        }
    }

    return min2distance(closest,closestbyY(horizontal,s,closest))  ; 
}

float riilclosest(point3d point[] , int n) { 
    qsort(point,n,sizeof(point3d),comparex) ; 

    float a = closest1(point,n); 

    qsort(point,n,sizeof(point3d),comparez) ; 

    float b = closest2(point,n);

    return min2distance(a,b) ; 
} 





int main () {  

    time_t start , end ; 
    time(&start) ; 

    int n ; 
    scanf("%d",&n) ; 
    
    point3d point[n] ;
    for(int i=0 ; i<n ; i++) { 
        point[i].x = rand() % 100  ;
        point[i].y = rand() % 100  ;
        point[i].z = rand() % 100  ;
    }
    
   
    printf("selesai\n") ; 
    bool ketemu = false ; 
    for(int i = 0 ; i<n ; i++) { 
        for(int j = i + 1 ; j <n ; j++) {  
            if(distance(point[i],point[j])==riilclosest(point,n) && not ketemu) { 
                cout<<point[i].x<<" "<<point[i].y<<" "<<point[i].z<<" ";
                cout<<endl ;  
                cout<<point[j].x<<" "<<point[j].y<<" "<<point[j].z<<" ";
                cout<<endl ;  
                ketemu = true ; 
            }
        }
    }
    cout << "The smallest distance is " << riilclosest(point, n)<<endl;
    

    time(&end) ; 
    double time_taken = double(end - start) ; 
    cout << "Time taken by program is : " << fixed
         << time_taken ;
    cout << " sec " << endl;
    
    return 0;

}
