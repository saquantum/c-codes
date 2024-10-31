#include "neillsdl2.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
#include<math.h>

#define MAXSIZE 100
#define MAXNUMBER 200
#define INITBIGR 180
#define INITSMLR 20
#define LOOPSTART 1
#define MAXUINT8 255

typedef struct{
    Uint8 r;
    Uint8 g;
    Uint8 b;
}colour;

typedef struct{
    int centerX;
    int centerY;
    int bigR;
    int smallR;
    double lineangle;
}ringinfo;

long long parsell(char* str);
int primefactors(long long n, int* buffer);
int primefactors2draw(int length, int* buffer);
void printfactors(int* a, int len);
bool isprime(int n);
void drawcircles(SDL_Simplewin* sw, int prime, ringinfo ri, colour c);
void recursion(SDL_Simplewin* sw, int n,  int length, int* facts, int index, ringinfo ri, int* colourindex);
colour getcolour(int size, int index);

int main(void) {
    SDL_Simplewin sw;
    Neill_SDL_Init(&sw);
    
    ringinfo ri={WWIDTH / 2, WHEIGHT / 2, INITBIGR, INITSMLR, M_PI / 2};
    // we are unable to implement this for a big enough number ~200 due to limited resolution
    for(int i=LOOPSTART;!sw.finished && i<MAXNUMBER;i++){
        
        // reset the screen
        SDL_SetRenderDrawColor(sw.renderer, 0, 0, 0, MAXUINT8);
        SDL_RenderClear(sw.renderer);
        
        // compute the factorisation
        int facts[MAXSIZE]={0};
        int len=primefactors(i,facts);
        len=primefactors2draw(len,facts);
        
        // recursively draw circles
        int colourindex=0;
        recursion(&sw, i, len, facts, 0, ri, &colourindex);
        
        // update & delay 
        Neill_SDL_UpdateScreen(&sw);
        SDL_Delay(1000);
        Neill_SDL_Events(&sw);
    }
    SDL_Quit();
    atexit(SDL_Quit);
    return 0;
}

void recursion(SDL_Simplewin* sw, int n,  int length, int* facts, int index, ringinfo ri, int* colourindex){
    // we treat 4 as a prime when plotting! 
    // length: length of factorization
    // facts: the array of prime factors
    // index: points to the current prime of facts
    
    // exit condition
    if(index>=length){
        // control the size of circles
        int plotbigR=ri.bigR+facts[index - 1]; // facts[index - 1] is the number of small circles of current ring
        int plotsmallR=(double)(2*M_PI*ri.bigR)/4.0;
        plotsmallR=ri.smallR<plotsmallR?ri.smallR:plotsmallR;
        plotsmallR=plotsmallR<plotbigR?plotsmallR:plotbigR;
        ringinfo tempri={ri.centerX, ri.centerY, plotbigR+1, plotsmallR+1, ri.lineangle};
        
        colour c=getcolour(n,*colourindex);
        drawcircles(sw, 1, tempri, c);
        (*colourindex)++;
        return;
    }
    
    int prime=facts[index];
    double anglediff = 2 * M_PI / prime;
    double angle0 = prime == 2? ri.lineangle : M_PI / 2 - M_PI / prime;
    
    ringinfo nextri = ri;
    for(int i=0;i<prime;i++){
        double angle = angle0 + i * anglediff;
        nextri.centerX = ri.centerX + (int)(ri.bigR * cos(angle));
        nextri.centerY = ri.centerY + (int)(ri.bigR * sin(angle));
        nextri.bigR = ri.bigR/prime;
        nextri.lineangle=angle;
        recursion(sw, n, length, facts, index + 1, nextri, colourindex);
    }
}

void drawcircles(SDL_Simplewin* sw, int prime, ringinfo ri, colour c){
    // draw a big ring of prime small circles with radius smallR centered at (X,Y) with radius bigR.
    if(prime==1){
        ri.bigR=0;
    }
    double anglediff = 2 * M_PI / prime;
    double angle0;
    // if prime=2, the line angle is taken into consideration.
    if (prime == 2) {
        angle0 = ri.lineangle;
    } else {
        // this formula assures that the bottom edge is parallel to the window
        angle0 = M_PI / 2 - M_PI / prime; 
    }
    double angle;
    for (int i = 0; i < prime; i++) {
        angle = angle0 + i * anglediff;
        // using polar coordinates, x=x0+cos(θ), y=y0+sin(θ).
        int smallCenterX = ri.centerX + (int)(ri.bigR * cos(angle));
        int smallCenterY = ri.centerY + (int)(ri.bigR * sin(angle));
        Neill_SDL_SetDrawColour(sw,c.r,c.g,c.b);
        Neill_SDL_RenderFillCircle(sw->renderer, smallCenterX, smallCenterY, ri.smallR);
    }
}

