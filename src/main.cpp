#include "actionneur.h"
//v0

//initialisation du moteur gauche

byte a=0,b=0,etat=0,com=1,fair,palaistoket=0,i,recepetion_tram[2],fai=1,etatp,pp;
int tdpalai[3]={95,73,48};
long time2=0,rot=stocage2;


AccelStepper motorT(1, step_t, dir_t);//declaration du moteur gauche
AccelStepper motorR(1, step_r, dir_r);//declatation du moteur droit

Servo servo_d;
Servo servo_g;



void setup() {
//  delay(8000);

  pinMode(POMPE, OUTPUT);//bas gauche
  digitalWrite(POMPE,LOW);//ne vert
  pinMode(ELECTROVANE, OUTPUT);//bas droit
  digitalWrite(ELECTROVANE,LOW);//en rouge

  pinMode(FIN_COURCE_ROTATION, INPUT_PULLUP);//haut gauche
  pinMode(FIN_COURCE_TRANSLATION, INPUT_PULLUP);//haut droit

  Wire.begin(my_adr);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  pinMode(reset_t, OUTPUT);
  digitalWrite(reset_t, HIGH);
  pinMode(sleep_t, OUTPUT);
  digitalWrite(sleep_t, HIGH);

  motorT.setSpeed(speed);
  motorT.setAcceleration(500);

  pinMode(reset_r, OUTPUT);
  digitalWrite(reset_r, HIGH);
  pinMode(sleep_r, OUTPUT);
  digitalWrite(sleep_r, HIGH);

  motorR.setMaxSpeed(1000);
  motorR.setAcceleration(10000);


  MsTimer2::set(10,IntrerrupTimer);//tout les  seconde
  MsTimer2::start();


/*  while (com!=1) {
    //Serial.println("x ");
  }
  com=0;*/
//-----------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------//
  //delay(10000);


  com=0;
  while (com!=1) {
    Serial.print("2 ");
    //Serial.println(com);
  }
  com=0;
  servo_d.attach(23);
  servo_g.attach(22);
  servo_d.write((int)(160+20)*0.888);//changer pour la mise a zero
  time2=0;
  while(time2!=200){
    Serial.println("a");
  }
  servo_g.write((int)11*0.777);
  recalageTranslation();
  recalageRotation();
  actioneurAZero();


//positif pour aller ver la zone de stocage



etat=1;


}

