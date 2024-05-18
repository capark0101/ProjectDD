// Fill out your copyright notice in the Description page of Project Settings.


#include "DD_TableDefine.h"

#include "DD_TableMapper.h"
#include "Utils/DD_Define.h"

void FDD_TableMapperData::Finalize()
{
	TablePath = nullptr;
	TableData = nullptr;
	
	if(IsValid(TableMapper))
	{
		TableMapper->Finalize();
		DD_DeleteObject(TableMapper);
	}
}
