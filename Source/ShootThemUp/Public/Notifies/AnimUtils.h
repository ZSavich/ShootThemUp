#pragma once

class AnimUtils
{
public:
    template <typename T>
    static T* FindNotifyByMontage(const UAnimMontage* Montage)
    {
        if(!Montage) return nullptr;
    
        const auto NotifiesEvents = Montage->Notifies;
        for(auto Event : NotifiesEvents)
        {
            const auto Notify = Cast<T>(Event.Notify);
            if(Notify) return Notify;
        }
        return nullptr;
    }
};

