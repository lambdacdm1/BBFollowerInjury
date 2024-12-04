#pragma once

namespace Hooks
{
    void Install() noexcept;

    class GetAVModifier
    {
    public:
        static float Thunk(RE::Character* a_this, RE::ACTOR_VALUE_MODIFIER a_modifier, RE::ActorValue av);

        inline static REL::Relocation<decltype(Thunk)> func;

        static void Patch();
    };

    class GetAV
    {
    public:
        static float Thunk(RE::ActorValueOwner* a_this, RE::ActorValue av);

        static void Patch();

        inline static REL::Relocation<decltype(&Thunk)> func;

        static constexpr std::size_t idx{ 1 }; // GetActorValue 0x01
    };

} // namespace Hooks
