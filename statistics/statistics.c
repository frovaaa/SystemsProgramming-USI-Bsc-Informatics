#include <stdio.h>

int main()
{
    float scanResult;
    int n = 0;
    float min, max, average, currentSum;

    while (scanf("%f", &scanResult) == 1)
    {
        if (n == 0)
        {
            min = scanResult;
            max = scanResult;
            currentSum = scanResult;
        }
        else
        {
            currentSum += scanResult;
            if (scanResult < min)
                min = scanResult;
            if (scanResult > max)
                max = scanResult;
        }
        n++;
    }

    if (n > 0)
    {
        average = currentSum / n;
        printf("%f %f %f\n", min, average, max);
    }
}