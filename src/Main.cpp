#include "Hooks.h"
#include "Logging.h"
#include "Settings.h"
#include "PenaltyManager.h"

void Listener(SKSE::MessagingInterface::Message* message) noexcept
{
    if (message->type == SKSE::MessagingInterface::kDataLoaded) {
        Settings::LoadSettings();
        Hooks::Install();
    }
}

bool RegisterFuncs(RE::BSScript::Internal::VirtualMachine* a_vm)
{
    if (!a_vm) {
        return false;
    }

    constexpr std::string_view scriptName = "AUG_FollowerInjuryScript"sv;
    a_vm->RegisterFunction("ApplyAttributePenalty", scriptName, PenaltyHandler::ApplyAttributePenalty);

    return true;
}

SKSEPluginLoad(const SKSE::LoadInterface* skse)
{
    InitLogging();

    const auto plugin{ SKSE::PluginDeclaration::GetSingleton() };
    const auto name{ plugin->GetName() };
    const auto version{ plugin->GetVersion() };

    logger::info("{} {} is loading...", name, version);

    Init(skse);

    // The following is only required if you use write_thunk_call or write_thunk jump. If you aren't using
    // those function, you can safely remove this line.
    //
    // To calculate the size of the trampoline, take the number of 5 byte write_call/write_branch, say p,
    // and the number of 6 byte write_call/write_branch, say q. Then, the size of the trampoline is given
    // by (p * 14) + (q * 8). E.g.: If you have two 5 byte write_calls and one 6 byte write_branch, the size
    // of the trampoline should be (2 * 14) + (1 * 8) = 34.
    SKSE::AllocTrampoline(14);

    if (const auto messaging{ SKSE::GetMessagingInterface() }; !messaging->RegisterListener(Listener)) {
        return false;
    }

    auto papyrus = SKSE::GetPapyrusInterface();
    if (papyrus) {
        if (papyrus->Register(RegisterFuncs)) {
            logger::info("Papyrus functions registered");     
        }
    }

    logger::info("{} has finished loading.", name);
    logger::info("");

    return true;
}
