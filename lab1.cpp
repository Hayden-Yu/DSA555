/*starter file for lab1*/

unsigned int factorial(unsigned int n){
    unsigned res = n;
    while(n > 1) {
        res *= --n;
    }
    return res == 0 ? (unsigned)1 : res;
}
double power (double base, unsigned int n){
    double res = base;
    for(unsigned i = 1; i < n; ++i){
        res *= base;
    } 
    return res;
}
unsigned int fibonacci (unsigned int n){
    
}