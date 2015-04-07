/*
*
*		Fichier : ServoMoteur.c
*
*		Contient le comportement simulé du servomoteur
*
*		Dernière modification : mardi 7 avril 2015
*
*	==============================================================
*
*	-----------------------FONCTIONS A UTILISER-------------------


static int     pwm_open(FAR struct file *filep);

static ssize_t pwm_write(FAR struct file *filep, FAR const char *buffer, size_t buflen);

static int     pwm_start(FAR struct pwm_upperhalf_s *upper, unsigned int oflags);

static int     pwm_ioctl(FAR struct file *filep, int cmd, unsigned long arg);

NB: Voir pwm.c dans le même dossier

*/

#include "ServoMoteur.h"
int (*my_pwm)();



void initializeServomoteur( int (*ServoMoteur)(int positionAngulaire)){
    my_pwm  = ServoMoteur;
}

int StrPostoInt(char posText[]){
    if(strcmp(posText,"close") == 0) return 0;
    else if (strcmp(posText,"full") == 0) return 180;
    else if (strcmp(posText,"half") == 0) return 90;
    else if (strcmp(posText,"quarter") == 0) return 45;
    else if (strcmp(posText,"three quarts") == 0) return 135;
    else return -1;
}

int mouvementStr(char val[]){
    int valint = StrPostoInt(val);
    if (valint != -1) return my_pwm(valint);
    else return valint;
}


int mouvement(int val){
    return  my_pwm(val);
    
}

/*
static int my_pwm_open ()
{
   int ret =  pwm_open();
   return ret;
}
*/
