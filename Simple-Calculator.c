#include <stdlib.h>
#include <stdio.h>

void ShowCalculatorMenue()
{
  printf("\n==================================================\n");
  printf("\t\t   Calculator");
  printf("\n==================================================\n");
  printf("[1] Addition (+) \t [2] Subtraction (-)");
  printf("\n[3] Multiplying (*) \t [4] Divisition (/)");
  printf("\n[5] Power (^x) \t\t [6] Factorial (x!)");
  printf("\n[7] sin \t\t [8] cos");
  printf("\n[9] Exit");
  printf("\n==================================================\n");
}

double Power(double A, int Power)
{
  float result = 1;

  if (Power == 0)
    return 1;
  else
  {
    for (int i = 0; i < Power; i++)
      result *= A;

    return result;
  }
}

double Factorial(int A)
{
  unsigned long long int fact = 1;
  for (int i = 1; i <= A; i++)
    fact *= i;

  return fact;
}

double CalculateSin(double x, int N)
{
  double sinX = 0;
  short One;

  x = x * 3.14 / 180; // To convert from degree to radian

  for (int i = 0; i < N; i++)
  {
    if (i % 2 == 0)
      One = 1;
    else
      One = -1;

    sinX += One / (Factorial(2 * i + 1)) * (Power(x, 2 * i + 1));
  }
  return sinX;
}

double CalculateCos(double x, int N)
{
  double cosX = 0;
  short One;

  x = x * 3.14 / 180; // To convert from degree to radian

  for (int i = 0; i < N; i++)
  {
    if (i % 2 == 0)
      One = 1;
    else
      One = -1;

    cosX += One / (Factorial(2 * i)) * (Power(x, 2 * i));
  }
  return cosX;
}

int main()
{
  int Choice;
  do
  {
    ShowCalculatorMenue();
    printf("Please enter your choice: ");
    scanf("%d", &Choice);

    double num1, num2, result;
    int N;

    switch (Choice)
    {
    case 1:
      printf("Enter two numbers: ");
      scanf("%lf %lf", &num1, &num2);
      result = num1 + num2;
      printf("Result: %lf\n", result);
      break;
    case 2:
      printf("Enter two numbers: ");
      scanf("%lf %lf", &num1, &num2);
      result = num1 - num2;
      printf("Result: %lf\n", result);
      break;
    case 3:
      printf("Enter two numbers: ");
      scanf("%lf %lf", &num1, &num2);
      result = num1 * num2;
      printf("Result: %lf\n", result);
      break;
    case 4:
      printf("Enter two numbers: ");
      scanf("%lf %lf", &num1, &num2);
      if (num2 == 0)
      {
        printf("Error: Division by zero is not allowed\n");
      }
      else
      {
        result = num1 / num2;
        printf("Result: %lf\n", result);
      }
      break;
    case 5:
      printf("Enter base x and power: ");
      scanf("%lf %d", &num1, &N);
      result = Power(num1, N);
      printf("Result: %lf\n", result);
      break;
    case 6:
      printf("Enter a number: ");
      scanf("%lf", &num1);
      if (num1 <= 0)
      {
        printf("Error: Factorial of zero and negative numbers don't exist\n");
      }
      else
      {
        result = Factorial(num1);
        printf("Result: %lf\n", result);
      }
      break;
    case 7:
      printf("Enter x (in degrees) and N for sin(x): ");
      scanf("%lf %d", &num1, &N);
      result = CalculateSin(num1, N);
      printf("Result: %lf\n", result);
      break;
    case 8:
      printf("Enter x (in degrees) and N for cos(x): ");
      scanf("%lf %d", &num1, &N);
      result = CalculateCos(num1, N);
      printf("Result: %lf\n", result);
      break;
    case 9:
      printf("Exiting the program.\n");
      break;
    default:
      printf("Invalid choice. Please select a valid option.\n");
    }
  } while (Choice != 9);

  return 0;
}
