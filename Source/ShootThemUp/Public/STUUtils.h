#pragma once

class STUUtils
{
public:
    template <typename T>
    static T* GetPlayerComponent(const AActor* PlayerPawn)
    {
        if(!PlayerPawn) return nullptr;

        const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
        const auto ResultComponent = Cast<T>(Component);
        if(!ResultComponent) return nullptr;
        return ResultComponent;
    }
};