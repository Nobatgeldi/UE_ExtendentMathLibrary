// Fill out your copyright notice in the Description page of Project Settings.


#include "CV_Intern_Functions.h"

FVector UCV_Intern_Functions::CalculateCentroid(UPARAM(ref)TArray<FVector>&Points)
{
	FVector centroid = FVector(0, 0, 0);
	int n = Points.Num();
    long double signedArea = 0.0;
    long double centroidX = 0.0, centroidY = 0.0;

    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        signedArea += (Points[i].X * Points[j].Y) - (Points[j].X * Points[i].Y);
        centroidX += (Points[i].X + Points[j].X) * (Points[i].X * Points[j].Y - Points[j].X * Points[i].Y);
        centroidY += (Points[i].Y + Points[j].Y) * (Points[i].X * Points[j].Y - Points[j].X * Points[i].Y);
    }

    signedArea *= 0.5;
    centroidX  /= (6.0 * signedArea);
    centroidY  /= (6.0 * signedArea);
	centroid.X  = centroidX;
	centroid.Y  = centroidY;
	centroid.Z  = 0;
	//UE_LOG(LogTemp, Warning, TEXT("The vector value is: %s"), *centroid.ToString());

	return centroid;
}