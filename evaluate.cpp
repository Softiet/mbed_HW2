#include <math.h>
int evaluate(float* data,float samp_interval){
    float slope = data[1]-data[0]>0?1:-1;
    float threshold = (data[0]+data[1])/2.0;
    int i;
    int counter = 0;
    int last; 
    for(i=1;i<299;i++){
        if(data[i] < threshold && data[i+1] > threshold &&slope == 1){
            counter ++;
            last = i;
        }
        else if(data[i] > threshold && data[i+1]<threshold && slope == -1){
            counter++;
            last = i;
        }
    }
    float calculated = float(counter)/(last*samp_interval);
    return int(round(calculated));
}