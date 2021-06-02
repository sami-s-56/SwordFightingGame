// Fill out your copyright notice in the Description page of Project Settings.


#include "TheObject.h"

UTheObject::UTheObject() 
{
	MyFloat = 0.0f;
}

void UTheObject::MyFunction()
{
	UE_LOG(LogTemp, Display, TEXT("This is My Function of TheObject Class"));
}
