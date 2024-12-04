#pragma once

class Settings : public Singleton<Settings>
{
public:
    static void LoadSettings() noexcept;

    inline static std::string FileName{};

    inline static bool debug_logging{};

    inline static std::string InjuryMagAV{};

    inline static RE::SpellItem* InjurySpell1;
    inline static RE::SpellItem* InjurySpell2;
    inline static RE::SpellItem* InjurySpell3;

    inline static RE::EffectSetting* FollowerInjuryEffect01;
    inline static RE::EffectSetting* FollowerInjuryEffect02;
    inline static RE::EffectSetting* FollowerInjuryEffect03;

    inline static RE::TESFaction* CurrentFollowerFaction;

    inline static RE::FormID ParseFormID(const std::string& str)
    {
        RE::FormID         result;
        std::istringstream ss{ str };
        ss >> std::hex >> result;
        return result;
    }

    template <typename T>
    inline static T* LoadFormPointerFromIni(std::string formId, std::string filename)
    {
        if (!formId.empty()) {
            auto objectFormId = ParseFormID(formId);
            auto form         = RE::TESDataHandler::GetSingleton()->LookupForm(objectFormId, filename)->As<T>();
            return form;
        }
        else {
            return nullptr;
        }
    }
};