void loop() {
//Serial.println(com);
  //motorR.run();

  /*  if(b>10)MsTimer2::stop();
    if((int)(((float)b)/200)%2!=0){
      digitalWrite(Led,HIGH);
    }
    else digitalWrite(Led,LOW);*/

//if(digitalRead(3)==1)//Serial.printlnln("mlkfdqs");
////Serial.printlnln(etat);

  switch(etat){
    case 1:    //attante de trame
      if(com==1){
        etat=recepetion_tram[0];
        //Serial.printlnln(etat);
        time2=0;
        fai=0;
      }
    break;
    case 2://ouveture eguille
    //--------------------------------------------------------------------------------------------------//
      //angle d'eguille ouver
      servo_g.write((int)(11+recepetion_tram[1])*0.777);
      if(time2==100&&fai==0){
        servo_d.write((int)(160-recepetion_tram[1])*0.888);//changer pour la mise a zero
        time2=0;
        fai=1;
      }
      if(time2==100&&fai==1){
        etat=1;
        com=0;
      }

    //---------------------------------------------------------------------------------------------------//
    break;


    case 3://fermeture eguille
      servo_d.write(0);
      if(time2==1){
        servo_g.write(90*0.755555555);
        etat=1;
        com=0;
      }
    break;
    case 4://sortir + allumer la ponpe
      motorT.move((long)(COEFICIEN_TRANSLATION*(SORTI_VANTOUSE-VANTOUSE_PRETE_SORTI)));//sor pour chercher paller
      etatp=4;
      etat=13;

    break;
    case 5:
      time2=0;
      digitalWrite(POMPE, HIGH);//allume la POMPE
      etatp=5;
      etat=13;
    break;
    case 6://rentré jusque la buté
      motorT.move((long)(COEFICIEN_TRANSLATION*-SORTI_VANTOUSE));//rentre dans l'actioneur
      etatp=6;
      etat=13;
    break;
    case 7://rotation dans la zone de stocage
      if(palaistoket>=3)rot=stocage1;//stocage 2 par defaut
      motorR.move((long)((rot-repo)*COEFICIEN_ROTATION));//par dans la zonz stocage
      //palaistoket++;
      etatp=7;
      etat=13;
    break;
    case 8://avancement dans la zone stocage
      //time2=0;
      //Serial.printlnln("palai ");
      pp=palaistoket%3;
      //Serial.printlnln(pp);
      motorT.move(tdpalai[palaistoket%3]*COEFICIEN_TRANSLATION);//pour la distantce a la quelle le lactioneur doit stokait le pallais
      etatp=8;
      etat=13;
    break;
    case 9://coupe la ponpe la l'electrovane
      time2=0;
      digitalWrite(POMPE,LOW);
      digitalWrite(ELECTROVANE,HIGH);
      etatp=9;
      etat=13;
    break;
    case 10://rentré en buté
      digitalWrite(ELECTROVANE,LOW);
      motorT.move(-tdpalai[palaistoket%3]*COEFICIEN_TRANSLATION);
      etatp=10;
      etat=13;
    break;
    case 11://rotation sortie
      motorR.move(-(rot-repo)*COEFICIEN_ROTATION);
      etatp=11;
      etat=13;
    break;
    case 12://sortie
      motorT.move(COEFICIEN_TRANSLATION*VANTOUSE_PRETE_SORTI);
      etatp=12;
      etat=13;
      palaistoket++;
    break;
    case 13://différent etatpe d'attente
      if(motorR.isRunning()==false && motorT.isRunning()==false){
        if(etatp==5||etatp==9){
          if(time2>500){
            etat=etatp+1;
          }
        }
        else etat=etatp+1;
        if(etat==14){
          etat=1;
          com=0;
        }
      }
    break;
    case 14:
      if(recepetion_tram[1]==1)rot=stocage1;
      else rot=stocage2;
      motorT.move((long)(COEFICIEN_TRANSLATION*(-VANTOUSE_PRETE_SORTI)));
      etatp=14;
      etat=20;
    break;
    case 15:
      motorR.move((long)(COEFICIEN_ROTATION*(rot-repo)));
      etatp=15;
      etat=20;
    break;
    case 16:
      motorT.move((long)(COEFICIEN_TRANSLATION*VANTOUSE_PRETE_SORTI));
      etatp=16;
      etat=20;
    break;
    case 17:
      motorT.move((long)(COEFICIEN_TRANSLATION*(-VANTOUSE_PRETE_SORTI)));
      etatp=17;
      etat=20;
    break;
    case 18:
      motorR.move((long)(COEFICIEN_ROTATION*(-rot+repo)));
      etatp=18;
      etat=20;
    break;
    case 19:
      motorT.move((long)(COEFICIEN_TRANSLATION*VANTOUSE_PRETE_SORTI));
      etatp=19;
      etat=20;
    break;
    case 20:
      if(motorR.isRunning()==false && motorT.isRunning()==false){
        etat=etatp+1;
        if(etat==21){
          etat=1;
          com=0;
        }
      }
    break;
  }
  motorR.run();//lancemant du moteur droit
  motorT.run();//lancemant du moteur gauche
}
void receiveEvent(int howMany){//fonction d'intérupetion l'or dun envoi du maitre
  byte i;//variable pour le for
  for(i=0;i<howMany;i++)recepetion_tram[i]=Wire.read();//rampli le tableau si avec les valeur de la transmition
  com=1;// passe la comme a 1 pour l'éxecution de la trame en cour
  for(i=0;i<howMany;i++)Serial.println(recepetion_tram[i]);
}
void requestEvent(){//fonciton d'intérupetion l'or d une deamande de trame
  Wire.write(com);//le maitre lira la valeur de com
}
void recalageTranslation(){
  motorT.move(20000);//moin pour sortire
  while(digitalRead(FIN_COURCE_TRANSLATION)==1){
    motorT.run();
  }
  motorT.setAcceleration(AXEL_T_FREINAGE_FIN_COURCE);
  motorT.stop();
  motorT.setAcceleration(AXEL_T_RECALAGE);
  motorT.setCurrentPosition(0);
  motorT.move(-400);
  motorT.run();
  while(motorT.isRunning()){
    motorT.run();
  }
  motorT.move(40000);//moin pour sortire

  while(digitalRead(FIN_COURCE_TRANSLATION)==1){
    motorT.run();
  }
  motorT.setAcceleration(AXEL_T_FREINAGE_FIN_COURCE);
  motorT.stop();
  motorT.setAcceleration(AXEL_T_RECALAGE);
}
void recalageRotation(){
  motorR.setCurrentPosition(0);

  motorR.move(-5000);
  motorR.run();
  while(digitalRead(FIN_COURCE_ROTATION)){
    motorR.run();
  }
  motorR.setAcceleration(AXEL_R_FREINAGE_FIN_COURCE);
  motorR.stop();
  motorR.setAcceleration(AXEL_R_RECALAGE);
  motorR.setCurrentPosition(0);


}
void actioneurAZero(){
  motorR.move(575);
  motorR.run();
  while(motorR.isRunning()){
    motorR.run();
  }
  motorR.setCurrentPosition(0);
  motorT.setCurrentPosition(0);
  motorT.move((long)VANTOUSE_PRETE_SORTI*COEFICIEN_TRANSLATION);
  motorT.run();
  while(motorT.isRunning()){
    motorT.run();
  }
  motorT.setCurrentPosition(0);
}
void IntrerrupTimer (){
  time2++;
//  //Serial.println("time ");
//  //Serial.printlnln(time2);
}
