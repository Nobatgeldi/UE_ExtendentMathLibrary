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

// ========== Interpolation Functions ==========

FVector UCV_Intern_Functions::Smoothstep(const FVector& A, const FVector& B, float Alpha)
{
	Alpha = FMath::Clamp(Alpha, 0.0f, 1.0f);
	float SmoothAlpha = Alpha * Alpha * (3.0f - 2.0f * Alpha);
	return FMath::Lerp(A, B, SmoothAlpha);
}

float UCV_Intern_Functions::EaseIn(float Alpha, float Power)
{
	Alpha = FMath::Clamp(Alpha, 0.0f, 1.0f);
	return FMath::Pow(Alpha, Power);
}

float UCV_Intern_Functions::EaseOut(float Alpha, float Power)
{
	Alpha = FMath::Clamp(Alpha, 0.0f, 1.0f);
	return 1.0f - FMath::Pow(1.0f - Alpha, Power);
}

float UCV_Intern_Functions::EaseInOut(float Alpha, float Power)
{
	Alpha = FMath::Clamp(Alpha, 0.0f, 1.0f);
	if (Alpha < 0.5f)
	{
		return FMath::Pow(2.0f * Alpha, Power) * 0.5f;
	}
	else
	{
		return 1.0f - FMath::Pow(2.0f * (1.0f - Alpha), Power) * 0.5f;
	}
}

// ========== Distance and Direction Functions ==========

float UCV_Intern_Functions::Distance2D(const FVector& A, const FVector& B)
{
	float DX = B.X - A.X;
	float DY = B.Y - A.Y;
	return FMath::Sqrt(DX * DX + DY * DY);
}

FVector UCV_Intern_Functions::GetDirection2D(const FVector& From, const FVector& To)
{
	FVector Direction = FVector(To.X - From.X, To.Y - From.Y, 0.0f);
	Direction.Normalize();
	return Direction;
}

FVector UCV_Intern_Functions::GetDirection3D(const FVector& From, const FVector& To)
{
	FVector Direction = To - From;
	Direction.Normalize();
	return Direction;
}

// ========== Angle Functions ==========

float UCV_Intern_Functions::AngleBetweenVectors(const FVector& A, const FVector& B)
{
	FVector NormalizedA = A.GetSafeNormal();
	FVector NormalizedB = B.GetSafeNormal();
	
	float DotProduct = FVector::DotProduct(NormalizedA, NormalizedB);
	DotProduct = FMath::Clamp(DotProduct, -1.0f, 1.0f);
	
	return FMath::Acos(DotProduct) * (180.0f / PI);
}

float UCV_Intern_Functions::SignedAngleBetweenVectors2D(const FVector& From, const FVector& To)
{
	FVector NormalizedFrom = FVector(From.X, From.Y, 0.0f).GetSafeNormal();
	FVector NormalizedTo = FVector(To.X, To.Y, 0.0f).GetSafeNormal();
	
	float DotProduct = FVector::DotProduct(NormalizedFrom, NormalizedTo);
	DotProduct = FMath::Clamp(DotProduct, -1.0f, 1.0f);
	
	float Angle = FMath::Acos(DotProduct) * (180.0f / PI);
	
	// Use cross product to determine sign
	float CrossZ = NormalizedFrom.X * NormalizedTo.Y - NormalizedFrom.Y * NormalizedTo.X;
	if (CrossZ < 0.0f)
	{
		Angle = -Angle;
	}
	
	return Angle;
}

// ========== Rotation Functions ==========

FVector UCV_Intern_Functions::RotateVectorAroundAxis(const FVector& Vector, const FVector& Axis, float AngleDegrees)
{
	FQuat Rotation = FQuat(Axis.GetSafeNormal(), FMath::DegreesToRadians(AngleDegrees));
	return Rotation.RotateVector(Vector);
}

FVector UCV_Intern_Functions::RotateVector2D(const FVector& Vector, float AngleDegrees)
{
	float AngleRadians = FMath::DegreesToRadians(AngleDegrees);
	float CosAngle = FMath::Cos(AngleRadians);
	float SinAngle = FMath::Sin(AngleRadians);
	
	float NewX = Vector.X * CosAngle - Vector.Y * SinAngle;
	float NewY = Vector.X * SinAngle + Vector.Y * CosAngle;
	
	return FVector(NewX, NewY, Vector.Z);
}

