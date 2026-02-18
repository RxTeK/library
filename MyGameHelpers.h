#pragma once
#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "TimerManager.h"

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

	inline bool SetTimerByEvent(UObject* WorldContextObject, FTimerHandle& TimerHandle, TFunction<void()> Event, float Time, bool bLoop = false, float FirstDelay = -1.0f)
	{
		if (!WorldContextObject || !Event)
		{
			return false;
		}

		UWorld* World = WorldContextObject->GetWorld();
		if (!World)
		{
			return false;
		}

		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda([Event = MoveTemp(Event)]() mutable
		{
			Event();
		});

		World->GetTimerManager().SetTimer(TimerHandle, MoveTemp(TimerDelegate), Time, bLoop, FirstDelay);
		return true;
	}

	inline FTimerHandle SetTimerByEvent(UObject* WorldContextObject, TFunction<void()> Event, float Time, bool bLoop = false, float FirstDelay = -1.0f)
	{
		FTimerHandle TimerHandle;
		SetTimerByEvent(WorldContextObject, TimerHandle, MoveTemp(Event), Time, bLoop, FirstDelay);
		return TimerHandle;
	}

	inline bool Delay(UObject* WorldContextObject, FTimerHandle& TimerHandle, TFunction<void()> Event, float Duration)
	{
		if (!WorldContextObject || !Event)
		{
			return false;
		}

		UWorld* World = WorldContextObject->GetWorld();
		if (!World)
		{
			return false;
		}

		const float SafeDuration = FMath::Max(0.0f, Duration);
		if (SafeDuration <= 0.0f)
		{
			FTimerDelegate TimerDelegate;
			TimerDelegate.BindLambda([Event = MoveTemp(Event)]() mutable
			{
				Event();
			});

			World->GetTimerManager().SetTimerForNextTick(MoveTemp(TimerDelegate));
			return true;
		}

		return SetTimerByEvent(WorldContextObject, TimerHandle, MoveTemp(Event), SafeDuration, false);
	}

	inline FTimerHandle Delay(UObject* WorldContextObject, TFunction<void()> Event, float Duration)
	{
		FTimerHandle TimerHandle;
		Delay(WorldContextObject, TimerHandle, MoveTemp(Event), Duration);
		return TimerHandle;
	}
}
