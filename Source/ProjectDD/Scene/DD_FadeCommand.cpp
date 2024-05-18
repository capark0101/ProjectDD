// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_FadeCommand.h"

void UDD_FadeCommand::SetCreateFrom(const ANSICHAR* File, const int32 Line)
{
	const FString FileName = FPaths::GetCleanFilename(ANSI_TO_TCHAR(File));
	const FString FileLine = FString::Format(TEXT("{0}({1})"), { FileName, Line} );
	CreateFileLine = FileLine;
}