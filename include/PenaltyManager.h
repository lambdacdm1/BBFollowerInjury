#pragma once
#include <Settings.h>
#include "Hooks.h"
#include "Utility.h"

class PenaltyHandler : public Singleton<Settings>
{
public:
    inline static void ApplyAttributePenalty(RE::StaticFunctionTag*, RE::Actor* a_actor, float injuryMag)
    {
        if (!a_actor) {
            return;
        }

        if (auto a_avowner = a_actor->AsActorValueOwner()) {
            auto target_av = Utility::GetActorValueIDFromName_str(Settings::InjuryMagAV);
            a_avowner->SetActorValue(target_av, injuryMag);
        }
    }
};
