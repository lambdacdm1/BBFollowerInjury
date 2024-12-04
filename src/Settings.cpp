#include "Settings.h"

void Settings::LoadSettings() noexcept
{
    logger::info("Loading settings");

    CSimpleIniA ini;

    ini.SetUnicode();
    ini.LoadFile(R"(.\Data\SKSE\Plugins\BBFollowerInjury.ini)");

    debug_logging = ini.GetBoolValue("Log", "Debug");

    if (debug_logging) {
        spdlog::set_level(spdlog::level::debug);
        logger::debug("Debug logging enabled");
    }

    // Load settings

	std::string fileName(ini.GetValue("General", "sModFileName", ""));
    FileName = fileName;

    std::string injurySpell1FormID((ini.GetValue("FormIDs", "InjurySpell1FormID", "")));
    InjurySpell1 = LoadFormPointerFromIni<RE::SpellItem>(injurySpell1FormID, FileName);

    std::string injurySpell2FormID((ini.GetValue("FormIDs", "InjurySpell2FormID", "")));
    InjurySpell2 = LoadFormPointerFromIni<RE::SpellItem>(injurySpell2FormID, FileName);

    std::string injurySpell3FormID((ini.GetValue("FormIDs", "InjurySpell3FormID", "")));
    InjurySpell3 = LoadFormPointerFromIni<RE::SpellItem>(injurySpell3FormID, FileName);

    std::string FollowerInjuryEffect01FormID((ini.GetValue("FormIDs", "FollowerInjuryEffect01FormID", "")));
    FollowerInjuryEffect01 = LoadFormPointerFromIni<RE::EffectSetting>(FollowerInjuryEffect01FormID, FileName);

    std::string FollowerInjuryEffect02FormID((ini.GetValue("FormIDs", "FollowerInjuryEffect02FormID", "")));
    FollowerInjuryEffect02 = LoadFormPointerFromIni<RE::EffectSetting>(FollowerInjuryEffect02FormID, FileName);

    std::string FollowerInjuryEffect03FormID((ini.GetValue("FormIDs", "FollowerInjuryEffect03FormID", "")));
    FollowerInjuryEffect03 = LoadFormPointerFromIni<RE::EffectSetting>(FollowerInjuryEffect03FormID, FileName);

    std::string CurrentFollowerFactionFormID((ini.GetValue("FormIDs", "CurrentFollowerFactionFormID", "")));
    CurrentFollowerFaction = LoadFormPointerFromIni<RE::TESFaction>(CurrentFollowerFactionFormID, "Skyrim.esm");

    std::string injuryMagAV(ini.GetValue("General", "sInjuryMagAV", ""));
    InjuryMagAV = injuryMagAV;

    logger::info("Loaded settings");
    logger::info("");
}
