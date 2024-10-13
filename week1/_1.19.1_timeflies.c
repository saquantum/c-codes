#include<stdio.h>
#include<assert.h>
//15:40 16:30 ->(16-15:30-40)=(1:-10)=50
// 22:40 04:15 ->(23-22:60-40)+(4:15)

int timediff(int h1,int m1,int h2,int m2);

int main(){
    int h1,m1,h2,m2;
    int h,m;
    
    printf("enter two times in the format: 23:00 04:15\n");
    scanf("%d:%d %d:%d",&h1,&m1,&h2,&m2);
    assert(h1>=0 && h2>=0 && h1<24 && h2<24);
    assert(m1>=0 && m2>=0 && m1<60 && m2<60);
    h=timediff(h1,m1,h2,m2)/60;
    m=timediff(h1,m1,h2,m2)%60;
    printf("difference is %02d:%02d\n",h,m);
    return 0;
}

int timediff(int h1,int m1,int h2,int m2){
    // the returned time difference is in minute
    if (h2>h1 || ( h2==h1 && m2>=m1 )){
        return (m2-m1)+(h2-h1)*60;
    }
    return (23-h1)*60+(60-m1)+h2*60+m2;
    
    
}
