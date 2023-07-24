#include "../s21_math.h"

#define MAX_WIDTH_D 20
#define MIN_WIDTH_D -10
#define MAX_INT_D 2147483647
#define MIN_INT_D -2147483648
#define MIN_F -100.100
#define MIN_F_L (long double)-100.100
#define MAX_F_L (long double)100.100
#define MAX_F 100.100
#define MAX_ACC_F 200
#define MIN_ACC_F 20  //
/*ß
#define FLOAT \
   50.12345678901234567890123456789012345678901234567890123456789012345678901234567890test=%9.0Lf=%9.0Lf=testtest=50.12=50.12=testtest=%2.8f=%2.8f=test
*/
#define FLOAT 50.1234567890
#define SIZE_STR 1000000
int main(void) {
  char *test[10] = {"test=% 10c=% 10c=test", "d %+16ld s %+d 32",
                    "23sd d %-20ld 33sd d", "24sd d %+-20ld s %+d 33",
                    "d %0+20ld s %0+20ld 35sd d"};
  int test_double = 'D';  // Int
  // int v = 13;  // Width.
  char *string = (char *)calloc(10000000, sizeof(char));
  char *string2 = (char *)calloc(10000000, sizeof(char));
  for (int i = 0; i < 1; i++) {
    LOG_INFO("");
    printf("Строка + спецификаторы:%s, переменные:%30.20u\n", test[i],
           test_double);
    sprintf(string, test[i], test_double, test_double);
    LOG_INFO("sprintf orig str :%s, len %ld", string, STR_LEN(string));
    s21_sprintf(string2, test[i], test_double, test_double);
    LOG_INFO("sprintf s21  str :%s, len %ld", string2, STR_LEN(string2));
    for (int j = 0; j < 1024; j++) {
      string2[j] = 0;
    }
  }
  free(string);
  free(string2);
  return 0;
}
