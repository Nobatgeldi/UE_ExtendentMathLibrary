// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CV_Intern_Functions.generated.h"

/**
 * 
 */
UCLASS()
class CV_INTERN_API UCV_Intern_Functions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	// Existing function
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Centroid", Keywords = "Covisart"), Category = "Covisart|Functions")
	static FVector CalculateCentroid(UPARAM(ref)TArray<FVector>&Points);

	// ========== Interpolation Functions ==========
	
	/** Smoothly interpolate between two vectors using cubic Hermite interpolation (Smoothstep) */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Smoothstep Vector", Keywords = "interpolate smooth ease"), Category = "Extended Math|Interpolation")
	static FVector Smoothstep(const FVector& A, const FVector& B, float Alpha);

	/** Ease in interpolation (starts slow, accelerates) */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Ease In", Keywords = "interpolate smooth ease"), Category = "Extended Math|Interpolation")
	static float EaseIn(float Alpha, float Power = 2.0f);

	/** Ease out interpolation (starts fast, decelerates) */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Ease Out", Keywords = "interpolate smooth ease"), Category = "Extended Math|Interpolation")
	static float EaseOut(float Alpha, float Power = 2.0f);

	/** Ease in-out interpolation (starts slow, accelerates, then decelerates) */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Ease In Out", Keywords = "interpolate smooth ease"), Category = "Extended Math|Interpolation")
	static float EaseInOut(float Alpha, float Power = 2.0f);

	// ========== Distance and Direction Functions ==========
	
	/** Calculate 2D distance between two vectors (ignoring Z) */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Distance 2D", Keywords = "distance length magnitude"), Category = "Extended Math|Distance")
	static float Distance2D(const FVector& A, const FVector& B);

	/** Get normalized direction vector from A to B in 2D (ignoring Z) */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get Direction 2D", Keywords = "direction normal vector"), Category = "Extended Math|Direction")
	static FVector GetDirection2D(const FVector& From, const FVector& To);

	/** Get normalized direction vector from A to B in 3D */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get Direction 3D", Keywords = "direction normal vector"), Category = "Extended Math|Direction")
	static FVector GetDirection3D(const FVector& From, const FVector& To);

	// ========== Angle Functions ==========
	
	/** Calculate angle between two vectors in degrees */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Angle Between Vectors", Keywords = "angle degrees dot"), Category = "Extended Math|Angles")
	static float AngleBetweenVectors(const FVector& A, const FVector& B);

	/** Calculate signed angle between two 2D vectors in degrees (positive = counterclockwise) */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Signed Angle 2D", Keywords = "angle degrees signed"), Category = "Extended Math|Angles")
	static float SignedAngleBetweenVectors2D(const FVector& From, const FVector& To);

	// ========== Rotation Functions ==========
	
	/** Rotate a vector around an arbitrary axis by angle in degrees */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Rotate Vector Around Axis", Keywords = "rotate rotation axis"), Category = "Extended Math|Rotation")
	static FVector RotateVectorAroundAxis(const FVector& Vector, const FVector& Axis, float AngleDegrees);

	/** Rotate a 2D vector by angle in degrees */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Rotate Vector 2D", Keywords = "rotate rotation 2d"), Category = "Extended Math|Rotation")
	static FVector RotateVector2D(const FVector& Vector, float AngleDegrees);

	// ========== Clamping and Remapping Functions ==========
	
	/** Clamp each component of a vector between min and max */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Clamp Vector", Keywords = "clamp min max limit"), Category = "Extended Math|Clamping")
	static FVector ClampVector(const FVector& Vector, const FVector& Min, const FVector& Max);

	/** Remap a value from one range to another */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Remap Value", Keywords = "remap range scale"), Category = "Extended Math|Remapping")
	static float RemapValue(float Value, float InMin, float InMax, float OutMin, float OutMax);

	/** Remap a vector from one range to another (component-wise) */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Remap Vector Range", Keywords = "remap range scale vector"), Category = "Extended Math|Remapping")
	static FVector RemapVectorRange(const FVector& Vector, float InMin, float InMax, float OutMin, float OutMax);

	// ========== Random Utility Functions ==========
	
	/** Generate a random point within a circle (2D, Z=0) */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Random Point In Circle", Keywords = "random circle point"), Category = "Extended Math|Random")
	static FVector RandomPointInCircle(float Radius);

	/** Generate a random point within a sphere */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Random Point In Sphere", Keywords = "random sphere point"), Category = "Extended Math|Random")
	static FVector RandomPointInSphere(float Radius);

	/** Generate a random unit vector (direction) */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Random Unit Vector", Keywords = "random direction normal"), Category = "Extended Math|Random")
	static FVector RandomUnitVector();

	/** Generate a random unit vector in 2D (Z=0) */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Random Unit Vector 2D", Keywords = "random direction normal 2d"), Category = "Extended Math|Random")
	static FVector RandomUnitVector2D();

	// ========== Projection Functions ==========
	
	/** Project a point onto a line defined by two points */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Project Point On Line", Keywords = "project line point"), Category = "Extended Math|Projection")
	static FVector ProjectPointOnLine(const FVector& Point, const FVector& LineStart, const FVector& LineEnd);

	/** Project a vector onto a plane defined by a normal */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Project Vector On Plane", Keywords = "project plane vector"), Category = "Extended Math|Projection")
	static FVector ProjectVectorOnPlane(const FVector& Vector, const FVector& PlaneNormal);

	/** Get the closest point on a line segment to a given point */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Closest Point On Segment", Keywords = "closest point line segment"), Category = "Extended Math|Projection")
	static FVector ClosestPointOnSegment(const FVector& Point, const FVector& SegmentStart, const FVector& SegmentEnd);
};
