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

#define reset_r   13 // pin du moteur gauche
#define sleep_r   15
#define step_r    0
#define dir_r     1

#define reset_t   9// pin du moteur droit
#define sleep_t   10
#define step_t    11
#define dir_t     12

#define my_adr    20

#define acceleration_rd  300//accélération(en mm s-2) du robot x 2coefficiant_go
#define speed         100

#define acceleration_rg  300//accélération du robot x 2coefficiant_go
#define speed         100

#define coeficien_turn_rd 18.06168339//coefficiant determiné par rapport au diamètre de roue, sélection du pas(ici 1/4),le tout pour 1°
#define coeficien_go   7.520210565//coefficiant determiné par rapport au diamètre de roue, sélection du pas(ici 1/4),le tout pour 1mm

#define coeficien_turn_rg 17.81426307//coefficiant determiné par rapport au diamètre de roue, sélection du pas(ici 1/4),le tout pour 1°

#define coeficien_go_rg   1//coefficiant determiné par rapport au diamètre de roue, sélection du pas(ici 1/4),le tout pour 1mm
#define coeficien_go_rd   1

#define pompe 22

#define stocage1 1
#define stocage2 2

#define pi 3.1415926536
void IntrerrupTimer();
void receiveEvent(int howMany);
void requestEvent();
