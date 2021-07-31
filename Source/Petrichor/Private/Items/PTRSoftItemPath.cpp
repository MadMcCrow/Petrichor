// Copyright © Noé Perard-Gayot 2021.

#include "Items/PTRSoftItemPath.h"
#include "Items/PTRItem.h"

UPTRItem* FPTRSoftItemPath::TryLoad() const
{
	return Cast<UPTRItem>(ItemPath.TryLoad());
}

TSoftObjectPtr<UPTRItem> FPTRSoftItemPath::ToSoftObject() const
{
	return TSoftObjectPtr<UPTRItem>(ItemPath);
}

FSoftObjectPath FPTRSoftItemPath::ToSoftPath() const
{
	return FSoftObjectPath(ItemPath);
}

UPTRItem* UPTRSoftItemPathLibrary::TryLoadSoftItemPath(const FPTRSoftItemPath& InPath) const
{
	return InPath.TryLoad();
}

FString UPTRSoftItemPathLibrary::SoftItemPathToString(const FPTRSoftItemPath& InPath) const
{
	return InPath.ToString();
}

TSoftObjectPtr<UPTRItem> UPTRSoftItemPathLibrary::SoftItemPathToSoftObject(const FPTRSoftItemPath& InPath) const
{
	return InPath.ToSoftObject();
}

FSoftObjectPath UPTRSoftItemPathLibrary::SoftItemPathToSoftPath(const FPTRSoftItemPath& InPath) const
{
	return InPath.ToSoftPath();
}

FPTRSoftItemPath UPTRSoftItemPathLibrary::SoftItemPathFromSoftObject(const TSoftObjectPtr<UPTRItem>& InPath) const
{
	return FPTRSoftItemPath(InPath);
}

FPTRSoftItemPath UPTRSoftItemPathLibrary::SoftItemPathFromSoftPath(const FSoftObjectPath& InPath) const
{
	return FPTRSoftItemPath(InPath);
}