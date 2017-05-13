/*starter file for lab2*/

unsigned int factorial(unsigned int n){
    if(n <= 1) 
        return (unsigned)1;
    return n * factorial(n - 1);
}
double power (double base, unsigned int n){
    if(n == 0) 
        return 1.;
    double half = power(base, n/2);
    return (n & 1 ? base : 1.) * half * half;
}
unsigned int fibonacci (unsigned int n){
    if(n == 0)
        return 0;
    else if(n == 1)
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}