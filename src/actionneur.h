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

#define reset_G   13 // pin du moteur gauche
#define sleep_G   15
#define step_G    0
#define dir_G     1

#define reset_D   9// pin du moteur droit
#define sleep_D   10
#define step_D    11
#define dir_D     12



#define acceleration_rd  300//accélération(en mm s-2) du robot x 2coefficiant_go
#define speed         100

#define acceleration_rg  300//accélération du robot x 2coefficiant_go
#define speed         100

#define coeficien_turn_rd 18.06168339//coefficiant determiné par rapport au diamètre de roue, sélection du pas(ici 1/4),le tout pour 1°
#define coeficien_go   7.520210565//coefficiant determiné par rapport au diamètre de roue, sélection du pas(ici 1/4),le tout pour 1mm

#define coeficien_turn_rg 17.81426307//coefficiant determiné par rapport au diamètre de roue, sélection du pas(ici 1/4),le tout pour 1°

#define coeficien_go_rg   1//coefficiant determiné par rapport au diamètre de roue, sélection du pas(ici 1/4),le tout pour 1mm
#define coeficien_go_rd   1


#define pi 3.1415926536
void IntrerrupTimer();
