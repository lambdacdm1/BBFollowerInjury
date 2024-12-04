#include "Hooks.h"

#include "PenaltyManager.h"
#include "Settings.h"
#include "Utility.h"
#include "xbyak/xbyak.h"

namespace Hooks
{
    void Install() noexcept
    {
        GetAV::Patch();
        GetAVModifier::Patch();

        logger::info("Installed AV hooks");
        logger::info("");
    }

    float GetAV::Thunk(RE::ActorValueOwner* a_this, RE::ActorValue av) // GetActorValue write_vfunc
    {
        if (a_this) {
            if (av == RE::ActorValue::kHealth) {
                float injuryMult = Utility::GetInjuryMult(a_this);
                return (injuryMult / 100.0f) * func(a_this, av);
            }
        }

        return func(a_this, av);
    };

    void GetAV::Patch() { stl::write_vfunc<RE::Character, GetAV>(5); };

    float GetAVModifier::Thunk(RE::Character* a_this, RE::ACTOR_VALUE_MODIFIER a_modifier, RE::ActorValue av) // GetActorValueModifier write_branch
    {
        RE::ActorValueOwner* a_avowner = skyrim_cast<RE::ActorValueOwner*>(a_this);

        if (a_this) {
            if (av == RE::ActorValue::kHealth) {
                if ((a_modifier == RE::ACTOR_VALUE_MODIFIER::kTemporary) || (a_modifier == RE::ACTOR_VALUE_MODIFIER::kPermanent)) {
                    float injuryMult = Utility::GetInjuryMult(a_avowner);
                    return injuryMult * func(a_this, a_modifier, av);
                }
            }
        }

        return func(a_this, a_modifier, av);
    };

    void GetAVModifier::Patch()
    {
        const std::uintptr_t hook_addr{ RELOCATION_ID(0, 38469).address() };

        auto return_addr = hook_addr + 0x06;

        struct Code : Xbyak::CodeGenerator
        {
            Code(uintptr_t ret_addr)
            {
                // uintptr_t arg_8 = qword ptr 10h
                mov(ptr[rsp + 0x10], rbx);

                mov(rax, ret_addr);
                jmp(rax);
            }
        } static code{ return_addr };

        auto placed_call = Utility::IsCallOrJump(hook_addr) > 0;

        stl::write_thunk_jump<GetAVModifier>(hook_addr);

        if (!placed_call)
            GetAVModifier::func = (uintptr_t)code.getCode();
    }

} // namespace Hooks
