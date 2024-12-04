#pragma once

#include "Settings.h"

namespace Utility
{
        namespace detail
        {
            inline RE::ActorValue GetActorValueIDFromName(const char* av_name)
            {
                // Courtesy of NoahBoddie
                // SE: 0x3E1450, AE: 0x3FC5A0, VR: ---
                using func_t = decltype(&GetActorValueIDFromName);
                REL::Relocation<func_t> func{ REL::RelocationID(26570, 27203) };
                return func(av_name);
            }

        } // namespace detail

        inline RE::ActorValue GetActorValueIDFromName_str(std::string_view av_name)
        {
            // Please make sure that you are using a null terminated string view. Wouldn't want it to be completely incorrect.
            return detail::GetActorValueIDFromName(av_name.data());
        }

        inline float GetInjuryMult(RE::ActorValueOwner* a_avowner) noexcept
        {
            if (a_avowner) {
                auto injuryAV  = GetActorValueIDFromName_str(Settings::InjuryMagAV);
                auto injuryMag = a_avowner->GetActorValue(injuryAV);
                return (1.0f - injuryMag);
            }
            return 1.0f;
        }

        inline int IsCallOrJump(uintptr_t addr)
        {
            // 0x15 0xE8//These are calls, represented by negative numbers
            // 0x25 0xE9//These are jumps, represented by positive numbers.
            // And zero represent it being neither.

            if (addr) {
                auto first_byte = reinterpret_cast<uint8_t*>(addr);

                switch (*first_byte) {
                case 0x15:
                case 0xE8: return -1;

                case 0x25:
                case 0xE9: return 1;
                }
            }

            return 0;
        }

} // namespace Utility