// ========== Clamping and Remapping Functions ==========

FVector UCV_Intern_Functions::ClampVector(const FVector& Vector, const FVector& Min, const FVector& Max)
{
	return FVector(
		FMath::Clamp(Vector.X, Min.X, Max.X),
		FMath::Clamp(Vector.Y, Min.Y, Max.Y),
		FMath::Clamp(Vector.Z, Min.Z, Max.Z)
	);
}

float UCV_Intern_Functions::RemapValue(float Value, float InMin, float InMax, float OutMin, float OutMax)
{
	if (FMath::IsNearlyEqual(InMax, InMin))
	{
		return OutMin;
	}
	
	float Normalized = (Value - InMin) / (InMax - InMin);
	return OutMin + Normalized * (OutMax - OutMin);
}

FVector UCV_Intern_Functions::RemapVectorRange(const FVector& Vector, float InMin, float InMax, float OutMin, float OutMax)
{
	return FVector(
		RemapValue(Vector.X, InMin, InMax, OutMin, OutMax),
		RemapValue(Vector.Y, InMin, InMax, OutMin, OutMax),
		RemapValue(Vector.Z, InMin, InMax, OutMin, OutMax)
	);
}

// ========== Random Utility Functions ==========

FVector UCV_Intern_Functions::RandomPointInCircle(float Radius)
{
	float Angle = FMath::FRandRange(0.0f, 2.0f * PI);
	float Distance = FMath::Sqrt(FMath::FRand()) * Radius;
	
	return FVector(
		Distance * FMath::Cos(Angle),
		Distance * FMath::Sin(Angle),
		0.0f
	);
}

FVector UCV_Intern_Functions::RandomPointInSphere(float Radius)
{
	// Use rejection sampling for uniform distribution
	FVector Point;
	do
	{
		Point = FVector(
			FMath::FRandRange(-1.0f, 1.0f),
			FMath::FRandRange(-1.0f, 1.0f),
			FMath::FRandRange(-1.0f, 1.0f)
		);
	} while (Point.SizeSquared() > 1.0f);
	
	return Point * Radius;
}

FVector UCV_Intern_Functions::RandomUnitVector()
{
	float Theta = FMath::FRandRange(0.0f, 2.0f * PI);
	float Phi = FMath::Acos(FMath::FRandRange(-1.0f, 1.0f));
	
	float SinPhi = FMath::Sin(Phi);
	
	return FVector(
		SinPhi * FMath::Cos(Theta),
		SinPhi * FMath::Sin(Theta),
		FMath::Cos(Phi)
	);
}

FVector UCV_Intern_Functions::RandomUnitVector2D()
{
	float Angle = FMath::FRandRange(0.0f, 2.0f * PI);
	return FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0.0f);
}

// ========== Projection Functions ==========

FVector UCV_Intern_Functions::ProjectPointOnLine(const FVector& Point, const FVector& LineStart, const FVector& LineEnd)
{
	FVector LineDirection = LineEnd - LineStart;
	float LineLength = LineDirection.Size();
	
	if (LineLength < KINDA_SMALL_NUMBER)
	{
		return LineStart;
	}
	
	LineDirection.Normalize();
	
	FVector PointVector = Point - LineStart;
	float ProjectionLength = FVector::DotProduct(PointVector, LineDirection);
	
	return LineStart + LineDirection * ProjectionLength;
}

FVector UCV_Intern_Functions::ProjectVectorOnPlane(const FVector& Vector, const FVector& PlaneNormal)
{
	FVector NormalizedPlaneNormal = PlaneNormal.GetSafeNormal();
	return Vector - NormalizedPlaneNormal * FVector::DotProduct(Vector, NormalizedPlaneNormal);
}

FVector UCV_Intern_Functions::ClosestPointOnSegment(const FVector& Point, const FVector& SegmentStart, const FVector& SegmentEnd)
{
	FVector SegmentVector = SegmentEnd - SegmentStart;
	float SegmentLengthSquared = SegmentVector.SizeSquared();
	
	if (SegmentLengthSquared < KINDA_SMALL_NUMBER)
	{
		return SegmentStart;
	}
	
	FVector PointVector = Point - SegmentStart;
	float T = FVector::DotProduct(PointVector, SegmentVector) / SegmentLengthSquared;
	T = FMath::Clamp(T, 0.0f, 1.0f);
	
	return SegmentStart + SegmentVector * T;
}