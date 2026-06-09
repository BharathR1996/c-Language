int bharath()
{
#if 0
    /* This code can be enabled to see the difference between volatile and non-volatile variables */
    int a = 10; 
#endif
    volatile int a = 10;    // comment when above code is enabled
    a = a + 1;
    a = a + 20;

    return 0;
}