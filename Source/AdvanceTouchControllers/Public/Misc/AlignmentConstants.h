// Copyright 2024 Tikhonov Gennadii, All Rights Reserved

#pragma once

const FVector2D AMC_MIDDLE = {0.5, 0.5};
const FVector2D AMC_TOPLEFT = {0, 0};
const FVector2D AMC_TOPRIGHT = {1.0, 0};
const FVector2D AMC_BOTTOMLEFT = {0, 1.0};
const FVector2D AMC_BOTTORIGHT = {1, 1};

// This array corresponds to the EControlAlignment
const FVector2D AMC_ALIGNMENTS_ARRAY[]
{
	AMC_MIDDLE,
	AMC_TOPLEFT,
	AMC_TOPRIGHT,
	AMC_BOTTOMLEFT,
	AMC_BOTTORIGHT
};


