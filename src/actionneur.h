#include <Arduino.h>
#include <Wire.h>         //liaison I2C pour les cartes
#include <FastCRC.h>      //gestion d'erreur sur bus I2C
#include <MsTimer2.h>
#include <AccelStepper.h> //un moteur pas a pas
        //AccelStepper motor_left(1, step_left, dir_left); definie la comme avec le diver
        //
#include <Servo.h>
#include <MultiStepper.h> //getion simultaner de moteur pas a pas limiter
#include <math.h>//pour les calculs

//#define Led 22

#define reset_t   13 // pin du moteur gauche
#define sleep_t   15
#define step_t    0
#define dir_t     1

#define reset_r   9// pin du moteur droit
#define sleep_r   10
#define step_r    11
#define dir_r     12

#define my_adr    20

#define AXEL_T_RECALAGE 1000
#define AXEL_T_FREINAGE_FIN_COURCE 200000

#define AXEL_R_RECALAGE 1000
#define AXEL_R_FREINAGE_FIN_COURCE 200000

#define acceleration_rd  10000//accélération(en mm s-2) du robot x 2coefficiant_go
#define speed         0.001

#define acceleration_rg  10000//accélération du robot x 2coefficiant_go
#define speed         0.001

#define coeficien_turn_rd 18.06168339//coefficiant determiné par rapport au diamètre de roue, sélection du pas(ici 1/4),le tout pour 1°
#define coeficien_go   7.520210565//coefficiant determiné par rapport au diamètre de roue, sélection du pas(ici 1/4),le tout pour 1mm

#define coeficien_turn_rg 17.81426307//coefficiant determiné par rapport au diamètre de roue, sélection du pas(ici 1/4),le tout pour 1°

#define coeficien_go_rg   1//coefficiant determiné par rapport au diamètre de roue, sélection du pas(ici 1/4),le tout pour 1mm
#define coeficien_go_rd   1

#define POMPE       5
#define ELECTROVANE 6

#define FIN_COURCE_TRANSLATION 4
#define FIN_COURCE_ROTATION    3

#define COEFICIEN_TRANSLATION -16.2037037

#define SORTI_VANTOUSE 145
#define VANTOUSE_PRETE_SORTI 109

#define COEFICIEN_ROTATION -4.4444


#define stocage1 206
#define stocage2 142
#define repo     65

#define pi 3.1415926536
void IntrerrupTimer();
void receiveEvent(int howMany);
void requestEvent();
void recalageTranslation();
void recalageRotation();
void actioneurAZero();
