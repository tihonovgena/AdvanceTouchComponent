// Copyright 2024 Tikhonov Gennadii, All Rights Reserved


#include "Misc/TimeHelper.h"

double UTimeHelper::GetTotalSecondsBetweenDate(const FDateTime& StartDate, const FDateTime& EndDate)
{
	const double StartDateTotalSeconds = GetTotalSecondsOfDate(StartDate);
	const double EndDateTotalSeconds = GetTotalSecondsOfDate(EndDate);
	return EndDateTotalSeconds - StartDateTotalSeconds;
}

double UTimeHelper::GetTotalSecondsOfDate(const FDateTime& DateTime)
{
	const FTimespan TimeSinceEpoch = DateTime - FDateTime::FromUnixTimestamp(0);
	return TimeSinceEpoch.GetTotalSeconds();
}
