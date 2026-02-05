#pragma once
#include "CoreMinimal.h"
#include "Engine/Engine.h"

namespace MaLib
{
	inline void Print(const FString& Text, float Duration = 2.0f, FColor Color = FColor::Green)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Text);
		}
	}

	inline void Log(const FString& Text)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Text);
	}

	inline void PrintF(const FString& Format, float Value)
	{
		Print(FString::Printf(TEXT("%s: %.2f"), *Format, Value));
	}

	inline TSet<FName>& DoOnceStorage()
	{
		static TSet<FName> ExecutedKeys;
		return ExecutedKeys;
	}

	inline bool DoOnce(const FName& Key)
	{
		TSet<FName>& ExecutedKeys = DoOnceStorage();

		if (ExecutedKeys.Contains(Key))
		{
			return false;
		}

		ExecutedKeys.Add(Key);
		return true;
	}

	template <typename FuncType>
	inline void DoOnceExecute(const FName& Key, FuncType&& Func)
	{
		if (DoOnce(Key))
		{
			Forward<FuncType>(Func)();
		}
	}

	inline void ResetDoOnce(const FName& Key)
	{
		DoOnceStorage().Remove(Key);
	}

	inline void ResetAllDoOnce()
	{
		DoOnceStorage().Reset();
	}
}
