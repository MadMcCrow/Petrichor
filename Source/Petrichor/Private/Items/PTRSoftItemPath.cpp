// Copyright © Noé Perard-Gayot 2021. Licenced under LGPL-3.0-or-later
// You should have received a copy of the GNU Lesser General Public License
// along with Petrichor. If not, see <https://www.gnu.org/licenses/>.

#include "Items/PTRSoftItemPath.h"
#include "Engine/AssetManager.h"
#include "Engine/AssetManagerTypes.h"
#include "Items/PTRItem.h"

FPTRSoftItemPath::FPTRSoftItemPath(const FPrimaryAssetId& AssetID)
{
	if (UAssetManager* Manager = UAssetManager::GetIfValid())
	{
		ItemPath = Manager->GetPrimaryAssetPath(AssetID);
	}
}

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

TSubclassOf<UPTRItem> FPTRSoftItemPath::GetClass() const
{
	if (const UAssetManager* Manager = UAssetManager::GetIfValid())
	{
		FAssetData AssetData;
		Manager->GetAssetDataForPath(ItemPath, AssetData);
		return AssetData.GetClass();
	}
	return TSubclassOf<UPTRItem>();
}

UPTRItem* UPTRSoftItemPathLibrary::TryLoadSoftItemPath(const FPTRSoftItemPath& InPath)
{
	return InPath.TryLoad();
}

FString UPTRSoftItemPathLibrary::SoftItemPathToString(const FPTRSoftItemPath& InPath)
{
	return InPath.ToString();
}

TSoftObjectPtr<UPTRItem> UPTRSoftItemPathLibrary::SoftItemPathToSoftObject(const FPTRSoftItemPath& InPath)
{
	return InPath.ToSoftObject();
}

FSoftObjectPath UPTRSoftItemPathLibrary::SoftItemPathToSoftPath(const FPTRSoftItemPath& InPath)
{
	return InPath.ToSoftPath();
}

FPTRSoftItemPath UPTRSoftItemPathLibrary::SoftItemPathFromSoftObject(const TSoftObjectPtr<UPTRItem>& InPath)
{
	return FPTRSoftItemPath(InPath);
}

FPTRSoftItemPath UPTRSoftItemPathLibrary::SoftItemPathFromSoftPath(const FSoftObjectPath& InPath)
{
	return FPTRSoftItemPath(InPath);
}

FPrimaryAssetId UPTRSoftItemPathLibrary::SoftItemPathToAssetID(const FPTRSoftItemPath& InPath)
{
	if (UAssetManager* Manager = UAssetManager::GetIfValid())
	{
		return Manager->GetPrimaryAssetIdForPath(InPath.ToSoftPath());
	}
	return FPrimaryAssetId();
}

FPTRSoftItemPath UPTRSoftItemPathLibrary::SoftItemPathFromAssetID(const FPrimaryAssetId& InID)
{
	if (UAssetManager* Manager = UAssetManager::GetIfValid())
	{
		return FPTRSoftItemPath(Manager->GetPrimaryAssetPath(InID));
	}
	return FPTRSoftItemPath();
}
