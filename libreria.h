#ifndef LIBRERIA_H
#define LIBRERIA_H
#include <stdio.h>
#include <omp.h>
//Obtener datos Matriz de confusión
float tn(int Ytrue[], int Yhat[]){
    float tn=0;
    for(int j=0; j<5; j++){
        if(Ytrue[j]==0 && Yhat[j]==0){
            tn++;
        }
    }
    return tn;
}
float fn(int Ytrue[], int Yhat[]){
    float FN=0;
    for(int j=0; j<5; j++){
        if(Ytrue[j]==1 && Yhat[j]==0){
            FN++;
        }
    }
    return FN;
}
float tp(int Ytrue[], int Yhat[]){
    float TP=0;
    for(int j=0; j<5; j++){
        if(Ytrue[j]==1 && Yhat[j]==1){
            TP++;
        }
    }
    return TP;
}
float fp(int Ytrue[], int Yhat[]){
    float FP=0;
    for(int j=0; j<5; j++){
        if(Ytrue[j]==0 && Yhat[j]==1){
            FP++;
        }
    }
    return FP;
}
//Obtener Tasa de detección y tasa de falsas alertas para la metrica CDR
double DetectionRate (int a,int b){
    double DR=0;
    DR=a/(a+b);
    return DR;
}
double FalseAlertRate (int a,int b){
    double FAR=0;
    FAR=a/(a+b);
    return FAR;
}
//Metricas
float BER(int Ytrue[], int Yhat[]){
    //Obtener b1 y b2
    float b1=0, b2=0;
    float TN=0, FN=0, TP=0, FP=0;
#pragma omp parallel
    {
#pragma omp single
        //Obtener TN
        TN = tn(Ytrue, Yhat);
#pragma omp single
        //Obtener FN
        FN = fn(Ytrue, Yhat);
#pragma omp single
        //Obtener TP
        TP = tp(Ytrue, Yhat);
#pragma omp single
        //Obtener FP
        FP = fp(Ytrue, Yhat);
    }


    b1 = FP/(TN+FP);
    b2 = FN/(FN+TP);

    return (0.5*(b1+b2));
}
float BCR(int Ytrue[], int Yhat[]){

    float TN=0, FN=0, TP=0, FP=0;
#pragma omp parallel
    {
#pragma omp single
        //Obtener TN
        TN = tn(Ytrue, Yhat);
#pragma omp single
        //Obtener FN
        FN = fn(Ytrue, Yhat);
#pragma omp single
        //Obtener TP
        TP = tp(Ytrue, Yhat);
#pragma omp single
        //Obtener FP
        FP = fp(Ytrue, Yhat);
    }

    //Obtener sensibiliadad y espicificidad
    float sensibilidad=0, especificidad=0;

    sensibilidad = TP/(TP+FN);
    especificidad = TN/(TN+FP);

    return ((sensibilidad+especificidad)/2);
}
double CorrectDetectionRate (int Ytrue[], int Yhat[]){
    float DR = DetectionRate(tp(Ytrue, Yhat),fn(Ytrue, Yhat));
    float FAR = FalseAlertRate(fp(Ytrue, Yhat),tn(Ytrue, Yhat));

    double CDR=0;
    CDR= DR-FAR;
    if (CDR>=0.5){
        printf("Umbral de la tasa de deteccion correcta positivo detectado\n\n");

    }
    else if(CDR<0.5){
        printf("Umbral de la tasa de deteccion correcta negativo detectado\n\n");
    }
    return CDR;

}

#endif // LIBRERIA_H
