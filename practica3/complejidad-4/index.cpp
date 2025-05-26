// int sum = 0;// 1
// for (int i = 0; i < n; i++) // 1 + (n-1) + 1
// {
//   for (int j = 0; j < i; i++) // n + n(n-1) + n*n
//   {
//     sum = sum + 1; //n*n
//   }
// }

int factorial(int n)
{
  if (n == 0)
    return 1;
  else
    return n * factorial(n - 1);
}