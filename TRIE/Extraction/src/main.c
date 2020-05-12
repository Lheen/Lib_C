#include <stdio.h>
#define NMAX 100

int	main()
{
  int	t[NMAX];
  int	nval = 0;
  int	kmax = 0;
  int	tempo = 0;
  int	i, j, k;

  printf("nb valeur a trier : ");
  scanf("%d",&nval);

  if (nval > NMAX)
    nval = NMAX;
  printf("Valeurs a trier : \n");
  for (k = 0; k < nval; k++)
    scanf("%d", &t[k]);
  printf("Valeurs a trier :\n");
  for (k = 0; k < nval; k++)
    printf("%5d", t[k]);
  printf("\n\n");
/*TRIE */
  for (i = 0; i < nval; i++)
    {
      kmax = i;
      for(j = i + 1; j < nval; j++)
	if (t[j] > t[kmax])
	  kmax = j;
      tempo = t[kmax];
      t[kmax] = t[i];
      t[i] = tempo;
      for (k = 0; k < nval; k++)
	printf("%5d", t[k]);
      printf("\n");
    }
/*AFFICHAGE */
  printf("Valeurs triees :\n");
  for (k = 0; k < nval; k++)
    printf("%5d", t[k]);
  printf("\n");
  return(0);
}
