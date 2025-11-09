#include <stdio.h>
#include <stdlib.h> /*pour utiliser la fonction de la veleur absolue: abs() */

typedef struct {
        int a_val,b_val,q_val,r_val;
        int x_val,y_val; /*Coefficients avant l'itération.Les coefficients stockés ici sont ceux utilisés au DÉBUT de l'étape*/
    } EtapeEuclide;
int main() { 
    int a,b,c,q,r,init_a,init_b,pgcd; /*Déclaration des variables*/
    int x,y,v,u,temp_x,temp_y;
    int i; /*compteur de la boucle*/

    printf("=============== Algorithme d'Euclide ===============\n\n");

    printf("Entrez les entiers a et b respectivement:\n"); /*Demande de saisie de a et b, on utilise \n pour retourner à la ligne*/
    scanf("%d%d",&a,&b);

    init_a=a; /*Stockage des valeurs initials de a et b*/
    init_b=b;
    
    x=1; y=0; /*Initialisation des coefficients de Bézout       (x et y) sont des coeffs pour a et (u et v) sont des coeffs pour b */
    u=0; v=1;

    printf("\na= %d et b= %d:\n",init_a,init_b); /*Etape optionnel juste pour la redaction et la clareté de reponse, on affiche les valeurs des variables saisies*/
 
    if (a< 0||b<0) { /*Vérification si a et b sont négatives ou non.    || désigne l'opérateur logique "ou"*/
        if (a<0)   {a = abs(a);}  /*si oui on attribue à cette variable sa valeur absolue*/
        if (b<0)   {b = abs(b);}   /*on fait la meme chose pour b*/
        printf("On sait que PGCD(a,b)=PGCD(|a|,|b|)\nDonc PGCD(%d,%d)=PGCD(%d,%d)\n",init_a,init_b,a,b);/*On affiche le message ecrit dans printf*/
    }

    if (b==0) { /*Vérification si b est nulle ou non*/
        printf("On sait que : PGCD(a,0)=|a|\n"); /*justification et affichage a la fin */
        u=1; /*tq a*u + 0*v = pgcd(a, 0) */
        v=0; 
    }

    EtapeEuclide historique[100];  
    i=0; /*Utilisation de la variable'i' comme compteur et indice de boucle*/
    while (b!=0 && i<100 ) {
        
        r=a%b; /*Le reste de la division entiere de a sur b*/
        q=a/b; /*Le quotient*/
        
        temp_x = x - u * q;  /*Calcule des NOUVEAUX coefficients (temp_x, temp_y) avec les anciens (x, y, u, v)*/
        temp_y = y - v * q;

        x = u; /*x prend les anciens u*/
        y = v; /*meme pour y*/

        u = temp_x; /*u prend le nouveau u*/
        v = temp_y; /*v prend le nouveau v*/
        
        /*Stockage de l'état AVANT la mise à jour (pour l'affichage)*/
        historique[i].a_val=a;
        historique[i].b_val=b;
        
        historique[i].r_val=r;
        historique[i].q_val=q;
        
        historique[i].x_val=x; /*Stocke l'ancien coefficient de 'a'*/
        historique[i].y_val=y; /*Stocke l'ancien coefficient de 'b'*/
        
        a=b; 
        b=r;
        
        i++;
    }

    printf("\nD'apres l'algorithme D'Euclide, on a:\n");

    int j; j=0;
    for (j=0;j<i;j++) { /*Affichage des etapes intermidiaire d'algorithme d'Euclide*/
        printf("%d = %d x %d + %d \n ", historique[j].a_val , historique[j].b_val , historique[j].q_val , historique[j].r_val );
    }

    pgcd=a;
    printf("\nPar consequent:     PGCD(%d,%d)=%d \n",init_a,init_b,pgcd);   /*À ce moment, le PGCD est la valeur actuelle de a.On l'affiche à l'utilisateur*/
    if (pgcd==1) { printf("Les deux nombres sont premiers entre eux\n\n");}
    
    printf("\n ===============Theoreme de Bezout===============\n\n");
    printf(" %d * x0 + %d * y0 = PGCD(%d,%d) \n\n",init_a,init_b,init_a,init_b); /*affichage des valeurs tel que a*x0+b*y0=pgcd(a,b)    */

    for (j=i-1 ;j>=0;j=j-1) { 
        if (historique[j].r_val == 0) {continue;} /*On saute cette iteration si r=0*/  
        printf(" %d = %d - %d x %d \n ",historique[j].r_val, historique[j].a_val , historique[j].b_val , historique[j].q_val); /*on affiche les etapes intermidiare en montant l'algorithme d'Euclide tq : r=a-b*q*/
    }
    printf("\non substitue les equation ligne par ligne jusqu'à retrouver les valeurs initiales de a et b\n Le resultat final est \n\n");
    printf("\t %d x (%d) + %d x (%d) = %d\n tel que x0=%d et y0=%d\n\n",init_a, x, init_b, y, init_a * x + init_b* y,x,y); /*affichage des coefficients de bezout, a,b,et pgcd apres verification des resultats*/

    printf("\n ----------------Equation a.x + b.y = c ----------------\n\n");
    printf("Entrez les entier c :\n"); /*Demande de saisie de c*/
    scanf("%d",&c);

    printf("%d . x + %d .y = %d \n",init_a,init_b,c); /*rappel de l'equation */

    if (c % pgcd !=0) { printf("il n'existe aucune solution entière can %d ne divise pas %d \n",pgcd,c);} /*verification si c est divisible par le pgcd(a,b) ou non, si non on affiche le message ecrit dans printf*/
    else{ /*si c est divisible par le pgcd(a,b)*/
        printf("il existe au moins une solution entiere car %d divise %d tel que (%d=%d x %d)\n\n",pgcd,c,c,pgcd,c/pgcd);
        printf("on a \t %d x (%d) + %d x (%d) = %d\n tel que x0=%d et y0=%d \n\n",init_a, x, init_b, y,pgcd,x,y); /*les coefficients de Bezout*/
        printf("La solution particuliere est :(xp, yp) = (x0 + c/d, y0 + c/d) \n Alors (xp, yp) = (%d + %d, %d + %d)=(%d,%d) \n\n",x,c/pgcd,y,c/pgcd,x+c/pgcd,y+c/pgcd);
        printf("la solution generale est : (x, y) = (xp + nk, yp + mk), k ∈ Z,\t\toù xp, yp, n, m ∈ Z sont des constantes fixees.\n\n Donc:\t(x, y) = (%d +(%d)k, %d + (%d)k)",x+c/pgcd,init_b/pgcd,y+c/pgcd,-init_a/pgcd);
    }
    
    

}