colour getcolour(int size, int index) {
    colour c = {0, 0, 0};
    // prettifying edge cases
    if (size <= 1) {
        c.b=MAXUINT8;
        return c;
    }
    if (size == 2) {
        c.b=index==0?MAXUINT8:0;
        c.g=index==1?MAXUINT8:0;
        return c;
    }
    if (size == 3) {
        c.b=index==0?MAXUINT8:0;
        c.r=index==1?MAXUINT8:0;
        c.g=index==2?MAXUINT8:0;
        return c;
    }
    
    double ratio=(double)index/(double)(size-1);
    double pos;
    // divide into 3 segments: b->r->g->b
    if (ratio < 1.0 / 3.0) {
        // blue to red, linearly shift c.b to 0 while c.r to 255
        pos = ratio * 3;  // a magic formula that makes pos in [0,1].
        c.b = (Uint8)(MAXUINT8 * (1 - pos));  
        c.r = (Uint8)(MAXUINT8 * pos);        
    } else if (ratio < 2.0 / 3.0) {
        // red to green
        pos = (ratio - 1.0 / 3.0) * 3;  // a magic formula that makes pos in [0,1].
        c.r = (Uint8)(MAXUINT8 * (1 - pos));      
        c.g = (Uint8)(MAXUINT8 * pos);            
    } else {
        // green to blue
        pos = (ratio - 2.0 / 3.0) * 3;  // a magic formula that makes pos in [0,1].
        c.g = (Uint8)(MAXUINT8 * (1 - pos));       
        c.b = (Uint8)(MAXUINT8 * pos);             
    }
    return c;
}

long long parsell(char* str) {
    long long n = 0L;
    int i = 0;
    bool minus = false;
    while (str[i]) {
        if (str[0] == '-') {
            minus = true;
        }
        if ('0' <= str[i] && str[i] <= '9') {
            n = n * 10L + (str[i] - '0');
        }
        i++;
    }
    return minus ? -n : n;
}

int primefactors(long long n, int* buffer) {
    int count = 0;
    while (n % 2 == 0) {
        buffer[count++] = 2;
        n /= 2;
    }
    while (n > 1) {
        bool flag = false;
        for (long long i = 3; !flag && i <= sqrt(n); i+=2) {
            if (isprime(i) && n % i == 0) {
                buffer[count++] = i;
                flag = true;
                n = n / i;
            }
        }
        if (!flag) {  // If no prime divisor is found, n is prime itself
            buffer[count++] = n;
            n = 1; // set n=1 to exit loop
        }
    }
    if (count > 1) {
        for (int i = 1; i < count; i++) {
            for (int j = i; j > 0; j--) {
                if (buffer[j] < buffer[j - 1]) {
                    int temp = buffer[j];
                    buffer[j] = buffer[j - 1];
                    buffer[j - 1] = temp;
                }
            }
        }
    }
    return count;
}

int primefactors2draw(int length, int* buffer){
    int out=0;
    int count2=0;
    for(int i=0;i<length;i++){
        if(buffer[i]==2){
            count2++;
        }
    }
    int count4=count2/2;
    count2=count2%2;
    int* temp=(int*)calloc(length,sizeof(int));
    assert(temp);
    int k = 0;
    for (int i = length - 1; i >= 0; i--) {
        if (buffer[i] != 2) {
            temp[k++] = buffer[i];
            out++;
        }
    }
    if (count2 > 0) {
        temp[k++] = 2;
        out++;
    }
    for (int i = 0; i < count4; i++) {
        temp[k++] = 4;
        out++;
    }
    for(int i=0;i<length;i++){
        if(i<out){
            buffer[i]=temp[i];
        }else{
            buffer[i]=0;
        }
    }
    free(temp);
    return out;
}

void printfactors(int* a, int len) {
    if (len <= 0) {
        return;
    }
   
    long long n = 1;
    for (int i = 0; i < len; i++) {
        n = n * a[i];
    }
    int count = 1;
    for (int i = 1; i < len; i++) {
        if (a[i - 1] != a[i]) {
            count++;
        }
    }

    // might use a hashMap to count.
    int* facs = (int*)calloc(count, sizeof(int));
    int* expos = (int*)calloc(count, sizeof(int));
    assert(facs && expos);
    int factor = a[0];
    int exponent = 1;
    int k = 0;
    for (int i = 1; i < len && k<count; i++) {
        if (a[i] == factor) {
            exponent++;
        }
        else {
            facs[k] = factor;
            expos[k] = exponent;
            k++;
            factor = a[i];
            exponent = 1;
        }
    }
    facs[k] = factor;
    expos[k] = exponent;
    k++;
    printf("%lld = 1 x ", n);
    for (int i = 0; i < k; i++) {
        if (expos[i] == 1) {
            printf("%d", facs[i]);
        }
        else {
            printf("%d^%d", facs[i], expos[i]);
        }
        if (i + 1 < k) {
            printf(" x ");
        }
    }
    printf("\n");
    free(facs);
    free(expos);
}

bool isprime(int n) {
    if (n <= 1) {
        return false;
    }
    if (n == 2) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }
    for (int i = 3; i <= floor(sqrt((double)n)); i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

