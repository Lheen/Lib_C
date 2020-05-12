#include <stdio.h>
#include "struct.h"


t_obj obj[NB_OBJ] =
  {
    {01, "name_1"},
    {02, "name_2"},
    {03, "name_3"},
    {04, "name_4"},
    {05, "name_5"},
    {06, "name_6"}
  };


int	main()
{
  int	index_code;
  int	current_code;
  int	left = 0;
  int	right = NB_OBJ - 1;
  int	middle;
  int	find = FALSE;

  printf("Witch Code do you want ?");
  scanf("%d", &index_code);
  while (left <= right && !find)
    {
      middle = (left + right) /2;
      current_code = obj[middle].code;
      if(current_code == index_code)
	find = TRUE;
      else if (current_code < index_code)
	left = middle + 1;
      else (right = middle - 1);
    }
  if (find)
    printf("Code find : %s\n", obj[middle].name);
  else
    printf("Code : %d doesn't exist\n",index_code);
  return(0);
}
