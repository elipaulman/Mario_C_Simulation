/* Elijah Paulman */
#include <stdbool.h>

typedef void (* ActionFunction)( void *data);
typedef bool (* ComparisonFunction)(void *data1, void *data2);
typedef bool (* CriteriaFunction)(void *data, void *helper);
typedef double (* NumericFunction)(void *data);

bool any(void *head, CriteriaFunction yes, void *helper);
int deleteSome(void **p2head, CriteriaFunction mustGo, void *helper, ActionFunction disposal, int text);
bool insert(void **p2head, void *data, ComparisonFunction goesInFrontOf, int text);
void iterate(void *head, ActionFunction doThis);
void sort(void **hptr, ComparisonFunction cf);
