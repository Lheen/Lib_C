#include <stdio.h>
#define VRAI 1
#define FAUX 0
#define NMAX 100


void	stock(int t[], int nval, int aff)
{
  int	i,j,k,tempo;
  int	permut;

  i = -1;
  permut = VRAI;
  while(i < nval - 1 && permut)
    {
      permut = FAUX;
      for(j = nval - 2; j > i; j--)
	{
	  if (t[j] > t[j + 1])
	    {
	      permut = VRAI;
	      tempo = t[j];
	      t[j] = t[j +1];
	      t[j + 1] = tempo;
	      if (aff)
		{
		  for(k = 0; k < nval; k++)
		    printf("%5d", t[k]);
		  printf("\n");
		}
	    }
	}
    }

}



int	main()
{
  int	t[NMAX];
  int	nval;
  int	k;

  printf("Valeurs a trier : \n");
  scanf("%d", &nval);
  printf("Valeurs a trier :\n");
  for (k = 0; k < nval; k++)
    scanf("%d", &t[k]);
  printf("\n\n");

  stock(t, nval, 1);

  printf("Valeurs triees :\n");
 for (k = 0; k < nval; k++)
   printf("%5d", t[k]);
 printf("\n");
 return(0);
}
